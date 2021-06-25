<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * TFRC library initialisation
 *
 * Copyright (c) 2007 The University of Aberdeen, Scotland, UK
 * Copyright (c) 2007 Arnalकरो Carvalho de Melo <acme@redhat.com>
 */
#समावेश <linux/moduleparam.h>
#समावेश "tfrc.h"

#अगर_घोषित CONFIG_IP_DCCP_TFRC_DEBUG
bool tfrc_debug;
module_param(tfrc_debug, bool, 0644);
MODULE_PARM_DESC(tfrc_debug, "Enable TFRC debug messages");
#पूर्ण_अगर

पूर्णांक __init tfrc_lib_init(व्योम)
अणु
	पूर्णांक rc = tfrc_li_init();

	अगर (rc)
		जाओ out;

	rc = tfrc_tx_packet_history_init();
	अगर (rc)
		जाओ out_मुक्त_loss_पूर्णांकervals;

	rc = tfrc_rx_packet_history_init();
	अगर (rc)
		जाओ out_मुक्त_tx_history;
	वापस 0;

out_मुक्त_tx_history:
	tfrc_tx_packet_history_निकास();
out_मुक्त_loss_पूर्णांकervals:
	tfrc_li_निकास();
out:
	वापस rc;
पूर्ण

व्योम tfrc_lib_निकास(व्योम)
अणु
	tfrc_rx_packet_history_निकास();
	tfrc_tx_packet_history_निकास();
	tfrc_li_निकास();
पूर्ण
