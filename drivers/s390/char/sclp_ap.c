<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * s390 crypto adapter related sclp functions.
 *
 * Copyright IBM Corp. 2020
 */
#घोषणा KMSG_COMPONENT "sclp_cmd"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/sclp.h>
#समावेश "sclp.h"

#घोषणा SCLP_CMDW_CONFIGURE_AP			0x001f0001
#घोषणा SCLP_CMDW_DECONFIGURE_AP		0x001e0001

काष्ठा ap_cfg_sccb अणु
	काष्ठा sccb_header header;
पूर्ण __packed;

अटल पूर्णांक करो_ap_configure(sclp_cmdw_t cmd, u32 apid)
अणु
	काष्ठा ap_cfg_sccb *sccb;
	पूर्णांक rc;

	अगर (!SCLP_HAS_AP_RECONFIG)
		वापस -EOPNOTSUPP;

	sccb = (काष्ठा ap_cfg_sccb *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!sccb)
		वापस -ENOMEM;

	sccb->header.length = PAGE_SIZE;
	cmd |= (apid & 0xFF) << 8;
	rc = sclp_sync_request(cmd, sccb);
	अगर (rc)
		जाओ out;
	चयन (sccb->header.response_code) अणु
	हाल 0x0020: हाल 0x0120: हाल 0x0440: हाल 0x0450:
		अवरोध;
	शेष:
		pr_warn("configure AP adapter %u failed: cmd=0x%08x response=0x%04x\n",
			apid, cmd, sccb->header.response_code);
		rc = -EIO;
		अवरोध;
	पूर्ण
out:
	मुक्त_page((अचिन्हित दीर्घ) sccb);
	वापस rc;
पूर्ण

पूर्णांक sclp_ap_configure(u32 apid)
अणु
	वापस करो_ap_configure(SCLP_CMDW_CONFIGURE_AP, apid);
पूर्ण
EXPORT_SYMBOL(sclp_ap_configure);

पूर्णांक sclp_ap_deconfigure(u32 apid)
अणु
	वापस करो_ap_configure(SCLP_CMDW_DECONFIGURE_AP, apid);
पूर्ण
EXPORT_SYMBOL(sclp_ap_deconfigure);
