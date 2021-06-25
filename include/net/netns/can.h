<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * can in net namespaces
 */

#अगर_अघोषित __NETNS_CAN_H__
#घोषणा __NETNS_CAN_H__

#समावेश <linux/spinlock.h>

काष्ठा can_dev_rcv_lists;
काष्ठा can_pkg_stats;
काष्ठा can_rcv_lists_stats;

काष्ठा netns_can अणु
#अगर IS_ENABLED(CONFIG_PROC_FS)
	काष्ठा proc_dir_entry *proc_dir;
	काष्ठा proc_dir_entry *pde_stats;
	काष्ठा proc_dir_entry *pde_reset_stats;
	काष्ठा proc_dir_entry *pde_rcvlist_all;
	काष्ठा proc_dir_entry *pde_rcvlist_fil;
	काष्ठा proc_dir_entry *pde_rcvlist_inv;
	काष्ठा proc_dir_entry *pde_rcvlist_sff;
	काष्ठा proc_dir_entry *pde_rcvlist_eff;
	काष्ठा proc_dir_entry *pde_rcvlist_err;
	काष्ठा proc_dir_entry *bcmproc_dir;
#पूर्ण_अगर

	/* receive filters subscribed क्रम 'all' CAN devices */
	काष्ठा can_dev_rcv_lists *rx_alldev_list;
	spinlock_t rcvlists_lock;
	काष्ठा समयr_list statसमयr; /* समयr क्रम statistics update */
	काष्ठा can_pkg_stats *pkg_stats;
	काष्ठा can_rcv_lists_stats *rcv_lists_stats;

	/* CAN GW per-net gateway jobs */
	काष्ठा hlist_head cgw_list;
पूर्ण;

#पूर्ण_अगर /* __NETNS_CAN_H__ */
