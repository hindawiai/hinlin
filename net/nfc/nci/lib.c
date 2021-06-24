<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  The NFC Controller Interface is the communication protocol between an
 *  NFC Controller (NFCC) and a Device Host (DH).
 *
 *  Copyright (C) 2011 Texas Instruments, Inc.
 *
 *  Written by Ilan Elias <ilane@ti.com>
 *
 *  Acknowledgements:
 *  This file is based on lib.c, which was written
 *  by Maxim Krasnyansky.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश <net/nfc/nci.h>
#समावेश <net/nfc/nci_core.h>

/* NCI status codes to Unix त्रुटि_सं mapping */
पूर्णांक nci_to_त्रुटि_सं(__u8 code)
अणु
	चयन (code) अणु
	हाल NCI_STATUS_OK:
		वापस 0;

	हाल NCI_STATUS_REJECTED:
		वापस -EBUSY;

	हाल NCI_STATUS_RF_FRAME_CORRUPTED:
		वापस -EBADMSG;

	हाल NCI_STATUS_NOT_INITIALIZED:
		वापस -EHOSTDOWN;

	हाल NCI_STATUS_SYNTAX_ERROR:
	हाल NCI_STATUS_SEMANTIC_ERROR:
	हाल NCI_STATUS_INVALID_PARAM:
	हाल NCI_STATUS_RF_PROTOCOL_ERROR:
	हाल NCI_STATUS_NFCEE_PROTOCOL_ERROR:
		वापस -EPROTO;

	हाल NCI_STATUS_UNKNOWN_GID:
	हाल NCI_STATUS_UNKNOWN_OID:
		वापस -EBADRQC;

	हाल NCI_STATUS_MESSAGE_SIZE_EXCEEDED:
		वापस -EMSGSIZE;

	हाल NCI_STATUS_DISCOVERY_ALREADY_STARTED:
		वापस -EALREADY;

	हाल NCI_STATUS_DISCOVERY_TARGET_ACTIVATION_FAILED:
	हाल NCI_STATUS_NFCEE_INTERFACE_ACTIVATION_FAILED:
		वापस -ECONNREFUSED;

	हाल NCI_STATUS_RF_TRANSMISSION_ERROR:
	हाल NCI_STATUS_NFCEE_TRANSMISSION_ERROR:
		वापस -ECOMM;

	हाल NCI_STATUS_RF_TIMEOUT_ERROR:
	हाल NCI_STATUS_NFCEE_TIMEOUT_ERROR:
		वापस -ETIMEDOUT;

	हाल NCI_STATUS_FAILED:
	शेष:
		वापस -ENOSYS;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(nci_to_त्रुटि_सं);
