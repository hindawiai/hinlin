<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * cec-priv.h - HDMI Consumer Electronics Control पूर्णांकernal header
 *
 * Copyright 2016 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _CEC_PRIV_H
#घोषणा _CEC_PRIV_H

#समावेश <linux/cec-funcs.h>
#समावेश <media/cec-notअगरier.h>

#घोषणा dprपूर्णांकk(lvl, fmt, arg...)					\
	करो अणु								\
		अगर (lvl <= cec_debug)					\
			pr_info("cec-%s: " fmt, adap->name, ## arg);	\
	पूर्ण जबतक (0)

/* devnode to cec_adapter */
#घोषणा to_cec_adapter(node) container_of(node, काष्ठा cec_adapter, devnode)

अटल अंतरभूत bool msg_is_raw(स्थिर काष्ठा cec_msg *msg)
अणु
	वापस msg->flags & CEC_MSG_FL_RAW;
पूर्ण

/* cec-core.c */
बाह्य पूर्णांक cec_debug;
पूर्णांक cec_get_device(काष्ठा cec_devnode *devnode);
व्योम cec_put_device(काष्ठा cec_devnode *devnode);

/* cec-adap.c */
पूर्णांक cec_monitor_all_cnt_inc(काष्ठा cec_adapter *adap);
व्योम cec_monitor_all_cnt_dec(काष्ठा cec_adapter *adap);
पूर्णांक cec_monitor_pin_cnt_inc(काष्ठा cec_adapter *adap);
व्योम cec_monitor_pin_cnt_dec(काष्ठा cec_adapter *adap);
पूर्णांक cec_adap_status(काष्ठा seq_file *file, व्योम *priv);
पूर्णांक cec_thपढ़ो_func(व्योम *_adap);
व्योम __cec_s_phys_addr(काष्ठा cec_adapter *adap, u16 phys_addr, bool block);
पूर्णांक __cec_s_log_addrs(काष्ठा cec_adapter *adap,
		      काष्ठा cec_log_addrs *log_addrs, bool block);
पूर्णांक cec_transmit_msg_fh(काष्ठा cec_adapter *adap, काष्ठा cec_msg *msg,
			काष्ठा cec_fh *fh, bool block);
व्योम cec_queue_event_fh(काष्ठा cec_fh *fh,
			स्थिर काष्ठा cec_event *new_ev, u64 ts);

/* cec-api.c */
बाह्य स्थिर काष्ठा file_operations cec_devnode_fops;

#पूर्ण_अगर
