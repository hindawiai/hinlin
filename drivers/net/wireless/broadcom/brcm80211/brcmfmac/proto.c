<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2013 Broadcom Corporation
 */


 #समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>

#समावेश <brcmu_wअगरi.h>
#समावेश "core.h"
#समावेश "bus.h"
#समावेश "debug.h"
#समावेश "proto.h"
#समावेश "bcdc.h"
#समावेश "msgbuf.h"


पूर्णांक brcmf_proto_attach(काष्ठा brcmf_pub *drvr)
अणु
	काष्ठा brcmf_proto *proto;

	brcmf_dbg(TRACE, "Enter\n");

	proto = kzalloc(माप(*proto), GFP_ATOMIC);
	अगर (!proto)
		जाओ fail;

	drvr->proto = proto;

	अगर (drvr->bus_अगर->proto_type == BRCMF_PROTO_BCDC) अणु
		अगर (brcmf_proto_bcdc_attach(drvr))
			जाओ fail;
	पूर्ण अन्यथा अगर (drvr->bus_अगर->proto_type == BRCMF_PROTO_MSGBUF) अणु
		अगर (brcmf_proto_msgbuf_attach(drvr))
			जाओ fail;
	पूर्ण अन्यथा अणु
		bphy_err(drvr, "Unsupported proto type %d\n",
			 drvr->bus_अगर->proto_type);
		जाओ fail;
	पूर्ण
	अगर (!proto->tx_queue_data || (proto->hdrpull == शून्य) ||
	    (proto->query_dcmd == शून्य) || (proto->set_dcmd == शून्य) ||
	    (proto->configure_addr_mode == शून्य) ||
	    (proto->delete_peer == शून्य) || (proto->add_tdls_peer == शून्य) ||
	    (proto->debugfs_create == शून्य)) अणु
		bphy_err(drvr, "Not all proto handlers have been installed\n");
		जाओ fail;
	पूर्ण
	वापस 0;

fail:
	kमुक्त(proto);
	drvr->proto = शून्य;
	वापस -ENOMEM;
पूर्ण

व्योम brcmf_proto_detach(काष्ठा brcmf_pub *drvr)
अणु
	brcmf_dbg(TRACE, "Enter\n");

	अगर (drvr->proto) अणु
		अगर (drvr->bus_अगर->proto_type == BRCMF_PROTO_BCDC)
			brcmf_proto_bcdc_detach(drvr);
		अन्यथा अगर (drvr->bus_अगर->proto_type == BRCMF_PROTO_MSGBUF)
			brcmf_proto_msgbuf_detach(drvr);
		kमुक्त(drvr->proto);
		drvr->proto = शून्य;
	पूर्ण
पूर्ण
