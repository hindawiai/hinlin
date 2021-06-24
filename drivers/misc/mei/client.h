<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2003-2018, Intel Corporation. All rights reserved.
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */

#अगर_अघोषित _MEI_CLIENT_H_
#घोषणा _MEI_CLIENT_H_

#समावेश <linux/types.h>
#समावेश <linux/poll.h>
#समावेश <linux/mei.h>

#समावेश "mei_dev.h"

/*
 * reference counting base function
 */
व्योम mei_me_cl_init(काष्ठा mei_me_client *me_cl);
व्योम mei_me_cl_put(काष्ठा mei_me_client *me_cl);
काष्ठा mei_me_client *mei_me_cl_get(काष्ठा mei_me_client *me_cl);

व्योम mei_me_cl_add(काष्ठा mei_device *dev, काष्ठा mei_me_client *me_cl);
व्योम mei_me_cl_del(काष्ठा mei_device *dev, काष्ठा mei_me_client *me_cl);

काष्ठा mei_me_client *mei_me_cl_by_uuid(काष्ठा mei_device *dev,
					स्थिर uuid_le *uuid);
काष्ठा mei_me_client *mei_me_cl_by_id(काष्ठा mei_device *dev, u8 client_id);
काष्ठा mei_me_client *mei_me_cl_by_uuid_id(काष्ठा mei_device *dev,
					   स्थिर uuid_le *uuid, u8 client_id);
व्योम mei_me_cl_rm_by_uuid(काष्ठा mei_device *dev, स्थिर uuid_le *uuid);
व्योम mei_me_cl_rm_by_uuid_id(काष्ठा mei_device *dev,
			     स्थिर uuid_le *uuid, u8 id);
व्योम mei_me_cl_rm_all(काष्ठा mei_device *dev);

/**
 * mei_me_cl_is_active - check whether me client is active in the fw
 *
 * @me_cl: me client
 *
 * Return: true अगर the me client is active in the firmware
 */
अटल अंतरभूत bool mei_me_cl_is_active(स्थिर काष्ठा mei_me_client *me_cl)
अणु
	वापस !list_empty_careful(&me_cl->list);
पूर्ण

/**
 * mei_me_cl_uuid - वापस me client protocol name (uuid)
 *
 * @me_cl: me client
 *
 * Return: me client protocol name
 */
अटल अंतरभूत स्थिर uuid_le *mei_me_cl_uuid(स्थिर काष्ठा mei_me_client *me_cl)
अणु
	वापस &me_cl->props.protocol_name;
पूर्ण

/**
 * mei_me_cl_ver - वापस me client protocol version
 *
 * @me_cl: me client
 *
 * Return: me client protocol version
 */
अटल अंतरभूत u8 mei_me_cl_ver(स्थिर काष्ठा mei_me_client *me_cl)
अणु
	वापस me_cl->props.protocol_version;
पूर्ण

/**
 * mei_me_cl_max_conn - वापस me client max number of connections
 *
 * @me_cl: me client
 *
 * Return: me client max number of connections
 */
अटल अंतरभूत u8 mei_me_cl_max_conn(स्थिर काष्ठा mei_me_client *me_cl)
अणु
	वापस me_cl->props.max_number_of_connections;
पूर्ण

/**
 * mei_me_cl_fixed - वापस me client fixed address, अगर any
 *
 * @me_cl: me client
 *
 * Return: me client fixed address
 */
अटल अंतरभूत u8 mei_me_cl_fixed(स्थिर काष्ठा mei_me_client *me_cl)
अणु
	वापस me_cl->props.fixed_address;
पूर्ण

/**
 * mei_me_cl_vt - वापस me client vtag supported status
 *
 * @me_cl: me client
 *
 * Return: true अगर me client supports vt tagging
 */
अटल अंतरभूत bool mei_me_cl_vt(स्थिर काष्ठा mei_me_client *me_cl)
अणु
	वापस me_cl->props.vt_supported == 1;
पूर्ण

/**
 * mei_me_cl_max_len - वापस me client max msg length
 *
 * @me_cl: me client
 *
 * Return: me client max msg length
 */
अटल अंतरभूत u32 mei_me_cl_max_len(स्थिर काष्ठा mei_me_client *me_cl)
अणु
	वापस me_cl->props.max_msg_length;
पूर्ण

/*
 * MEI IO Functions
 */
व्योम mei_io_cb_मुक्त(काष्ठा mei_cl_cb *priv_cb);

/*
 * MEI Host Client Functions
 */

काष्ठा mei_cl *mei_cl_allocate(काष्ठा mei_device *dev);

पूर्णांक mei_cl_link(काष्ठा mei_cl *cl);
पूर्णांक mei_cl_unlink(काष्ठा mei_cl *cl);

काष्ठा mei_cl *mei_cl_alloc_linked(काष्ठा mei_device *dev);

काष्ठा mei_cl_cb *mei_cl_पढ़ो_cb(काष्ठा mei_cl *cl, स्थिर काष्ठा file *fp);

व्योम mei_cl_add_rd_completed(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb);
व्योम mei_cl_del_rd_completed(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb);

काष्ठा mei_cl_cb *mei_cl_alloc_cb(काष्ठा mei_cl *cl, माप_प्रकार length,
				  क्रमागत mei_cb_file_ops type,
				  स्थिर काष्ठा file *fp);
काष्ठा mei_cl_cb *mei_cl_enqueue_ctrl_wr_cb(काष्ठा mei_cl *cl, माप_प्रकार length,
					    क्रमागत mei_cb_file_ops type,
					    स्थिर काष्ठा file *fp);
पूर्णांक mei_cl_flush_queues(काष्ठा mei_cl *cl, स्थिर काष्ठा file *fp);

काष्ठा mei_cl_vtag *mei_cl_vtag_alloc(काष्ठा file *fp, u8 vtag);
स्थिर काष्ठा file *mei_cl_fp_by_vtag(स्थिर काष्ठा mei_cl *cl, u8 vtag);
पूर्णांक mei_cl_vt_support_check(स्थिर काष्ठा mei_cl *cl);
/*
 *  MEI input output function prototype
 */

/**
 * mei_cl_is_connected - host client is connected
 *
 * @cl: host client
 *
 * Return: true अगर the host client is connected
 */
अटल अंतरभूत bool mei_cl_is_connected(काष्ठा mei_cl *cl)
अणु
	वापस  cl->state == MEI_खाता_CONNECTED;
पूर्ण

/**
 * mei_cl_me_id - me client id
 *
 * @cl: host client
 *
 * Return: me client id or 0 अगर client is not connected
 */
अटल अंतरभूत u8 mei_cl_me_id(स्थिर काष्ठा mei_cl *cl)
अणु
	वापस cl->me_cl ? cl->me_cl->client_id : 0;
पूर्ण

/**
 * mei_cl_mtu - maximal message that client can send and receive
 *
 * @cl: host client
 *
 * Return: mtu or 0 अगर client is not connected
 */
अटल अंतरभूत माप_प्रकार mei_cl_mtu(स्थिर काष्ठा mei_cl *cl)
अणु
	वापस cl->me_cl ? cl->me_cl->props.max_msg_length : 0;
पूर्ण

/**
 * mei_cl_is_fixed_address - check whether the me client uses fixed address
 *
 * @cl: host client
 *
 * Return: true अगर the client is connected and it has fixed me address
 */
अटल अंतरभूत bool mei_cl_is_fixed_address(स्थिर काष्ठा mei_cl *cl)
अणु
	वापस cl->me_cl && cl->me_cl->props.fixed_address;
पूर्ण

/**
 * mei_cl_is_single_recv_buf- check whether the me client
 *       uses single receiving buffer
 *
 * @cl: host client
 *
 * Return: true अगर single_recv_buf == 1; 0 otherwise
 */
अटल अंतरभूत bool mei_cl_is_single_recv_buf(स्थिर काष्ठा mei_cl *cl)
अणु
	वापस cl->me_cl->props.single_recv_buf;
पूर्ण

/**
 * mei_cl_uuid -  client's uuid
 *
 * @cl: host client
 *
 * Return: वापस uuid of connected me client
 */
अटल अंतरभूत स्थिर uuid_le *mei_cl_uuid(स्थिर काष्ठा mei_cl *cl)
अणु
	वापस mei_me_cl_uuid(cl->me_cl);
पूर्ण

/**
 * mei_cl_host_addr - client's host address
 *
 * @cl: host client
 *
 * Return: 0 क्रम fixed address client, host address क्रम dynamic client
 */
अटल अंतरभूत u8 mei_cl_host_addr(स्थिर काष्ठा mei_cl *cl)
अणु
	वापस  mei_cl_is_fixed_address(cl) ? 0 : cl->host_client_id;
पूर्ण

पूर्णांक mei_cl_disconnect(काष्ठा mei_cl *cl);
पूर्णांक mei_cl_irq_disconnect(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb,
			  काष्ठा list_head *cmpl_list);
पूर्णांक mei_cl_connect(काष्ठा mei_cl *cl, काष्ठा mei_me_client *me_cl,
		   स्थिर काष्ठा file *file);
पूर्णांक mei_cl_irq_connect(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb,
		       काष्ठा list_head *cmpl_list);
पूर्णांक mei_cl_पढ़ो_start(काष्ठा mei_cl *cl, माप_प्रकार length, स्थिर काष्ठा file *fp);
sमाप_प्रकार mei_cl_ग_लिखो(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb);
पूर्णांक mei_cl_irq_ग_लिखो(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb,
		     काष्ठा list_head *cmpl_list);

व्योम mei_cl_complete(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb);

व्योम mei_host_client_init(काष्ठा mei_device *dev);

u8 mei_cl_notअगरy_fop2req(क्रमागत mei_cb_file_ops fop);
क्रमागत mei_cb_file_ops mei_cl_notअगरy_req2fop(u8 request);
पूर्णांक mei_cl_notअगरy_request(काष्ठा mei_cl *cl,
			  स्थिर काष्ठा file *file, u8 request);
पूर्णांक mei_cl_irq_notअगरy(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb,
		      काष्ठा list_head *cmpl_list);
पूर्णांक mei_cl_notअगरy_get(काष्ठा mei_cl *cl, bool block, bool *notअगरy_ev);
व्योम mei_cl_notअगरy(काष्ठा mei_cl *cl);

व्योम mei_cl_all_disconnect(काष्ठा mei_device *dev);

पूर्णांक mei_cl_irq_dma_map(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb,
		       काष्ठा list_head *cmpl_list);
पूर्णांक mei_cl_irq_dma_unmap(काष्ठा mei_cl *cl, काष्ठा mei_cl_cb *cb,
			 काष्ठा list_head *cmpl_list);
पूर्णांक mei_cl_dma_alloc_and_map(काष्ठा mei_cl *cl, स्थिर काष्ठा file *fp,
			     u8 buffer_id, माप_प्रकार size);
पूर्णांक mei_cl_dma_unmap(काष्ठा mei_cl *cl, स्थिर काष्ठा file *fp);

#घोषणा MEI_CL_FMT "cl:host=%02d me=%02d "
#घोषणा MEI_CL_PRM(cl) (cl)->host_client_id, mei_cl_me_id(cl)

#घोषणा cl_dbg(dev, cl, क्रमmat, arg...) \
	dev_dbg((dev)->dev, MEI_CL_FMT क्रमmat, MEI_CL_PRM(cl), ##arg)

#घोषणा cl_warn(dev, cl, क्रमmat, arg...) \
	dev_warn((dev)->dev, MEI_CL_FMT क्रमmat, MEI_CL_PRM(cl), ##arg)

#घोषणा cl_err(dev, cl, क्रमmat, arg...) \
	dev_err((dev)->dev, MEI_CL_FMT क्रमmat, MEI_CL_PRM(cl), ##arg)

#पूर्ण_अगर /* _MEI_CLIENT_H_ */
