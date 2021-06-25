<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2019 Intel Corporation. */

#अगर_अघोषित XSK_H_
#घोषणा XSK_H_

/* Masks क्रम xdp_umem_page flags.
 * The low 12-bits of the addr will be 0 since this is the page address, so we
 * can use them क्रम flags.
 */
#घोषणा XSK_NEXT_PG_CONTIG_SHIFT 0
#घोषणा XSK_NEXT_PG_CONTIG_MASK BIT_ULL(XSK_NEXT_PG_CONTIG_SHIFT)

काष्ठा xdp_ring_offset_v1 अणु
	__u64 producer;
	__u64 consumer;
	__u64 desc;
पूर्ण;

काष्ठा xdp_mmap_offsets_v1 अणु
	काष्ठा xdp_ring_offset_v1 rx;
	काष्ठा xdp_ring_offset_v1 tx;
	काष्ठा xdp_ring_offset_v1 fr;
	काष्ठा xdp_ring_offset_v1 cr;
पूर्ण;

/* Nodes are linked in the काष्ठा xdp_sock map_list field, and used to
 * track which maps a certain socket reside in.
 */

काष्ठा xsk_map_node अणु
	काष्ठा list_head node;
	काष्ठा xsk_map *map;
	काष्ठा xdp_sock **map_entry;
पूर्ण;

अटल अंतरभूत काष्ठा xdp_sock *xdp_sk(काष्ठा sock *sk)
अणु
	वापस (काष्ठा xdp_sock *)sk;
पूर्ण

व्योम xsk_map_try_sock_delete(काष्ठा xsk_map *map, काष्ठा xdp_sock *xs,
			     काष्ठा xdp_sock **map_entry);
व्योम xsk_clear_pool_at_qid(काष्ठा net_device *dev, u16 queue_id);
पूर्णांक xsk_reg_pool_at_qid(काष्ठा net_device *dev, काष्ठा xsk_buff_pool *pool,
			u16 queue_id);

#पूर्ण_अगर /* XSK_H_ */
