<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Copyright IBM Corp. 2015
 *    Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#समावेश <linux/kernel.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/lowcore.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/mem_detect.h>
#समावेश <यंत्र/facility.h>
#समावेश "sclp.h"
#समावेश "sclp_rw.h"

अटल काष्ठा पढ़ो_info_sccb __bootdata(sclp_info_sccb);
अटल पूर्णांक __bootdata(sclp_info_sccb_valid);
अक्षर *sclp_early_sccb = (अक्षर *) EARLY_SCCB_OFFSET;
पूर्णांक sclp_init_state = sclp_init_state_uninitialized;
/*
 * Used to keep track of the size of the event masks. Qemu until version 2.11
 * only supports 4 and needs a workaround.
 */
bool sclp_mask_compat_mode;

व्योम sclp_early_रुको_irq(व्योम)
अणु
	अचिन्हित दीर्घ psw_mask, addr;
	psw_t psw_ext_save, psw_रुको;
	जोड़ ctlreg0 cr0, cr0_new;

	__ctl_store(cr0.val, 0, 0);
	cr0_new.val = cr0.val & ~CR0_IRQ_SUBCLASS_MASK;
	cr0_new.lap = 0;
	cr0_new.sssm = 1;
	__ctl_load(cr0_new.val, 0, 0);

	psw_ext_save = S390_lowcore.बाह्यal_new_psw;
	psw_mask = __extract_psw();
	S390_lowcore.बाह्यal_new_psw.mask = psw_mask;
	psw_रुको.mask = psw_mask | PSW_MASK_EXT | PSW_MASK_WAIT;
	S390_lowcore.ext_पूर्णांक_code = 0;

	करो अणु
		यंत्र अस्थिर(
			"	larl	%[addr],0f\n"
			"	stg	%[addr],%[psw_wait_addr]\n"
			"	stg	%[addr],%[psw_ext_addr]\n"
			"	lpswe	%[psw_wait]\n"
			"0:\n"
			: [addr] "=&d" (addr),
			  [psw_रुको_addr] "=Q" (psw_रुको.addr),
			  [psw_ext_addr] "=Q" (S390_lowcore.बाह्यal_new_psw.addr)
			: [psw_रुको] "Q" (psw_रुको)
			: "cc", "memory");
	पूर्ण जबतक (S390_lowcore.ext_पूर्णांक_code != EXT_IRQ_SERVICE_SIG);

	S390_lowcore.बाह्यal_new_psw = psw_ext_save;
	__ctl_load(cr0.val, 0, 0);
पूर्ण

पूर्णांक sclp_early_cmd(sclp_cmdw_t cmd, व्योम *sccb)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	flags = arch_local_irq_save();
	rc = sclp_service_call(cmd, sccb);
	अगर (rc)
		जाओ out;
	sclp_early_रुको_irq();
out:
	arch_local_irq_restore(flags);
	वापस rc;
पूर्ण

काष्ठा ग_लिखो_sccb अणु
	काष्ठा sccb_header header;
	काष्ठा msg_buf msg;
पूर्ण __packed;

/* Output multi-line text using SCLP Message पूर्णांकerface. */
अटल व्योम sclp_early_prपूर्णांक_lm(स्थिर अक्षर *str, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित अक्षर *ptr, *end, ch;
	अचिन्हित पूर्णांक count, offset;
	काष्ठा ग_लिखो_sccb *sccb;
	काष्ठा msg_buf *msg;
	काष्ठा mdb *mdb;
	काष्ठा mto *mto;
	काष्ठा go *go;

	sccb = (काष्ठा ग_लिखो_sccb *) sclp_early_sccb;
	end = (अचिन्हित अक्षर *) sccb + EARLY_SCCB_SIZE - 1;
	स_रखो(sccb, 0, माप(*sccb));
	ptr = (अचिन्हित अक्षर *) &sccb->msg.mdb.mto;
	offset = 0;
	करो अणु
		क्रम (count = माप(*mto); offset < len; count++) अणु
			ch = str[offset++];
			अगर ((ch == 0x0a) || (ptr + count > end))
				अवरोध;
			ptr[count] = _ascebc[ch];
		पूर्ण
		mto = (काष्ठा mto *) ptr;
		स_रखो(mto, 0, माप(*mto));
		mto->length = count;
		mto->type = 4;
		mto->line_type_flags = LNTPFLGS_ENDTEXT;
		ptr += count;
	पूर्ण जबतक ((offset < len) && (ptr + माप(*mto) <= end));
	len = ptr - (अचिन्हित अक्षर *) sccb;
	sccb->header.length = len - दुरत्व(काष्ठा ग_लिखो_sccb, header);
	msg = &sccb->msg;
	msg->header.type = EVTYP_MSG;
	msg->header.length = len - दुरत्व(काष्ठा ग_लिखो_sccb, msg.header);
	mdb = &msg->mdb;
	mdb->header.type = 1;
	mdb->header.tag = 0xD4C4C240;
	mdb->header.revision_code = 1;
	mdb->header.length = len - दुरत्व(काष्ठा ग_लिखो_sccb, msg.mdb.header);
	go = &mdb->go;
	go->length = माप(*go);
	go->type = 1;
	sclp_early_cmd(SCLP_CMDW_WRITE_EVENT_DATA, sccb);
पूर्ण

काष्ठा vt220_sccb अणु
	काष्ठा sccb_header header;
	काष्ठा अणु
		काष्ठा evbuf_header header;
		अक्षर data[];
	पूर्ण msg;
पूर्ण __packed;

/* Output multi-line text using SCLP VT220 पूर्णांकerface. */
अटल व्योम sclp_early_prपूर्णांक_vt220(स्थिर अक्षर *str, अचिन्हित पूर्णांक len)
अणु
	काष्ठा vt220_sccb *sccb;

	sccb = (काष्ठा vt220_sccb *) sclp_early_sccb;
	अगर (माप(*sccb) + len >= EARLY_SCCB_SIZE)
		len = EARLY_SCCB_SIZE - माप(*sccb);
	स_रखो(sccb, 0, माप(*sccb));
	स_नकल(&sccb->msg.data, str, len);
	sccb->header.length = माप(*sccb) + len;
	sccb->msg.header.length = माप(sccb->msg) + len;
	sccb->msg.header.type = EVTYP_VT220MSG;
	sclp_early_cmd(SCLP_CMDW_WRITE_EVENT_DATA, sccb);
पूर्ण

पूर्णांक sclp_early_set_event_mask(काष्ठा init_sccb *sccb,
			      sccb_mask_t receive_mask,
			      sccb_mask_t send_mask)
अणु
retry:
	स_रखो(sccb, 0, माप(*sccb));
	sccb->header.length = माप(*sccb);
	अगर (sclp_mask_compat_mode)
		sccb->mask_length = SCLP_MASK_SIZE_COMPAT;
	अन्यथा
		sccb->mask_length = माप(sccb_mask_t);
	sccb_set_recv_mask(sccb, receive_mask);
	sccb_set_send_mask(sccb, send_mask);
	अगर (sclp_early_cmd(SCLP_CMDW_WRITE_EVENT_MASK, sccb))
		वापस -EIO;
	अगर ((sccb->header.response_code == 0x74f0) && !sclp_mask_compat_mode) अणु
		sclp_mask_compat_mode = true;
		जाओ retry;
	पूर्ण
	अगर (sccb->header.response_code != 0x20)
		वापस -EIO;
	वापस 0;
पूर्ण

अचिन्हित पूर्णांक sclp_early_con_check_linemode(काष्ठा init_sccb *sccb)
अणु
	अगर (!(sccb_get_sclp_send_mask(sccb) & EVTYP_OPCMD_MASK))
		वापस 0;
	अगर (!(sccb_get_sclp_recv_mask(sccb) & (EVTYP_MSG_MASK | EVTYP_PMSGCMD_MASK)))
		वापस 0;
	वापस 1;
पूर्ण

अचिन्हित पूर्णांक sclp_early_con_check_vt220(काष्ठा init_sccb *sccb)
अणु
	अगर (sccb_get_sclp_send_mask(sccb) & EVTYP_VT220MSG_MASK)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक sclp_early_setup(पूर्णांक disable, पूर्णांक *have_linemode, पूर्णांक *have_vt220)
अणु
	अचिन्हित दीर्घ receive_mask, send_mask;
	काष्ठा init_sccb *sccb;
	पूर्णांक rc;

	BUILD_BUG_ON(माप(काष्ठा init_sccb) > PAGE_SIZE);

	*have_linemode = *have_vt220 = 0;
	sccb = (काष्ठा init_sccb *) sclp_early_sccb;
	receive_mask = disable ? 0 : EVTYP_OPCMD_MASK;
	send_mask = disable ? 0 : EVTYP_VT220MSG_MASK | EVTYP_MSG_MASK;
	rc = sclp_early_set_event_mask(sccb, receive_mask, send_mask);
	अगर (rc)
		वापस rc;
	*have_linemode = sclp_early_con_check_linemode(sccb);
	*have_vt220 = !!(sccb_get_send_mask(sccb) & EVTYP_VT220MSG_MASK);
	वापस rc;
पूर्ण

/*
 * Output one or more lines of text on the SCLP console (VT220 and /
 * or line-mode).
 */
व्योम __sclp_early_prपूर्णांकk(स्थिर अक्षर *str, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक have_linemode, have_vt220;

	अगर (sclp_init_state != sclp_init_state_uninitialized)
		वापस;
	अगर (sclp_early_setup(0, &have_linemode, &have_vt220) != 0)
		वापस;
	अगर (have_linemode)
		sclp_early_prपूर्णांक_lm(str, len);
	अगर (have_vt220)
		sclp_early_prपूर्णांक_vt220(str, len);
	sclp_early_setup(1, &have_linemode, &have_vt220);
पूर्ण

व्योम sclp_early_prपूर्णांकk(स्थिर अक्षर *str)
अणु
	__sclp_early_prपूर्णांकk(str, म_माप(str));
पूर्ण

पूर्णांक __init sclp_early_पढ़ो_info(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक length = test_facility(140) ? EXT_SCCB_READ_SCP : PAGE_SIZE;
	काष्ठा पढ़ो_info_sccb *sccb = &sclp_info_sccb;
	sclp_cmdw_t commands[] = अणुSCLP_CMDW_READ_SCP_INFO_FORCED,
				  SCLP_CMDW_READ_SCP_INFOपूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(commands); i++) अणु
		स_रखो(sccb, 0, length);
		sccb->header.length = length;
		sccb->header.function_code = 0x80;
		sccb->header.control_mask[2] = 0x80;
		अगर (sclp_early_cmd(commands[i], sccb))
			अवरोध;
		अगर (sccb->header.response_code == 0x10) अणु
			sclp_info_sccb_valid = 1;
			वापस 0;
		पूर्ण
		अगर (sccb->header.response_code != 0x1f0)
			अवरोध;
	पूर्ण
	वापस -EIO;
पूर्ण

काष्ठा पढ़ो_info_sccb * __init sclp_early_get_info(व्योम)
अणु
	अगर (!sclp_info_sccb_valid)
		वापस शून्य;

	वापस &sclp_info_sccb;
पूर्ण

पूर्णांक __init sclp_early_get_memsize(अचिन्हित दीर्घ *mem)
अणु
	अचिन्हित दीर्घ rnmax;
	अचिन्हित दीर्घ rnsize;
	काष्ठा पढ़ो_info_sccb *sccb = &sclp_info_sccb;

	अगर (!sclp_info_sccb_valid)
		वापस -EIO;

	rnmax = sccb->rnmax ? sccb->rnmax : sccb->rnmax2;
	rnsize = sccb->rnsize ? sccb->rnsize : sccb->rnsize2;
	rnsize <<= 20;
	*mem = rnsize * rnmax;
	वापस 0;
पूर्ण

पूर्णांक __init sclp_early_get_hsa_size(अचिन्हित दीर्घ *hsa_size)
अणु
	अगर (!sclp_info_sccb_valid)
		वापस -EIO;

	*hsa_size = 0;
	अगर (sclp_info_sccb.hsa_size)
		*hsa_size = (sclp_info_sccb.hsa_size - 1) * PAGE_SIZE;
	वापस 0;
पूर्ण

#घोषणा SCLP_STORAGE_INFO_FACILITY     0x0000400000000000UL

व्योम __weak __init add_mem_detect_block(u64 start, u64 end) अणुपूर्ण
पूर्णांक __init sclp_early_पढ़ो_storage_info(व्योम)
अणु
	काष्ठा पढ़ो_storage_sccb *sccb = (काष्ठा पढ़ो_storage_sccb *)sclp_early_sccb;
	पूर्णांक rc, id, max_id = 0;
	अचिन्हित दीर्घ rn, rzm;
	sclp_cmdw_t command;
	u16 sn;

	अगर (!sclp_info_sccb_valid)
		वापस -EIO;

	अगर (!(sclp_info_sccb.facilities & SCLP_STORAGE_INFO_FACILITY))
		वापस -EOPNOTSUPP;

	rzm = sclp_info_sccb.rnsize ?: sclp_info_sccb.rnsize2;
	rzm <<= 20;

	क्रम (id = 0; id <= max_id; id++) अणु
		स_रखो(sclp_early_sccb, 0, EARLY_SCCB_SIZE);
		sccb->header.length = EARLY_SCCB_SIZE;
		command = SCLP_CMDW_READ_STORAGE_INFO | (id << 8);
		rc = sclp_early_cmd(command, sccb);
		अगर (rc)
			जाओ fail;

		max_id = sccb->max_id;
		चयन (sccb->header.response_code) अणु
		हाल 0x0010:
			क्रम (sn = 0; sn < sccb->asचिन्हित; sn++) अणु
				अगर (!sccb->entries[sn])
					जारी;
				rn = sccb->entries[sn] >> 16;
				add_mem_detect_block((rn - 1) * rzm, rn * rzm);
			पूर्ण
			अवरोध;
		हाल 0x0310:
		हाल 0x0410:
			अवरोध;
		शेष:
			जाओ fail;
		पूर्ण
	पूर्ण

	वापस 0;
fail:
	mem_detect.count = 0;
	वापस -EIO;
पूर्ण
