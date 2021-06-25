<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __BEN_VLAN_PROC_INC__
#घोषणा __BEN_VLAN_PROC_INC__

#अगर_घोषित CONFIG_PROC_FS
काष्ठा net;

पूर्णांक vlan_proc_init(काष्ठा net *net);
व्योम vlan_proc_rem_dev(काष्ठा net_device *vlandev);
पूर्णांक vlan_proc_add_dev(काष्ठा net_device *vlandev);
व्योम vlan_proc_cleanup(काष्ठा net *net);

#अन्यथा /* No CONFIG_PROC_FS */

#घोषणा vlan_proc_init(net)	(0)
#घोषणा vlan_proc_cleanup(net)	करो अणुपूर्ण जबतक (0)
#घोषणा vlan_proc_add_dev(dev)	(अणु(व्योम)(dev), 0; पूर्ण)
#घोषणा vlan_proc_rem_dev(dev)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर /* !(__BEN_VLAN_PROC_INC__) */
