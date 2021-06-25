<शैली गुरु>
/* bnx2fc_debug.c: QLogic Linux FCoE offload driver.
 * Handles operations such as session offload/upload etc, and manages
 * session resources such as connection id and qp resources.
 *
 * Copyright (c) 2008-2013 Broadcom Corporation
 * Copyright (c) 2014-2016 QLogic Corporation
 * Copyright (c) 2016-2017 Cavium Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 */

#समावेश "bnx2fc.h"

व्योम BNX2FC_IO_DBG(स्थिर काष्ठा bnx2fc_cmd *io_req, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (likely(!(bnx2fc_debug_level & LOG_IO)))
		वापस;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (io_req && io_req->port && io_req->port->lport &&
	    io_req->port->lport->host)
		shost_prपूर्णांकk(KERN_INFO, io_req->port->lport->host,
			     PFX "xid:0x%x %pV",
			     io_req->xid, &vaf);
	अन्यथा
		pr_info("NULL %pV", &vaf);

	बहु_पूर्ण(args);
पूर्ण

व्योम BNX2FC_TGT_DBG(स्थिर काष्ठा bnx2fc_rport *tgt, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (likely(!(bnx2fc_debug_level & LOG_TGT)))
		वापस;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (tgt && tgt->port && tgt->port->lport && tgt->port->lport->host &&
	    tgt->rport)
		shost_prपूर्णांकk(KERN_INFO, tgt->port->lport->host,
			     PFX "port:%x %pV",
			     tgt->rport->port_id, &vaf);
	अन्यथा
		pr_info("NULL %pV", &vaf);

	बहु_पूर्ण(args);
पूर्ण

व्योम BNX2FC_HBA_DBG(स्थिर काष्ठा fc_lport *lport, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (likely(!(bnx2fc_debug_level & LOG_HBA)))
		वापस;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (lport && lport->host)
		shost_prपूर्णांकk(KERN_INFO, lport->host, PFX "%pV", &vaf);
	अन्यथा
		pr_info("NULL %pV", &vaf);

	बहु_पूर्ण(args);
पूर्ण
