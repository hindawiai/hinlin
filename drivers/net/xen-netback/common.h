<शैली गुरु>
/*
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#अगर_अघोषित __XEN_NETBACK__COMMON_H__
#घोषणा __XEN_NETBACK__COMMON_H__

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/ip.h>
#समावेश <linux/in.h>
#समावेश <linux/पन.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>

#समावेश <xen/पूर्णांकerface/io/netअगर.h>
#समावेश <xen/पूर्णांकerface/grant_table.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/page.h>
#समावेश <linux/debugfs.h>

प्रकार अचिन्हित पूर्णांक pending_ring_idx_t;
#घोषणा INVALID_PENDING_RING_IDX (~0U)

काष्ठा pending_tx_info अणु
	काष्ठा xen_netअगर_tx_request req; /* tx request */
	अचिन्हित पूर्णांक extra_count;
	/* Callback data क्रम released SKBs. The callback is always
	 * xenvअगर_zerocopy_callback, desc contains the pending_idx, which is
	 * also an index in pending_tx_info array. It is initialized in
	 * xenvअगर_alloc and it never changes.
	 * skb_shinfo(skb)->deकाष्ठाor_arg poपूर्णांकs to the first mapped slot's
	 * callback_काष्ठा in this array of काष्ठा pending_tx_info's, then ctx
	 * to the next, or शून्य अगर there is no more slot क्रम this skb.
	 * ubuf_to_vअगर is a helper which finds the काष्ठा xenvअगर from a poपूर्णांकer
	 * to this field.
	 */
	काष्ठा ubuf_info callback_काष्ठा;
पूर्ण;

#घोषणा XEN_NETIF_TX_RING_SIZE __CONST_RING_SIZE(xen_netअगर_tx, XEN_PAGE_SIZE)
#घोषणा XEN_NETIF_RX_RING_SIZE __CONST_RING_SIZE(xen_netअगर_rx, XEN_PAGE_SIZE)

काष्ठा xenvअगर_rx_meta अणु
	पूर्णांक id;
	पूर्णांक size;
	पूर्णांक gso_type;
	पूर्णांक gso_size;
पूर्ण;

#घोषणा GSO_BIT(type) \
	(1 << XEN_NETIF_GSO_TYPE_ ## type)

/* Discriminate from any valid pending_idx value. */
#घोषणा INVALID_PENDING_IDX 0xFFFF

#घोषणा MAX_BUFFER_OFFSET XEN_PAGE_SIZE

#घोषणा MAX_PENDING_REQS XEN_NETIF_TX_RING_SIZE

/* The maximum number of frags is derived from the size of a grant (same
 * as a Xen page size क्रम now).
 */
#घोषणा MAX_XEN_SKB_FRAGS (65536 / XEN_PAGE_SIZE + 1)

#घोषणा NETBACK_INVALID_HANDLE -1

/* To aव्योम confusion, we define XEN_NETBK_LEGACY_SLOTS_MAX indicating
 * the maximum slots a valid packet can use. Now this value is defined
 * to be XEN_NETIF_NR_SLOTS_MIN, which is supposed to be supported by
 * all backend.
 */
#घोषणा XEN_NETBK_LEGACY_SLOTS_MAX XEN_NETIF_NR_SLOTS_MIN

/* Queue name is पूर्णांकerface name with "-qNNN" appended */
#घोषणा QUEUE_NAME_SIZE (IFNAMSIZ + 5)

/* IRQ name is queue name with "-tx" or "-rx" appended */
#घोषणा IRQ_NAME_SIZE (QUEUE_NAME_SIZE + 3)

काष्ठा xenvअगर;

काष्ठा xenvअगर_stats अणु
	/* Stats fields to be updated per-queue.
	 * A subset of काष्ठा net_device_stats that contains only the
	 * fields that are updated in netback.c क्रम each queue.
	 */
	u64 rx_bytes;
	u64 rx_packets;
	u64 tx_bytes;
	u64 tx_packets;

	/* Additional stats used by xenvअगर */
	अचिन्हित दीर्घ rx_gso_checksum_fixup;
	अचिन्हित दीर्घ tx_zerocopy_sent;
	अचिन्हित दीर्घ tx_zerocopy_success;
	अचिन्हित दीर्घ tx_zerocopy_fail;
	अचिन्हित दीर्घ tx_frag_overflow;
पूर्ण;

#घोषणा COPY_BATCH_SIZE 64

काष्ठा xenvअगर_copy_state अणु
	काष्ठा gnttab_copy op[COPY_BATCH_SIZE];
	RING_IDX idx[COPY_BATCH_SIZE];
	अचिन्हित पूर्णांक num;
	काष्ठा sk_buff_head *completed;
पूर्ण;

काष्ठा xenvअगर_queue अणु /* Per-queue data क्रम xenvअगर */
	अचिन्हित पूर्णांक id; /* Queue ID, 0-based */
	अक्षर name[QUEUE_NAME_SIZE]; /* DEVNAME-qN */
	काष्ठा xenvअगर *vअगर; /* Parent VIF */

	/*
	 * TX/RX common EOI handling.
	 * When feature-split-event-channels = 0, पूर्णांकerrupt handler sets
	 * NETBK_COMMON_EOI, otherwise NETBK_RX_EOI and NETBK_TX_EOI are set
	 * by the RX and TX पूर्णांकerrupt handlers.
	 * RX and TX handler thपढ़ोs will issue an EOI when either
	 * NETBK_COMMON_EOI or their specअगरic bits (NETBK_RX_EOI or
	 * NETBK_TX_EOI) are set and they will reset those bits.
	 */
	atomic_t eoi_pending;
#घोषणा NETBK_RX_EOI		0x01
#घोषणा NETBK_TX_EOI		0x02
#घोषणा NETBK_COMMON_EOI	0x04

	/* Use NAPI क्रम guest TX */
	काष्ठा napi_काष्ठा napi;
	/* When feature-split-event-channels = 0, tx_irq = rx_irq. */
	अचिन्हित पूर्णांक tx_irq;
	/* Only used when feature-split-event-channels = 1 */
	अक्षर tx_irq_name[IRQ_NAME_SIZE]; /* DEVNAME-qN-tx */
	काष्ठा xen_netअगर_tx_back_ring tx;
	काष्ठा sk_buff_head tx_queue;
	काष्ठा page *mmap_pages[MAX_PENDING_REQS];
	pending_ring_idx_t pending_prod;
	pending_ring_idx_t pending_cons;
	u16 pending_ring[MAX_PENDING_REQS];
	काष्ठा pending_tx_info pending_tx_info[MAX_PENDING_REQS];
	grant_handle_t grant_tx_handle[MAX_PENDING_REQS];

	काष्ठा gnttab_copy tx_copy_ops[MAX_PENDING_REQS];
	काष्ठा gnttab_map_grant_ref tx_map_ops[MAX_PENDING_REQS];
	काष्ठा gnttab_unmap_grant_ref tx_unmap_ops[MAX_PENDING_REQS];
	/* passed to gnttab_[un]map_refs with pages under (un)mapping */
	काष्ठा page *pages_to_map[MAX_PENDING_REQS];
	काष्ठा page *pages_to_unmap[MAX_PENDING_REQS];

	/* This prevents zerocopy callbacks  to race over dealloc_ring */
	spinlock_t callback_lock;
	/* This prevents dealloc thपढ़ो and NAPI instance to race over response
	 * creation and pending_ring in xenvअगर_idx_release. In xenvअगर_tx_err
	 * it only protect response creation
	 */
	spinlock_t response_lock;
	pending_ring_idx_t dealloc_prod;
	pending_ring_idx_t dealloc_cons;
	u16 dealloc_ring[MAX_PENDING_REQS];
	काष्ठा task_काष्ठा *dealloc_task;
	रुको_queue_head_t dealloc_wq;
	atomic_t inflight_packets;

	/* Use kthपढ़ो क्रम guest RX */
	काष्ठा task_काष्ठा *task;
	रुको_queue_head_t wq;
	/* When feature-split-event-channels = 0, tx_irq = rx_irq. */
	अचिन्हित पूर्णांक rx_irq;
	/* Only used when feature-split-event-channels = 1 */
	अक्षर rx_irq_name[IRQ_NAME_SIZE]; /* DEVNAME-qN-rx */
	काष्ठा xen_netअगर_rx_back_ring rx;
	काष्ठा sk_buff_head rx_queue;

	अचिन्हित पूर्णांक rx_queue_max;
	अचिन्हित पूर्णांक rx_queue_len;
	अचिन्हित दीर्घ last_rx_समय;
	bool stalled;

	काष्ठा xenvअगर_copy_state rx_copy;

	/* Transmit shaping: allow 'credit_bytes' every 'credit_usec'. */
	अचिन्हित दीर्घ   credit_bytes;
	अचिन्हित दीर्घ   credit_usec;
	अचिन्हित दीर्घ   reमुख्यing_credit;
	काष्ठा समयr_list credit_समयout;
	u64 credit_winकरोw_start;
	bool rate_limited;

	/* Statistics */
	काष्ठा xenvअगर_stats stats;
पूर्ण;

क्रमागत state_bit_shअगरt अणु
	/* This bit marks that the vअगर is connected */
	VIF_STATUS_CONNECTED,
पूर्ण;

काष्ठा xenvअगर_mcast_addr अणु
	काष्ठा list_head entry;
	काष्ठा rcu_head rcu;
	u8 addr[6];
पूर्ण;

#घोषणा XEN_NETBK_MCAST_MAX 64

#घोषणा XEN_NETBK_MAX_HASH_KEY_SIZE 40
#घोषणा XEN_NETBK_MAX_HASH_MAPPING_SIZE 128
#घोषणा XEN_NETBK_HASH_TAG_SIZE 40

काष्ठा xenvअगर_hash_cache_entry अणु
	काष्ठा list_head link;
	काष्ठा rcu_head rcu;
	u8 tag[XEN_NETBK_HASH_TAG_SIZE];
	अचिन्हित पूर्णांक len;
	u32 val;
	पूर्णांक seq;
पूर्ण;

काष्ठा xenvअगर_hash_cache अणु
	spinlock_t lock;
	काष्ठा list_head list;
	अचिन्हित पूर्णांक count;
	atomic_t seq;
पूर्ण;

काष्ठा xenvअगर_hash अणु
	अचिन्हित पूर्णांक alg;
	u32 flags;
	bool mapping_sel;
	u8 key[XEN_NETBK_MAX_HASH_KEY_SIZE];
	u32 mapping[2][XEN_NETBK_MAX_HASH_MAPPING_SIZE];
	अचिन्हित पूर्णांक size;
	काष्ठा xenvअगर_hash_cache cache;
पूर्ण;

काष्ठा backend_info अणु
	काष्ठा xenbus_device *dev;
	काष्ठा xenvअगर *vअगर;

	/* This is the state that will be reflected in xenstore when any
	 * active hotplug script completes.
	 */
	क्रमागत xenbus_state state;

	क्रमागत xenbus_state frontend_state;
	काष्ठा xenbus_watch hotplug_status_watch;
	u8 have_hotplug_status_watch:1;

	स्थिर अक्षर *hotplug_script;
पूर्ण;

काष्ठा xenvअगर अणु
	/* Unique identअगरier क्रम this पूर्णांकerface. */
	करोmid_t          करोmid;
	अचिन्हित पूर्णांक     handle;

	u8               fe_dev_addr[6];
	काष्ठा list_head fe_mcast_addr;
	अचिन्हित पूर्णांक     fe_mcast_count;

	/* Frontend feature inक्रमmation. */
	पूर्णांक gso_mask;

	u8 can_sg:1;
	u8 ip_csum:1;
	u8 ipv6_csum:1;
	u8 multicast_control:1;

	/* headroom requested by xen-netfront */
	u16 xdp_headroom;

	/* Is this पूर्णांकerface disabled? True when backend discovers
	 * frontend is rogue.
	 */
	bool disabled;
	अचिन्हित दीर्घ status;
	अचिन्हित दीर्घ drain_समयout;
	अचिन्हित दीर्घ stall_समयout;

	/* Queues */
	काष्ठा xenvअगर_queue *queues;
	अचिन्हित पूर्णांक num_queues; /* active queues, resource allocated */
	अचिन्हित पूर्णांक stalled_queues;

	काष्ठा xenvअगर_hash hash;

	काष्ठा xenbus_watch credit_watch;
	काष्ठा xenbus_watch mcast_ctrl_watch;

	काष्ठा backend_info *be;

	spinlock_t lock;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *xenvअगर_dbg_root;
#पूर्ण_अगर

	काष्ठा xen_netअगर_ctrl_back_ring ctrl;
	अचिन्हित पूर्णांक ctrl_irq;

	/* Miscellaneous निजी stuff. */
	काष्ठा net_device *dev;
पूर्ण;

काष्ठा xenvअगर_rx_cb अणु
	अचिन्हित दीर्घ expires;
	पूर्णांक meta_slots_used;
पूर्ण;

#घोषणा XENVIF_RX_CB(skb) ((काष्ठा xenvअगर_rx_cb *)(skb)->cb)

अटल अंतरभूत काष्ठा xenbus_device *xenvअगर_to_xenbus_device(काष्ठा xenvअगर *vअगर)
अणु
	वापस to_xenbus_device(vअगर->dev->dev.parent);
पूर्ण

व्योम xenvअगर_tx_credit_callback(काष्ठा समयr_list *t);

काष्ठा xenvअगर *xenvअगर_alloc(काष्ठा device *parent,
			    करोmid_t करोmid,
			    अचिन्हित पूर्णांक handle);

पूर्णांक xenvअगर_init_queue(काष्ठा xenvअगर_queue *queue);
व्योम xenvअगर_deinit_queue(काष्ठा xenvअगर_queue *queue);

पूर्णांक xenvअगर_connect_data(काष्ठा xenvअगर_queue *queue,
			अचिन्हित दीर्घ tx_ring_ref,
			अचिन्हित दीर्घ rx_ring_ref,
			अचिन्हित पूर्णांक tx_evtchn,
			अचिन्हित पूर्णांक rx_evtchn);
व्योम xenvअगर_disconnect_data(काष्ठा xenvअगर *vअगर);
पूर्णांक xenvअगर_connect_ctrl(काष्ठा xenvअगर *vअगर, grant_ref_t ring_ref,
			अचिन्हित पूर्णांक evtchn);
व्योम xenvअगर_disconnect_ctrl(काष्ठा xenvअगर *vअगर);
व्योम xenvअगर_मुक्त(काष्ठा xenvअगर *vअगर);

पूर्णांक xenvअगर_xenbus_init(व्योम);
व्योम xenvअगर_xenbus_fini(व्योम);

पूर्णांक xenvअगर_schedulable(काष्ठा xenvअगर *vअगर);

पूर्णांक xenvअगर_queue_stopped(काष्ठा xenvअगर_queue *queue);
व्योम xenvअगर_wake_queue(काष्ठा xenvअगर_queue *queue);

/* (Un)Map communication rings. */
व्योम xenvअगर_unmap_frontend_data_rings(काष्ठा xenvअगर_queue *queue);
पूर्णांक xenvअगर_map_frontend_data_rings(काष्ठा xenvअगर_queue *queue,
				   grant_ref_t tx_ring_ref,
				   grant_ref_t rx_ring_ref);

/* Check क्रम SKBs from frontend and schedule backend processing */
व्योम xenvअगर_napi_schedule_or_enable_events(काष्ठा xenvअगर_queue *queue);

/* Prevent the device from generating any further traffic. */
व्योम xenvअगर_carrier_off(काष्ठा xenvअगर *vअगर);

पूर्णांक xenvअगर_tx_action(काष्ठा xenvअगर_queue *queue, पूर्णांक budget);

पूर्णांक xenvअगर_kthपढ़ो_guest_rx(व्योम *data);
व्योम xenvअगर_kick_thपढ़ो(काष्ठा xenvअगर_queue *queue);

पूर्णांक xenvअगर_dealloc_kthपढ़ो(व्योम *data);

irqवापस_t xenvअगर_ctrl_irq_fn(पूर्णांक irq, व्योम *data);

bool xenvअगर_have_rx_work(काष्ठा xenvअगर_queue *queue, bool test_kthपढ़ो);
व्योम xenvअगर_rx_action(काष्ठा xenvअगर_queue *queue);
व्योम xenvअगर_rx_queue_tail(काष्ठा xenvअगर_queue *queue, काष्ठा sk_buff *skb);

व्योम xenvअगर_carrier_on(काष्ठा xenvअगर *vअगर);

/* Callback from stack when TX packet can be released */
व्योम xenvअगर_zerocopy_callback(काष्ठा sk_buff *skb, काष्ठा ubuf_info *ubuf,
			      bool zerocopy_success);

/* Unmap a pending page and release it back to the guest */
व्योम xenvअगर_idx_unmap(काष्ठा xenvअगर_queue *queue, u16 pending_idx);

अटल अंतरभूत pending_ring_idx_t nr_pending_reqs(काष्ठा xenvअगर_queue *queue)
अणु
	वापस MAX_PENDING_REQS -
		queue->pending_prod + queue->pending_cons;
पूर्ण

irqवापस_t xenvअगर_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

बाह्य bool separate_tx_rx_irq;
बाह्य bool provides_xdp_headroom;

बाह्य अचिन्हित पूर्णांक rx_drain_समयout_msecs;
बाह्य अचिन्हित पूर्णांक rx_stall_समयout_msecs;
बाह्य अचिन्हित पूर्णांक xenvअगर_max_queues;
बाह्य अचिन्हित पूर्णांक xenvअगर_hash_cache_size;

#अगर_घोषित CONFIG_DEBUG_FS
बाह्य काष्ठा dentry *xen_netback_dbg_root;
#पूर्ण_अगर

व्योम xenvअगर_skb_zerocopy_prepare(काष्ठा xenvअगर_queue *queue,
				 काष्ठा sk_buff *skb);
व्योम xenvअगर_skb_zerocopy_complete(काष्ठा xenvअगर_queue *queue);

/* Multicast control */
bool xenvअगर_mcast_match(काष्ठा xenvअगर *vअगर, स्थिर u8 *addr);
व्योम xenvअगर_mcast_addr_list_मुक्त(काष्ठा xenvअगर *vअगर);

/* Hash */
व्योम xenvअगर_init_hash(काष्ठा xenvअगर *vअगर);
व्योम xenvअगर_deinit_hash(काष्ठा xenvअगर *vअगर);

u32 xenvअगर_set_hash_alg(काष्ठा xenvअगर *vअगर, u32 alg);
u32 xenvअगर_get_hash_flags(काष्ठा xenvअगर *vअगर, u32 *flags);
u32 xenvअगर_set_hash_flags(काष्ठा xenvअगर *vअगर, u32 flags);
u32 xenvअगर_set_hash_key(काष्ठा xenvअगर *vअगर, u32 gref, u32 len);
u32 xenvअगर_set_hash_mapping_size(काष्ठा xenvअगर *vअगर, u32 size);
u32 xenvअगर_set_hash_mapping(काष्ठा xenvअगर *vअगर, u32 gref, u32 len,
			    u32 off);

व्योम xenvअगर_set_skb_hash(काष्ठा xenvअगर *vअगर, काष्ठा sk_buff *skb);

#अगर_घोषित CONFIG_DEBUG_FS
व्योम xenvअगर_dump_hash_info(काष्ठा xenvअगर *vअगर, काष्ठा seq_file *m);
#पूर्ण_अगर

#पूर्ण_अगर /* __XEN_NETBACK__COMMON_H__ */
