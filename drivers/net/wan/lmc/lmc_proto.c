<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
 /*
  * Copyright (c) 1997-2000 LAN Media Corporation (LMC)
  * All rights reserved.  www.lanmedia.com
  *
  * This code is written by:
  * Andrew Stanley-Jones (asj@cban.com)
  * Rob Braun (bbraun@vix.com),
  * Michael Graff (explorer@vix.com) and
  * Matt Thomas (matt@3am-software.com).
  *
  * With Help By:
  * David Boggs
  * Ron Crane
  * Allan Cox
  *
  * Driver क्रम the LanMedia LMC5200, LMC5245, LMC1000, LMC1200 cards.
  */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/inet.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/processor.h>             /* Processor type क्रम cache alignment. */
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <linux/smp.h>

#समावेश "lmc.h"
#समावेश "lmc_var.h"
#समावेश "lmc_debug.h"
#समावेश "lmc_ioctl.h"
#समावेश "lmc_proto.h"

// attach
व्योम lmc_proto_attach(lmc_softc_t *sc) /*FOLD00*/
अणु
    अगर (sc->अगर_type == LMC_NET) अणु
            काष्ठा net_device *dev = sc->lmc_device;
            /*
	     * They set a few basics because they करोn't use HDLC
             */
            dev->flags |= IFF_POINTOPOINT;
            dev->hard_header_len = 0;
            dev->addr_len = 0;
        पूर्ण
पूर्ण

पूर्णांक lmc_proto_ioctl(lmc_softc_t *sc, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	अगर (sc->अगर_type == LMC_PPP)
		वापस hdlc_ioctl(sc->lmc_device, अगरr, cmd);
	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक lmc_proto_खोलो(lmc_softc_t *sc)
अणु
	पूर्णांक ret = 0;

	अगर (sc->अगर_type == LMC_PPP) अणु
		ret = hdlc_खोलो(sc->lmc_device);
		अगर (ret < 0)
			prपूर्णांकk(KERN_WARNING "%s: HDLC open failed: %d\n",
			       sc->name, ret);
	पूर्ण
	वापस ret;
पूर्ण

व्योम lmc_proto_बंद(lmc_softc_t *sc)
अणु
	अगर (sc->अगर_type == LMC_PPP)
		hdlc_बंद(sc->lmc_device);
पूर्ण

__be16 lmc_proto_type(lmc_softc_t *sc, काष्ठा sk_buff *skb) /*FOLD00*/
अणु
    चयन(sc->अगर_type)अणु
    हाल LMC_PPP:
	    वापस hdlc_type_trans(skb, sc->lmc_device);
    हाल LMC_NET:
        वापस htons(ETH_P_802_2);
    हाल LMC_RAW: /* Packet type क्रम skbuff kind of useless */
        वापस htons(ETH_P_802_2);
    शेष:
        prपूर्णांकk(KERN_WARNING "%s: No protocol set for this interface, assuming 802.2 (which is wrong!!)\n", sc->name);
        वापस htons(ETH_P_802_2);
    पूर्ण
पूर्ण

व्योम lmc_proto_netअगर(lmc_softc_t *sc, काष्ठा sk_buff *skb) /*FOLD00*/
अणु
    चयन(sc->अगर_type)अणु
    हाल LMC_PPP:
    हाल LMC_NET:
    शेष:
        netअगर_rx(skb);
        अवरोध;
    हाल LMC_RAW:
        अवरोध;
    पूर्ण
पूर्ण
