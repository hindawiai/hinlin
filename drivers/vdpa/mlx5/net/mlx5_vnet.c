<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020 Mellanox Technologies Ltd. */

#समावेश <linux/module.h>
#समावेश <linux/vdpa.h>
#समावेश <linux/vringh.h>
#समावेश <uapi/linux/virtio_net.h>
#समावेश <uapi/linux/virtio_ids.h>
#समावेश <linux/virtio_config.h>
#समावेश <linux/auxiliary_bus.h>
#समावेश <linux/mlx5/cq.h>
#समावेश <linux/mlx5/qp.h>
#समावेश <linux/mlx5/device.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/vport.h>
#समावेश <linux/mlx5/fs.h>
#समावेश <linux/mlx5/mlx5_अगरc_vdpa.h>
#समावेश <linux/mlx5/mpfs.h>
#समावेश "mlx5_vdpa.h"

MODULE_AUTHOR("Eli Cohen <eli@mellanox.com>");
MODULE_DESCRIPTION("Mellanox VDPA driver");
MODULE_LICENSE("Dual BSD/GPL");

#घोषणा to_mlx5_vdpa_ndev(__mvdev)                                             \
	container_of(__mvdev, काष्ठा mlx5_vdpa_net, mvdev)
#घोषणा to_mvdev(__vdev) container_of((__vdev), काष्ठा mlx5_vdpa_dev, vdev)

#घोषणा VALID_FEATURES_MASK                                                                        \
	(BIT_ULL(VIRTIO_NET_F_CSUM) | BIT_ULL(VIRTIO_NET_F_GUEST_CSUM) |                                   \
	 BIT_ULL(VIRTIO_NET_F_CTRL_GUEST_OFFLOADS) | BIT_ULL(VIRTIO_NET_F_MTU) | BIT_ULL(VIRTIO_NET_F_MAC) |   \
	 BIT_ULL(VIRTIO_NET_F_GUEST_TSO4) | BIT_ULL(VIRTIO_NET_F_GUEST_TSO6) |                             \
	 BIT_ULL(VIRTIO_NET_F_GUEST_ECN) | BIT_ULL(VIRTIO_NET_F_GUEST_UFO) | BIT_ULL(VIRTIO_NET_F_HOST_TSO4) | \
	 BIT_ULL(VIRTIO_NET_F_HOST_TSO6) | BIT_ULL(VIRTIO_NET_F_HOST_ECN) | BIT_ULL(VIRTIO_NET_F_HOST_UFO) |   \
	 BIT_ULL(VIRTIO_NET_F_MRG_RXBUF) | BIT_ULL(VIRTIO_NET_F_STATUS) | BIT_ULL(VIRTIO_NET_F_CTRL_VQ) |      \
	 BIT_ULL(VIRTIO_NET_F_CTRL_RX) | BIT_ULL(VIRTIO_NET_F_CTRL_VLAN) |                                 \
	 BIT_ULL(VIRTIO_NET_F_CTRL_RX_EXTRA) | BIT_ULL(VIRTIO_NET_F_GUEST_ANNOUNCE) |                      \
	 BIT_ULL(VIRTIO_NET_F_MQ) | BIT_ULL(VIRTIO_NET_F_CTRL_MAC_ADDR) | BIT_ULL(VIRTIO_NET_F_HASH_REPORT) |  \
	 BIT_ULL(VIRTIO_NET_F_RSS) | BIT_ULL(VIRTIO_NET_F_RSC_EXT) | BIT_ULL(VIRTIO_NET_F_STANDBY) |           \
	 BIT_ULL(VIRTIO_NET_F_SPEED_DUPLEX) | BIT_ULL(VIRTIO_F_NOTIFY_ON_EMPTY) |                          \
	 BIT_ULL(VIRTIO_F_ANY_LAYOUT) | BIT_ULL(VIRTIO_F_VERSION_1) | BIT_ULL(VIRTIO_F_ACCESS_PLATFORM) |      \
	 BIT_ULL(VIRTIO_F_RING_PACKED) | BIT_ULL(VIRTIO_F_ORDER_PLATFORM) | BIT_ULL(VIRTIO_F_SR_IOV))

#घोषणा VALID_STATUS_MASK                                                                          \
	(VIRTIO_CONFIG_S_ACKNOWLEDGE | VIRTIO_CONFIG_S_DRIVER | VIRTIO_CONFIG_S_DRIVER_OK |        \
	 VIRTIO_CONFIG_S_FEATURES_OK | VIRTIO_CONFIG_S_NEEDS_RESET | VIRTIO_CONFIG_S_FAILED)

काष्ठा mlx5_vdpa_net_resources अणु
	u32 tisn;
	u32 tdn;
	u32 tirn;
	u32 rqtn;
	bool valid;
पूर्ण;

काष्ठा mlx5_vdpa_cq_buf अणु
	काष्ठा mlx5_frag_buf_ctrl fbc;
	काष्ठा mlx5_frag_buf frag_buf;
	पूर्णांक cqe_size;
	पूर्णांक nent;
पूर्ण;

काष्ठा mlx5_vdpa_cq अणु
	काष्ठा mlx5_core_cq mcq;
	काष्ठा mlx5_vdpa_cq_buf buf;
	काष्ठा mlx5_db db;
	पूर्णांक cqe;
पूर्ण;

काष्ठा mlx5_vdpa_umem अणु
	काष्ठा mlx5_frag_buf_ctrl fbc;
	काष्ठा mlx5_frag_buf frag_buf;
	पूर्णांक size;
	u32 id;
पूर्ण;

काष्ठा mlx5_vdpa_qp अणु
	काष्ठा mlx5_core_qp mqp;
	काष्ठा mlx5_frag_buf frag_buf;
	काष्ठा mlx5_db db;
	u16 head;
	bool fw;
पूर्ण;

काष्ठा mlx5_vq_restore_info अणु
	u32 num_ent;
	u64 desc_addr;
	u64 device_addr;
	u64 driver_addr;
	u16 avail_index;
	u16 used_index;
	bool पढ़ोy;
	काष्ठा vdpa_callback cb;
	bool restore;
पूर्ण;

काष्ठा mlx5_vdpa_virtqueue अणु
	bool पढ़ोy;
	u64 desc_addr;
	u64 device_addr;
	u64 driver_addr;
	u32 num_ent;
	काष्ठा vdpa_callback event_cb;

	/* Resources क्रम implementing the notअगरication channel from the device
	 * to the driver. fwqp is the firmware end of an RC connection; the
	 * other end is vqqp used by the driver. cq is is where completions are
	 * reported.
	 */
	काष्ठा mlx5_vdpa_cq cq;
	काष्ठा mlx5_vdpa_qp fwqp;
	काष्ठा mlx5_vdpa_qp vqqp;

	/* umem resources are required क्रम the virtqueue operation. They're use
	 * is पूर्णांकernal and they must be provided by the driver.
	 */
	काष्ठा mlx5_vdpa_umem umem1;
	काष्ठा mlx5_vdpa_umem umem2;
	काष्ठा mlx5_vdpa_umem umem3;

	bool initialized;
	पूर्णांक index;
	u32 virtq_id;
	काष्ठा mlx5_vdpa_net *ndev;
	u16 avail_idx;
	u16 used_idx;
	पूर्णांक fw_state;

	/* keep last in the काष्ठा */
	काष्ठा mlx5_vq_restore_info ri;
पूर्ण;

/* We will हटाओ this limitation once mlx5_vdpa_alloc_resources()
 * provides क्रम driver space allocation
 */
#घोषणा MLX5_MAX_SUPPORTED_VQS 16

काष्ठा mlx5_vdpa_net अणु
	काष्ठा mlx5_vdpa_dev mvdev;
	काष्ठा mlx5_vdpa_net_resources res;
	काष्ठा virtio_net_config config;
	काष्ठा mlx5_vdpa_virtqueue vqs[MLX5_MAX_SUPPORTED_VQS];

	/* Serialize vq resources creation and deकाष्ठाion. This is required
	 * since memory map might change and we need to destroy and create
	 * resources जबतक driver in operational.
	 */
	काष्ठा mutex reslock;
	काष्ठा mlx5_flow_table *rxft;
	काष्ठा mlx5_fc *rx_counter;
	काष्ठा mlx5_flow_handle *rx_rule;
	bool setup;
	u16 mtu;
पूर्ण;

अटल व्योम मुक्त_resources(काष्ठा mlx5_vdpa_net *ndev);
अटल व्योम init_mvqs(काष्ठा mlx5_vdpa_net *ndev);
अटल पूर्णांक setup_driver(काष्ठा mlx5_vdpa_net *ndev);
अटल व्योम tearकरोwn_driver(काष्ठा mlx5_vdpa_net *ndev);

अटल bool mlx5_vdpa_debug;

#घोषणा MLX5_LOG_VIO_FLAG(_feature)                                                                \
	करो अणु                                                                                       \
		अगर (features & BIT_ULL(_feature))                                                  \
			mlx5_vdpa_info(mvdev, "%s\n", #_feature);                                  \
	पूर्ण जबतक (0)

#घोषणा MLX5_LOG_VIO_STAT(_status)                                                                 \
	करो अणु                                                                                       \
		अगर (status & (_status))                                                            \
			mlx5_vdpa_info(mvdev, "%s\n", #_status);                                   \
	पूर्ण जबतक (0)

अटल अंतरभूत u32 mlx5_vdpa_max_qps(पूर्णांक max_vqs)
अणु
	वापस max_vqs / 2;
पूर्ण

अटल व्योम prपूर्णांक_status(काष्ठा mlx5_vdpa_dev *mvdev, u8 status, bool set)
अणु
	अगर (status & ~VALID_STATUS_MASK)
		mlx5_vdpa_warn(mvdev, "Warning: there are invalid status bits 0x%x\n",
			       status & ~VALID_STATUS_MASK);

	अगर (!mlx5_vdpa_debug)
		वापस;

	mlx5_vdpa_info(mvdev, "driver status %s", set ? "set" : "get");
	अगर (set && !status) अणु
		mlx5_vdpa_info(mvdev, "driver resets the device\n");
		वापस;
	पूर्ण

	MLX5_LOG_VIO_STAT(VIRTIO_CONFIG_S_ACKNOWLEDGE);
	MLX5_LOG_VIO_STAT(VIRTIO_CONFIG_S_DRIVER);
	MLX5_LOG_VIO_STAT(VIRTIO_CONFIG_S_DRIVER_OK);
	MLX5_LOG_VIO_STAT(VIRTIO_CONFIG_S_FEATURES_OK);
	MLX5_LOG_VIO_STAT(VIRTIO_CONFIG_S_NEEDS_RESET);
	MLX5_LOG_VIO_STAT(VIRTIO_CONFIG_S_FAILED);
पूर्ण

अटल व्योम prपूर्णांक_features(काष्ठा mlx5_vdpa_dev *mvdev, u64 features, bool set)
अणु
	अगर (features & ~VALID_FEATURES_MASK)
		mlx5_vdpa_warn(mvdev, "There are invalid feature bits 0x%llx\n",
			       features & ~VALID_FEATURES_MASK);

	अगर (!mlx5_vdpa_debug)
		वापस;

	mlx5_vdpa_info(mvdev, "driver %s feature bits:\n", set ? "sets" : "reads");
	अगर (!features)
		mlx5_vdpa_info(mvdev, "all feature bits are cleared\n");

	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_CSUM);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_GUEST_CSUM);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_CTRL_GUEST_OFFLOADS);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_MTU);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_MAC);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_GUEST_TSO4);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_GUEST_TSO6);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_GUEST_ECN);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_GUEST_UFO);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_HOST_TSO4);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_HOST_TSO6);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_HOST_ECN);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_HOST_UFO);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_MRG_RXBUF);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_STATUS);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_CTRL_VQ);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_CTRL_RX);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_CTRL_VLAN);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_CTRL_RX_EXTRA);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_GUEST_ANNOUNCE);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_MQ);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_CTRL_MAC_ADDR);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_HASH_REPORT);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_RSS);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_RSC_EXT);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_STANDBY);
	MLX5_LOG_VIO_FLAG(VIRTIO_NET_F_SPEED_DUPLEX);
	MLX5_LOG_VIO_FLAG(VIRTIO_F_NOTIFY_ON_EMPTY);
	MLX5_LOG_VIO_FLAG(VIRTIO_F_ANY_LAYOUT);
	MLX5_LOG_VIO_FLAG(VIRTIO_F_VERSION_1);
	MLX5_LOG_VIO_FLAG(VIRTIO_F_ACCESS_PLATFORM);
	MLX5_LOG_VIO_FLAG(VIRTIO_F_RING_PACKED);
	MLX5_LOG_VIO_FLAG(VIRTIO_F_ORDER_PLATFORM);
	MLX5_LOG_VIO_FLAG(VIRTIO_F_SR_IOV);
पूर्ण

अटल पूर्णांक create_tis(काष्ठा mlx5_vdpa_net *ndev)
अणु
	काष्ठा mlx5_vdpa_dev *mvdev = &ndev->mvdev;
	u32 in[MLX5_ST_SZ_DW(create_tis_in)] = अणुपूर्ण;
	व्योम *tisc;
	पूर्णांक err;

	tisc = MLX5_ADDR_OF(create_tis_in, in, ctx);
	MLX5_SET(tisc, tisc, transport_करोमुख्य, ndev->res.tdn);
	err = mlx5_vdpa_create_tis(mvdev, in, &ndev->res.tisn);
	अगर (err)
		mlx5_vdpa_warn(mvdev, "create TIS (%d)\n", err);

	वापस err;
पूर्ण

अटल व्योम destroy_tis(काष्ठा mlx5_vdpa_net *ndev)
अणु
	mlx5_vdpa_destroy_tis(&ndev->mvdev, ndev->res.tisn);
पूर्ण

#घोषणा MLX5_VDPA_CQE_SIZE 64
#घोषणा MLX5_VDPA_LOG_CQE_SIZE ilog2(MLX5_VDPA_CQE_SIZE)

अटल पूर्णांक cq_frag_buf_alloc(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_cq_buf *buf, पूर्णांक nent)
अणु
	काष्ठा mlx5_frag_buf *frag_buf = &buf->frag_buf;
	u8 log_wq_stride = MLX5_VDPA_LOG_CQE_SIZE;
	u8 log_wq_sz = MLX5_VDPA_LOG_CQE_SIZE;
	पूर्णांक err;

	err = mlx5_frag_buf_alloc_node(ndev->mvdev.mdev, nent * MLX5_VDPA_CQE_SIZE, frag_buf,
				       ndev->mvdev.mdev->priv.numa_node);
	अगर (err)
		वापस err;

	mlx5_init_fbc(frag_buf->frags, log_wq_stride, log_wq_sz, &buf->fbc);

	buf->cqe_size = MLX5_VDPA_CQE_SIZE;
	buf->nent = nent;

	वापस 0;
पूर्ण

अटल पूर्णांक umem_frag_buf_alloc(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_umem *umem, पूर्णांक size)
अणु
	काष्ठा mlx5_frag_buf *frag_buf = &umem->frag_buf;

	वापस mlx5_frag_buf_alloc_node(ndev->mvdev.mdev, size, frag_buf,
					ndev->mvdev.mdev->priv.numa_node);
पूर्ण

अटल व्योम cq_frag_buf_मुक्त(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_cq_buf *buf)
अणु
	mlx5_frag_buf_मुक्त(ndev->mvdev.mdev, &buf->frag_buf);
पूर्ण

अटल व्योम *get_cqe(काष्ठा mlx5_vdpa_cq *vcq, पूर्णांक n)
अणु
	वापस mlx5_frag_buf_get_wqe(&vcq->buf.fbc, n);
पूर्ण

अटल व्योम cq_frag_buf_init(काष्ठा mlx5_vdpa_cq *vcq, काष्ठा mlx5_vdpa_cq_buf *buf)
अणु
	काष्ठा mlx5_cqe64 *cqe64;
	व्योम *cqe;
	पूर्णांक i;

	क्रम (i = 0; i < buf->nent; i++) अणु
		cqe = get_cqe(vcq, i);
		cqe64 = cqe;
		cqe64->op_own = MLX5_CQE_INVALID << 4;
	पूर्ण
पूर्ण

अटल व्योम *get_sw_cqe(काष्ठा mlx5_vdpa_cq *cq, पूर्णांक n)
अणु
	काष्ठा mlx5_cqe64 *cqe64 = get_cqe(cq, n & (cq->cqe - 1));

	अगर (likely(get_cqe_opcode(cqe64) != MLX5_CQE_INVALID) &&
	    !((cqe64->op_own & MLX5_CQE_OWNER_MASK) ^ !!(n & cq->cqe)))
		वापस cqe64;

	वापस शून्य;
पूर्ण

अटल व्योम rx_post(काष्ठा mlx5_vdpa_qp *vqp, पूर्णांक n)
अणु
	vqp->head += n;
	vqp->db.db[0] = cpu_to_be32(vqp->head);
पूर्ण

अटल व्योम qp_prepare(काष्ठा mlx5_vdpa_net *ndev, bool fw, व्योम *in,
		       काष्ठा mlx5_vdpa_virtqueue *mvq, u32 num_ent)
अणु
	काष्ठा mlx5_vdpa_qp *vqp;
	__be64 *pas;
	व्योम *qpc;

	vqp = fw ? &mvq->fwqp : &mvq->vqqp;
	MLX5_SET(create_qp_in, in, uid, ndev->mvdev.res.uid);
	qpc = MLX5_ADDR_OF(create_qp_in, in, qpc);
	अगर (vqp->fw) अणु
		/* Firmware QP is allocated by the driver क्रम the firmware's
		 * use so we can skip part of the params as they will be chosen by firmware
		 */
		qpc = MLX5_ADDR_OF(create_qp_in, in, qpc);
		MLX5_SET(qpc, qpc, rq_type, MLX5_ZERO_LEN_RQ);
		MLX5_SET(qpc, qpc, no_sq, 1);
		वापस;
	पूर्ण

	MLX5_SET(qpc, qpc, st, MLX5_QP_ST_RC);
	MLX5_SET(qpc, qpc, pm_state, MLX5_QP_PM_MIGRATED);
	MLX5_SET(qpc, qpc, pd, ndev->mvdev.res.pdn);
	MLX5_SET(qpc, qpc, mtu, MLX5_QPC_MTU_256_BYTES);
	MLX5_SET(qpc, qpc, uar_page, ndev->mvdev.res.uar->index);
	MLX5_SET(qpc, qpc, log_page_size, vqp->frag_buf.page_shअगरt - MLX5_ADAPTER_PAGE_SHIFT);
	MLX5_SET(qpc, qpc, no_sq, 1);
	MLX5_SET(qpc, qpc, cqn_rcv, mvq->cq.mcq.cqn);
	MLX5_SET(qpc, qpc, log_rq_size, ilog2(num_ent));
	MLX5_SET(qpc, qpc, rq_type, MLX5_NON_ZERO_RQ);
	pas = (__be64 *)MLX5_ADDR_OF(create_qp_in, in, pas);
	mlx5_fill_page_frag_array(&vqp->frag_buf, pas);
पूर्ण

अटल पूर्णांक rq_buf_alloc(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_qp *vqp, u32 num_ent)
अणु
	वापस mlx5_frag_buf_alloc_node(ndev->mvdev.mdev,
					num_ent * माप(काष्ठा mlx5_wqe_data_seg), &vqp->frag_buf,
					ndev->mvdev.mdev->priv.numa_node);
पूर्ण

अटल व्योम rq_buf_मुक्त(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_qp *vqp)
अणु
	mlx5_frag_buf_मुक्त(ndev->mvdev.mdev, &vqp->frag_buf);
पूर्ण

अटल पूर्णांक qp_create(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_virtqueue *mvq,
		     काष्ठा mlx5_vdpa_qp *vqp)
अणु
	काष्ठा mlx5_core_dev *mdev = ndev->mvdev.mdev;
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_qp_in);
	u32 out[MLX5_ST_SZ_DW(create_qp_out)] = अणुपूर्ण;
	व्योम *qpc;
	व्योम *in;
	पूर्णांक err;

	अगर (!vqp->fw) अणु
		vqp = &mvq->vqqp;
		err = rq_buf_alloc(ndev, vqp, mvq->num_ent);
		अगर (err)
			वापस err;

		err = mlx5_db_alloc(ndev->mvdev.mdev, &vqp->db);
		अगर (err)
			जाओ err_db;
		inlen += vqp->frag_buf.npages * माप(__be64);
	पूर्ण

	in = kzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		जाओ err_kzalloc;
	पूर्ण

	qp_prepare(ndev, vqp->fw, in, mvq, mvq->num_ent);
	qpc = MLX5_ADDR_OF(create_qp_in, in, qpc);
	MLX5_SET(qpc, qpc, st, MLX5_QP_ST_RC);
	MLX5_SET(qpc, qpc, pm_state, MLX5_QP_PM_MIGRATED);
	MLX5_SET(qpc, qpc, pd, ndev->mvdev.res.pdn);
	MLX5_SET(qpc, qpc, mtu, MLX5_QPC_MTU_256_BYTES);
	अगर (!vqp->fw)
		MLX5_SET64(qpc, qpc, dbr_addr, vqp->db.dma);
	MLX5_SET(create_qp_in, in, opcode, MLX5_CMD_OP_CREATE_QP);
	err = mlx5_cmd_exec(mdev, in, inlen, out, माप(out));
	kमुक्त(in);
	अगर (err)
		जाओ err_kzalloc;

	vqp->mqp.uid = ndev->mvdev.res.uid;
	vqp->mqp.qpn = MLX5_GET(create_qp_out, out, qpn);

	अगर (!vqp->fw)
		rx_post(vqp, mvq->num_ent);

	वापस 0;

err_kzalloc:
	अगर (!vqp->fw)
		mlx5_db_मुक्त(ndev->mvdev.mdev, &vqp->db);
err_db:
	अगर (!vqp->fw)
		rq_buf_मुक्त(ndev, vqp);

	वापस err;
पूर्ण

अटल व्योम qp_destroy(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_qp *vqp)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_qp_in)] = अणुपूर्ण;

	MLX5_SET(destroy_qp_in, in, opcode, MLX5_CMD_OP_DESTROY_QP);
	MLX5_SET(destroy_qp_in, in, qpn, vqp->mqp.qpn);
	MLX5_SET(destroy_qp_in, in, uid, ndev->mvdev.res.uid);
	अगर (mlx5_cmd_exec_in(ndev->mvdev.mdev, destroy_qp, in))
		mlx5_vdpa_warn(&ndev->mvdev, "destroy qp 0x%x\n", vqp->mqp.qpn);
	अगर (!vqp->fw) अणु
		mlx5_db_मुक्त(ndev->mvdev.mdev, &vqp->db);
		rq_buf_मुक्त(ndev, vqp);
	पूर्ण
पूर्ण

अटल व्योम *next_cqe_sw(काष्ठा mlx5_vdpa_cq *cq)
अणु
	वापस get_sw_cqe(cq, cq->mcq.cons_index);
पूर्ण

अटल पूर्णांक mlx5_vdpa_poll_one(काष्ठा mlx5_vdpa_cq *vcq)
अणु
	काष्ठा mlx5_cqe64 *cqe64;

	cqe64 = next_cqe_sw(vcq);
	अगर (!cqe64)
		वापस -EAGAIN;

	vcq->mcq.cons_index++;
	वापस 0;
पूर्ण

अटल व्योम mlx5_vdpa_handle_completions(काष्ठा mlx5_vdpa_virtqueue *mvq, पूर्णांक num)
अणु
	mlx5_cq_set_ci(&mvq->cq.mcq);

	/* make sure CQ cosumer update is visible to the hardware beक्रमe updating
	 * RX करोorbell record.
	 */
	dma_wmb();
	rx_post(&mvq->vqqp, num);
	अगर (mvq->event_cb.callback)
		mvq->event_cb.callback(mvq->event_cb.निजी);
पूर्ण

अटल व्योम mlx5_vdpa_cq_comp(काष्ठा mlx5_core_cq *mcq, काष्ठा mlx5_eqe *eqe)
अणु
	काष्ठा mlx5_vdpa_virtqueue *mvq = container_of(mcq, काष्ठा mlx5_vdpa_virtqueue, cq.mcq);
	काष्ठा mlx5_vdpa_net *ndev = mvq->ndev;
	व्योम __iomem *uar_page = ndev->mvdev.res.uar->map;
	पूर्णांक num = 0;

	जबतक (!mlx5_vdpa_poll_one(&mvq->cq)) अणु
		num++;
		अगर (num > mvq->num_ent / 2) अणु
			/* If completions keep coming जबतक we poll, we want to
			 * let the hardware know that we consumed them by
			 * updating the करोorbell record.  We also let vdpa core
			 * know about this so it passes it on the virtio driver
			 * on the guest.
			 */
			mlx5_vdpa_handle_completions(mvq, num);
			num = 0;
		पूर्ण
	पूर्ण

	अगर (num)
		mlx5_vdpa_handle_completions(mvq, num);

	mlx5_cq_arm(&mvq->cq.mcq, MLX5_CQ_DB_REQ_NOT, uar_page, mvq->cq.mcq.cons_index);
पूर्ण

अटल पूर्णांक cq_create(काष्ठा mlx5_vdpa_net *ndev, u16 idx, u32 num_ent)
अणु
	काष्ठा mlx5_vdpa_virtqueue *mvq = &ndev->vqs[idx];
	काष्ठा mlx5_core_dev *mdev = ndev->mvdev.mdev;
	व्योम __iomem *uar_page = ndev->mvdev.res.uar->map;
	u32 out[MLX5_ST_SZ_DW(create_cq_out)];
	काष्ठा mlx5_vdpa_cq *vcq = &mvq->cq;
	अचिन्हित पूर्णांक irqn;
	__be64 *pas;
	पूर्णांक inlen;
	व्योम *cqc;
	व्योम *in;
	पूर्णांक err;
	पूर्णांक eqn;

	err = mlx5_db_alloc(mdev, &vcq->db);
	अगर (err)
		वापस err;

	vcq->mcq.set_ci_db = vcq->db.db;
	vcq->mcq.arm_db = vcq->db.db + 1;
	vcq->mcq.cqe_sz = 64;

	err = cq_frag_buf_alloc(ndev, &vcq->buf, num_ent);
	अगर (err)
		जाओ err_db;

	cq_frag_buf_init(vcq, &vcq->buf);

	inlen = MLX5_ST_SZ_BYTES(create_cq_in) +
		MLX5_FLD_SZ_BYTES(create_cq_in, pas[0]) * vcq->buf.frag_buf.npages;
	in = kzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		जाओ err_vzalloc;
	पूर्ण

	MLX5_SET(create_cq_in, in, uid, ndev->mvdev.res.uid);
	pas = (__be64 *)MLX5_ADDR_OF(create_cq_in, in, pas);
	mlx5_fill_page_frag_array(&vcq->buf.frag_buf, pas);

	cqc = MLX5_ADDR_OF(create_cq_in, in, cq_context);
	MLX5_SET(cqc, cqc, log_page_size, vcq->buf.frag_buf.page_shअगरt - MLX5_ADAPTER_PAGE_SHIFT);

	/* Use vector 0 by शेष. Consider adding code to choose least used
	 * vector.
	 */
	err = mlx5_vector2eqn(mdev, 0, &eqn, &irqn);
	अगर (err)
		जाओ err_vec;

	cqc = MLX5_ADDR_OF(create_cq_in, in, cq_context);
	MLX5_SET(cqc, cqc, log_cq_size, ilog2(num_ent));
	MLX5_SET(cqc, cqc, uar_page, ndev->mvdev.res.uar->index);
	MLX5_SET(cqc, cqc, c_eqn, eqn);
	MLX5_SET64(cqc, cqc, dbr_addr, vcq->db.dma);

	err = mlx5_core_create_cq(mdev, &vcq->mcq, in, inlen, out, माप(out));
	अगर (err)
		जाओ err_vec;

	vcq->mcq.comp = mlx5_vdpa_cq_comp;
	vcq->cqe = num_ent;
	vcq->mcq.set_ci_db = vcq->db.db;
	vcq->mcq.arm_db = vcq->db.db + 1;
	mlx5_cq_arm(&mvq->cq.mcq, MLX5_CQ_DB_REQ_NOT, uar_page, mvq->cq.mcq.cons_index);
	kमुक्त(in);
	वापस 0;

err_vec:
	kमुक्त(in);
err_vzalloc:
	cq_frag_buf_मुक्त(ndev, &vcq->buf);
err_db:
	mlx5_db_मुक्त(ndev->mvdev.mdev, &vcq->db);
	वापस err;
पूर्ण

अटल व्योम cq_destroy(काष्ठा mlx5_vdpa_net *ndev, u16 idx)
अणु
	काष्ठा mlx5_vdpa_virtqueue *mvq = &ndev->vqs[idx];
	काष्ठा mlx5_core_dev *mdev = ndev->mvdev.mdev;
	काष्ठा mlx5_vdpa_cq *vcq = &mvq->cq;

	अगर (mlx5_core_destroy_cq(mdev, &vcq->mcq)) अणु
		mlx5_vdpa_warn(&ndev->mvdev, "destroy CQ 0x%x\n", vcq->mcq.cqn);
		वापस;
	पूर्ण
	cq_frag_buf_मुक्त(ndev, &vcq->buf);
	mlx5_db_मुक्त(ndev->mvdev.mdev, &vcq->db);
पूर्ण

अटल पूर्णांक umem_size(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_virtqueue *mvq, पूर्णांक num,
		     काष्ठा mlx5_vdpa_umem **umemp)
अणु
	काष्ठा mlx5_core_dev *mdev = ndev->mvdev.mdev;
	पूर्णांक p_a;
	पूर्णांक p_b;

	चयन (num) अणु
	हाल 1:
		p_a = MLX5_CAP_DEV_VDPA_EMULATION(mdev, umem_1_buffer_param_a);
		p_b = MLX5_CAP_DEV_VDPA_EMULATION(mdev, umem_1_buffer_param_b);
		*umemp = &mvq->umem1;
		अवरोध;
	हाल 2:
		p_a = MLX5_CAP_DEV_VDPA_EMULATION(mdev, umem_2_buffer_param_a);
		p_b = MLX5_CAP_DEV_VDPA_EMULATION(mdev, umem_2_buffer_param_b);
		*umemp = &mvq->umem2;
		अवरोध;
	हाल 3:
		p_a = MLX5_CAP_DEV_VDPA_EMULATION(mdev, umem_3_buffer_param_a);
		p_b = MLX5_CAP_DEV_VDPA_EMULATION(mdev, umem_3_buffer_param_b);
		*umemp = &mvq->umem3;
		अवरोध;
	पूर्ण
	वापस p_a * mvq->num_ent + p_b;
पूर्ण

अटल व्योम umem_frag_buf_मुक्त(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_umem *umem)
अणु
	mlx5_frag_buf_मुक्त(ndev->mvdev.mdev, &umem->frag_buf);
पूर्ण

अटल पूर्णांक create_umem(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_virtqueue *mvq, पूर्णांक num)
अणु
	पूर्णांक inlen;
	u32 out[MLX5_ST_SZ_DW(create_umem_out)] = अणुपूर्ण;
	व्योम *um;
	व्योम *in;
	पूर्णांक err;
	__be64 *pas;
	पूर्णांक size;
	काष्ठा mlx5_vdpa_umem *umem;

	size = umem_size(ndev, mvq, num, &umem);
	अगर (size < 0)
		वापस size;

	umem->size = size;
	err = umem_frag_buf_alloc(ndev, umem, size);
	अगर (err)
		वापस err;

	inlen = MLX5_ST_SZ_BYTES(create_umem_in) + MLX5_ST_SZ_BYTES(mtt) * umem->frag_buf.npages;

	in = kzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		जाओ err_in;
	पूर्ण

	MLX5_SET(create_umem_in, in, opcode, MLX5_CMD_OP_CREATE_UMEM);
	MLX5_SET(create_umem_in, in, uid, ndev->mvdev.res.uid);
	um = MLX5_ADDR_OF(create_umem_in, in, umem);
	MLX5_SET(umem, um, log_page_size, umem->frag_buf.page_shअगरt - MLX5_ADAPTER_PAGE_SHIFT);
	MLX5_SET64(umem, um, num_of_mtt, umem->frag_buf.npages);

	pas = (__be64 *)MLX5_ADDR_OF(umem, um, mtt[0]);
	mlx5_fill_page_frag_array_perm(&umem->frag_buf, pas, MLX5_MTT_PERM_RW);

	err = mlx5_cmd_exec(ndev->mvdev.mdev, in, inlen, out, माप(out));
	अगर (err) अणु
		mlx5_vdpa_warn(&ndev->mvdev, "create umem(%d)\n", err);
		जाओ err_cmd;
	पूर्ण

	kमुक्त(in);
	umem->id = MLX5_GET(create_umem_out, out, umem_id);

	वापस 0;

err_cmd:
	kमुक्त(in);
err_in:
	umem_frag_buf_मुक्त(ndev, umem);
	वापस err;
पूर्ण

अटल व्योम umem_destroy(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_virtqueue *mvq, पूर्णांक num)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_umem_in)] = अणुपूर्ण;
	u32 out[MLX5_ST_SZ_DW(destroy_umem_out)] = अणुपूर्ण;
	काष्ठा mlx5_vdpa_umem *umem;

	चयन (num) अणु
	हाल 1:
		umem = &mvq->umem1;
		अवरोध;
	हाल 2:
		umem = &mvq->umem2;
		अवरोध;
	हाल 3:
		umem = &mvq->umem3;
		अवरोध;
	पूर्ण

	MLX5_SET(destroy_umem_in, in, opcode, MLX5_CMD_OP_DESTROY_UMEM);
	MLX5_SET(destroy_umem_in, in, umem_id, umem->id);
	अगर (mlx5_cmd_exec(ndev->mvdev.mdev, in, माप(in), out, माप(out)))
		वापस;

	umem_frag_buf_मुक्त(ndev, umem);
पूर्ण

अटल पूर्णांक umems_create(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_virtqueue *mvq)
अणु
	पूर्णांक num;
	पूर्णांक err;

	क्रम (num = 1; num <= 3; num++) अणु
		err = create_umem(ndev, mvq, num);
		अगर (err)
			जाओ err_umem;
	पूर्ण
	वापस 0;

err_umem:
	क्रम (num--; num > 0; num--)
		umem_destroy(ndev, mvq, num);

	वापस err;
पूर्ण

अटल व्योम umems_destroy(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_virtqueue *mvq)
अणु
	पूर्णांक num;

	क्रम (num = 3; num > 0; num--)
		umem_destroy(ndev, mvq, num);
पूर्ण

अटल पूर्णांक get_queue_type(काष्ठा mlx5_vdpa_net *ndev)
अणु
	u32 type_mask;

	type_mask = MLX5_CAP_DEV_VDPA_EMULATION(ndev->mvdev.mdev, virtio_queue_type);

	/* prefer split queue */
	अगर (type_mask & MLX5_VIRTIO_EMULATION_CAP_VIRTIO_QUEUE_TYPE_PACKED)
		वापस MLX5_VIRTIO_EMULATION_VIRTIO_QUEUE_TYPE_PACKED;

	WARN_ON(!(type_mask & MLX5_VIRTIO_EMULATION_CAP_VIRTIO_QUEUE_TYPE_SPLIT));

	वापस MLX5_VIRTIO_EMULATION_VIRTIO_QUEUE_TYPE_SPLIT;
पूर्ण

अटल bool vq_is_tx(u16 idx)
अणु
	वापस idx % 2;
पूर्ण

अटल u16 get_features_12_3(u64 features)
अणु
	वापस (!!(features & BIT_ULL(VIRTIO_NET_F_HOST_TSO4)) << 9) |
	       (!!(features & BIT_ULL(VIRTIO_NET_F_HOST_TSO6)) << 8) |
	       (!!(features & BIT_ULL(VIRTIO_NET_F_CSUM)) << 7) |
	       (!!(features & BIT_ULL(VIRTIO_NET_F_GUEST_CSUM)) << 6);
पूर्ण

अटल पूर्णांक create_virtqueue(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_virtqueue *mvq)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_virtio_net_q_in);
	u32 out[MLX5_ST_SZ_DW(create_virtio_net_q_out)] = अणुपूर्ण;
	व्योम *obj_context;
	व्योम *cmd_hdr;
	व्योम *vq_ctx;
	व्योम *in;
	पूर्णांक err;

	err = umems_create(ndev, mvq);
	अगर (err)
		वापस err;

	in = kzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	cmd_hdr = MLX5_ADDR_OF(create_virtio_net_q_in, in, general_obj_in_cmd_hdr);

	MLX5_SET(general_obj_in_cmd_hdr, cmd_hdr, opcode, MLX5_CMD_OP_CREATE_GENERAL_OBJECT);
	MLX5_SET(general_obj_in_cmd_hdr, cmd_hdr, obj_type, MLX5_OBJ_TYPE_VIRTIO_NET_Q);
	MLX5_SET(general_obj_in_cmd_hdr, cmd_hdr, uid, ndev->mvdev.res.uid);

	obj_context = MLX5_ADDR_OF(create_virtio_net_q_in, in, obj_context);
	MLX5_SET(virtio_net_q_object, obj_context, hw_available_index, mvq->avail_idx);
	MLX5_SET(virtio_net_q_object, obj_context, hw_used_index, mvq->used_idx);
	MLX5_SET(virtio_net_q_object, obj_context, queue_feature_bit_mask_12_3,
		 get_features_12_3(ndev->mvdev.actual_features));
	vq_ctx = MLX5_ADDR_OF(virtio_net_q_object, obj_context, virtio_q_context);
	MLX5_SET(virtio_q, vq_ctx, virtio_q_type, get_queue_type(ndev));

	अगर (vq_is_tx(mvq->index))
		MLX5_SET(virtio_net_q_object, obj_context, tisn_or_qpn, ndev->res.tisn);

	MLX5_SET(virtio_q, vq_ctx, event_mode, MLX5_VIRTIO_Q_EVENT_MODE_QP_MODE);
	MLX5_SET(virtio_q, vq_ctx, queue_index, mvq->index);
	MLX5_SET(virtio_q, vq_ctx, event_qpn_or_msix, mvq->fwqp.mqp.qpn);
	MLX5_SET(virtio_q, vq_ctx, queue_size, mvq->num_ent);
	MLX5_SET(virtio_q, vq_ctx, virtio_version_1_0,
		 !!(ndev->mvdev.actual_features & BIT_ULL(VIRTIO_F_VERSION_1)));
	MLX5_SET64(virtio_q, vq_ctx, desc_addr, mvq->desc_addr);
	MLX5_SET64(virtio_q, vq_ctx, used_addr, mvq->device_addr);
	MLX5_SET64(virtio_q, vq_ctx, available_addr, mvq->driver_addr);
	MLX5_SET(virtio_q, vq_ctx, virtio_q_mkey, ndev->mvdev.mr.mkey.key);
	MLX5_SET(virtio_q, vq_ctx, umem_1_id, mvq->umem1.id);
	MLX5_SET(virtio_q, vq_ctx, umem_1_size, mvq->umem1.size);
	MLX5_SET(virtio_q, vq_ctx, umem_2_id, mvq->umem2.id);
	MLX5_SET(virtio_q, vq_ctx, umem_2_size, mvq->umem1.size);
	MLX5_SET(virtio_q, vq_ctx, umem_3_id, mvq->umem3.id);
	MLX5_SET(virtio_q, vq_ctx, umem_3_size, mvq->umem1.size);
	MLX5_SET(virtio_q, vq_ctx, pd, ndev->mvdev.res.pdn);
	अगर (MLX5_CAP_DEV_VDPA_EMULATION(ndev->mvdev.mdev, eth_frame_offload_type))
		MLX5_SET(virtio_q, vq_ctx, virtio_version_1_0, 1);

	err = mlx5_cmd_exec(ndev->mvdev.mdev, in, inlen, out, माप(out));
	अगर (err)
		जाओ err_cmd;

	kमुक्त(in);
	mvq->virtq_id = MLX5_GET(general_obj_out_cmd_hdr, out, obj_id);

	वापस 0;

err_cmd:
	kमुक्त(in);
err_alloc:
	umems_destroy(ndev, mvq);
	वापस err;
पूर्ण

अटल व्योम destroy_virtqueue(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_virtqueue *mvq)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_virtio_net_q_in)] = अणुपूर्ण;
	u32 out[MLX5_ST_SZ_DW(destroy_virtio_net_q_out)] = अणुपूर्ण;

	MLX5_SET(destroy_virtio_net_q_in, in, general_obj_out_cmd_hdr.opcode,
		 MLX5_CMD_OP_DESTROY_GENERAL_OBJECT);
	MLX5_SET(destroy_virtio_net_q_in, in, general_obj_out_cmd_hdr.obj_id, mvq->virtq_id);
	MLX5_SET(destroy_virtio_net_q_in, in, general_obj_out_cmd_hdr.uid, ndev->mvdev.res.uid);
	MLX5_SET(destroy_virtio_net_q_in, in, general_obj_out_cmd_hdr.obj_type,
		 MLX5_OBJ_TYPE_VIRTIO_NET_Q);
	अगर (mlx5_cmd_exec(ndev->mvdev.mdev, in, माप(in), out, माप(out))) अणु
		mlx5_vdpa_warn(&ndev->mvdev, "destroy virtqueue 0x%x\n", mvq->virtq_id);
		वापस;
	पूर्ण
	umems_destroy(ndev, mvq);
पूर्ण

अटल u32 get_rqpn(काष्ठा mlx5_vdpa_virtqueue *mvq, bool fw)
अणु
	वापस fw ? mvq->vqqp.mqp.qpn : mvq->fwqp.mqp.qpn;
पूर्ण

अटल u32 get_qpn(काष्ठा mlx5_vdpa_virtqueue *mvq, bool fw)
अणु
	वापस fw ? mvq->fwqp.mqp.qpn : mvq->vqqp.mqp.qpn;
पूर्ण

अटल व्योम alloc_inout(काष्ठा mlx5_vdpa_net *ndev, पूर्णांक cmd, व्योम **in, पूर्णांक *inlen, व्योम **out,
			पूर्णांक *outlen, u32 qpn, u32 rqpn)
अणु
	व्योम *qpc;
	व्योम *pp;

	चयन (cmd) अणु
	हाल MLX5_CMD_OP_2RST_QP:
		*inlen = MLX5_ST_SZ_BYTES(qp_2rst_in);
		*outlen = MLX5_ST_SZ_BYTES(qp_2rst_out);
		*in = kzalloc(*inlen, GFP_KERNEL);
		*out = kzalloc(*outlen, GFP_KERNEL);
		अगर (!*in || !*out)
			जाओ outerr;

		MLX5_SET(qp_2rst_in, *in, opcode, cmd);
		MLX5_SET(qp_2rst_in, *in, uid, ndev->mvdev.res.uid);
		MLX5_SET(qp_2rst_in, *in, qpn, qpn);
		अवरोध;
	हाल MLX5_CMD_OP_RST2INIT_QP:
		*inlen = MLX5_ST_SZ_BYTES(rst2init_qp_in);
		*outlen = MLX5_ST_SZ_BYTES(rst2init_qp_out);
		*in = kzalloc(*inlen, GFP_KERNEL);
		*out = kzalloc(MLX5_ST_SZ_BYTES(rst2init_qp_out), GFP_KERNEL);
		अगर (!*in || !*out)
			जाओ outerr;

		MLX5_SET(rst2init_qp_in, *in, opcode, cmd);
		MLX5_SET(rst2init_qp_in, *in, uid, ndev->mvdev.res.uid);
		MLX5_SET(rst2init_qp_in, *in, qpn, qpn);
		qpc = MLX5_ADDR_OF(rst2init_qp_in, *in, qpc);
		MLX5_SET(qpc, qpc, remote_qpn, rqpn);
		MLX5_SET(qpc, qpc, rwe, 1);
		pp = MLX5_ADDR_OF(qpc, qpc, primary_address_path);
		MLX5_SET(ads, pp, vhca_port_num, 1);
		अवरोध;
	हाल MLX5_CMD_OP_INIT2RTR_QP:
		*inlen = MLX5_ST_SZ_BYTES(init2rtr_qp_in);
		*outlen = MLX5_ST_SZ_BYTES(init2rtr_qp_out);
		*in = kzalloc(*inlen, GFP_KERNEL);
		*out = kzalloc(MLX5_ST_SZ_BYTES(init2rtr_qp_out), GFP_KERNEL);
		अगर (!*in || !*out)
			जाओ outerr;

		MLX5_SET(init2rtr_qp_in, *in, opcode, cmd);
		MLX5_SET(init2rtr_qp_in, *in, uid, ndev->mvdev.res.uid);
		MLX5_SET(init2rtr_qp_in, *in, qpn, qpn);
		qpc = MLX5_ADDR_OF(rst2init_qp_in, *in, qpc);
		MLX5_SET(qpc, qpc, mtu, MLX5_QPC_MTU_256_BYTES);
		MLX5_SET(qpc, qpc, log_msg_max, 30);
		MLX5_SET(qpc, qpc, remote_qpn, rqpn);
		pp = MLX5_ADDR_OF(qpc, qpc, primary_address_path);
		MLX5_SET(ads, pp, fl, 1);
		अवरोध;
	हाल MLX5_CMD_OP_RTR2RTS_QP:
		*inlen = MLX5_ST_SZ_BYTES(rtr2rts_qp_in);
		*outlen = MLX5_ST_SZ_BYTES(rtr2rts_qp_out);
		*in = kzalloc(*inlen, GFP_KERNEL);
		*out = kzalloc(MLX5_ST_SZ_BYTES(rtr2rts_qp_out), GFP_KERNEL);
		अगर (!*in || !*out)
			जाओ outerr;

		MLX5_SET(rtr2rts_qp_in, *in, opcode, cmd);
		MLX5_SET(rtr2rts_qp_in, *in, uid, ndev->mvdev.res.uid);
		MLX5_SET(rtr2rts_qp_in, *in, qpn, qpn);
		qpc = MLX5_ADDR_OF(rst2init_qp_in, *in, qpc);
		pp = MLX5_ADDR_OF(qpc, qpc, primary_address_path);
		MLX5_SET(ads, pp, ack_समयout, 14);
		MLX5_SET(qpc, qpc, retry_count, 7);
		MLX5_SET(qpc, qpc, rnr_retry, 7);
		अवरोध;
	शेष:
		जाओ outerr_nullअगरy;
	पूर्ण

	वापस;

outerr:
	kमुक्त(*in);
	kमुक्त(*out);
outerr_nullअगरy:
	*in = शून्य;
	*out = शून्य;
पूर्ण

अटल व्योम मुक्त_inout(व्योम *in, व्योम *out)
अणु
	kमुक्त(in);
	kमुक्त(out);
पूर्ण

/* Two QPs are used by each virtqueue. One is used by the driver and one by
 * firmware. The fw argument indicates whether the subjected QP is the one used
 * by firmware.
 */
अटल पूर्णांक modअगरy_qp(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_virtqueue *mvq, bool fw, पूर्णांक cmd)
अणु
	पूर्णांक outlen;
	पूर्णांक inlen;
	व्योम *out;
	व्योम *in;
	पूर्णांक err;

	alloc_inout(ndev, cmd, &in, &inlen, &out, &outlen, get_qpn(mvq, fw), get_rqpn(mvq, fw));
	अगर (!in || !out)
		वापस -ENOMEM;

	err = mlx5_cmd_exec(ndev->mvdev.mdev, in, inlen, out, outlen);
	मुक्त_inout(in, out);
	वापस err;
पूर्ण

अटल पूर्णांक connect_qps(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_virtqueue *mvq)
अणु
	पूर्णांक err;

	err = modअगरy_qp(ndev, mvq, true, MLX5_CMD_OP_2RST_QP);
	अगर (err)
		वापस err;

	err = modअगरy_qp(ndev, mvq, false, MLX5_CMD_OP_2RST_QP);
	अगर (err)
		वापस err;

	err = modअगरy_qp(ndev, mvq, true, MLX5_CMD_OP_RST2INIT_QP);
	अगर (err)
		वापस err;

	err = modअगरy_qp(ndev, mvq, false, MLX5_CMD_OP_RST2INIT_QP);
	अगर (err)
		वापस err;

	err = modअगरy_qp(ndev, mvq, true, MLX5_CMD_OP_INIT2RTR_QP);
	अगर (err)
		वापस err;

	err = modअगरy_qp(ndev, mvq, false, MLX5_CMD_OP_INIT2RTR_QP);
	अगर (err)
		वापस err;

	वापस modअगरy_qp(ndev, mvq, true, MLX5_CMD_OP_RTR2RTS_QP);
पूर्ण

काष्ठा mlx5_virtq_attr अणु
	u8 state;
	u16 available_index;
	u16 used_index;
पूर्ण;

अटल पूर्णांक query_virtqueue(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_virtqueue *mvq,
			   काष्ठा mlx5_virtq_attr *attr)
अणु
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(query_virtio_net_q_out);
	u32 in[MLX5_ST_SZ_DW(query_virtio_net_q_in)] = अणुपूर्ण;
	व्योम *out;
	व्योम *obj_context;
	व्योम *cmd_hdr;
	पूर्णांक err;

	out = kzalloc(outlen, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	cmd_hdr = MLX5_ADDR_OF(query_virtio_net_q_in, in, general_obj_in_cmd_hdr);

	MLX5_SET(general_obj_in_cmd_hdr, cmd_hdr, opcode, MLX5_CMD_OP_QUERY_GENERAL_OBJECT);
	MLX5_SET(general_obj_in_cmd_hdr, cmd_hdr, obj_type, MLX5_OBJ_TYPE_VIRTIO_NET_Q);
	MLX5_SET(general_obj_in_cmd_hdr, cmd_hdr, obj_id, mvq->virtq_id);
	MLX5_SET(general_obj_in_cmd_hdr, cmd_hdr, uid, ndev->mvdev.res.uid);
	err = mlx5_cmd_exec(ndev->mvdev.mdev, in, माप(in), out, outlen);
	अगर (err)
		जाओ err_cmd;

	obj_context = MLX5_ADDR_OF(query_virtio_net_q_out, out, obj_context);
	स_रखो(attr, 0, माप(*attr));
	attr->state = MLX5_GET(virtio_net_q_object, obj_context, state);
	attr->available_index = MLX5_GET(virtio_net_q_object, obj_context, hw_available_index);
	attr->used_index = MLX5_GET(virtio_net_q_object, obj_context, hw_used_index);
	kमुक्त(out);
	वापस 0;

err_cmd:
	kमुक्त(out);
	वापस err;
पूर्ण

अटल पूर्णांक modअगरy_virtqueue(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_virtqueue *mvq, पूर्णांक state)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(modअगरy_virtio_net_q_in);
	u32 out[MLX5_ST_SZ_DW(modअगरy_virtio_net_q_out)] = अणुपूर्ण;
	व्योम *obj_context;
	व्योम *cmd_hdr;
	व्योम *in;
	पूर्णांक err;

	in = kzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	cmd_hdr = MLX5_ADDR_OF(modअगरy_virtio_net_q_in, in, general_obj_in_cmd_hdr);

	MLX5_SET(general_obj_in_cmd_hdr, cmd_hdr, opcode, MLX5_CMD_OP_MODIFY_GENERAL_OBJECT);
	MLX5_SET(general_obj_in_cmd_hdr, cmd_hdr, obj_type, MLX5_OBJ_TYPE_VIRTIO_NET_Q);
	MLX5_SET(general_obj_in_cmd_hdr, cmd_hdr, obj_id, mvq->virtq_id);
	MLX5_SET(general_obj_in_cmd_hdr, cmd_hdr, uid, ndev->mvdev.res.uid);

	obj_context = MLX5_ADDR_OF(modअगरy_virtio_net_q_in, in, obj_context);
	MLX5_SET64(virtio_net_q_object, obj_context, modअगरy_field_select,
		   MLX5_VIRTQ_MODIFY_MASK_STATE);
	MLX5_SET(virtio_net_q_object, obj_context, state, state);
	err = mlx5_cmd_exec(ndev->mvdev.mdev, in, inlen, out, माप(out));
	kमुक्त(in);
	अगर (!err)
		mvq->fw_state = state;

	वापस err;
पूर्ण

अटल पूर्णांक setup_vq(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_virtqueue *mvq)
अणु
	u16 idx = mvq->index;
	पूर्णांक err;

	अगर (!mvq->num_ent)
		वापस 0;

	अगर (mvq->initialized) अणु
		mlx5_vdpa_warn(&ndev->mvdev, "attempt re init\n");
		वापस -EINVAL;
	पूर्ण

	err = cq_create(ndev, idx, mvq->num_ent);
	अगर (err)
		वापस err;

	err = qp_create(ndev, mvq, &mvq->fwqp);
	अगर (err)
		जाओ err_fwqp;

	err = qp_create(ndev, mvq, &mvq->vqqp);
	अगर (err)
		जाओ err_vqqp;

	err = connect_qps(ndev, mvq);
	अगर (err)
		जाओ err_connect;

	err = create_virtqueue(ndev, mvq);
	अगर (err)
		जाओ err_connect;

	अगर (mvq->पढ़ोy) अणु
		err = modअगरy_virtqueue(ndev, mvq, MLX5_VIRTIO_NET_Q_OBJECT_STATE_RDY);
		अगर (err) अणु
			mlx5_vdpa_warn(&ndev->mvdev, "failed to modify to ready vq idx %d(%d)\n",
				       idx, err);
			जाओ err_connect;
		पूर्ण
	पूर्ण

	mvq->initialized = true;
	वापस 0;

err_connect:
	qp_destroy(ndev, &mvq->vqqp);
err_vqqp:
	qp_destroy(ndev, &mvq->fwqp);
err_fwqp:
	cq_destroy(ndev, idx);
	वापस err;
पूर्ण

अटल व्योम suspend_vq(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_virtqueue *mvq)
अणु
	काष्ठा mlx5_virtq_attr attr;

	अगर (!mvq->initialized)
		वापस;

	अगर (mvq->fw_state != MLX5_VIRTIO_NET_Q_OBJECT_STATE_RDY)
		वापस;

	अगर (modअगरy_virtqueue(ndev, mvq, MLX5_VIRTIO_NET_Q_OBJECT_STATE_SUSPEND))
		mlx5_vdpa_warn(&ndev->mvdev, "modify to suspend failed\n");

	अगर (query_virtqueue(ndev, mvq, &attr)) अणु
		mlx5_vdpa_warn(&ndev->mvdev, "failed to query virtqueue\n");
		वापस;
	पूर्ण
	mvq->avail_idx = attr.available_index;
	mvq->used_idx = attr.used_index;
पूर्ण

अटल व्योम suspend_vqs(काष्ठा mlx5_vdpa_net *ndev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLX5_MAX_SUPPORTED_VQS; i++)
		suspend_vq(ndev, &ndev->vqs[i]);
पूर्ण

अटल व्योम tearकरोwn_vq(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_virtqueue *mvq)
अणु
	अगर (!mvq->initialized)
		वापस;

	suspend_vq(ndev, mvq);
	destroy_virtqueue(ndev, mvq);
	qp_destroy(ndev, &mvq->vqqp);
	qp_destroy(ndev, &mvq->fwqp);
	cq_destroy(ndev, mvq->index);
	mvq->initialized = false;
पूर्ण

अटल पूर्णांक create_rqt(काष्ठा mlx5_vdpa_net *ndev)
अणु
	पूर्णांक log_max_rqt;
	__be32 *list;
	व्योम *rqtc;
	पूर्णांक inlen;
	व्योम *in;
	पूर्णांक i, j;
	पूर्णांक err;

	log_max_rqt = min_t(पूर्णांक, 1, MLX5_CAP_GEN(ndev->mvdev.mdev, log_max_rqt_size));
	अगर (log_max_rqt < 1)
		वापस -EOPNOTSUPP;

	inlen = MLX5_ST_SZ_BYTES(create_rqt_in) + (1 << log_max_rqt) * MLX5_ST_SZ_BYTES(rq_num);
	in = kzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(create_rqt_in, in, uid, ndev->mvdev.res.uid);
	rqtc = MLX5_ADDR_OF(create_rqt_in, in, rqt_context);

	MLX5_SET(rqtc, rqtc, list_q_type, MLX5_RQTC_LIST_Q_TYPE_VIRTIO_NET_Q);
	MLX5_SET(rqtc, rqtc, rqt_max_size, 1 << log_max_rqt);
	MLX5_SET(rqtc, rqtc, rqt_actual_size, 1);
	list = MLX5_ADDR_OF(rqtc, rqtc, rq_num[0]);
	क्रम (i = 0, j = 0; j < ndev->mvdev.max_vqs; j++) अणु
		अगर (!ndev->vqs[j].initialized)
			जारी;

		अगर (!vq_is_tx(ndev->vqs[j].index)) अणु
			list[i] = cpu_to_be32(ndev->vqs[j].virtq_id);
			i++;
		पूर्ण
	पूर्ण

	err = mlx5_vdpa_create_rqt(&ndev->mvdev, in, inlen, &ndev->res.rqtn);
	kमुक्त(in);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल व्योम destroy_rqt(काष्ठा mlx5_vdpa_net *ndev)
अणु
	mlx5_vdpa_destroy_rqt(&ndev->mvdev, ndev->res.rqtn);
पूर्ण

अटल पूर्णांक create_tir(काष्ठा mlx5_vdpa_net *ndev)
अणु
#घोषणा HASH_IP_L4PORTS                                                                            \
	(MLX5_HASH_FIELD_SEL_SRC_IP | MLX5_HASH_FIELD_SEL_DST_IP | MLX5_HASH_FIELD_SEL_L4_SPORT |  \
	 MLX5_HASH_FIELD_SEL_L4_DPORT)
	अटल स्थिर u8 rx_hash_toeplitz_key[] = अणु 0x2c, 0xc6, 0x81, 0xd1, 0x5b, 0xdb, 0xf4, 0xf7,
						   0xfc, 0xa2, 0x83, 0x19, 0xdb, 0x1a, 0x3e, 0x94,
						   0x6b, 0x9e, 0x38, 0xd9, 0x2c, 0x9c, 0x03, 0xd1,
						   0xad, 0x99, 0x44, 0xa7, 0xd9, 0x56, 0x3d, 0x59,
						   0x06, 0x3c, 0x25, 0xf3, 0xfc, 0x1f, 0xdc, 0x2a पूर्ण;
	व्योम *rss_key;
	व्योम *outer;
	व्योम *tirc;
	व्योम *in;
	पूर्णांक err;

	in = kzalloc(MLX5_ST_SZ_BYTES(create_tir_in), GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(create_tir_in, in, uid, ndev->mvdev.res.uid);
	tirc = MLX5_ADDR_OF(create_tir_in, in, ctx);
	MLX5_SET(tirc, tirc, disp_type, MLX5_TIRC_DISP_TYPE_INसूचीECT);

	MLX5_SET(tirc, tirc, rx_hash_symmetric, 1);
	MLX5_SET(tirc, tirc, rx_hash_fn, MLX5_RX_HASH_FN_TOEPLITZ);
	rss_key = MLX5_ADDR_OF(tirc, tirc, rx_hash_toeplitz_key);
	स_नकल(rss_key, rx_hash_toeplitz_key, माप(rx_hash_toeplitz_key));

	outer = MLX5_ADDR_OF(tirc, tirc, rx_hash_field_selector_outer);
	MLX5_SET(rx_hash_field_select, outer, l3_prot_type, MLX5_L3_PROT_TYPE_IPV4);
	MLX5_SET(rx_hash_field_select, outer, l4_prot_type, MLX5_L4_PROT_TYPE_TCP);
	MLX5_SET(rx_hash_field_select, outer, selected_fields, HASH_IP_L4PORTS);

	MLX5_SET(tirc, tirc, indirect_table, ndev->res.rqtn);
	MLX5_SET(tirc, tirc, transport_करोमुख्य, ndev->res.tdn);

	err = mlx5_vdpa_create_tir(&ndev->mvdev, in, &ndev->res.tirn);
	kमुक्त(in);
	वापस err;
पूर्ण

अटल व्योम destroy_tir(काष्ठा mlx5_vdpa_net *ndev)
अणु
	mlx5_vdpa_destroy_tir(&ndev->mvdev, ndev->res.tirn);
पूर्ण

अटल पूर्णांक add_fwd_to_tir(काष्ठा mlx5_vdpa_net *ndev)
अणु
	काष्ठा mlx5_flow_destination dest[2] = अणुपूर्ण;
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5_flow_act flow_act = अणुपूर्ण;
	काष्ठा mlx5_flow_namespace *ns;
	पूर्णांक err;

	/* क्रम now, one entry, match all, क्रमward to tir */
	ft_attr.max_fte = 1;
	ft_attr.स्वतःgroup.max_num_groups = 1;

	ns = mlx5_get_flow_namespace(ndev->mvdev.mdev, MLX5_FLOW_NAMESPACE_BYPASS);
	अगर (!ns) अणु
		mlx5_vdpa_warn(&ndev->mvdev, "get flow namespace\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	ndev->rxft = mlx5_create_स्वतः_grouped_flow_table(ns, &ft_attr);
	अगर (IS_ERR(ndev->rxft))
		वापस PTR_ERR(ndev->rxft);

	ndev->rx_counter = mlx5_fc_create(ndev->mvdev.mdev, false);
	अगर (IS_ERR(ndev->rx_counter)) अणु
		err = PTR_ERR(ndev->rx_counter);
		जाओ err_fc;
	पूर्ण

	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST | MLX5_FLOW_CONTEXT_ACTION_COUNT;
	dest[0].type = MLX5_FLOW_DESTINATION_TYPE_TIR;
	dest[0].tir_num = ndev->res.tirn;
	dest[1].type = MLX5_FLOW_DESTINATION_TYPE_COUNTER;
	dest[1].counter_id = mlx5_fc_id(ndev->rx_counter);
	ndev->rx_rule = mlx5_add_flow_rules(ndev->rxft, शून्य, &flow_act, dest, 2);
	अगर (IS_ERR(ndev->rx_rule)) अणु
		err = PTR_ERR(ndev->rx_rule);
		ndev->rx_rule = शून्य;
		जाओ err_rule;
	पूर्ण

	वापस 0;

err_rule:
	mlx5_fc_destroy(ndev->mvdev.mdev, ndev->rx_counter);
err_fc:
	mlx5_destroy_flow_table(ndev->rxft);
	वापस err;
पूर्ण

अटल व्योम हटाओ_fwd_to_tir(काष्ठा mlx5_vdpa_net *ndev)
अणु
	अगर (!ndev->rx_rule)
		वापस;

	mlx5_del_flow_rules(ndev->rx_rule);
	mlx5_fc_destroy(ndev->mvdev.mdev, ndev->rx_counter);
	mlx5_destroy_flow_table(ndev->rxft);

	ndev->rx_rule = शून्य;
पूर्ण

अटल व्योम mlx5_vdpa_kick_vq(काष्ठा vdpa_device *vdev, u16 idx)
अणु
	काष्ठा mlx5_vdpa_dev *mvdev = to_mvdev(vdev);
	काष्ठा mlx5_vdpa_net *ndev = to_mlx5_vdpa_ndev(mvdev);
	काष्ठा mlx5_vdpa_virtqueue *mvq = &ndev->vqs[idx];

	अगर (unlikely(!mvq->पढ़ोy))
		वापस;

	ioग_लिखो16(idx, ndev->mvdev.res.kick_addr);
पूर्ण

अटल पूर्णांक mlx5_vdpa_set_vq_address(काष्ठा vdpa_device *vdev, u16 idx, u64 desc_area,
				    u64 driver_area, u64 device_area)
अणु
	काष्ठा mlx5_vdpa_dev *mvdev = to_mvdev(vdev);
	काष्ठा mlx5_vdpa_net *ndev = to_mlx5_vdpa_ndev(mvdev);
	काष्ठा mlx5_vdpa_virtqueue *mvq = &ndev->vqs[idx];

	mvq->desc_addr = desc_area;
	mvq->device_addr = device_area;
	mvq->driver_addr = driver_area;
	वापस 0;
पूर्ण

अटल व्योम mlx5_vdpa_set_vq_num(काष्ठा vdpa_device *vdev, u16 idx, u32 num)
अणु
	काष्ठा mlx5_vdpa_dev *mvdev = to_mvdev(vdev);
	काष्ठा mlx5_vdpa_net *ndev = to_mlx5_vdpa_ndev(mvdev);
	काष्ठा mlx5_vdpa_virtqueue *mvq;

	mvq = &ndev->vqs[idx];
	mvq->num_ent = num;
पूर्ण

अटल व्योम mlx5_vdpa_set_vq_cb(काष्ठा vdpa_device *vdev, u16 idx, काष्ठा vdpa_callback *cb)
अणु
	काष्ठा mlx5_vdpa_dev *mvdev = to_mvdev(vdev);
	काष्ठा mlx5_vdpa_net *ndev = to_mlx5_vdpa_ndev(mvdev);
	काष्ठा mlx5_vdpa_virtqueue *vq = &ndev->vqs[idx];

	vq->event_cb = *cb;
पूर्ण

अटल व्योम mlx5_vdpa_set_vq_पढ़ोy(काष्ठा vdpa_device *vdev, u16 idx, bool पढ़ोy)
अणु
	काष्ठा mlx5_vdpa_dev *mvdev = to_mvdev(vdev);
	काष्ठा mlx5_vdpa_net *ndev = to_mlx5_vdpa_ndev(mvdev);
	काष्ठा mlx5_vdpa_virtqueue *mvq = &ndev->vqs[idx];

	अगर (!पढ़ोy)
		suspend_vq(ndev, mvq);

	mvq->पढ़ोy = पढ़ोy;
पूर्ण

अटल bool mlx5_vdpa_get_vq_पढ़ोy(काष्ठा vdpa_device *vdev, u16 idx)
अणु
	काष्ठा mlx5_vdpa_dev *mvdev = to_mvdev(vdev);
	काष्ठा mlx5_vdpa_net *ndev = to_mlx5_vdpa_ndev(mvdev);
	काष्ठा mlx5_vdpa_virtqueue *mvq = &ndev->vqs[idx];

	वापस mvq->पढ़ोy;
पूर्ण

अटल पूर्णांक mlx5_vdpa_set_vq_state(काष्ठा vdpa_device *vdev, u16 idx,
				  स्थिर काष्ठा vdpa_vq_state *state)
अणु
	काष्ठा mlx5_vdpa_dev *mvdev = to_mvdev(vdev);
	काष्ठा mlx5_vdpa_net *ndev = to_mlx5_vdpa_ndev(mvdev);
	काष्ठा mlx5_vdpa_virtqueue *mvq = &ndev->vqs[idx];

	अगर (mvq->fw_state == MLX5_VIRTIO_NET_Q_OBJECT_STATE_RDY) अणु
		mlx5_vdpa_warn(mvdev, "can't modify available index\n");
		वापस -EINVAL;
	पूर्ण

	mvq->used_idx = state->avail_index;
	mvq->avail_idx = state->avail_index;
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_vdpa_get_vq_state(काष्ठा vdpa_device *vdev, u16 idx, काष्ठा vdpa_vq_state *state)
अणु
	काष्ठा mlx5_vdpa_dev *mvdev = to_mvdev(vdev);
	काष्ठा mlx5_vdpa_net *ndev = to_mlx5_vdpa_ndev(mvdev);
	काष्ठा mlx5_vdpa_virtqueue *mvq = &ndev->vqs[idx];
	काष्ठा mlx5_virtq_attr attr;
	पूर्णांक err;

	/* If the virtq object was destroyed, use the value saved at
	 * the last minute of suspend_vq. This caters क्रम userspace
	 * that cares about emulating the index after vq is stopped.
	 */
	अगर (!mvq->initialized) अणु
		/* Firmware वापसs a wrong value क्रम the available index.
		 * Since both values should be identical, we take the value of
		 * used_idx which is reported correctly.
		 */
		state->avail_index = mvq->used_idx;
		वापस 0;
	पूर्ण

	err = query_virtqueue(ndev, mvq, &attr);
	अगर (err) अणु
		mlx5_vdpa_warn(mvdev, "failed to query virtqueue\n");
		वापस err;
	पूर्ण
	state->avail_index = attr.used_index;
	वापस 0;
पूर्ण

अटल u32 mlx5_vdpa_get_vq_align(काष्ठा vdpa_device *vdev)
अणु
	वापस PAGE_SIZE;
पूर्ण

क्रमागत अणु MLX5_VIRTIO_NET_F_GUEST_CSUM = 1 << 9,
	MLX5_VIRTIO_NET_F_CSUM = 1 << 10,
	MLX5_VIRTIO_NET_F_HOST_TSO6 = 1 << 11,
	MLX5_VIRTIO_NET_F_HOST_TSO4 = 1 << 12,
पूर्ण;

अटल u64 mlx_to_vritio_features(u16 dev_features)
अणु
	u64 result = 0;

	अगर (dev_features & MLX5_VIRTIO_NET_F_GUEST_CSUM)
		result |= BIT_ULL(VIRTIO_NET_F_GUEST_CSUM);
	अगर (dev_features & MLX5_VIRTIO_NET_F_CSUM)
		result |= BIT_ULL(VIRTIO_NET_F_CSUM);
	अगर (dev_features & MLX5_VIRTIO_NET_F_HOST_TSO6)
		result |= BIT_ULL(VIRTIO_NET_F_HOST_TSO6);
	अगर (dev_features & MLX5_VIRTIO_NET_F_HOST_TSO4)
		result |= BIT_ULL(VIRTIO_NET_F_HOST_TSO4);

	वापस result;
पूर्ण

अटल u64 mlx5_vdpa_get_features(काष्ठा vdpa_device *vdev)
अणु
	काष्ठा mlx5_vdpa_dev *mvdev = to_mvdev(vdev);
	काष्ठा mlx5_vdpa_net *ndev = to_mlx5_vdpa_ndev(mvdev);
	u16 dev_features;

	dev_features = MLX5_CAP_DEV_VDPA_EMULATION(mvdev->mdev, device_features_bits_mask);
	ndev->mvdev.mlx_features = mlx_to_vritio_features(dev_features);
	अगर (MLX5_CAP_DEV_VDPA_EMULATION(mvdev->mdev, virtio_version_1_0))
		ndev->mvdev.mlx_features |= BIT_ULL(VIRTIO_F_VERSION_1);
	ndev->mvdev.mlx_features |= BIT_ULL(VIRTIO_F_ACCESS_PLATFORM);
	prपूर्णांक_features(mvdev, ndev->mvdev.mlx_features, false);
	वापस ndev->mvdev.mlx_features;
पूर्ण

अटल पूर्णांक verअगरy_min_features(काष्ठा mlx5_vdpa_dev *mvdev, u64 features)
अणु
	अगर (!(features & BIT_ULL(VIRTIO_F_ACCESS_PLATFORM)))
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल पूर्णांक setup_virtqueues(काष्ठा mlx5_vdpa_net *ndev)
अणु
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < 2 * mlx5_vdpa_max_qps(ndev->mvdev.max_vqs); i++) अणु
		err = setup_vq(ndev, &ndev->vqs[i]);
		अगर (err)
			जाओ err_vq;
	पूर्ण

	वापस 0;

err_vq:
	क्रम (--i; i >= 0; i--)
		tearकरोwn_vq(ndev, &ndev->vqs[i]);

	वापस err;
पूर्ण

अटल व्योम tearकरोwn_virtqueues(काष्ठा mlx5_vdpa_net *ndev)
अणु
	काष्ठा mlx5_vdpa_virtqueue *mvq;
	पूर्णांक i;

	क्रम (i = ndev->mvdev.max_vqs - 1; i >= 0; i--) अणु
		mvq = &ndev->vqs[i];
		अगर (!mvq->initialized)
			जारी;

		tearकरोwn_vq(ndev, mvq);
	पूर्ण
पूर्ण

/* TODO: cross-endian support */
अटल अंतरभूत bool mlx5_vdpa_is_little_endian(काष्ठा mlx5_vdpa_dev *mvdev)
अणु
	वापस virtio_legacy_is_little_endian() ||
		(mvdev->actual_features & BIT_ULL(VIRTIO_F_VERSION_1));
पूर्ण

अटल __virtio16 cpu_to_mlx5vdpa16(काष्ठा mlx5_vdpa_dev *mvdev, u16 val)
अणु
	वापस __cpu_to_virtio16(mlx5_vdpa_is_little_endian(mvdev), val);
पूर्ण

अटल पूर्णांक mlx5_vdpa_set_features(काष्ठा vdpa_device *vdev, u64 features)
अणु
	काष्ठा mlx5_vdpa_dev *mvdev = to_mvdev(vdev);
	काष्ठा mlx5_vdpa_net *ndev = to_mlx5_vdpa_ndev(mvdev);
	पूर्णांक err;

	prपूर्णांक_features(mvdev, features, true);

	err = verअगरy_min_features(mvdev, features);
	अगर (err)
		वापस err;

	ndev->mvdev.actual_features = features & ndev->mvdev.mlx_features;
	ndev->config.mtu = cpu_to_mlx5vdpa16(mvdev, ndev->mtu);
	ndev->config.status |= cpu_to_mlx5vdpa16(mvdev, VIRTIO_NET_S_LINK_UP);
	वापस err;
पूर्ण

अटल व्योम mlx5_vdpa_set_config_cb(काष्ठा vdpa_device *vdev, काष्ठा vdpa_callback *cb)
अणु
	/* not implemented */
	mlx5_vdpa_warn(to_mvdev(vdev), "set config callback not supported\n");
पूर्ण

#घोषणा MLX5_VDPA_MAX_VQ_ENTRIES 256
अटल u16 mlx5_vdpa_get_vq_num_max(काष्ठा vdpa_device *vdev)
अणु
	वापस MLX5_VDPA_MAX_VQ_ENTRIES;
पूर्ण

अटल u32 mlx5_vdpa_get_device_id(काष्ठा vdpa_device *vdev)
अणु
	वापस VIRTIO_ID_NET;
पूर्ण

अटल u32 mlx5_vdpa_get_venकरोr_id(काष्ठा vdpa_device *vdev)
अणु
	वापस PCI_VENDOR_ID_MELLANOX;
पूर्ण

अटल u8 mlx5_vdpa_get_status(काष्ठा vdpa_device *vdev)
अणु
	काष्ठा mlx5_vdpa_dev *mvdev = to_mvdev(vdev);
	काष्ठा mlx5_vdpa_net *ndev = to_mlx5_vdpa_ndev(mvdev);

	prपूर्णांक_status(mvdev, ndev->mvdev.status, false);
	वापस ndev->mvdev.status;
पूर्ण

अटल पूर्णांक save_channel_info(काष्ठा mlx5_vdpa_net *ndev, काष्ठा mlx5_vdpa_virtqueue *mvq)
अणु
	काष्ठा mlx5_vq_restore_info *ri = &mvq->ri;
	काष्ठा mlx5_virtq_attr attr;
	पूर्णांक err;

	अगर (!mvq->initialized)
		वापस 0;

	err = query_virtqueue(ndev, mvq, &attr);
	अगर (err)
		वापस err;

	ri->avail_index = attr.available_index;
	ri->used_index = attr.used_index;
	ri->पढ़ोy = mvq->पढ़ोy;
	ri->num_ent = mvq->num_ent;
	ri->desc_addr = mvq->desc_addr;
	ri->device_addr = mvq->device_addr;
	ri->driver_addr = mvq->driver_addr;
	ri->cb = mvq->event_cb;
	ri->restore = true;
	वापस 0;
पूर्ण

अटल पूर्णांक save_channels_info(काष्ठा mlx5_vdpa_net *ndev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ndev->mvdev.max_vqs; i++) अणु
		स_रखो(&ndev->vqs[i].ri, 0, माप(ndev->vqs[i].ri));
		save_channel_info(ndev, &ndev->vqs[i]);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mlx5_clear_vqs(काष्ठा mlx5_vdpa_net *ndev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ndev->mvdev.max_vqs; i++)
		स_रखो(&ndev->vqs[i], 0, दुरत्व(काष्ठा mlx5_vdpa_virtqueue, ri));
पूर्ण

अटल व्योम restore_channels_info(काष्ठा mlx5_vdpa_net *ndev)
अणु
	काष्ठा mlx5_vdpa_virtqueue *mvq;
	काष्ठा mlx5_vq_restore_info *ri;
	पूर्णांक i;

	mlx5_clear_vqs(ndev);
	init_mvqs(ndev);
	क्रम (i = 0; i < ndev->mvdev.max_vqs; i++) अणु
		mvq = &ndev->vqs[i];
		ri = &mvq->ri;
		अगर (!ri->restore)
			जारी;

		mvq->avail_idx = ri->avail_index;
		mvq->used_idx = ri->used_index;
		mvq->पढ़ोy = ri->पढ़ोy;
		mvq->num_ent = ri->num_ent;
		mvq->desc_addr = ri->desc_addr;
		mvq->device_addr = ri->device_addr;
		mvq->driver_addr = ri->driver_addr;
		mvq->event_cb = ri->cb;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_vdpa_change_map(काष्ठा mlx5_vdpa_net *ndev, काष्ठा vhost_iotlb *iotlb)
अणु
	पूर्णांक err;

	suspend_vqs(ndev);
	err = save_channels_info(ndev);
	अगर (err)
		जाओ err_mr;

	tearकरोwn_driver(ndev);
	mlx5_vdpa_destroy_mr(&ndev->mvdev);
	err = mlx5_vdpa_create_mr(&ndev->mvdev, iotlb);
	अगर (err)
		जाओ err_mr;

	अगर (!(ndev->mvdev.status & VIRTIO_CONFIG_S_DRIVER_OK))
		वापस 0;

	restore_channels_info(ndev);
	err = setup_driver(ndev);
	अगर (err)
		जाओ err_setup;

	वापस 0;

err_setup:
	mlx5_vdpa_destroy_mr(&ndev->mvdev);
err_mr:
	वापस err;
पूर्ण

अटल पूर्णांक setup_driver(काष्ठा mlx5_vdpa_net *ndev)
अणु
	पूर्णांक err;

	mutex_lock(&ndev->reslock);
	अगर (ndev->setup) अणु
		mlx5_vdpa_warn(&ndev->mvdev, "setup driver called for already setup driver\n");
		err = 0;
		जाओ out;
	पूर्ण
	err = setup_virtqueues(ndev);
	अगर (err) अणु
		mlx5_vdpa_warn(&ndev->mvdev, "setup_virtqueues\n");
		जाओ out;
	पूर्ण

	err = create_rqt(ndev);
	अगर (err) अणु
		mlx5_vdpa_warn(&ndev->mvdev, "create_rqt\n");
		जाओ err_rqt;
	पूर्ण

	err = create_tir(ndev);
	अगर (err) अणु
		mlx5_vdpa_warn(&ndev->mvdev, "create_tir\n");
		जाओ err_tir;
	पूर्ण

	err = add_fwd_to_tir(ndev);
	अगर (err) अणु
		mlx5_vdpa_warn(&ndev->mvdev, "add_fwd_to_tir\n");
		जाओ err_fwd;
	पूर्ण
	ndev->setup = true;
	mutex_unlock(&ndev->reslock);

	वापस 0;

err_fwd:
	destroy_tir(ndev);
err_tir:
	destroy_rqt(ndev);
err_rqt:
	tearकरोwn_virtqueues(ndev);
out:
	mutex_unlock(&ndev->reslock);
	वापस err;
पूर्ण

अटल व्योम tearकरोwn_driver(काष्ठा mlx5_vdpa_net *ndev)
अणु
	mutex_lock(&ndev->reslock);
	अगर (!ndev->setup)
		जाओ out;

	हटाओ_fwd_to_tir(ndev);
	destroy_tir(ndev);
	destroy_rqt(ndev);
	tearकरोwn_virtqueues(ndev);
	ndev->setup = false;
out:
	mutex_unlock(&ndev->reslock);
पूर्ण

अटल व्योम mlx5_vdpa_set_status(काष्ठा vdpa_device *vdev, u8 status)
अणु
	काष्ठा mlx5_vdpa_dev *mvdev = to_mvdev(vdev);
	काष्ठा mlx5_vdpa_net *ndev = to_mlx5_vdpa_ndev(mvdev);
	पूर्णांक err;

	prपूर्णांक_status(mvdev, status, true);
	अगर (!status) अणु
		mlx5_vdpa_info(mvdev, "performing device reset\n");
		tearकरोwn_driver(ndev);
		mlx5_vdpa_destroy_mr(&ndev->mvdev);
		ndev->mvdev.status = 0;
		ndev->mvdev.mlx_features = 0;
		++mvdev->generation;
		वापस;
	पूर्ण

	अगर ((status ^ ndev->mvdev.status) & VIRTIO_CONFIG_S_DRIVER_OK) अणु
		अगर (status & VIRTIO_CONFIG_S_DRIVER_OK) अणु
			err = setup_driver(ndev);
			अगर (err) अणु
				mlx5_vdpa_warn(mvdev, "failed to setup driver\n");
				जाओ err_setup;
			पूर्ण
		पूर्ण अन्यथा अणु
			mlx5_vdpa_warn(mvdev, "did not expect DRIVER_OK to be cleared\n");
			वापस;
		पूर्ण
	पूर्ण

	ndev->mvdev.status = status;
	वापस;

err_setup:
	mlx5_vdpa_destroy_mr(&ndev->mvdev);
	ndev->mvdev.status |= VIRTIO_CONFIG_S_FAILED;
पूर्ण

अटल माप_प्रकार mlx5_vdpa_get_config_size(काष्ठा vdpa_device *vdev)
अणु
	वापस माप(काष्ठा virtio_net_config);
पूर्ण

अटल व्योम mlx5_vdpa_get_config(काष्ठा vdpa_device *vdev, अचिन्हित पूर्णांक offset, व्योम *buf,
				 अचिन्हित पूर्णांक len)
अणु
	काष्ठा mlx5_vdpa_dev *mvdev = to_mvdev(vdev);
	काष्ठा mlx5_vdpa_net *ndev = to_mlx5_vdpa_ndev(mvdev);

	अगर (offset + len <= माप(काष्ठा virtio_net_config))
		स_नकल(buf, (u8 *)&ndev->config + offset, len);
पूर्ण

अटल व्योम mlx5_vdpa_set_config(काष्ठा vdpa_device *vdev, अचिन्हित पूर्णांक offset, स्थिर व्योम *buf,
				 अचिन्हित पूर्णांक len)
अणु
	/* not supported */
पूर्ण

अटल u32 mlx5_vdpa_get_generation(काष्ठा vdpa_device *vdev)
अणु
	काष्ठा mlx5_vdpa_dev *mvdev = to_mvdev(vdev);

	वापस mvdev->generation;
पूर्ण

अटल पूर्णांक mlx5_vdpa_set_map(काष्ठा vdpa_device *vdev, काष्ठा vhost_iotlb *iotlb)
अणु
	काष्ठा mlx5_vdpa_dev *mvdev = to_mvdev(vdev);
	काष्ठा mlx5_vdpa_net *ndev = to_mlx5_vdpa_ndev(mvdev);
	bool change_map;
	पूर्णांक err;

	err = mlx5_vdpa_handle_set_map(mvdev, iotlb, &change_map);
	अगर (err) अणु
		mlx5_vdpa_warn(mvdev, "set map failed(%d)\n", err);
		वापस err;
	पूर्ण

	अगर (change_map)
		वापस mlx5_vdpa_change_map(ndev, iotlb);

	वापस 0;
पूर्ण

अटल व्योम mlx5_vdpa_मुक्त(काष्ठा vdpa_device *vdev)
अणु
	काष्ठा mlx5_vdpa_dev *mvdev = to_mvdev(vdev);
	काष्ठा mlx5_core_dev *pfmdev;
	काष्ठा mlx5_vdpa_net *ndev;

	ndev = to_mlx5_vdpa_ndev(mvdev);

	मुक्त_resources(ndev);
	अगर (!is_zero_ether_addr(ndev->config.mac)) अणु
		pfmdev = pci_get_drvdata(pci_physfn(mvdev->mdev->pdev));
		mlx5_mpfs_del_mac(pfmdev, ndev->config.mac);
	पूर्ण
	mlx5_vdpa_मुक्त_resources(&ndev->mvdev);
	mutex_destroy(&ndev->reslock);
पूर्ण

अटल काष्ठा vdpa_notअगरication_area mlx5_get_vq_notअगरication(काष्ठा vdpa_device *vdev, u16 idx)
अणु
	काष्ठा vdpa_notअगरication_area ret = अणुपूर्ण;

	वापस ret;
पूर्ण

अटल पूर्णांक mlx5_get_vq_irq(काष्ठा vdpa_device *vdv, u16 idx)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा vdpa_config_ops mlx5_vdpa_ops = अणु
	.set_vq_address = mlx5_vdpa_set_vq_address,
	.set_vq_num = mlx5_vdpa_set_vq_num,
	.kick_vq = mlx5_vdpa_kick_vq,
	.set_vq_cb = mlx5_vdpa_set_vq_cb,
	.set_vq_पढ़ोy = mlx5_vdpa_set_vq_पढ़ोy,
	.get_vq_पढ़ोy = mlx5_vdpa_get_vq_पढ़ोy,
	.set_vq_state = mlx5_vdpa_set_vq_state,
	.get_vq_state = mlx5_vdpa_get_vq_state,
	.get_vq_notअगरication = mlx5_get_vq_notअगरication,
	.get_vq_irq = mlx5_get_vq_irq,
	.get_vq_align = mlx5_vdpa_get_vq_align,
	.get_features = mlx5_vdpa_get_features,
	.set_features = mlx5_vdpa_set_features,
	.set_config_cb = mlx5_vdpa_set_config_cb,
	.get_vq_num_max = mlx5_vdpa_get_vq_num_max,
	.get_device_id = mlx5_vdpa_get_device_id,
	.get_venकरोr_id = mlx5_vdpa_get_venकरोr_id,
	.get_status = mlx5_vdpa_get_status,
	.set_status = mlx5_vdpa_set_status,
	.get_config_size = mlx5_vdpa_get_config_size,
	.get_config = mlx5_vdpa_get_config,
	.set_config = mlx5_vdpa_set_config,
	.get_generation = mlx5_vdpa_get_generation,
	.set_map = mlx5_vdpa_set_map,
	.मुक्त = mlx5_vdpa_मुक्त,
पूर्ण;

अटल पूर्णांक query_mtu(काष्ठा mlx5_core_dev *mdev, u16 *mtu)
अणु
	u16 hw_mtu;
	पूर्णांक err;

	err = mlx5_query_nic_vport_mtu(mdev, &hw_mtu);
	अगर (err)
		वापस err;

	*mtu = hw_mtu - MLX5V_ETH_HARD_MTU;
	वापस 0;
पूर्ण

अटल पूर्णांक alloc_resources(काष्ठा mlx5_vdpa_net *ndev)
अणु
	काष्ठा mlx5_vdpa_net_resources *res = &ndev->res;
	पूर्णांक err;

	अगर (res->valid) अणु
		mlx5_vdpa_warn(&ndev->mvdev, "resources already allocated\n");
		वापस -EEXIST;
	पूर्ण

	err = mlx5_vdpa_alloc_transport_करोमुख्य(&ndev->mvdev, &res->tdn);
	अगर (err)
		वापस err;

	err = create_tis(ndev);
	अगर (err)
		जाओ err_tis;

	res->valid = true;

	वापस 0;

err_tis:
	mlx5_vdpa_dealloc_transport_करोमुख्य(&ndev->mvdev, res->tdn);
	वापस err;
पूर्ण

अटल व्योम मुक्त_resources(काष्ठा mlx5_vdpa_net *ndev)
अणु
	काष्ठा mlx5_vdpa_net_resources *res = &ndev->res;

	अगर (!res->valid)
		वापस;

	destroy_tis(ndev);
	mlx5_vdpa_dealloc_transport_करोमुख्य(&ndev->mvdev, res->tdn);
	res->valid = false;
पूर्ण

अटल व्योम init_mvqs(काष्ठा mlx5_vdpa_net *ndev)
अणु
	काष्ठा mlx5_vdpa_virtqueue *mvq;
	पूर्णांक i;

	क्रम (i = 0; i < 2 * mlx5_vdpa_max_qps(ndev->mvdev.max_vqs); ++i) अणु
		mvq = &ndev->vqs[i];
		स_रखो(mvq, 0, दुरत्व(काष्ठा mlx5_vdpa_virtqueue, ri));
		mvq->index = i;
		mvq->ndev = ndev;
		mvq->fwqp.fw = true;
	पूर्ण
	क्रम (; i < ndev->mvdev.max_vqs; i++) अणु
		mvq = &ndev->vqs[i];
		स_रखो(mvq, 0, दुरत्व(काष्ठा mlx5_vdpa_virtqueue, ri));
		mvq->index = i;
		mvq->ndev = ndev;
	पूर्ण
पूर्ण

काष्ठा mlx5_vdpa_mgmtdev अणु
	काष्ठा vdpa_mgmt_dev mgtdev;
	काष्ठा mlx5_adev *madev;
	काष्ठा mlx5_vdpa_net *ndev;
पूर्ण;

अटल पूर्णांक mlx5_vdpa_dev_add(काष्ठा vdpa_mgmt_dev *v_mdev, स्थिर अक्षर *name)
अणु
	काष्ठा mlx5_vdpa_mgmtdev *mgtdev = container_of(v_mdev, काष्ठा mlx5_vdpa_mgmtdev, mgtdev);
	काष्ठा virtio_net_config *config;
	काष्ठा mlx5_core_dev *pfmdev;
	काष्ठा mlx5_vdpa_dev *mvdev;
	काष्ठा mlx5_vdpa_net *ndev;
	काष्ठा mlx5_core_dev *mdev;
	u32 max_vqs;
	पूर्णांक err;

	अगर (mgtdev->ndev)
		वापस -ENOSPC;

	mdev = mgtdev->madev->mdev;
	/* we save one virtqueue क्रम control virtqueue should we require it */
	max_vqs = MLX5_CAP_DEV_VDPA_EMULATION(mdev, max_num_virtio_queues);
	max_vqs = min_t(u32, max_vqs, MLX5_MAX_SUPPORTED_VQS);

	ndev = vdpa_alloc_device(काष्ठा mlx5_vdpa_net, mvdev.vdev, mdev->device, &mlx5_vdpa_ops,
				 name);
	अगर (IS_ERR(ndev))
		वापस PTR_ERR(ndev);

	ndev->mvdev.max_vqs = max_vqs;
	mvdev = &ndev->mvdev;
	mvdev->mdev = mdev;
	init_mvqs(ndev);
	mutex_init(&ndev->reslock);
	config = &ndev->config;
	err = query_mtu(mdev, &ndev->mtu);
	अगर (err)
		जाओ err_mtu;

	err = mlx5_query_nic_vport_mac_address(mdev, 0, 0, config->mac);
	अगर (err)
		जाओ err_mtu;

	अगर (!is_zero_ether_addr(config->mac)) अणु
		pfmdev = pci_get_drvdata(pci_physfn(mdev->pdev));
		err = mlx5_mpfs_add_mac(pfmdev, config->mac);
		अगर (err)
			जाओ err_mtu;
	पूर्ण

	mvdev->vdev.dma_dev = mdev->device;
	err = mlx5_vdpa_alloc_resources(&ndev->mvdev);
	अगर (err)
		जाओ err_mpfs;

	err = alloc_resources(ndev);
	अगर (err)
		जाओ err_res;

	mvdev->vdev.mdev = &mgtdev->mgtdev;
	err = _vdpa_रेजिस्टर_device(&mvdev->vdev, 2 * mlx5_vdpa_max_qps(max_vqs));
	अगर (err)
		जाओ err_reg;

	mgtdev->ndev = ndev;
	वापस 0;

err_reg:
	मुक्त_resources(ndev);
err_res:
	mlx5_vdpa_मुक्त_resources(&ndev->mvdev);
err_mpfs:
	अगर (!is_zero_ether_addr(config->mac))
		mlx5_mpfs_del_mac(pfmdev, config->mac);
err_mtu:
	mutex_destroy(&ndev->reslock);
	put_device(&mvdev->vdev.dev);
	वापस err;
पूर्ण

अटल व्योम mlx5_vdpa_dev_del(काष्ठा vdpa_mgmt_dev *v_mdev, काष्ठा vdpa_device *dev)
अणु
	काष्ठा mlx5_vdpa_mgmtdev *mgtdev = container_of(v_mdev, काष्ठा mlx5_vdpa_mgmtdev, mgtdev);

	_vdpa_unरेजिस्टर_device(dev);
	mgtdev->ndev = शून्य;
पूर्ण

अटल स्थिर काष्ठा vdpa_mgmtdev_ops mdev_ops = अणु
	.dev_add = mlx5_vdpa_dev_add,
	.dev_del = mlx5_vdpa_dev_del,
पूर्ण;

अटल काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_NET, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल पूर्णांक mlx5v_probe(काष्ठा auxiliary_device *adev,
		       स्थिर काष्ठा auxiliary_device_id *id)

अणु
	काष्ठा mlx5_adev *madev = container_of(adev, काष्ठा mlx5_adev, adev);
	काष्ठा mlx5_core_dev *mdev = madev->mdev;
	काष्ठा mlx5_vdpa_mgmtdev *mgtdev;
	पूर्णांक err;

	mgtdev = kzalloc(माप(*mgtdev), GFP_KERNEL);
	अगर (!mgtdev)
		वापस -ENOMEM;

	mgtdev->mgtdev.ops = &mdev_ops;
	mgtdev->mgtdev.device = mdev->device;
	mgtdev->mgtdev.id_table = id_table;
	mgtdev->madev = madev;

	err = vdpa_mgmtdev_रेजिस्टर(&mgtdev->mgtdev);
	अगर (err)
		जाओ reg_err;

	dev_set_drvdata(&adev->dev, mgtdev);

	वापस 0;

reg_err:
	kमुक्त(mgtdev);
	वापस err;
पूर्ण

अटल व्योम mlx5v_हटाओ(काष्ठा auxiliary_device *adev)
अणु
	काष्ठा mlx5_vdpa_mgmtdev *mgtdev;

	mgtdev = dev_get_drvdata(&adev->dev);
	vdpa_mgmtdev_unरेजिस्टर(&mgtdev->mgtdev);
	kमुक्त(mgtdev);
पूर्ण

अटल स्थिर काष्ठा auxiliary_device_id mlx5v_id_table[] = अणु
	अणु .name = MLX5_ADEV_NAME ".vnet", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(auxiliary, mlx5v_id_table);

अटल काष्ठा auxiliary_driver mlx5v_driver = अणु
	.name = "vnet",
	.probe = mlx5v_probe,
	.हटाओ = mlx5v_हटाओ,
	.id_table = mlx5v_id_table,
पूर्ण;

module_auxiliary_driver(mlx5v_driver);
