<शैली गुरु>
#अगर_अघोषित NF_CONNTRACK_BRIDGE_
#घोषणा NF_CONNTRACK_BRIDGE_

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <uapi/linux/अगर_ether.h>

काष्ठा nf_hook_ops;

काष्ठा nf_ct_bridge_info अणु
	काष्ठा nf_hook_ops	*ops;
	अचिन्हित पूर्णांक		ops_size;
	काष्ठा module		*me;
पूर्ण;

व्योम nf_ct_bridge_रेजिस्टर(काष्ठा nf_ct_bridge_info *info);
व्योम nf_ct_bridge_unरेजिस्टर(काष्ठा nf_ct_bridge_info *info);

#पूर्ण_अगर
