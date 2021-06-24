<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Luca Bigliardi (shammash@artha.org).
 */

#समावेश <मानकघोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <libvdeplug.h>
#समावेश <net_user.h>
#समावेश <um_दो_स्मृति.h>
#समावेश "vde.h"

अटल पूर्णांक vde_user_init(व्योम *data, व्योम *dev)
अणु
	काष्ठा vde_data *pri = data;
	VDECONN *conn = शून्य;
	पूर्णांक err = -EINVAL;

	pri->dev = dev;

	conn = vde_खोलो(pri->vde_चयन, pri->descr, pri->args);

	अगर (conn == शून्य) अणु
		err = -त्रुटि_सं;
		prपूर्णांकk(UM_KERN_ERR "vde_user_init: vde_open failed, "
		       "errno = %d\n", त्रुटि_सं);
		वापस err;
	पूर्ण

	prपूर्णांकk(UM_KERN_INFO "vde backend - connection opened\n");

	pri->conn = conn;

	वापस 0;
पूर्ण

अटल पूर्णांक vde_user_खोलो(व्योम *data)
अणु
	काष्ठा vde_data *pri = data;

	अगर (pri->conn != शून्य)
		वापस vde_datafd(pri->conn);

	prपूर्णांकk(UM_KERN_WARNING "vde_open - we have no VDECONN to open");
	वापस -EINVAL;
पूर्ण

अटल व्योम vde_हटाओ(व्योम *data)
अणु
	काष्ठा vde_data *pri = data;

	अगर (pri->conn != शून्य) अणु
		prपूर्णांकk(UM_KERN_INFO "vde backend - closing connection\n");
		vde_बंद(pri->conn);
		pri->conn = शून्य;
		kमुक्त(pri->args);
		pri->args = शून्य;
		वापस;
	पूर्ण

	prपूर्णांकk(UM_KERN_WARNING "vde_remove - we have no VDECONN to remove");
पूर्ण

स्थिर काष्ठा net_user_info vde_user_info = अणु
	.init		= vde_user_init,
	.खोलो		= vde_user_खोलो,
	.बंद	 	= शून्य,
	.हटाओ	 	= vde_हटाओ,
	.add_address	= शून्य,
	.delete_address = शून्य,
	.mtu		= ETH_MAX_PACKET,
	.max_packet	= ETH_MAX_PACKET + ETH_HEADER_OTHER,
पूर्ण;

व्योम vde_init_libstuff(काष्ठा vde_data *vpri, काष्ठा vde_init *init)
अणु
	काष्ठा vde_खोलो_args *args;

	vpri->args = uml_kदो_स्मृति(माप(काष्ठा vde_खोलो_args), UM_GFP_KERNEL);
	अगर (vpri->args == शून्य) अणु
		prपूर्णांकk(UM_KERN_ERR "vde_init_libstuff - vde_open_args "
		       "allocation failed");
		वापस;
	पूर्ण

	args = vpri->args;

	args->port = init->port;
	args->group = init->group;
	args->mode = init->mode ? init->mode : 0700;

	args->port ?  prपूर्णांकk("port %d", args->port) :
		prपूर्णांकk("undefined port");
पूर्ण

पूर्णांक vde_user_पढ़ो(व्योम *conn, व्योम *buf, पूर्णांक len)
अणु
	VDECONN *vconn = conn;
	पूर्णांक rv;

	अगर (vconn == शून्य)
		वापस 0;

	rv = vde_recv(vconn, buf, len, 0);
	अगर (rv < 0) अणु
		अगर (त्रुटि_सं == EAGAIN)
			वापस 0;
		वापस -त्रुटि_सं;
	पूर्ण
	अन्यथा अगर (rv == 0)
		वापस -ENOTCONN;

	वापस rv;
पूर्ण

पूर्णांक vde_user_ग_लिखो(व्योम *conn, व्योम *buf, पूर्णांक len)
अणु
	VDECONN *vconn = conn;

	अगर (vconn == शून्य)
		वापस 0;

	वापस vde_send(vconn, buf, len, 0);
पूर्ण

