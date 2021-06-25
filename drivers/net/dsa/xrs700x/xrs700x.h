<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regmap.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश <uapi/linux/अगर_link.h>

काष्ठा xrs700x_info अणु
	अचिन्हित पूर्णांक id;
	स्थिर अक्षर *name;
	माप_प्रकार num_ports;
पूर्ण;

बाह्य स्थिर काष्ठा xrs700x_info xrs7003e_info;
बाह्य स्थिर काष्ठा xrs700x_info xrs7003f_info;
बाह्य स्थिर काष्ठा xrs700x_info xrs7004e_info;
बाह्य स्थिर काष्ठा xrs700x_info xrs7004f_info;

काष्ठा xrs700x_port अणु
	काष्ठा mutex mib_mutex; /* protects mib_data */
	u64 *mib_data;
	काष्ठा rtnl_link_stats64 stats64;
	काष्ठा u64_stats_sync syncp;
पूर्ण;

काष्ठा xrs700x अणु
	काष्ठा dsa_चयन *ds;
	काष्ठा device *dev;
	व्योम *priv;
	काष्ठा regmap *regmap;
	काष्ठा regmap_field *ps_क्रमward;
	काष्ठा regmap_field *ps_management;
	काष्ठा regmap_field *ps_sel_speed;
	काष्ठा regmap_field *ps_cur_speed;
	काष्ठा delayed_work mib_work;
	काष्ठा xrs700x_port *ports;
पूर्ण;

काष्ठा xrs700x *xrs700x_चयन_alloc(काष्ठा device *base, व्योम *devpriv);
पूर्णांक xrs700x_चयन_रेजिस्टर(काष्ठा xrs700x *priv);
व्योम xrs700x_चयन_हटाओ(काष्ठा xrs700x *priv);
