<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Luca Bigliardi (shammash@artha.org).
 *
 * Transport usage:
 *  ethN=vde,<vde_चयन>,<mac addr>,<port>,<group>,<mode>,<description>
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <net_kern.h>
#समावेश <net_user.h>
#समावेश "vde.h"

अटल व्योम vde_init(काष्ठा net_device *dev, व्योम *data)
अणु
	काष्ठा vde_init *init = data;
	काष्ठा uml_net_निजी *pri;
	काष्ठा vde_data *vpri;

	pri = netdev_priv(dev);
	vpri = (काष्ठा vde_data *) pri->user;

	vpri->vde_चयन = init->vde_चयन;
	vpri->descr = init->descr ? init->descr : "UML vde_transport";
	vpri->args = शून्य;
	vpri->conn = शून्य;
	vpri->dev = dev;

	prपूर्णांकk("vde backend - %s, ", vpri->vde_चयन ?
	       vpri->vde_चयन : "(default socket)");

	vde_init_libstuff(vpri, init);

	prपूर्णांकk("\n");
पूर्ण

अटल पूर्णांक vde_पढ़ो(पूर्णांक fd, काष्ठा sk_buff *skb, काष्ठा uml_net_निजी *lp)
अणु
	काष्ठा vde_data *pri = (काष्ठा vde_data *) &lp->user;

	अगर (pri->conn != शून्य)
		वापस vde_user_पढ़ो(pri->conn, skb_mac_header(skb),
				     skb->dev->mtu + ETH_HEADER_OTHER);

	prपूर्णांकk(KERN_ERR "vde_read - we have no VDECONN to read from");
	वापस -EBADF;
पूर्ण

अटल पूर्णांक vde_ग_लिखो(पूर्णांक fd, काष्ठा sk_buff *skb, काष्ठा uml_net_निजी *lp)
अणु
	काष्ठा vde_data *pri = (काष्ठा vde_data *) &lp->user;

	अगर (pri->conn != शून्य)
		वापस vde_user_ग_लिखो((व्योम *)pri->conn, skb->data,
				      skb->len);

	prपूर्णांकk(KERN_ERR "vde_write - we have no VDECONN to write to");
	वापस -EBADF;
पूर्ण

अटल स्थिर काष्ठा net_kern_info vde_kern_info = अणु
	.init			= vde_init,
	.protocol		= eth_protocol,
	.पढ़ो			= vde_पढ़ो,
	.ग_लिखो			= vde_ग_लिखो,
पूर्ण;

अटल पूर्णांक vde_setup(अक्षर *str, अक्षर **mac_out, व्योम *data)
अणु
	काष्ठा vde_init *init = data;
	अक्षर *reमुख्य, *port_str = शून्य, *mode_str = शून्य, *last;

	*init = ((काष्ठा vde_init)
		अणु .vde_चयन		= शून्य,
		  .descr		= शून्य,
		  .port			= 0,
		  .group		= शून्य,
		  .mode			= 0 पूर्ण);

	reमुख्य = split_अगर_spec(str, &init->vde_चयन, mac_out, &port_str,
				&init->group, &mode_str, &init->descr, शून्य);

	अगर (reमुख्य != शून्य)
		prपूर्णांकk(KERN_WARNING "vde_setup - Ignoring extra data :"
		       "'%s'\n", reमुख्य);

	अगर (port_str != शून्य) अणु
		init->port = simple_म_से_अदीर्घ(port_str, &last, 10);
		अगर ((*last != '\0') || (last == port_str)) अणु
			prपूर्णांकk(KERN_ERR "vde_setup - Bad port : '%s'\n",
						port_str);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (mode_str != शून्य) अणु
		init->mode = simple_म_से_अदीर्घ(mode_str, &last, 8);
		अगर ((*last != '\0') || (last == mode_str)) अणु
			prपूर्णांकk(KERN_ERR "vde_setup - Bad mode : '%s'\n",
						mode_str);
			वापस 0;
		पूर्ण
	पूर्ण

	prपूर्णांकk(KERN_INFO "Configured vde device: %s\n", init->vde_चयन ?
	       init->vde_चयन : "(default socket)");

	वापस 1;
पूर्ण

अटल काष्ठा transport vde_transport = अणु
	.list 		= LIST_HEAD_INIT(vde_transport.list),
	.name 		= "vde",
	.setup  	= vde_setup,
	.user 		= &vde_user_info,
	.kern 		= &vde_kern_info,
	.निजी_size 	= माप(काष्ठा vde_data),
	.setup_size 	= माप(काष्ठा vde_init),
पूर्ण;

अटल पूर्णांक रेजिस्टर_vde(व्योम)
अणु
	रेजिस्टर_transport(&vde_transport);
	वापस 0;
पूर्ण

late_initcall(रेजिस्टर_vde);
