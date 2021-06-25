<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Thunderbolt driver - control channel and configuration commands
 *
 * Copyright (c) 2014 Andreas Noever <andreas.noever@gmail.com>
 * Copyright (C) 2018, Intel Corporation
 */

#अगर_अघोषित _TB_CFG
#घोषणा _TB_CFG

#समावेश <linux/kref.h>
#समावेश <linux/thunderbolt.h>

#समावेश "nhi.h"
#समावेश "tb_msgs.h"

/* control channel */
काष्ठा tb_ctl;

प्रकार bool (*event_cb)(व्योम *data, क्रमागत tb_cfg_pkg_type type,
			 स्थिर व्योम *buf, माप_प्रकार size);

काष्ठा tb_ctl *tb_ctl_alloc(काष्ठा tb_nhi *nhi, पूर्णांक समयout_msec, event_cb cb,
			    व्योम *cb_data);
व्योम tb_ctl_start(काष्ठा tb_ctl *ctl);
व्योम tb_ctl_stop(काष्ठा tb_ctl *ctl);
व्योम tb_ctl_मुक्त(काष्ठा tb_ctl *ctl);

/* configuration commands */

काष्ठा tb_cfg_result अणु
	u64 response_route;
	u32 response_port; /*
			    * If err = 1 then this is the port that send the
			    * error.
			    * If err = 0 and अगर this was a cfg_पढ़ो/ग_लिखो then
			    * this is the the upstream port of the responding
			    * चयन.
			    * Otherwise the field is set to zero.
			    */
	पूर्णांक err; /* negative errors, 0 क्रम success, 1 क्रम tb errors */
	क्रमागत tb_cfg_error tb_error; /* valid अगर err == 1 */
पूर्ण;

काष्ठा ctl_pkg अणु
	काष्ठा tb_ctl *ctl;
	व्योम *buffer;
	काष्ठा ring_frame frame;
पूर्ण;

/**
 * काष्ठा tb_cfg_request - Control channel request
 * @kref: Reference count
 * @ctl: Poपूर्णांकer to the control channel काष्ठाure. Only set when the
 *	 request is queued.
 * @request_size: Size of the request packet (in bytes)
 * @request_type: Type of the request packet
 * @response: Response is stored here
 * @response_size: Maximum size of one response packet
 * @response_type: Expected type of the response packet
 * @npackets: Number of packets expected to be वापसed with this request
 * @match: Function used to match the incoming packet
 * @copy: Function used to copy the incoming packet to @response
 * @callback: Callback called when the request is finished successfully
 * @callback_data: Data to be passed to @callback
 * @flags: Flags क्रम the request
 * @work: Work item used to complete the request
 * @result: Result after the request has been completed
 * @list: Requests are queued using this field
 *
 * An arbitrary request over Thunderbolt control channel. For standard
 * control channel message, one should use tb_cfg_पढ़ो/ग_लिखो() and
 * मित्रs अगर possible.
 */
काष्ठा tb_cfg_request अणु
	काष्ठा kref kref;
	काष्ठा tb_ctl *ctl;
	स्थिर व्योम *request;
	माप_प्रकार request_size;
	क्रमागत tb_cfg_pkg_type request_type;
	व्योम *response;
	माप_प्रकार response_size;
	क्रमागत tb_cfg_pkg_type response_type;
	माप_प्रकार npackets;
	bool (*match)(स्थिर काष्ठा tb_cfg_request *req,
		      स्थिर काष्ठा ctl_pkg *pkg);
	bool (*copy)(काष्ठा tb_cfg_request *req, स्थिर काष्ठा ctl_pkg *pkg);
	व्योम (*callback)(व्योम *callback_data);
	व्योम *callback_data;
	अचिन्हित दीर्घ flags;
	काष्ठा work_काष्ठा work;
	काष्ठा tb_cfg_result result;
	काष्ठा list_head list;
पूर्ण;

#घोषणा TB_CFG_REQUEST_ACTIVE		0
#घोषणा TB_CFG_REQUEST_CANCELED		1

काष्ठा tb_cfg_request *tb_cfg_request_alloc(व्योम);
व्योम tb_cfg_request_get(काष्ठा tb_cfg_request *req);
व्योम tb_cfg_request_put(काष्ठा tb_cfg_request *req);
पूर्णांक tb_cfg_request(काष्ठा tb_ctl *ctl, काष्ठा tb_cfg_request *req,
		   व्योम (*callback)(व्योम *), व्योम *callback_data);
व्योम tb_cfg_request_cancel(काष्ठा tb_cfg_request *req, पूर्णांक err);
काष्ठा tb_cfg_result tb_cfg_request_sync(काष्ठा tb_ctl *ctl,
			काष्ठा tb_cfg_request *req, पूर्णांक समयout_msec);

अटल अंतरभूत u64 tb_cfg_get_route(स्थिर काष्ठा tb_cfg_header *header)
अणु
	वापस (u64) header->route_hi << 32 | header->route_lo;
पूर्ण

अटल अंतरभूत काष्ठा tb_cfg_header tb_cfg_make_header(u64 route)
अणु
	काष्ठा tb_cfg_header header = अणु
		.route_hi = route >> 32,
		.route_lo = route,
	पूर्ण;
	/* check क्रम overflow, route_hi is not 32 bits! */
	WARN_ON(tb_cfg_get_route(&header) != route);
	वापस header;
पूर्ण

पूर्णांक tb_cfg_ack_plug(काष्ठा tb_ctl *ctl, u64 route, u32 port, bool unplug);
काष्ठा tb_cfg_result tb_cfg_reset(काष्ठा tb_ctl *ctl, u64 route);
काष्ठा tb_cfg_result tb_cfg_पढ़ो_raw(काष्ठा tb_ctl *ctl, व्योम *buffer,
				     u64 route, u32 port,
				     क्रमागत tb_cfg_space space, u32 offset,
				     u32 length, पूर्णांक समयout_msec);
काष्ठा tb_cfg_result tb_cfg_ग_लिखो_raw(काष्ठा tb_ctl *ctl, स्थिर व्योम *buffer,
				      u64 route, u32 port,
				      क्रमागत tb_cfg_space space, u32 offset,
				      u32 length, पूर्णांक समयout_msec);
पूर्णांक tb_cfg_पढ़ो(काष्ठा tb_ctl *ctl, व्योम *buffer, u64 route, u32 port,
		क्रमागत tb_cfg_space space, u32 offset, u32 length);
पूर्णांक tb_cfg_ग_लिखो(काष्ठा tb_ctl *ctl, स्थिर व्योम *buffer, u64 route, u32 port,
		 क्रमागत tb_cfg_space space, u32 offset, u32 length);
पूर्णांक tb_cfg_get_upstream_port(काष्ठा tb_ctl *ctl, u64 route);


#पूर्ण_अगर
