<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 *   redistributing this file, you may करो so under either license.
 *
 *   GPL LICENSE SUMMARY
 *
 *   Copyright(c) 2012 Intel Corporation. All rights reserved.
 *   Copyright (C) 2015 EMC Corporation. All Rights Reserved.
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of version 2 of the GNU General Public License as
 *   published by the Free Software Foundation.
 *
 *   BSD LICENSE
 *
 *   Copyright(c) 2012 Intel Corporation. All rights reserved.
 *   Copyright (C) 2015 EMC Corporation. All Rights Reserved.
 *
 *   Redistribution and use in source and binary क्रमms, with or without
 *   modअगरication, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copy
 *       notice, this list of conditions and the following disclaimer in
 *       the करोcumentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to enकरोrse or promote products derived
 *       from this software without specअगरic prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * PCIe NTB Transport Linux driver
 *
 * Contact Inक्रमmation:
 * Jon Mason <jon.mason@पूर्णांकel.com>
 */

काष्ठा ntb_transport_qp;

काष्ठा ntb_transport_client अणु
	काष्ठा device_driver driver;
	पूर्णांक (*probe)(काष्ठा device *client_dev);
	व्योम (*हटाओ)(काष्ठा device *client_dev);
पूर्ण;

पूर्णांक ntb_transport_रेजिस्टर_client(काष्ठा ntb_transport_client *drvr);
व्योम ntb_transport_unरेजिस्टर_client(काष्ठा ntb_transport_client *drvr);
पूर्णांक ntb_transport_रेजिस्टर_client_dev(अक्षर *device_name);
व्योम ntb_transport_unरेजिस्टर_client_dev(अक्षर *device_name);

काष्ठा ntb_queue_handlers अणु
	व्योम (*rx_handler)(काष्ठा ntb_transport_qp *qp, व्योम *qp_data,
			   व्योम *data, पूर्णांक len);
	व्योम (*tx_handler)(काष्ठा ntb_transport_qp *qp, व्योम *qp_data,
			   व्योम *data, पूर्णांक len);
	व्योम (*event_handler)(व्योम *data, पूर्णांक status);
पूर्ण;

अचिन्हित अक्षर ntb_transport_qp_num(काष्ठा ntb_transport_qp *qp);
अचिन्हित पूर्णांक ntb_transport_max_size(काष्ठा ntb_transport_qp *qp);
काष्ठा ntb_transport_qp *
ntb_transport_create_queue(व्योम *data, काष्ठा device *client_dev,
			   स्थिर काष्ठा ntb_queue_handlers *handlers);
व्योम ntb_transport_मुक्त_queue(काष्ठा ntb_transport_qp *qp);
पूर्णांक ntb_transport_rx_enqueue(काष्ठा ntb_transport_qp *qp, व्योम *cb, व्योम *data,
			     अचिन्हित पूर्णांक len);
पूर्णांक ntb_transport_tx_enqueue(काष्ठा ntb_transport_qp *qp, व्योम *cb, व्योम *data,
			     अचिन्हित पूर्णांक len);
व्योम *ntb_transport_rx_हटाओ(काष्ठा ntb_transport_qp *qp, अचिन्हित पूर्णांक *len);
व्योम ntb_transport_link_up(काष्ठा ntb_transport_qp *qp);
व्योम ntb_transport_link_करोwn(काष्ठा ntb_transport_qp *qp);
bool ntb_transport_link_query(काष्ठा ntb_transport_qp *qp);
अचिन्हित पूर्णांक ntb_transport_tx_मुक्त_entry(काष्ठा ntb_transport_qp *qp);
