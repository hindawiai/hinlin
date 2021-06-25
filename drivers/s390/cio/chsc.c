<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *   S/390 common I/O routines -- channel subप्रणाली call
 *
 *    Copyright IBM Corp. 1999,2012
 *    Author(s): Ingo Adlung (adlung@de.ibm.com)
 *		 Cornelia Huck (cornelia.huck@de.ibm.com)
 *		 Arnd Bergmann (arndb@de.ibm.com)
 */

#घोषणा KMSG_COMPONENT "cio"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/chpid.h>
#समावेश <यंत्र/chsc.h>
#समावेश <यंत्र/crw.h>
#समावेश <यंत्र/isc.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/ap.h>

#समावेश "css.h"
#समावेश "cio.h"
#समावेश "cio_debug.h"
#समावेश "ioasm.h"
#समावेश "chp.h"
#समावेश "chsc.h"

अटल व्योम *sei_page;
अटल व्योम *chsc_page;
अटल DEFINE_SPINLOCK(chsc_page_lock);

#घोषणा SEI_VF_FLA	0xc0 /* VF flag क्रम Full Link Address */
#घोषणा SEI_RS_CHPID	0x4  /* 4 in RS field indicates CHPID */

/**
 * chsc_error_from_response() - convert a chsc response to an error
 * @response: chsc response code
 *
 * Returns an appropriate Linux error code क्रम @response.
 */
पूर्णांक chsc_error_from_response(पूर्णांक response)
अणु
	चयन (response) अणु
	हाल 0x0001:
		वापस 0;
	हाल 0x0002:
	हाल 0x0003:
	हाल 0x0006:
	हाल 0x0007:
	हाल 0x0008:
	हाल 0x000a:
	हाल 0x0104:
		वापस -EINVAL;
	हाल 0x0004:
	हाल 0x0106:		/* "Wrong Channel Parm" क्रम the op 0x003d */
		वापस -EOPNOTSUPP;
	हाल 0x000b:
	हाल 0x0107:		/* "Channel busy" क्रम the op 0x003d */
		वापस -EBUSY;
	हाल 0x0100:
	हाल 0x0102:
		वापस -ENOMEM;
	हाल 0x0108:		/* "HW limit exceeded" क्रम the op 0x003d */
		वापस -EUSERS;
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(chsc_error_from_response);

काष्ठा chsc_ssd_area अणु
	काष्ठा chsc_header request;
	u16 :10;
	u16 ssid:2;
	u16 :4;
	u16 f_sch;	  /* first subchannel */
	u16 :16;
	u16 l_sch;	  /* last subchannel */
	u32 :32;
	काष्ठा chsc_header response;
	u32 :32;
	u8 sch_valid : 1;
	u8 dev_valid : 1;
	u8 st	     : 3; /* subchannel type */
	u8 zeroes    : 3;
	u8  unit_addr;	  /* unit address */
	u16 devno;	  /* device number */
	u8 path_mask;
	u8 fla_valid_mask;
	u16 sch;	  /* subchannel */
	u8 chpid[8];	  /* chpids 0-7 */
	u16 fla[8];	  /* full link addresses 0-7 */
पूर्ण __packed __aligned(PAGE_SIZE);

पूर्णांक chsc_get_ssd_info(काष्ठा subchannel_id schid, काष्ठा chsc_ssd_info *ssd)
अणु
	काष्ठा chsc_ssd_area *ssd_area;
	अचिन्हित दीर्घ flags;
	पूर्णांक ccode;
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक mask;

	spin_lock_irqsave(&chsc_page_lock, flags);
	स_रखो(chsc_page, 0, PAGE_SIZE);
	ssd_area = chsc_page;
	ssd_area->request.length = 0x0010;
	ssd_area->request.code = 0x0004;
	ssd_area->ssid = schid.ssid;
	ssd_area->f_sch = schid.sch_no;
	ssd_area->l_sch = schid.sch_no;

	ccode = chsc(ssd_area);
	/* Check response. */
	अगर (ccode > 0) अणु
		ret = (ccode == 3) ? -ENODEV : -EBUSY;
		जाओ out;
	पूर्ण
	ret = chsc_error_from_response(ssd_area->response.code);
	अगर (ret != 0) अणु
		CIO_MSG_EVENT(2, "chsc: ssd failed for 0.%x.%04x (rc=%04x)\n",
			      schid.ssid, schid.sch_no,
			      ssd_area->response.code);
		जाओ out;
	पूर्ण
	अगर (!ssd_area->sch_valid) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण
	/* Copy data */
	ret = 0;
	स_रखो(ssd, 0, माप(काष्ठा chsc_ssd_info));
	अगर ((ssd_area->st != SUBCHANNEL_TYPE_IO) &&
	    (ssd_area->st != SUBCHANNEL_TYPE_MSG))
		जाओ out;
	ssd->path_mask = ssd_area->path_mask;
	ssd->fla_valid_mask = ssd_area->fla_valid_mask;
	क्रम (i = 0; i < 8; i++) अणु
		mask = 0x80 >> i;
		अगर (ssd_area->path_mask & mask) अणु
			chp_id_init(&ssd->chpid[i]);
			ssd->chpid[i].id = ssd_area->chpid[i];
		पूर्ण
		अगर (ssd_area->fla_valid_mask & mask)
			ssd->fla[i] = ssd_area->fla[i];
	पूर्ण
out:
	spin_unlock_irqrestore(&chsc_page_lock, flags);
	वापस ret;
पूर्ण

/**
 * chsc_ssqd() - store subchannel QDIO data (SSQD)
 * @schid: id of the subchannel on which SSQD is perक्रमmed
 * @ssqd: request and response block क्रम SSQD
 *
 * Returns 0 on success.
 */
पूर्णांक chsc_ssqd(काष्ठा subchannel_id schid, काष्ठा chsc_ssqd_area *ssqd)
अणु
	स_रखो(ssqd, 0, माप(*ssqd));
	ssqd->request.length = 0x0010;
	ssqd->request.code = 0x0024;
	ssqd->first_sch = schid.sch_no;
	ssqd->last_sch = schid.sch_no;
	ssqd->ssid = schid.ssid;

	अगर (chsc(ssqd))
		वापस -EIO;

	वापस chsc_error_from_response(ssqd->response.code);
पूर्ण
EXPORT_SYMBOL_GPL(chsc_ssqd);

/**
 * chsc_sadc() - set adapter device controls (SADC)
 * @schid: id of the subchannel on which SADC is perक्रमmed
 * @scssc: request and response block क्रम SADC
 * @summary_indicator_addr: summary indicator address
 * @subchannel_indicator_addr: subchannel indicator address
 * @isc: Interruption Subclass क्रम this subchannel
 *
 * Returns 0 on success.
 */
पूर्णांक chsc_sadc(काष्ठा subchannel_id schid, काष्ठा chsc_scssc_area *scssc,
	      u64 summary_indicator_addr, u64 subchannel_indicator_addr, u8 isc)
अणु
	स_रखो(scssc, 0, माप(*scssc));
	scssc->request.length = 0x0fe0;
	scssc->request.code = 0x0021;
	scssc->operation_code = 0;

	scssc->summary_indicator_addr = summary_indicator_addr;
	scssc->subchannel_indicator_addr = subchannel_indicator_addr;

	scssc->ks = PAGE_DEFAULT_KEY >> 4;
	scssc->kc = PAGE_DEFAULT_KEY >> 4;
	scssc->isc = isc;
	scssc->schid = schid;

	/* enable the समय delay disablement facility */
	अगर (css_general_अक्षरacteristics.aअगर_tdd)
		scssc->word_with_d_bit = 0x10000000;

	अगर (chsc(scssc))
		वापस -EIO;

	वापस chsc_error_from_response(scssc->response.code);
पूर्ण
EXPORT_SYMBOL_GPL(chsc_sadc);

अटल पूर्णांक s390_subchannel_हटाओ_chpid(काष्ठा subchannel *sch, व्योम *data)
अणु
	spin_lock_irq(sch->lock);
	अगर (sch->driver && sch->driver->chp_event)
		अगर (sch->driver->chp_event(sch, data, CHP_OFFLINE) != 0)
			जाओ out_unreg;
	spin_unlock_irq(sch->lock);
	वापस 0;

out_unreg:
	sch->lpm = 0;
	spin_unlock_irq(sch->lock);
	css_schedule_eval(sch->schid);
	वापस 0;
पूर्ण

व्योम chsc_chp_offline(काष्ठा chp_id chpid)
अणु
	काष्ठा channel_path *chp = chpid_to_chp(chpid);
	काष्ठा chp_link link;
	अक्षर dbf_txt[15];

	प्र_लिखो(dbf_txt, "chpr%x.%02x", chpid.cssid, chpid.id);
	CIO_TRACE_EVENT(2, dbf_txt);

	अगर (chp_get_status(chpid) <= 0)
		वापस;
	स_रखो(&link, 0, माप(काष्ठा chp_link));
	link.chpid = chpid;
	/* Wait until previous actions have settled. */
	css_रुको_क्रम_slow_path();

	mutex_lock(&chp->lock);
	chp_update_desc(chp);
	mutex_unlock(&chp->lock);

	क्रम_each_subchannel_staged(s390_subchannel_हटाओ_chpid, शून्य, &link);
पूर्ण

अटल पूर्णांक __s390_process_res_acc(काष्ठा subchannel *sch, व्योम *data)
अणु
	spin_lock_irq(sch->lock);
	अगर (sch->driver && sch->driver->chp_event)
		sch->driver->chp_event(sch, data, CHP_ONLINE);
	spin_unlock_irq(sch->lock);

	वापस 0;
पूर्ण

अटल व्योम s390_process_res_acc(काष्ठा chp_link *link)
अणु
	अक्षर dbf_txt[15];

	प्र_लिखो(dbf_txt, "accpr%x.%02x", link->chpid.cssid,
		link->chpid.id);
	CIO_TRACE_EVENT( 2, dbf_txt);
	अगर (link->fla != 0) अणु
		प्र_लिखो(dbf_txt, "fla%x", link->fla);
		CIO_TRACE_EVENT( 2, dbf_txt);
	पूर्ण
	/* Wait until previous actions have settled. */
	css_रुको_क्रम_slow_path();
	/*
	 * I/O resources may have become accessible.
	 * Scan through all subchannels that may be concerned and
	 * करो a validation on those.
	 * The more inक्रमmation we have (info), the less scanning
	 * will we have to करो.
	 */
	क्रम_each_subchannel_staged(__s390_process_res_acc, शून्य, link);
	css_schedule_reprobe();
पूर्ण

अटल पूर्णांक process_fces_event(काष्ठा subchannel *sch, व्योम *data)
अणु
	spin_lock_irq(sch->lock);
	अगर (sch->driver && sch->driver->chp_event)
		sch->driver->chp_event(sch, data, CHP_FCES_EVENT);
	spin_unlock_irq(sch->lock);
	वापस 0;
पूर्ण

काष्ठा chsc_sei_nt0_area अणु
	u8  flags;
	u8  vf;				/* validity flags */
	u8  rs;				/* reporting source */
	u8  cc;				/* content code */
	u16 fla;			/* full link address */
	u16 rsid;			/* reporting source id */
	u32 reserved1;
	u32 reserved2;
	/* ccdf has to be big enough क्रम a link-incident record */
	u8  ccdf[PAGE_SIZE - 24 - 16];	/* content-code dependent field */
पूर्ण __packed;

काष्ठा chsc_sei_nt2_area अणु
	u8  flags;			/* p and v bit */
	u8  reserved1;
	u8  reserved2;
	u8  cc;				/* content code */
	u32 reserved3[13];
	u8  ccdf[PAGE_SIZE - 24 - 56];	/* content-code dependent field */
पूर्ण __packed;

#घोषणा CHSC_SEI_NT0	(1ULL << 63)
#घोषणा CHSC_SEI_NT2	(1ULL << 61)

काष्ठा chsc_sei अणु
	काष्ठा chsc_header request;
	u32 reserved1;
	u64 ntsm;			/* notअगरication type mask */
	काष्ठा chsc_header response;
	u32 :24;
	u8 nt;
	जोड़ अणु
		काष्ठा chsc_sei_nt0_area nt0_area;
		काष्ठा chsc_sei_nt2_area nt2_area;
		u8 nt_area[PAGE_SIZE - 24];
	पूर्ण u;
पूर्ण __packed __aligned(PAGE_SIZE);

/*
 * Link Incident Record as defined in SA22-7202, "ESCON I/O Interface"
 */

#घोषणा LIR_IQ_CLASS_INFO		0
#घोषणा LIR_IQ_CLASS_DEGRADED		1
#घोषणा LIR_IQ_CLASS_NOT_OPERATIONAL	2

काष्ठा lir अणु
	काष्ठा अणु
		u32 null:1;
		u32 reserved:3;
		u32 class:2;
		u32 reserved2:2;
	पूर्ण __packed iq;
	u32 ic:8;
	u32 reserved:16;
	काष्ठा node_descriptor incident_node;
	काष्ठा node_descriptor attached_node;
	u8 reserved2[32];
पूर्ण __packed;

#घोषणा PARAMS_LEN	10	/* PARAMS=xx,xxxxxx */
#घोषणा NODEID_LEN	35	/* NODEID=tttttt/mdl,mmm.ppssssssssssss,xxxx */

/* Copy EBCIDC text, convert to ASCII and optionally add delimiter. */
अटल अक्षर *store_ebcdic(अक्षर *dest, स्थिर अक्षर *src, अचिन्हित दीर्घ len,
			  अक्षर delim)
अणु
	स_नकल(dest, src, len);
	EBCASC(dest, len);

	अगर (delim)
		dest[len++] = delim;

	वापस dest + len;
पूर्ण

अटल व्योम chsc_link_from_sei(काष्ठा chp_link *link,
				काष्ठा chsc_sei_nt0_area *sei_area)
अणु
	अगर ((sei_area->vf & SEI_VF_FLA) != 0) अणु
		link->fla	= sei_area->fla;
		link->fla_mask	= ((sei_area->vf & SEI_VF_FLA) == SEI_VF_FLA) ?
							0xffff : 0xff00;
	पूर्ण
पूर्ण

/* Format node ID and parameters क्रम output in LIR log message. */
अटल व्योम क्रमmat_node_data(अक्षर *params, अक्षर *id, काष्ठा node_descriptor *nd)
अणु
	स_रखो(params, 0, PARAMS_LEN);
	स_रखो(id, 0, NODEID_LEN);

	अगर (nd->validity != ND_VALIDITY_VALID) अणु
		म_नकलन(params, "n/a", PARAMS_LEN - 1);
		म_नकलन(id, "n/a", NODEID_LEN - 1);
		वापस;
	पूर्ण

	/* PARAMS=xx,xxxxxx */
	snम_लिखो(params, PARAMS_LEN, "%02x,%06x", nd->byte0, nd->params);
	/* NODEID=tttttt/mdl,mmm.ppssssssssssss,xxxx */
	id = store_ebcdic(id, nd->type, माप(nd->type), '/');
	id = store_ebcdic(id, nd->model, माप(nd->model), ',');
	id = store_ebcdic(id, nd->manufacturer, माप(nd->manufacturer), '.');
	id = store_ebcdic(id, nd->plant, माप(nd->plant), 0);
	id = store_ebcdic(id, nd->seq, माप(nd->seq), ',');
	प्र_लिखो(id, "%04X", nd->tag);
पूर्ण

अटल व्योम chsc_process_sei_link_incident(काष्ठा chsc_sei_nt0_area *sei_area)
अणु
	काष्ठा lir *lir = (काष्ठा lir *) &sei_area->ccdf;
	अक्षर iuparams[PARAMS_LEN], iunodeid[NODEID_LEN], auparams[PARAMS_LEN],
	     aunodeid[NODEID_LEN];

	CIO_CRW_EVENT(4, "chsc: link incident (rs=%02x, rs_id=%04x, iq=%02x)\n",
		      sei_area->rs, sei_area->rsid, sei_area->ccdf[0]);

	/* Ignore शून्य Link Incident Records. */
	अगर (lir->iq.null)
		वापस;

	/* Inक्रमm user that a link requires मुख्यtenance actions because it has
	 * become degraded or not operational. Note that this log message is
	 * the primary पूर्णांकention behind a Link Incident Record. */

	क्रमmat_node_data(iuparams, iunodeid, &lir->incident_node);
	क्रमmat_node_data(auparams, aunodeid, &lir->attached_node);

	चयन (lir->iq.class) अणु
	हाल LIR_IQ_CLASS_DEGRADED:
		pr_warn("Link degraded: RS=%02x RSID=%04x IC=%02x "
			"IUPARAMS=%s IUNODEID=%s AUPARAMS=%s AUNODEID=%s\n",
			sei_area->rs, sei_area->rsid, lir->ic, iuparams,
			iunodeid, auparams, aunodeid);
		अवरोध;
	हाल LIR_IQ_CLASS_NOT_OPERATIONAL:
		pr_err("Link stopped: RS=%02x RSID=%04x IC=%02x "
		       "IUPARAMS=%s IUNODEID=%s AUPARAMS=%s AUNODEID=%s\n",
		       sei_area->rs, sei_area->rsid, lir->ic, iuparams,
		       iunodeid, auparams, aunodeid);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम chsc_process_sei_res_acc(काष्ठा chsc_sei_nt0_area *sei_area)
अणु
	काष्ठा channel_path *chp;
	काष्ठा chp_link link;
	काष्ठा chp_id chpid;
	पूर्णांक status;

	CIO_CRW_EVENT(4, "chsc: resource accessibility event (rs=%02x, "
		      "rs_id=%04x)\n", sei_area->rs, sei_area->rsid);
	अगर (sei_area->rs != 4)
		वापस;
	chp_id_init(&chpid);
	chpid.id = sei_area->rsid;
	/* allocate a new channel path काष्ठाure, अगर needed */
	status = chp_get_status(chpid);
	अगर (!status)
		वापस;

	अगर (status < 0) अणु
		chp_new(chpid);
	पूर्ण अन्यथा अणु
		chp = chpid_to_chp(chpid);
		mutex_lock(&chp->lock);
		chp_update_desc(chp);
		mutex_unlock(&chp->lock);
	पूर्ण
	स_रखो(&link, 0, माप(काष्ठा chp_link));
	link.chpid = chpid;
	chsc_link_from_sei(&link, sei_area);
	s390_process_res_acc(&link);
पूर्ण

अटल व्योम chsc_process_sei_chp_avail(काष्ठा chsc_sei_nt0_area *sei_area)
अणु
	काष्ठा channel_path *chp;
	काष्ठा chp_id chpid;
	u8 *data;
	पूर्णांक num;

	CIO_CRW_EVENT(4, "chsc: channel path availability information\n");
	अगर (sei_area->rs != 0)
		वापस;
	data = sei_area->ccdf;
	chp_id_init(&chpid);
	क्रम (num = 0; num <= __MAX_CHPID; num++) अणु
		अगर (!chp_test_bit(data, num))
			जारी;
		chpid.id = num;

		CIO_CRW_EVENT(4, "Update information for channel path "
			      "%x.%02x\n", chpid.cssid, chpid.id);
		chp = chpid_to_chp(chpid);
		अगर (!chp) अणु
			chp_new(chpid);
			जारी;
		पूर्ण
		mutex_lock(&chp->lock);
		chp_update_desc(chp);
		mutex_unlock(&chp->lock);
	पूर्ण
पूर्ण

काष्ठा chp_config_data अणु
	u8 map[32];
	u8 op;
	u8 pc;
पूर्ण;

अटल व्योम chsc_process_sei_chp_config(काष्ठा chsc_sei_nt0_area *sei_area)
अणु
	काष्ठा chp_config_data *data;
	काष्ठा chp_id chpid;
	पूर्णांक num;
	अक्षर *events[3] = अणु"configure", "deconfigure", "cancel deconfigure"पूर्ण;

	CIO_CRW_EVENT(4, "chsc: channel-path-configuration notification\n");
	अगर (sei_area->rs != 0)
		वापस;
	data = (काष्ठा chp_config_data *) &(sei_area->ccdf);
	chp_id_init(&chpid);
	क्रम (num = 0; num <= __MAX_CHPID; num++) अणु
		अगर (!chp_test_bit(data->map, num))
			जारी;
		chpid.id = num;
		pr_notice("Processing %s for channel path %x.%02x\n",
			  events[data->op], chpid.cssid, chpid.id);
		चयन (data->op) अणु
		हाल 0:
			chp_cfg_schedule(chpid, 1);
			अवरोध;
		हाल 1:
			chp_cfg_schedule(chpid, 0);
			अवरोध;
		हाल 2:
			chp_cfg_cancel_deconfigure(chpid);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम chsc_process_sei_scm_change(काष्ठा chsc_sei_nt0_area *sei_area)
अणु
	पूर्णांक ret;

	CIO_CRW_EVENT(4, "chsc: scm change notification\n");
	अगर (sei_area->rs != 7)
		वापस;

	ret = scm_update_inक्रमmation();
	अगर (ret)
		CIO_CRW_EVENT(0, "chsc: updating change notification"
			      " failed (rc=%d).\n", ret);
पूर्ण

अटल व्योम chsc_process_sei_scm_avail(काष्ठा chsc_sei_nt0_area *sei_area)
अणु
	पूर्णांक ret;

	CIO_CRW_EVENT(4, "chsc: scm available information\n");
	अगर (sei_area->rs != 7)
		वापस;

	ret = scm_process_availability_inक्रमmation();
	अगर (ret)
		CIO_CRW_EVENT(0, "chsc: process availability information"
			      " failed (rc=%d).\n", ret);
पूर्ण

अटल व्योम chsc_process_sei_ap_cfg_chg(काष्ठा chsc_sei_nt0_area *sei_area)
अणु
	CIO_CRW_EVENT(3, "chsc: ap config changed\n");
	अगर (sei_area->rs != 5)
		वापस;

	ap_bus_cfg_chg();
पूर्ण

अटल व्योम chsc_process_sei_fces_event(काष्ठा chsc_sei_nt0_area *sei_area)
अणु
	काष्ठा chp_link link;
	काष्ठा chp_id chpid;
	काष्ठा channel_path *chp;

	CIO_CRW_EVENT(4,
	"chsc: FCES status notification (rs=%02x, rs_id=%04x, FCES-status=%x)\n",
		sei_area->rs, sei_area->rsid, sei_area->ccdf[0]);

	अगर (sei_area->rs != SEI_RS_CHPID)
		वापस;
	chp_id_init(&chpid);
	chpid.id = sei_area->rsid;

	/* Ignore the event on unknown/invalid chp */
	chp = chpid_to_chp(chpid);
	अगर (!chp)
		वापस;

	स_रखो(&link, 0, माप(काष्ठा chp_link));
	link.chpid = chpid;
	chsc_link_from_sei(&link, sei_area);

	क्रम_each_subchannel_staged(process_fces_event, शून्य, &link);
पूर्ण

अटल व्योम chsc_process_sei_nt2(काष्ठा chsc_sei_nt2_area *sei_area)
अणु
	चयन (sei_area->cc) अणु
	हाल 1:
		zpci_event_error(sei_area->ccdf);
		अवरोध;
	हाल 2:
		zpci_event_availability(sei_area->ccdf);
		अवरोध;
	शेष:
		CIO_CRW_EVENT(2, "chsc: sei nt2 unhandled cc=%d\n",
			      sei_area->cc);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम chsc_process_sei_nt0(काष्ठा chsc_sei_nt0_area *sei_area)
अणु
	/* which kind of inक्रमmation was stored? */
	चयन (sei_area->cc) अणु
	हाल 1: /* link incident*/
		chsc_process_sei_link_incident(sei_area);
		अवरोध;
	हाल 2: /* i/o resource accessibility */
		chsc_process_sei_res_acc(sei_area);
		अवरोध;
	हाल 3: /* ap config changed */
		chsc_process_sei_ap_cfg_chg(sei_area);
		अवरोध;
	हाल 7: /* channel-path-availability inक्रमmation */
		chsc_process_sei_chp_avail(sei_area);
		अवरोध;
	हाल 8: /* channel-path-configuration notअगरication */
		chsc_process_sei_chp_config(sei_area);
		अवरोध;
	हाल 12: /* scm change notअगरication */
		chsc_process_sei_scm_change(sei_area);
		अवरोध;
	हाल 14: /* scm available notअगरication */
		chsc_process_sei_scm_avail(sei_area);
		अवरोध;
	हाल 15: /* FCES event notअगरication */
		chsc_process_sei_fces_event(sei_area);
		अवरोध;
	शेष: /* other stuff */
		CIO_CRW_EVENT(2, "chsc: sei nt0 unhandled cc=%d\n",
			      sei_area->cc);
		अवरोध;
	पूर्ण

	/* Check अगर we might have lost some inक्रमmation. */
	अगर (sei_area->flags & 0x40) अणु
		CIO_CRW_EVENT(2, "chsc: event overflow\n");
		css_schedule_eval_all();
	पूर्ण
पूर्ण

अटल व्योम chsc_process_event_inक्रमmation(काष्ठा chsc_sei *sei, u64 ntsm)
अणु
	अटल पूर्णांक ntsm_unsupported;

	जबतक (true) अणु
		स_रखो(sei, 0, माप(*sei));
		sei->request.length = 0x0010;
		sei->request.code = 0x000e;
		अगर (!ntsm_unsupported)
			sei->ntsm = ntsm;

		अगर (chsc(sei))
			अवरोध;

		अगर (sei->response.code != 0x0001) अणु
			CIO_CRW_EVENT(2, "chsc: sei failed (rc=%04x, ntsm=%llx)\n",
				      sei->response.code, sei->ntsm);

			अगर (sei->response.code == 3 && sei->ntsm) अणु
				/* Fallback क्रम old firmware. */
				ntsm_unsupported = 1;
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		CIO_CRW_EVENT(2, "chsc: sei successful (nt=%d)\n", sei->nt);
		चयन (sei->nt) अणु
		हाल 0:
			chsc_process_sei_nt0(&sei->u.nt0_area);
			अवरोध;
		हाल 2:
			chsc_process_sei_nt2(&sei->u.nt2_area);
			अवरोध;
		शेष:
			CIO_CRW_EVENT(2, "chsc: unhandled nt: %d\n", sei->nt);
			अवरोध;
		पूर्ण

		अगर (!(sei->u.nt0_area.flags & 0x80))
			अवरोध;
	पूर्ण
पूर्ण

/*
 * Handle channel subप्रणाली related CRWs.
 * Use store event inक्रमmation to find out what's going on.
 *
 * Note: Access to sei_page is serialized through machine check handler
 * thपढ़ो, so no need क्रम locking.
 */
अटल व्योम chsc_process_crw(काष्ठा crw *crw0, काष्ठा crw *crw1, पूर्णांक overflow)
अणु
	काष्ठा chsc_sei *sei = sei_page;

	अगर (overflow) अणु
		css_schedule_eval_all();
		वापस;
	पूर्ण
	CIO_CRW_EVENT(2, "CRW reports slct=%d, oflw=%d, "
		      "chn=%d, rsc=%X, anc=%d, erc=%X, rsid=%X\n",
		      crw0->slct, crw0->oflw, crw0->chn, crw0->rsc, crw0->anc,
		      crw0->erc, crw0->rsid);

	CIO_TRACE_EVENT(2, "prcss");
	chsc_process_event_inक्रमmation(sei, CHSC_SEI_NT0 | CHSC_SEI_NT2);
पूर्ण

व्योम chsc_chp_online(काष्ठा chp_id chpid)
अणु
	काष्ठा channel_path *chp = chpid_to_chp(chpid);
	काष्ठा chp_link link;
	अक्षर dbf_txt[15];

	प्र_लिखो(dbf_txt, "cadd%x.%02x", chpid.cssid, chpid.id);
	CIO_TRACE_EVENT(2, dbf_txt);

	अगर (chp_get_status(chpid) != 0) अणु
		स_रखो(&link, 0, माप(काष्ठा chp_link));
		link.chpid = chpid;
		/* Wait until previous actions have settled. */
		css_रुको_क्रम_slow_path();

		mutex_lock(&chp->lock);
		chp_update_desc(chp);
		mutex_unlock(&chp->lock);

		क्रम_each_subchannel_staged(__s390_process_res_acc, शून्य,
					   &link);
		css_schedule_reprobe();
	पूर्ण
पूर्ण

अटल व्योम __s390_subchannel_vary_chpid(काष्ठा subchannel *sch,
					 काष्ठा chp_id chpid, पूर्णांक on)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा chp_link link;

	स_रखो(&link, 0, माप(काष्ठा chp_link));
	link.chpid = chpid;
	spin_lock_irqsave(sch->lock, flags);
	अगर (sch->driver && sch->driver->chp_event)
		sch->driver->chp_event(sch, &link,
				       on ? CHP_VARY_ON : CHP_VARY_OFF);
	spin_unlock_irqrestore(sch->lock, flags);
पूर्ण

अटल पूर्णांक s390_subchannel_vary_chpid_off(काष्ठा subchannel *sch, व्योम *data)
अणु
	काष्ठा chp_id *chpid = data;

	__s390_subchannel_vary_chpid(sch, *chpid, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक s390_subchannel_vary_chpid_on(काष्ठा subchannel *sch, व्योम *data)
अणु
	काष्ठा chp_id *chpid = data;

	__s390_subchannel_vary_chpid(sch, *chpid, 1);
	वापस 0;
पूर्ण

/**
 * chsc_chp_vary - propagate channel-path vary operation to subchannels
 * @chpid: channl-path ID
 * @on: non-zero क्रम vary online, zero क्रम vary offline
 */
पूर्णांक chsc_chp_vary(काष्ठा chp_id chpid, पूर्णांक on)
अणु
	काष्ठा channel_path *chp = chpid_to_chp(chpid);

	/* Wait until previous actions have settled. */
	css_रुको_क्रम_slow_path();
	/*
	 * Reकरो PathVerअगरication on the devices the chpid connects to
	 */
	अगर (on) अणु
		/* Try to update the channel path description. */
		chp_update_desc(chp);
		क्रम_each_subchannel_staged(s390_subchannel_vary_chpid_on,
					   शून्य, &chpid);
		css_schedule_reprobe();
	पूर्ण अन्यथा
		क्रम_each_subchannel_staged(s390_subchannel_vary_chpid_off,
					   शून्य, &chpid);

	वापस 0;
पूर्ण

अटल व्योम
chsc_हटाओ_cmg_attr(काष्ठा channel_subप्रणाली *css)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= __MAX_CHPID; i++) अणु
		अगर (!css->chps[i])
			जारी;
		chp_हटाओ_cmg_attr(css->chps[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक
chsc_add_cmg_attr(काष्ठा channel_subप्रणाली *css)
अणु
	पूर्णांक i, ret;

	ret = 0;
	क्रम (i = 0; i <= __MAX_CHPID; i++) अणु
		अगर (!css->chps[i])
			जारी;
		ret = chp_add_cmg_attr(css->chps[i]);
		अगर (ret)
			जाओ cleanup;
	पूर्ण
	वापस ret;
cleanup:
	क्रम (--i; i >= 0; i--) अणु
		अगर (!css->chps[i])
			जारी;
		chp_हटाओ_cmg_attr(css->chps[i]);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक __chsc_करो_secm(काष्ठा channel_subप्रणाली *css, पूर्णांक enable)
अणु
	काष्ठा अणु
		काष्ठा chsc_header request;
		u32 operation_code : 2;
		u32 : 30;
		u32 key : 4;
		u32 : 28;
		u32 zeroes1;
		u32 cub_addr1;
		u32 zeroes2;
		u32 cub_addr2;
		u32 reserved[13];
		काष्ठा chsc_header response;
		u32 status : 8;
		u32 : 4;
		u32 fmt : 4;
		u32 : 16;
	पूर्ण *secm_area;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, ccode;

	spin_lock_irqsave(&chsc_page_lock, flags);
	स_रखो(chsc_page, 0, PAGE_SIZE);
	secm_area = chsc_page;
	secm_area->request.length = 0x0050;
	secm_area->request.code = 0x0016;

	secm_area->key = PAGE_DEFAULT_KEY >> 4;
	secm_area->cub_addr1 = (u64)(अचिन्हित दीर्घ)css->cub_addr1;
	secm_area->cub_addr2 = (u64)(अचिन्हित दीर्घ)css->cub_addr2;

	secm_area->operation_code = enable ? 0 : 1;

	ccode = chsc(secm_area);
	अगर (ccode > 0) अणु
		ret = (ccode == 3) ? -ENODEV : -EBUSY;
		जाओ out;
	पूर्ण

	चयन (secm_area->response.code) अणु
	हाल 0x0102:
	हाल 0x0103:
		ret = -EINVAL;
		अवरोध;
	शेष:
		ret = chsc_error_from_response(secm_area->response.code);
	पूर्ण
	अगर (ret != 0)
		CIO_CRW_EVENT(2, "chsc: secm failed (rc=%04x)\n",
			      secm_area->response.code);
out:
	spin_unlock_irqrestore(&chsc_page_lock, flags);
	वापस ret;
पूर्ण

पूर्णांक
chsc_secm(काष्ठा channel_subप्रणाली *css, पूर्णांक enable)
अणु
	पूर्णांक ret;

	अगर (enable && !css->cm_enabled) अणु
		css->cub_addr1 = (व्योम *)get_zeroed_page(GFP_KERNEL | GFP_DMA);
		css->cub_addr2 = (व्योम *)get_zeroed_page(GFP_KERNEL | GFP_DMA);
		अगर (!css->cub_addr1 || !css->cub_addr2) अणु
			मुक्त_page((अचिन्हित दीर्घ)css->cub_addr1);
			मुक्त_page((अचिन्हित दीर्घ)css->cub_addr2);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	ret = __chsc_करो_secm(css, enable);
	अगर (!ret) अणु
		css->cm_enabled = enable;
		अगर (css->cm_enabled) अणु
			ret = chsc_add_cmg_attr(css);
			अगर (ret) अणु
				__chsc_करो_secm(css, 0);
				css->cm_enabled = 0;
			पूर्ण
		पूर्ण अन्यथा
			chsc_हटाओ_cmg_attr(css);
	पूर्ण
	अगर (!css->cm_enabled) अणु
		मुक्त_page((अचिन्हित दीर्घ)css->cub_addr1);
		मुक्त_page((अचिन्हित दीर्घ)css->cub_addr2);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक chsc_determine_channel_path_desc(काष्ठा chp_id chpid, पूर्णांक fmt, पूर्णांक rfmt,
				     पूर्णांक c, पूर्णांक m, व्योम *page)
अणु
	काष्ठा chsc_scpd *scpd_area;
	पूर्णांक ccode, ret;

	अगर ((rfmt == 1 || rfmt == 0) && c == 1 &&
	    !css_general_अक्षरacteristics.fcs)
		वापस -EINVAL;
	अगर ((rfmt == 2) && !css_general_अक्षरacteristics.cib)
		वापस -EINVAL;
	अगर ((rfmt == 3) && !css_general_अक्षरacteristics.util_str)
		वापस -EINVAL;

	स_रखो(page, 0, PAGE_SIZE);
	scpd_area = page;
	scpd_area->request.length = 0x0010;
	scpd_area->request.code = 0x0002;
	scpd_area->cssid = chpid.cssid;
	scpd_area->first_chpid = chpid.id;
	scpd_area->last_chpid = chpid.id;
	scpd_area->m = m;
	scpd_area->c = c;
	scpd_area->fmt = fmt;
	scpd_area->rfmt = rfmt;

	ccode = chsc(scpd_area);
	अगर (ccode > 0)
		वापस (ccode == 3) ? -ENODEV : -EBUSY;

	ret = chsc_error_from_response(scpd_area->response.code);
	अगर (ret)
		CIO_CRW_EVENT(2, "chsc: scpd failed (rc=%04x)\n",
			      scpd_area->response.code);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(chsc_determine_channel_path_desc);

#घोषणा chsc_det_chp_desc(FMT, c)					\
पूर्णांक chsc_determine_fmt##FMT##_channel_path_desc(			\
	काष्ठा chp_id chpid, काष्ठा channel_path_desc_fmt##FMT *desc)	\
अणु									\
	काष्ठा chsc_scpd *scpd_area;					\
	अचिन्हित दीर्घ flags;						\
	पूर्णांक ret;							\
									\
	spin_lock_irqsave(&chsc_page_lock, flags);			\
	scpd_area = chsc_page;						\
	ret = chsc_determine_channel_path_desc(chpid, 0, FMT, c, 0,	\
					       scpd_area);		\
	अगर (ret)							\
		जाओ out;						\
									\
	स_नकल(desc, scpd_area->data, माप(*desc));			\
out:									\
	spin_unlock_irqrestore(&chsc_page_lock, flags);			\
	वापस ret;							\
पूर्ण

chsc_det_chp_desc(0, 0)
chsc_det_chp_desc(1, 1)
chsc_det_chp_desc(3, 0)

अटल व्योम
chsc_initialize_cmg_अक्षरs(काष्ठा channel_path *chp, u8 cmcv,
			  काष्ठा cmg_अक्षरs *अक्षरs)
अणु
	पूर्णांक i, mask;

	क्रम (i = 0; i < NR_MEASUREMENT_CHARS; i++) अणु
		mask = 0x80 >> (i + 3);
		अगर (cmcv & mask)
			chp->cmg_अक्षरs.values[i] = अक्षरs->values[i];
		अन्यथा
			chp->cmg_अक्षरs.values[i] = 0;
	पूर्ण
पूर्ण

पूर्णांक chsc_get_channel_measurement_अक्षरs(काष्ठा channel_path *chp)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ccode, ret;

	काष्ठा अणु
		काष्ठा chsc_header request;
		u32 : 24;
		u32 first_chpid : 8;
		u32 : 24;
		u32 last_chpid : 8;
		u32 zeroes1;
		काष्ठा chsc_header response;
		u32 zeroes2;
		u32 not_valid : 1;
		u32 shared : 1;
		u32 : 22;
		u32 chpid : 8;
		u32 cmcv : 5;
		u32 : 11;
		u32 cmgq : 8;
		u32 cmg : 8;
		u32 zeroes3;
		u32 data[NR_MEASUREMENT_CHARS];
	पूर्ण *scmc_area;

	chp->shared = -1;
	chp->cmg = -1;

	अगर (!css_chsc_अक्षरacteristics.scmc || !css_chsc_अक्षरacteristics.secm)
		वापस -EINVAL;

	spin_lock_irqsave(&chsc_page_lock, flags);
	स_रखो(chsc_page, 0, PAGE_SIZE);
	scmc_area = chsc_page;
	scmc_area->request.length = 0x0010;
	scmc_area->request.code = 0x0022;
	scmc_area->first_chpid = chp->chpid.id;
	scmc_area->last_chpid = chp->chpid.id;

	ccode = chsc(scmc_area);
	अगर (ccode > 0) अणु
		ret = (ccode == 3) ? -ENODEV : -EBUSY;
		जाओ out;
	पूर्ण

	ret = chsc_error_from_response(scmc_area->response.code);
	अगर (ret) अणु
		CIO_CRW_EVENT(2, "chsc: scmc failed (rc=%04x)\n",
			      scmc_area->response.code);
		जाओ out;
	पूर्ण
	अगर (scmc_area->not_valid)
		जाओ out;

	chp->cmg = scmc_area->cmg;
	chp->shared = scmc_area->shared;
	अगर (chp->cmg != 2 && chp->cmg != 3) अणु
		/* No cmg-dependent data. */
		जाओ out;
	पूर्ण
	chsc_initialize_cmg_अक्षरs(chp, scmc_area->cmcv,
				  (काष्ठा cmg_अक्षरs *) &scmc_area->data);
out:
	spin_unlock_irqrestore(&chsc_page_lock, flags);
	वापस ret;
पूर्ण

पूर्णांक __init chsc_init(व्योम)
अणु
	पूर्णांक ret;

	sei_page = (व्योम *)get_zeroed_page(GFP_KERNEL | GFP_DMA);
	chsc_page = (व्योम *)get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!sei_page || !chsc_page) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण
	ret = crw_रेजिस्टर_handler(CRW_RSC_CSS, chsc_process_crw);
	अगर (ret)
		जाओ out_err;
	वापस ret;
out_err:
	मुक्त_page((अचिन्हित दीर्घ)chsc_page);
	मुक्त_page((अचिन्हित दीर्घ)sei_page);
	वापस ret;
पूर्ण

व्योम __init chsc_init_cleanup(व्योम)
अणु
	crw_unरेजिस्टर_handler(CRW_RSC_CSS);
	मुक्त_page((अचिन्हित दीर्घ)chsc_page);
	मुक्त_page((अचिन्हित दीर्घ)sei_page);
पूर्ण

पूर्णांक __chsc_enable_facility(काष्ठा chsc_sda_area *sda_area, पूर्णांक operation_code)
अणु
	पूर्णांक ret;

	sda_area->request.length = 0x0400;
	sda_area->request.code = 0x0031;
	sda_area->operation_code = operation_code;

	ret = chsc(sda_area);
	अगर (ret > 0) अणु
		ret = (ret == 3) ? -ENODEV : -EBUSY;
		जाओ out;
	पूर्ण

	चयन (sda_area->response.code) अणु
	हाल 0x0101:
		ret = -EOPNOTSUPP;
		अवरोध;
	शेष:
		ret = chsc_error_from_response(sda_area->response.code);
	पूर्ण
out:
	वापस ret;
पूर्ण

पूर्णांक chsc_enable_facility(पूर्णांक operation_code)
अणु
	काष्ठा chsc_sda_area *sda_area;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&chsc_page_lock, flags);
	स_रखो(chsc_page, 0, PAGE_SIZE);
	sda_area = chsc_page;

	ret = __chsc_enable_facility(sda_area, operation_code);
	अगर (ret != 0)
		CIO_CRW_EVENT(2, "chsc: sda (oc=%x) failed (rc=%04x)\n",
			      operation_code, sda_area->response.code);

	spin_unlock_irqrestore(&chsc_page_lock, flags);
	वापस ret;
पूर्ण

पूर्णांक __init chsc_get_cssid_iid(पूर्णांक idx, u8 *cssid, u8 *iid)
अणु
	काष्ठा अणु
		काष्ठा chsc_header request;
		u8 atype;
		u32 : 24;
		u32 reserved1[6];
		काष्ठा chsc_header response;
		u32 reserved2[3];
		काष्ठा अणु
			u8 cssid;
			u8 iid;
			u32 : 16;
		पूर्ण list[0];
	पूर्ण *sdcal_area;
	पूर्णांक ret;

	spin_lock_irq(&chsc_page_lock);
	स_रखो(chsc_page, 0, PAGE_SIZE);
	sdcal_area = chsc_page;
	sdcal_area->request.length = 0x0020;
	sdcal_area->request.code = 0x0034;
	sdcal_area->atype = 4;

	ret = chsc(sdcal_area);
	अगर (ret) अणु
		ret = (ret == 3) ? -ENODEV : -EBUSY;
		जाओ निकास;
	पूर्ण

	ret = chsc_error_from_response(sdcal_area->response.code);
	अगर (ret) अणु
		CIO_CRW_EVENT(2, "chsc: sdcal failed (rc=%04x)\n",
			      sdcal_area->response.code);
		जाओ निकास;
	पूर्ण

	अगर ((addr_t) &sdcal_area->list[idx] <
	    (addr_t) &sdcal_area->response + sdcal_area->response.length) अणु
		*cssid = sdcal_area->list[idx].cssid;
		*iid = sdcal_area->list[idx].iid;
	पूर्ण
	अन्यथा
		ret = -ENODEV;
निकास:
	spin_unlock_irq(&chsc_page_lock);
	वापस ret;
पूर्ण

काष्ठा css_general_अक्षर css_general_अक्षरacteristics;
काष्ठा css_chsc_अक्षर css_chsc_अक्षरacteristics;

पूर्णांक __init
chsc_determine_css_अक्षरacteristics(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक result;
	काष्ठा अणु
		काष्ठा chsc_header request;
		u32 reserved1;
		u32 reserved2;
		u32 reserved3;
		काष्ठा chsc_header response;
		u32 reserved4;
		u32 general_अक्षर[510];
		u32 chsc_अक्षर[508];
	पूर्ण *scsc_area;

	spin_lock_irqsave(&chsc_page_lock, flags);
	स_रखो(chsc_page, 0, PAGE_SIZE);
	scsc_area = chsc_page;
	scsc_area->request.length = 0x0010;
	scsc_area->request.code = 0x0010;

	result = chsc(scsc_area);
	अगर (result) अणु
		result = (result == 3) ? -ENODEV : -EBUSY;
		जाओ निकास;
	पूर्ण

	result = chsc_error_from_response(scsc_area->response.code);
	अगर (result == 0) अणु
		स_नकल(&css_general_अक्षरacteristics, scsc_area->general_अक्षर,
		       माप(css_general_अक्षरacteristics));
		स_नकल(&css_chsc_अक्षरacteristics, scsc_area->chsc_अक्षर,
		       माप(css_chsc_अक्षरacteristics));
	पूर्ण अन्यथा
		CIO_CRW_EVENT(2, "chsc: scsc failed (rc=%04x)\n",
			      scsc_area->response.code);
निकास:
	spin_unlock_irqrestore(&chsc_page_lock, flags);
	वापस result;
पूर्ण

EXPORT_SYMBOL_GPL(css_general_अक्षरacteristics);
EXPORT_SYMBOL_GPL(css_chsc_अक्षरacteristics);

पूर्णांक chsc_sstpc(व्योम *page, अचिन्हित पूर्णांक op, u16 ctrl, u64 *घड़ी_delta)
अणु
	काष्ठा अणु
		काष्ठा chsc_header request;
		अचिन्हित पूर्णांक rsvd0;
		अचिन्हित पूर्णांक op : 8;
		अचिन्हित पूर्णांक rsvd1 : 8;
		अचिन्हित पूर्णांक ctrl : 16;
		अचिन्हित पूर्णांक rsvd2[5];
		काष्ठा chsc_header response;
		अचिन्हित पूर्णांक rsvd3[3];
		u64 घड़ी_delta;
		अचिन्हित पूर्णांक rsvd4[2];
	पूर्ण *rr;
	पूर्णांक rc;

	स_रखो(page, 0, PAGE_SIZE);
	rr = page;
	rr->request.length = 0x0020;
	rr->request.code = 0x0033;
	rr->op = op;
	rr->ctrl = ctrl;
	rc = chsc(rr);
	अगर (rc)
		वापस -EIO;
	rc = (rr->response.code == 0x0001) ? 0 : -EIO;
	अगर (घड़ी_delta)
		*घड़ी_delta = rr->घड़ी_delta;
	वापस rc;
पूर्ण

पूर्णांक chsc_sstpi(व्योम *page, व्योम *result, माप_प्रकार size)
अणु
	काष्ठा अणु
		काष्ठा chsc_header request;
		अचिन्हित पूर्णांक rsvd0[3];
		काष्ठा chsc_header response;
		अक्षर data[];
	पूर्ण *rr;
	पूर्णांक rc;

	स_रखो(page, 0, PAGE_SIZE);
	rr = page;
	rr->request.length = 0x0010;
	rr->request.code = 0x0038;
	rc = chsc(rr);
	अगर (rc)
		वापस -EIO;
	स_नकल(result, &rr->data, size);
	वापस (rr->response.code == 0x0001) ? 0 : -EIO;
पूर्ण

पूर्णांक chsc_stzi(व्योम *page, व्योम *result, माप_प्रकार size)
अणु
	काष्ठा अणु
		काष्ठा chsc_header request;
		अचिन्हित पूर्णांक rsvd0[3];
		काष्ठा chsc_header response;
		अक्षर data[];
	पूर्ण *rr;
	पूर्णांक rc;

	स_रखो(page, 0, PAGE_SIZE);
	rr = page;
	rr->request.length = 0x0010;
	rr->request.code = 0x003e;
	rc = chsc(rr);
	अगर (rc)
		वापस -EIO;
	स_नकल(result, &rr->data, size);
	वापस (rr->response.code == 0x0001) ? 0 : -EIO;
पूर्ण

पूर्णांक chsc_siosl(काष्ठा subchannel_id schid)
अणु
	काष्ठा अणु
		काष्ठा chsc_header request;
		u32 word1;
		काष्ठा subchannel_id sid;
		u32 word3;
		काष्ठा chsc_header response;
		u32 word[11];
	पूर्ण *siosl_area;
	अचिन्हित दीर्घ flags;
	पूर्णांक ccode;
	पूर्णांक rc;

	spin_lock_irqsave(&chsc_page_lock, flags);
	स_रखो(chsc_page, 0, PAGE_SIZE);
	siosl_area = chsc_page;
	siosl_area->request.length = 0x0010;
	siosl_area->request.code = 0x0046;
	siosl_area->word1 = 0x80000000;
	siosl_area->sid = schid;

	ccode = chsc(siosl_area);
	अगर (ccode > 0) अणु
		अगर (ccode == 3)
			rc = -ENODEV;
		अन्यथा
			rc = -EBUSY;
		CIO_MSG_EVENT(2, "chsc: chsc failed for 0.%x.%04x (ccode=%d)\n",
			      schid.ssid, schid.sch_no, ccode);
		जाओ out;
	पूर्ण
	rc = chsc_error_from_response(siosl_area->response.code);
	अगर (rc)
		CIO_MSG_EVENT(2, "chsc: siosl failed for 0.%x.%04x (rc=%04x)\n",
			      schid.ssid, schid.sch_no,
			      siosl_area->response.code);
	अन्यथा
		CIO_MSG_EVENT(4, "chsc: siosl succeeded for 0.%x.%04x\n",
			      schid.ssid, schid.sch_no);
out:
	spin_unlock_irqrestore(&chsc_page_lock, flags);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(chsc_siosl);

/**
 * chsc_scm_info() - store SCM inक्रमmation (SSI)
 * @scm_area: request and response block क्रम SSI
 * @token: continuation token
 *
 * Returns 0 on success.
 */
पूर्णांक chsc_scm_info(काष्ठा chsc_scm_info *scm_area, u64 token)
अणु
	पूर्णांक ccode, ret;

	स_रखो(scm_area, 0, माप(*scm_area));
	scm_area->request.length = 0x0020;
	scm_area->request.code = 0x004C;
	scm_area->reqtok = token;

	ccode = chsc(scm_area);
	अगर (ccode > 0) अणु
		ret = (ccode == 3) ? -ENODEV : -EBUSY;
		जाओ out;
	पूर्ण
	ret = chsc_error_from_response(scm_area->response.code);
	अगर (ret != 0)
		CIO_MSG_EVENT(2, "chsc: scm info failed (rc=%04x)\n",
			      scm_area->response.code);
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(chsc_scm_info);

/**
 * chsc_pnso() - Perक्रमm Network-Subchannel Operation
 * @schid:		id of the subchannel on which PNSO is perक्रमmed
 * @pnso_area:		request and response block क्रम the operation
 * @oc:			Operation Code
 * @resume_token:	resume token क्रम multiblock response
 * @cnc:		Boolean change-notअगरication control
 *
 * pnso_area must be allocated by the caller with get_zeroed_page(GFP_KERNEL)
 *
 * Returns 0 on success.
 */
पूर्णांक chsc_pnso(काष्ठा subchannel_id schid, काष्ठा chsc_pnso_area *pnso_area,
	      u8 oc, काष्ठा chsc_pnso_resume_token resume_token, पूर्णांक cnc)
अणु
	स_रखो(pnso_area, 0, माप(*pnso_area));
	pnso_area->request.length = 0x0030;
	pnso_area->request.code = 0x003d; /* network-subchannel operation */
	pnso_area->m	   = schid.m;
	pnso_area->ssid  = schid.ssid;
	pnso_area->sch	 = schid.sch_no;
	pnso_area->cssid = schid.cssid;
	pnso_area->oc	 = oc;
	pnso_area->resume_token = resume_token;
	pnso_area->n	   = (cnc != 0);
	अगर (chsc(pnso_area))
		वापस -EIO;
	वापस chsc_error_from_response(pnso_area->response.code);
पूर्ण

पूर्णांक chsc_sgib(u32 origin)
अणु
	काष्ठा अणु
		काष्ठा chsc_header request;
		u16 op;
		u8  reserved01[2];
		u8  reserved02:4;
		u8  fmt:4;
		u8  reserved03[7];
		/* operation data area begin */
		u8  reserved04[4];
		u32 gib_origin;
		u8  reserved05[10];
		u8  aix;
		u8  reserved06[4029];
		काष्ठा chsc_header response;
		u8  reserved07[4];
	पूर्ण *sgib_area;
	पूर्णांक ret;

	spin_lock_irq(&chsc_page_lock);
	स_रखो(chsc_page, 0, PAGE_SIZE);
	sgib_area = chsc_page;
	sgib_area->request.length = 0x0fe0;
	sgib_area->request.code = 0x0021;
	sgib_area->op = 0x1;
	sgib_area->gib_origin = origin;

	ret = chsc(sgib_area);
	अगर (ret == 0)
		ret = chsc_error_from_response(sgib_area->response.code);
	spin_unlock_irq(&chsc_page_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(chsc_sgib);

#घोषणा SCUD_REQ_LEN	0x10 /* SCUD request block length */
#घोषणा SCUD_REQ_CMD	0x4b /* SCUD Command Code */

काष्ठा chse_cudb अणु
	u16 flags:8;
	u16 chp_valid:8;
	u16 cu;
	u32 esm_valid:8;
	u32:24;
	u8 chpid[8];
	u32:32;
	u32:32;
	u8 esm[8];
	u32 efla[8];
पूर्ण __packed;

काष्ठा chsc_scud अणु
	काष्ठा chsc_header request;
	u16:4;
	u16 fmt:4;
	u16 cssid:8;
	u16 first_cu;
	u16:16;
	u16 last_cu;
	u32:32;
	काष्ठा chsc_header response;
	u16:4;
	u16 fmt_resp:4;
	u32:24;
	काष्ठा chse_cudb cudb[];
पूर्ण __packed;

/**
 * chsc_scud() - Store control-unit description.
 * @cu:		number of the control-unit
 * @esm:	8 1-byte endpoपूर्णांक security mode values
 * @esm_valid:	validity mask क्रम @esm
 *
 * Interface to retrieve inक्रमmation about the endpoपूर्णांक security
 * modes क्रम up to 8 paths of a control unit.
 *
 * Returns 0 on success.
 */
पूर्णांक chsc_scud(u16 cu, u64 *esm, u8 *esm_valid)
अणु
	काष्ठा chsc_scud *scud = chsc_page;
	पूर्णांक ret;

	spin_lock_irq(&chsc_page_lock);
	स_रखो(chsc_page, 0, PAGE_SIZE);
	scud->request.length = SCUD_REQ_LEN;
	scud->request.code = SCUD_REQ_CMD;
	scud->fmt = 0;
	scud->cssid = 0;
	scud->first_cu = cu;
	scud->last_cu = cu;

	ret = chsc(scud);
	अगर (!ret)
		ret = chsc_error_from_response(scud->response.code);

	अगर (!ret && (scud->response.length <= 8 || scud->fmt_resp != 0
			|| !(scud->cudb[0].flags & 0x80)
			|| scud->cudb[0].cu != cu)) अणु

		CIO_MSG_EVENT(2, "chsc: scud failed rc=%04x, L2=%04x "
			"FMT=%04x, cudb.flags=%02x, cudb.cu=%04x",
			scud->response.code, scud->response.length,
			scud->fmt_resp, scud->cudb[0].flags, scud->cudb[0].cu);
		ret = -EINVAL;
	पूर्ण

	अगर (ret)
		जाओ out;

	स_नकल(esm, scud->cudb[0].esm, माप(*esm));
	*esm_valid = scud->cudb[0].esm_valid;
out:
	spin_unlock_irq(&chsc_page_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(chsc_scud);
