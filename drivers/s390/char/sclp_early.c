<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SCLP early driver
 *
 * Copyright IBM Corp. 2013
 */

#घोषणा KMSG_COMPONENT "sclp_early"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/memblock.h>
#समावेश <यंत्र/ctl_reg.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/ipl.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/facility.h>
#समावेश "sclp_sdias.h"
#समावेश "sclp.h"

अटल काष्ठा sclp_ipl_info sclp_ipl_info;

काष्ठा sclp_info sclp;
EXPORT_SYMBOL(sclp);

अटल व्योम __init sclp_early_facilities_detect(व्योम)
अणु
	काष्ठा sclp_core_entry *cpue;
	काष्ठा पढ़ो_info_sccb *sccb;
	u16 boot_cpu_address, cpu;

	sccb = sclp_early_get_info();
	अगर (!sccb)
		वापस;

	sclp.facilities = sccb->facilities;
	sclp.has_sprp = !!(sccb->fac84 & 0x02);
	sclp.has_core_type = !!(sccb->fac84 & 0x01);
	sclp.has_gsls = !!(sccb->fac85 & 0x80);
	sclp.has_64bscao = !!(sccb->fac116 & 0x80);
	sclp.has_cmma = !!(sccb->fac116 & 0x40);
	sclp.has_esca = !!(sccb->fac116 & 0x08);
	sclp.has_pfmfi = !!(sccb->fac117 & 0x40);
	sclp.has_ibs = !!(sccb->fac117 & 0x20);
	sclp.has_gisaf = !!(sccb->fac118 & 0x08);
	sclp.has_hvs = !!(sccb->fac119 & 0x80);
	sclp.has_kss = !!(sccb->fac98 & 0x01);
	sclp.has_sipl = !!(sccb->cbl & 0x4000);
	अगर (sccb->fac85 & 0x02)
		S390_lowcore.machine_flags |= MACHINE_FLAG_ESOP;
	अगर (sccb->fac91 & 0x40)
		S390_lowcore.machine_flags |= MACHINE_FLAG_TLB_GUEST;
	अगर (sccb->cpuoff > 134)
		sclp.has_diag318 = !!(sccb->byte_134 & 0x80);
	sclp.rnmax = sccb->rnmax ? sccb->rnmax : sccb->rnmax2;
	sclp.rzm = sccb->rnsize ? sccb->rnsize : sccb->rnsize2;
	sclp.rzm <<= 20;
	sclp.ibc = sccb->ibc;

	अगर (sccb->hamaxघात && sccb->hamaxघात < 64)
		sclp.hamax = (1UL << sccb->hamaxघात) - 1;
	अन्यथा
		sclp.hamax = U64_MAX;

	अगर (!sccb->hcpua) अणु
		अगर (MACHINE_IS_VM)
			sclp.max_cores = 64;
		अन्यथा
			sclp.max_cores = sccb->ncpurl;
	पूर्ण अन्यथा अणु
		sclp.max_cores = sccb->hcpua + 1;
	पूर्ण

	boot_cpu_address = stap();
	cpue = (व्योम *)sccb + sccb->cpuoff;
	क्रम (cpu = 0; cpu < sccb->ncpurl; cpue++, cpu++) अणु
		अगर (boot_cpu_address != cpue->core_id)
			जारी;
		sclp.has_siअगर = cpue->siअगर;
		sclp.has_sigpअगर = cpue->sigpअगर;
		sclp.has_sief2 = cpue->sief2;
		sclp.has_gpere = cpue->gpere;
		sclp.has_ib = cpue->ib;
		sclp.has_cei = cpue->cei;
		sclp.has_skey = cpue->skey;
		अवरोध;
	पूर्ण

	/* Save IPL inक्रमmation */
	sclp_ipl_info.is_valid = 1;
	अगर (sccb->fac91 & 0x2)
		sclp_ipl_info.has_dump = 1;
	स_नकल(&sclp_ipl_info.loadparm, &sccb->loadparm, LOADPARM_LEN);

	अगर (sccb->hsa_size)
		sclp.hsa_size = (sccb->hsa_size - 1) * PAGE_SIZE;
	sclp.mtid = (sccb->fac42 & 0x80) ? (sccb->fac42 & 31) : 0;
	sclp.mtid_cp = (sccb->fac42 & 0x80) ? (sccb->fac43 & 31) : 0;
	sclp.mtid_prev = (sccb->fac42 & 0x80) ? (sccb->fac66 & 31) : 0;

	sclp.hmfai = sccb->hmfai;
	sclp.has_dirq = !!(sccb->cpudirq & 0x80);
पूर्ण

/*
 * This function will be called after sclp_early_facilities_detect(), which माला_लो
 * called from early.c code. The sclp_early_facilities_detect() function retrieves
 * and saves the IPL inक्रमmation.
 */
व्योम __init sclp_early_get_ipl_info(काष्ठा sclp_ipl_info *info)
अणु
	*info = sclp_ipl_info;
पूर्ण

पूर्णांक __init sclp_early_get_core_info(काष्ठा sclp_core_info *info)
अणु
	काष्ठा पढ़ो_cpu_info_sccb *sccb;
	पूर्णांक length = test_facility(140) ? EXT_SCCB_READ_CPU : PAGE_SIZE;
	पूर्णांक rc = 0;

	अगर (!SCLP_HAS_CPU_INFO)
		वापस -EOPNOTSUPP;

	sccb = memblock_alloc_low(length, PAGE_SIZE);
	अगर (!sccb)
		वापस -ENOMEM;

	स_रखो(sccb, 0, length);
	sccb->header.length = length;
	sccb->header.control_mask[2] = 0x80;
	अगर (sclp_early_cmd(SCLP_CMDW_READ_CPU_INFO, sccb)) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण
	अगर (sccb->header.response_code != 0x0010) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण
	sclp_fill_core_info(info, sccb);
out:
	memblock_मुक्त_early((अचिन्हित दीर्घ)sccb, length);
	वापस rc;
पूर्ण

अटल व्योम __init sclp_early_console_detect(काष्ठा init_sccb *sccb)
अणु
	अगर (sccb->header.response_code != 0x20)
		वापस;

	अगर (sclp_early_con_check_vt220(sccb))
		sclp.has_vt220 = 1;

	अगर (sclp_early_con_check_linemode(sccb))
		sclp.has_linemode = 1;
पूर्ण

व्योम __init sclp_early_detect(व्योम)
अणु
	व्योम *sccb = sclp_early_sccb;

	sclp_early_facilities_detect();

	/*
	 * Turn off SCLP event notअगरications.  Also save remote masks in the
	 * sccb.  These are sufficient to detect sclp console capabilities.
	 */
	sclp_early_set_event_mask(sccb, 0, 0);
	sclp_early_console_detect(sccb);
पूर्ण
