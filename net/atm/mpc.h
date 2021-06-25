<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _MPC_H_
#घोषणा _MPC_H_

#समावेश <linux/types.h>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगmpc.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश "mpoa_caches.h"

/* kernel -> mpc-daemon */
पूर्णांक msg_to_mpoad(काष्ठा k_message *msg, काष्ठा mpoa_client *mpc);

काष्ठा mpoa_client अणु
	काष्ठा mpoa_client *next;
	काष्ठा net_device *dev;      /* lec in question                     */
	पूर्णांक dev_num;                 /* e.g. 2 क्रम lec2                     */

	काष्ठा aपंचांग_vcc *mpoad_vcc;   /* control channel to mpoad            */
	uपूर्णांक8_t mps_ctrl_addr[ATM_ESA_LEN];  /* MPS control ATM address     */
	uपूर्णांक8_t our_ctrl_addr[ATM_ESA_LEN];  /* MPC's control ATM address   */

	rwlock_t ingress_lock;
	स्थिर काष्ठा in_cache_ops *in_ops; /* ingress cache operations      */
	in_cache_entry *in_cache;    /* the ingress cache of this MPC       */

	rwlock_t egress_lock;
	स्थिर काष्ठा eg_cache_ops *eg_ops; /* egress cache operations       */
	eg_cache_entry *eg_cache;    /* the egress  cache of this MPC       */

	uपूर्णांक8_t *mps_macs;           /* array of MPS MAC addresses, >=1     */
	पूर्णांक number_of_mps_macs;      /* number of the above MAC addresses   */
	काष्ठा mpc_parameters parameters;  /* parameters क्रम this client    */

	स्थिर काष्ठा net_device_ops *old_ops;
	काष्ठा net_device_ops new_ops;
पूर्ण;


काष्ठा aपंचांग_mpoa_qos अणु
	काष्ठा aपंचांग_mpoa_qos *next;
	__be32 ipaddr;
	काष्ठा aपंचांग_qos qos;
पूर्ण;


/* MPOA QoS operations */
काष्ठा aपंचांग_mpoa_qos *aपंचांग_mpoa_add_qos(__be32 dst_ip, काष्ठा aपंचांग_qos *qos);
काष्ठा aपंचांग_mpoa_qos *aपंचांग_mpoa_search_qos(__be32 dst_ip);
पूर्णांक aपंचांग_mpoa_delete_qos(काष्ठा aपंचांग_mpoa_qos *qos);

/* Display QoS entries. This is क्रम the procfs */
काष्ठा seq_file;
व्योम aपंचांग_mpoa_disp_qos(काष्ठा seq_file *m);

#अगर_घोषित CONFIG_PROC_FS
पूर्णांक mpc_proc_init(व्योम);
व्योम mpc_proc_clean(व्योम);
#अन्यथा
#घोषणा mpc_proc_init() (0)
#घोषणा mpc_proc_clean() करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

#पूर्ण_अगर /* _MPC_H_ */
