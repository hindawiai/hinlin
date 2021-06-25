<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2015-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/dcbnl.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/list.h>
#समावेश <linux/netlink.h>

#समावेश "spectrum.h"
#समावेश "core.h"
#समावेश "port.h"
#समावेश "reg.h"

काष्ठा mlxsw_sp_sb_pr अणु
	क्रमागत mlxsw_reg_sbpr_mode mode;
	u32 size;
	u8 मुक्तze_mode:1,
	   मुक्तze_size:1;
पूर्ण;

काष्ठा mlxsw_cp_sb_occ अणु
	u32 cur;
	u32 max;
पूर्ण;

काष्ठा mlxsw_sp_sb_cm अणु
	u32 min_buff;
	u32 max_buff;
	u16 pool_index;
	काष्ठा mlxsw_cp_sb_occ occ;
	u8 मुक्तze_pool:1,
	   मुक्तze_thresh:1;
पूर्ण;

#घोषणा MLXSW_SP_SB_INFI -1U
#घोषणा MLXSW_SP_SB_REST -2U

काष्ठा mlxsw_sp_sb_pm अणु
	u32 min_buff;
	u32 max_buff;
	काष्ठा mlxsw_cp_sb_occ occ;
पूर्ण;

काष्ठा mlxsw_sp_sb_mm अणु
	u32 min_buff;
	u32 max_buff;
	u16 pool_index;
पूर्ण;

काष्ठा mlxsw_sp_sb_pool_des अणु
	क्रमागत mlxsw_reg_sbxx_dir dir;
	u8 pool;
पूर्ण;

#घोषणा MLXSW_SP_SB_POOL_ING		0
#घोषणा MLXSW_SP_SB_POOL_EGR		4
#घोषणा MLXSW_SP_SB_POOL_EGR_MC		8
#घोषणा MLXSW_SP_SB_POOL_ING_CPU	9
#घोषणा MLXSW_SP_SB_POOL_EGR_CPU	10

अटल स्थिर काष्ठा mlxsw_sp_sb_pool_des mlxsw_sp1_sb_pool_dess[] = अणु
	अणुMLXSW_REG_SBXX_सूची_INGRESS, 0पूर्ण,
	अणुMLXSW_REG_SBXX_सूची_INGRESS, 1पूर्ण,
	अणुMLXSW_REG_SBXX_सूची_INGRESS, 2पूर्ण,
	अणुMLXSW_REG_SBXX_सूची_INGRESS, 3पूर्ण,
	अणुMLXSW_REG_SBXX_सूची_EGRESS, 0पूर्ण,
	अणुMLXSW_REG_SBXX_सूची_EGRESS, 1पूर्ण,
	अणुMLXSW_REG_SBXX_सूची_EGRESS, 2पूर्ण,
	अणुMLXSW_REG_SBXX_सूची_EGRESS, 3पूर्ण,
	अणुMLXSW_REG_SBXX_सूची_EGRESS, 15पूर्ण,
	अणुMLXSW_REG_SBXX_सूची_INGRESS, 4पूर्ण,
	अणुMLXSW_REG_SBXX_सूची_EGRESS, 4पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_sb_pool_des mlxsw_sp2_sb_pool_dess[] = अणु
	अणुMLXSW_REG_SBXX_सूची_INGRESS, 0पूर्ण,
	अणुMLXSW_REG_SBXX_सूची_INGRESS, 1पूर्ण,
	अणुMLXSW_REG_SBXX_सूची_INGRESS, 2पूर्ण,
	अणुMLXSW_REG_SBXX_सूची_INGRESS, 3पूर्ण,
	अणुMLXSW_REG_SBXX_सूची_EGRESS, 0पूर्ण,
	अणुMLXSW_REG_SBXX_सूची_EGRESS, 1पूर्ण,
	अणुMLXSW_REG_SBXX_सूची_EGRESS, 2पूर्ण,
	अणुMLXSW_REG_SBXX_सूची_EGRESS, 3पूर्ण,
	अणुMLXSW_REG_SBXX_सूची_EGRESS, 15पूर्ण,
	अणुMLXSW_REG_SBXX_सूची_INGRESS, 4पूर्ण,
	अणुMLXSW_REG_SBXX_सूची_EGRESS, 4पूर्ण,
पूर्ण;

#घोषणा MLXSW_SP_SB_ING_TC_COUNT 8
#घोषणा MLXSW_SP_SB_EG_TC_COUNT 16

काष्ठा mlxsw_sp_sb_port अणु
	काष्ठा mlxsw_sp_sb_cm ing_cms[MLXSW_SP_SB_ING_TC_COUNT];
	काष्ठा mlxsw_sp_sb_cm eg_cms[MLXSW_SP_SB_EG_TC_COUNT];
	काष्ठा mlxsw_sp_sb_pm *pms;
पूर्ण;

काष्ठा mlxsw_sp_sb अणु
	काष्ठा mlxsw_sp_sb_pr *prs;
	काष्ठा mlxsw_sp_sb_port *ports;
	u32 cell_size;
	u32 max_headroom_cells;
	u64 sb_size;
पूर्ण;

काष्ठा mlxsw_sp_sb_vals अणु
	अचिन्हित पूर्णांक pool_count;
	स्थिर काष्ठा mlxsw_sp_sb_pool_des *pool_dess;
	स्थिर काष्ठा mlxsw_sp_sb_pm *pms;
	स्थिर काष्ठा mlxsw_sp_sb_pm *pms_cpu;
	स्थिर काष्ठा mlxsw_sp_sb_pr *prs;
	स्थिर काष्ठा mlxsw_sp_sb_mm *mms;
	स्थिर काष्ठा mlxsw_sp_sb_cm *cms_ingress;
	स्थिर काष्ठा mlxsw_sp_sb_cm *cms_egress;
	स्थिर काष्ठा mlxsw_sp_sb_cm *cms_cpu;
	अचिन्हित पूर्णांक mms_count;
	अचिन्हित पूर्णांक cms_ingress_count;
	अचिन्हित पूर्णांक cms_egress_count;
	अचिन्हित पूर्णांक cms_cpu_count;
पूर्ण;

काष्ठा mlxsw_sp_sb_ops अणु
	u32 (*पूर्णांक_buf_size_get)(पूर्णांक mtu, u32 speed);
पूर्ण;

u32 mlxsw_sp_cells_bytes(स्थिर काष्ठा mlxsw_sp *mlxsw_sp, u32 cells)
अणु
	वापस mlxsw_sp->sb->cell_size * cells;
पूर्ण

u32 mlxsw_sp_bytes_cells(स्थिर काष्ठा mlxsw_sp *mlxsw_sp, u32 bytes)
अणु
	वापस DIV_ROUND_UP(bytes, mlxsw_sp->sb->cell_size);
पूर्ण

अटल u32 mlxsw_sp_port_headroom_8x_adjust(स्थिर काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					    u32 size_cells)
अणु
	/* Ports with eight lanes use two headroom buffers between which the
	 * configured headroom size is split. Thereक्रमe, multiply the calculated
	 * headroom size by two.
	 */
	वापस mlxsw_sp_port->mapping.width == 8 ? 2 * size_cells : size_cells;
पूर्ण

अटल काष्ठा mlxsw_sp_sb_pr *mlxsw_sp_sb_pr_get(काष्ठा mlxsw_sp *mlxsw_sp,
						 u16 pool_index)
अणु
	वापस &mlxsw_sp->sb->prs[pool_index];
पूर्ण

अटल bool mlxsw_sp_sb_cm_exists(u8 pg_buff, क्रमागत mlxsw_reg_sbxx_dir dir)
अणु
	अगर (dir == MLXSW_REG_SBXX_सूची_INGRESS)
		वापस pg_buff < MLXSW_SP_SB_ING_TC_COUNT;
	अन्यथा
		वापस pg_buff < MLXSW_SP_SB_EG_TC_COUNT;
पूर्ण

अटल काष्ठा mlxsw_sp_sb_cm *mlxsw_sp_sb_cm_get(काष्ठा mlxsw_sp *mlxsw_sp,
						 u8 local_port, u8 pg_buff,
						 क्रमागत mlxsw_reg_sbxx_dir dir)
अणु
	काष्ठा mlxsw_sp_sb_port *sb_port = &mlxsw_sp->sb->ports[local_port];

	WARN_ON(!mlxsw_sp_sb_cm_exists(pg_buff, dir));
	अगर (dir == MLXSW_REG_SBXX_सूची_INGRESS)
		वापस &sb_port->ing_cms[pg_buff];
	अन्यथा
		वापस &sb_port->eg_cms[pg_buff];
पूर्ण

अटल काष्ठा mlxsw_sp_sb_pm *mlxsw_sp_sb_pm_get(काष्ठा mlxsw_sp *mlxsw_sp,
						 u8 local_port, u16 pool_index)
अणु
	वापस &mlxsw_sp->sb->ports[local_port].pms[pool_index];
पूर्ण

अटल पूर्णांक mlxsw_sp_sb_pr_ग_लिखो(काष्ठा mlxsw_sp *mlxsw_sp, u16 pool_index,
				क्रमागत mlxsw_reg_sbpr_mode mode,
				u32 size, bool infi_size)
अणु
	स्थिर काष्ठा mlxsw_sp_sb_pool_des *des =
		&mlxsw_sp->sb_vals->pool_dess[pool_index];
	अक्षर sbpr_pl[MLXSW_REG_SBPR_LEN];
	काष्ठा mlxsw_sp_sb_pr *pr;
	पूर्णांक err;

	mlxsw_reg_sbpr_pack(sbpr_pl, des->pool, des->dir, mode,
			    size, infi_size);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(sbpr), sbpr_pl);
	अगर (err)
		वापस err;

	अगर (infi_size)
		size = mlxsw_sp_bytes_cells(mlxsw_sp, mlxsw_sp->sb->sb_size);
	pr = mlxsw_sp_sb_pr_get(mlxsw_sp, pool_index);
	pr->mode = mode;
	pr->size = size;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_sb_cm_ग_लिखो(काष्ठा mlxsw_sp *mlxsw_sp, u8 local_port,
				u8 pg_buff, u32 min_buff, u32 max_buff,
				bool infi_max, u16 pool_index)
अणु
	स्थिर काष्ठा mlxsw_sp_sb_pool_des *des =
		&mlxsw_sp->sb_vals->pool_dess[pool_index];
	अक्षर sbcm_pl[MLXSW_REG_SBCM_LEN];
	काष्ठा mlxsw_sp_sb_cm *cm;
	पूर्णांक err;

	mlxsw_reg_sbcm_pack(sbcm_pl, local_port, pg_buff, des->dir,
			    min_buff, max_buff, infi_max, des->pool);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(sbcm), sbcm_pl);
	अगर (err)
		वापस err;

	अगर (mlxsw_sp_sb_cm_exists(pg_buff, des->dir)) अणु
		अगर (infi_max)
			max_buff = mlxsw_sp_bytes_cells(mlxsw_sp,
							mlxsw_sp->sb->sb_size);

		cm = mlxsw_sp_sb_cm_get(mlxsw_sp, local_port, pg_buff,
					des->dir);
		cm->min_buff = min_buff;
		cm->max_buff = max_buff;
		cm->pool_index = pool_index;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_sb_pm_ग_लिखो(काष्ठा mlxsw_sp *mlxsw_sp, u8 local_port,
				u16 pool_index, u32 min_buff, u32 max_buff)
अणु
	स्थिर काष्ठा mlxsw_sp_sb_pool_des *des =
		&mlxsw_sp->sb_vals->pool_dess[pool_index];
	अक्षर sbpm_pl[MLXSW_REG_SBPM_LEN];
	काष्ठा mlxsw_sp_sb_pm *pm;
	पूर्णांक err;

	mlxsw_reg_sbpm_pack(sbpm_pl, local_port, des->pool, des->dir, false,
			    min_buff, max_buff);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(sbpm), sbpm_pl);
	अगर (err)
		वापस err;

	pm = mlxsw_sp_sb_pm_get(mlxsw_sp, local_port, pool_index);
	pm->min_buff = min_buff;
	pm->max_buff = max_buff;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_sb_pm_occ_clear(काष्ठा mlxsw_sp *mlxsw_sp, u8 local_port,
				    u16 pool_index, काष्ठा list_head *bulk_list)
अणु
	स्थिर काष्ठा mlxsw_sp_sb_pool_des *des =
		&mlxsw_sp->sb_vals->pool_dess[pool_index];
	अक्षर sbpm_pl[MLXSW_REG_SBPM_LEN];

	अगर (local_port == MLXSW_PORT_CPU_PORT &&
	    des->dir == MLXSW_REG_SBXX_सूची_INGRESS)
		वापस 0;

	mlxsw_reg_sbpm_pack(sbpm_pl, local_port, des->pool, des->dir,
			    true, 0, 0);
	वापस mlxsw_reg_trans_query(mlxsw_sp->core, MLXSW_REG(sbpm), sbpm_pl,
				     bulk_list, शून्य, 0);
पूर्ण

अटल व्योम mlxsw_sp_sb_pm_occ_query_cb(काष्ठा mlxsw_core *mlxsw_core,
					अक्षर *sbpm_pl, माप_प्रकार sbpm_pl_len,
					अचिन्हित दीर्घ cb_priv)
अणु
	काष्ठा mlxsw_sp_sb_pm *pm = (काष्ठा mlxsw_sp_sb_pm *) cb_priv;

	mlxsw_reg_sbpm_unpack(sbpm_pl, &pm->occ.cur, &pm->occ.max);
पूर्ण

अटल पूर्णांक mlxsw_sp_sb_pm_occ_query(काष्ठा mlxsw_sp *mlxsw_sp, u8 local_port,
				    u16 pool_index, काष्ठा list_head *bulk_list)
अणु
	स्थिर काष्ठा mlxsw_sp_sb_pool_des *des =
		&mlxsw_sp->sb_vals->pool_dess[pool_index];
	अक्षर sbpm_pl[MLXSW_REG_SBPM_LEN];
	काष्ठा mlxsw_sp_sb_pm *pm;

	अगर (local_port == MLXSW_PORT_CPU_PORT &&
	    des->dir == MLXSW_REG_SBXX_सूची_INGRESS)
		वापस 0;

	pm = mlxsw_sp_sb_pm_get(mlxsw_sp, local_port, pool_index);
	mlxsw_reg_sbpm_pack(sbpm_pl, local_port, des->pool, des->dir,
			    false, 0, 0);
	वापस mlxsw_reg_trans_query(mlxsw_sp->core, MLXSW_REG(sbpm), sbpm_pl,
				     bulk_list,
				     mlxsw_sp_sb_pm_occ_query_cb,
				     (अचिन्हित दीर्घ) pm);
पूर्ण

व्योम mlxsw_sp_hdroom_prios_reset_buf_idx(काष्ठा mlxsw_sp_hdroom *hdroom)
अणु
	पूर्णांक prio;

	क्रम (prio = 0; prio < IEEE_8021QAZ_MAX_TCS; prio++) अणु
		चयन (hdroom->mode) अणु
		हाल MLXSW_SP_HDROOM_MODE_DCB:
			hdroom->prios.prio[prio].buf_idx = hdroom->prios.prio[prio].ets_buf_idx;
			अवरोध;
		हाल MLXSW_SP_HDROOM_MODE_TC:
			hdroom->prios.prio[prio].buf_idx = hdroom->prios.prio[prio].set_buf_idx;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम mlxsw_sp_hdroom_bufs_reset_lossiness(काष्ठा mlxsw_sp_hdroom *hdroom)
अणु
	पूर्णांक prio;
	पूर्णांक i;

	क्रम (i = 0; i < DCBX_MAX_BUFFERS; i++)
		hdroom->bufs.buf[i].lossy = true;

	क्रम (prio = 0; prio < IEEE_8021Q_MAX_PRIORITIES; prio++) अणु
		अगर (!hdroom->prios.prio[prio].lossy)
			hdroom->bufs.buf[hdroom->prios.prio[prio].buf_idx].lossy = false;
	पूर्ण
पूर्ण

अटल u16 mlxsw_sp_hdroom_buf_threshold_get(स्थिर काष्ठा mlxsw_sp *mlxsw_sp, पूर्णांक mtu)
अणु
	वापस 2 * mlxsw_sp_bytes_cells(mlxsw_sp, mtu);
पूर्ण

अटल व्योम mlxsw_sp_hdroom_buf_pack(अक्षर *pbmc_pl, पूर्णांक index, u16 size, u16 thres, bool lossy)
अणु
	अगर (lossy)
		mlxsw_reg_pbmc_lossy_buffer_pack(pbmc_pl, index, size);
	अन्यथा
		mlxsw_reg_pbmc_lossless_buffer_pack(pbmc_pl, index, size,
						    thres);
पूर्ण

अटल u16 mlxsw_sp_hdroom_buf_delay_get(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
					 स्थिर काष्ठा mlxsw_sp_hdroom *hdroom)
अणु
	u16 delay_cells;

	delay_cells = mlxsw_sp_bytes_cells(mlxsw_sp, hdroom->delay_bytes);

	/* In the worst हाल scenario the delay will be made up of packets that
	 * are all of size CELL_SIZE + 1, which means each packet will require
	 * almost twice its true size when buffered in the चयन. We thereक्रमe
	 * multiply this value by the "cell factor", which is बंद to 2.
	 *
	 * Another MTU is added in हाल the transmitting host alपढ़ोy started
	 * transmitting a maximum length frame when the PFC packet was received.
	 */
	वापस 2 * delay_cells + mlxsw_sp_bytes_cells(mlxsw_sp, hdroom->mtu);
पूर्ण

अटल u32 mlxsw_sp_hdroom_पूर्णांक_buf_size_get(काष्ठा mlxsw_sp *mlxsw_sp, पूर्णांक mtu, u32 speed)
अणु
	u32 buffsize = mlxsw_sp->sb_ops->पूर्णांक_buf_size_get(speed, mtu);

	वापस mlxsw_sp_bytes_cells(mlxsw_sp, buffsize) + 1;
पूर्ण

अटल bool mlxsw_sp_hdroom_buf_is_used(स्थिर काष्ठा mlxsw_sp_hdroom *hdroom, पूर्णांक buf)
अणु
	पूर्णांक prio;

	क्रम (prio = 0; prio < IEEE_8021QAZ_MAX_TCS; prio++) अणु
		अगर (hdroom->prios.prio[prio].buf_idx == buf)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

व्योम mlxsw_sp_hdroom_bufs_reset_sizes(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				      काष्ठा mlxsw_sp_hdroom *hdroom)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	u16 reserve_cells;
	पूर्णांक i;

	/* Internal buffer. */
	reserve_cells = mlxsw_sp_hdroom_पूर्णांक_buf_size_get(mlxsw_sp, mlxsw_sp_port->max_speed,
							 mlxsw_sp_port->max_mtu);
	reserve_cells = mlxsw_sp_port_headroom_8x_adjust(mlxsw_sp_port, reserve_cells);
	hdroom->पूर्णांक_buf.reserve_cells = reserve_cells;

	अगर (hdroom->पूर्णांक_buf.enable)
		hdroom->पूर्णांक_buf.size_cells = reserve_cells;
	अन्यथा
		hdroom->पूर्णांक_buf.size_cells = 0;

	/* PG buffers. */
	क्रम (i = 0; i < DCBX_MAX_BUFFERS; i++) अणु
		काष्ठा mlxsw_sp_hdroom_buf *buf = &hdroom->bufs.buf[i];
		u16 thres_cells;
		u16 delay_cells;

		अगर (!mlxsw_sp_hdroom_buf_is_used(hdroom, i)) अणु
			thres_cells = 0;
			delay_cells = 0;
		पूर्ण अन्यथा अगर (buf->lossy) अणु
			thres_cells = mlxsw_sp_hdroom_buf_threshold_get(mlxsw_sp, hdroom->mtu);
			delay_cells = 0;
		पूर्ण अन्यथा अणु
			thres_cells = mlxsw_sp_hdroom_buf_threshold_get(mlxsw_sp, hdroom->mtu);
			delay_cells = mlxsw_sp_hdroom_buf_delay_get(mlxsw_sp, hdroom);
		पूर्ण

		thres_cells = mlxsw_sp_port_headroom_8x_adjust(mlxsw_sp_port, thres_cells);
		delay_cells = mlxsw_sp_port_headroom_8x_adjust(mlxsw_sp_port, delay_cells);

		buf->thres_cells = thres_cells;
		अगर (hdroom->mode == MLXSW_SP_HDROOM_MODE_DCB) अणु
			buf->size_cells = thres_cells + delay_cells;
		पूर्ण अन्यथा अणु
			/* Do not allow going below the minimum size, even अगर
			 * the user requested it.
			 */
			buf->size_cells = max(buf->set_size_cells, buf->thres_cells);
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा MLXSW_SP_PB_UNUSED 8

अटल पूर्णांक mlxsw_sp_hdroom_configure_buffers(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					     स्थिर काष्ठा mlxsw_sp_hdroom *hdroom, bool क्रमce)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर pbmc_pl[MLXSW_REG_PBMC_LEN];
	bool dirty;
	पूर्णांक err;
	पूर्णांक i;

	dirty = स_भेद(&mlxsw_sp_port->hdroom->bufs, &hdroom->bufs, माप(hdroom->bufs));
	अगर (!dirty && !क्रमce)
		वापस 0;

	mlxsw_reg_pbmc_pack(pbmc_pl, mlxsw_sp_port->local_port, 0xffff, 0xffff / 2);
	क्रम (i = 0; i < MLXSW_SP_PB_COUNT; i++) अणु
		स्थिर काष्ठा mlxsw_sp_hdroom_buf *buf = &hdroom->bufs.buf[i];

		अगर (i == MLXSW_SP_PB_UNUSED)
			जारी;

		mlxsw_sp_hdroom_buf_pack(pbmc_pl, i, buf->size_cells, buf->thres_cells, buf->lossy);
	पूर्ण

	mlxsw_reg_pbmc_lossy_buffer_pack(pbmc_pl, MLXSW_REG_PBMC_PORT_SHARED_BUF_IDX, 0);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(pbmc), pbmc_pl);
	अगर (err)
		वापस err;

	mlxsw_sp_port->hdroom->bufs = hdroom->bufs;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_hdroom_configure_priomap(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					     स्थिर काष्ठा mlxsw_sp_hdroom *hdroom, bool क्रमce)
अणु
	अक्षर pptb_pl[MLXSW_REG_PPTB_LEN];
	bool dirty;
	पूर्णांक prio;
	पूर्णांक err;

	dirty = स_भेद(&mlxsw_sp_port->hdroom->prios, &hdroom->prios, माप(hdroom->prios));
	अगर (!dirty && !क्रमce)
		वापस 0;

	mlxsw_reg_pptb_pack(pptb_pl, mlxsw_sp_port->local_port);
	क्रम (prio = 0; prio < IEEE_8021QAZ_MAX_TCS; prio++)
		mlxsw_reg_pptb_prio_to_buff_pack(pptb_pl, prio, hdroom->prios.prio[prio].buf_idx);

	err = mlxsw_reg_ग_लिखो(mlxsw_sp_port->mlxsw_sp->core, MLXSW_REG(pptb), pptb_pl);
	अगर (err)
		वापस err;

	mlxsw_sp_port->hdroom->prios = hdroom->prios;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_hdroom_configure_पूर्णांक_buf(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					     स्थिर काष्ठा mlxsw_sp_hdroom *hdroom, bool क्रमce)
अणु
	अक्षर sbib_pl[MLXSW_REG_SBIB_LEN];
	bool dirty;
	पूर्णांक err;

	dirty = स_भेद(&mlxsw_sp_port->hdroom->पूर्णांक_buf, &hdroom->पूर्णांक_buf, माप(hdroom->पूर्णांक_buf));
	अगर (!dirty && !क्रमce)
		वापस 0;

	mlxsw_reg_sbib_pack(sbib_pl, mlxsw_sp_port->local_port, hdroom->पूर्णांक_buf.size_cells);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp_port->mlxsw_sp->core, MLXSW_REG(sbib), sbib_pl);
	अगर (err)
		वापस err;

	mlxsw_sp_port->hdroom->पूर्णांक_buf = hdroom->पूर्णांक_buf;
	वापस 0;
पूर्ण

अटल bool mlxsw_sp_hdroom_bufs_fit(काष्ठा mlxsw_sp *mlxsw_sp,
				     स्थिर काष्ठा mlxsw_sp_hdroom *hdroom)
अणु
	u32 taken_headroom_cells = 0;
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SP_PB_COUNT; i++)
		taken_headroom_cells += hdroom->bufs.buf[i].size_cells;

	taken_headroom_cells += hdroom->पूर्णांक_buf.reserve_cells;
	वापस taken_headroom_cells <= mlxsw_sp->sb->max_headroom_cells;
पूर्ण

अटल पूर्णांक __mlxsw_sp_hdroom_configure(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				       स्थिर काष्ठा mlxsw_sp_hdroom *hdroom, bool क्रमce)
अणु
	काष्ठा mlxsw_sp_hdroom orig_hdroom;
	काष्ठा mlxsw_sp_hdroom पंचांगp_hdroom;
	पूर्णांक err;
	पूर्णांक i;

	/* Port buffers need to be configured in three steps. First, all buffers
	 * with non-zero size are configured. Then, prio-to-buffer map is
	 * updated, allowing traffic to flow to the now non-zero buffers.
	 * Finally, zero-sized buffers are configured, because now no traffic
	 * should be directed to them anymore. This way, in a non-congested
	 * प्रणाली, no packet drops are पूर्णांकroduced by the reconfiguration.
	 */

	orig_hdroom = *mlxsw_sp_port->hdroom;
	पंचांगp_hdroom = orig_hdroom;
	क्रम (i = 0; i < MLXSW_SP_PB_COUNT; i++) अणु
		अगर (hdroom->bufs.buf[i].size_cells)
			पंचांगp_hdroom.bufs.buf[i] = hdroom->bufs.buf[i];
	पूर्ण

	अगर (!mlxsw_sp_hdroom_bufs_fit(mlxsw_sp_port->mlxsw_sp, &पंचांगp_hdroom) ||
	    !mlxsw_sp_hdroom_bufs_fit(mlxsw_sp_port->mlxsw_sp, hdroom))
		वापस -ENOBUFS;

	err = mlxsw_sp_hdroom_configure_buffers(mlxsw_sp_port, &पंचांगp_hdroom, क्रमce);
	अगर (err)
		वापस err;

	err = mlxsw_sp_hdroom_configure_priomap(mlxsw_sp_port, hdroom, क्रमce);
	अगर (err)
		जाओ err_configure_priomap;

	err = mlxsw_sp_hdroom_configure_buffers(mlxsw_sp_port, hdroom, false);
	अगर (err)
		जाओ err_configure_buffers;

	err = mlxsw_sp_hdroom_configure_पूर्णांक_buf(mlxsw_sp_port, hdroom, false);
	अगर (err)
		जाओ err_configure_पूर्णांक_buf;

	*mlxsw_sp_port->hdroom = *hdroom;
	वापस 0;

err_configure_पूर्णांक_buf:
	mlxsw_sp_hdroom_configure_buffers(mlxsw_sp_port, &पंचांगp_hdroom, false);
err_configure_buffers:
	mlxsw_sp_hdroom_configure_priomap(mlxsw_sp_port, &पंचांगp_hdroom, false);
err_configure_priomap:
	mlxsw_sp_hdroom_configure_buffers(mlxsw_sp_port, &orig_hdroom, false);
	वापस err;
पूर्ण

पूर्णांक mlxsw_sp_hdroom_configure(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			      स्थिर काष्ठा mlxsw_sp_hdroom *hdroom)
अणु
	वापस __mlxsw_sp_hdroom_configure(mlxsw_sp_port, hdroom, false);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_headroom_init(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_hdroom hdroom = अणुपूर्ण;
	u32 size9;
	पूर्णांक prio;

	hdroom.mtu = mlxsw_sp_port->dev->mtu;
	hdroom.mode = MLXSW_SP_HDROOM_MODE_DCB;
	क्रम (prio = 0; prio < IEEE_8021QAZ_MAX_TCS; prio++)
		hdroom.prios.prio[prio].lossy = true;

	mlxsw_sp_hdroom_bufs_reset_lossiness(&hdroom);
	mlxsw_sp_hdroom_bufs_reset_sizes(mlxsw_sp_port, &hdroom);

	/* Buffer 9 is used क्रम control traffic. */
	size9 = mlxsw_sp_port_headroom_8x_adjust(mlxsw_sp_port, mlxsw_sp_port->max_mtu);
	hdroom.bufs.buf[9].size_cells = mlxsw_sp_bytes_cells(mlxsw_sp, size9);

	वापस __mlxsw_sp_hdroom_configure(mlxsw_sp_port, &hdroom, true);
पूर्ण

अटल पूर्णांक mlxsw_sp_sb_port_init(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_sb_port *sb_port)
अणु
	काष्ठा mlxsw_sp_sb_pm *pms;

	pms = kसुस्मृति(mlxsw_sp->sb_vals->pool_count, माप(*pms),
		      GFP_KERNEL);
	अगर (!pms)
		वापस -ENOMEM;
	sb_port->pms = pms;
	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_sb_port_fini(काष्ठा mlxsw_sp_sb_port *sb_port)
अणु
	kमुक्त(sb_port->pms);
पूर्ण

अटल पूर्णांक mlxsw_sp_sb_ports_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अचिन्हित पूर्णांक max_ports = mlxsw_core_max_ports(mlxsw_sp->core);
	काष्ठा mlxsw_sp_sb_pr *prs;
	पूर्णांक i;
	पूर्णांक err;

	mlxsw_sp->sb->ports = kसुस्मृति(max_ports,
				      माप(काष्ठा mlxsw_sp_sb_port),
				      GFP_KERNEL);
	अगर (!mlxsw_sp->sb->ports)
		वापस -ENOMEM;

	prs = kसुस्मृति(mlxsw_sp->sb_vals->pool_count, माप(*prs),
		      GFP_KERNEL);
	अगर (!prs) अणु
		err = -ENOMEM;
		जाओ err_alloc_prs;
	पूर्ण
	mlxsw_sp->sb->prs = prs;

	क्रम (i = 0; i < max_ports; i++) अणु
		err = mlxsw_sp_sb_port_init(mlxsw_sp, &mlxsw_sp->sb->ports[i]);
		अगर (err)
			जाओ err_sb_port_init;
	पूर्ण

	वापस 0;

err_sb_port_init:
	क्रम (i--; i >= 0; i--)
		mlxsw_sp_sb_port_fini(&mlxsw_sp->sb->ports[i]);
	kमुक्त(mlxsw_sp->sb->prs);
err_alloc_prs:
	kमुक्त(mlxsw_sp->sb->ports);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_sb_ports_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	पूर्णांक max_ports = mlxsw_core_max_ports(mlxsw_sp->core);
	पूर्णांक i;

	क्रम (i = max_ports - 1; i >= 0; i--)
		mlxsw_sp_sb_port_fini(&mlxsw_sp->sb->ports[i]);
	kमुक्त(mlxsw_sp->sb->prs);
	kमुक्त(mlxsw_sp->sb->ports);
पूर्ण

#घोषणा MLXSW_SP_SB_PR(_mode, _size)	\
	अणु				\
		.mode = _mode,		\
		.size = _size,		\
	पूर्ण

#घोषणा MLXSW_SP_SB_PR_EXT(_mode, _size, _मुक्तze_mode, _मुक्तze_size)	\
	अणु								\
		.mode = _mode,						\
		.size = _size,						\
		.मुक्तze_mode = _मुक्तze_mode,				\
		.मुक्तze_size = _मुक्तze_size,				\
	पूर्ण

#घोषणा MLXSW_SP1_SB_PR_CPU_SIZE	(256 * 1000)

/* Order according to mlxsw_sp1_sb_pool_dess */
अटल स्थिर काष्ठा mlxsw_sp_sb_pr mlxsw_sp1_sb_prs[] = अणु
	MLXSW_SP_SB_PR(MLXSW_REG_SBPR_MODE_DYNAMIC, MLXSW_SP_SB_REST),
	MLXSW_SP_SB_PR(MLXSW_REG_SBPR_MODE_DYNAMIC, 0),
	MLXSW_SP_SB_PR(MLXSW_REG_SBPR_MODE_DYNAMIC, 0),
	MLXSW_SP_SB_PR(MLXSW_REG_SBPR_MODE_DYNAMIC, 0),
	MLXSW_SP_SB_PR_EXT(MLXSW_REG_SBPR_MODE_DYNAMIC, MLXSW_SP_SB_REST,
			   true, false),
	MLXSW_SP_SB_PR(MLXSW_REG_SBPR_MODE_DYNAMIC, 0),
	MLXSW_SP_SB_PR(MLXSW_REG_SBPR_MODE_DYNAMIC, 0),
	MLXSW_SP_SB_PR(MLXSW_REG_SBPR_MODE_DYNAMIC, 0),
	MLXSW_SP_SB_PR_EXT(MLXSW_REG_SBPR_MODE_STATIC, MLXSW_SP_SB_INFI,
			   true, true),
	MLXSW_SP_SB_PR_EXT(MLXSW_REG_SBPR_MODE_DYNAMIC,
			   MLXSW_SP1_SB_PR_CPU_SIZE, true, false),
	MLXSW_SP_SB_PR_EXT(MLXSW_REG_SBPR_MODE_DYNAMIC,
			   MLXSW_SP1_SB_PR_CPU_SIZE, true, false),
पूर्ण;

#घोषणा MLXSW_SP2_SB_PR_CPU_SIZE	(256 * 1000)

/* Order according to mlxsw_sp2_sb_pool_dess */
अटल स्थिर काष्ठा mlxsw_sp_sb_pr mlxsw_sp2_sb_prs[] = अणु
	MLXSW_SP_SB_PR(MLXSW_REG_SBPR_MODE_DYNAMIC, MLXSW_SP_SB_REST),
	MLXSW_SP_SB_PR(MLXSW_REG_SBPR_MODE_STATIC, 0),
	MLXSW_SP_SB_PR(MLXSW_REG_SBPR_MODE_STATIC, 0),
	MLXSW_SP_SB_PR(MLXSW_REG_SBPR_MODE_STATIC, 0),
	MLXSW_SP_SB_PR_EXT(MLXSW_REG_SBPR_MODE_DYNAMIC, MLXSW_SP_SB_REST,
			   true, false),
	MLXSW_SP_SB_PR(MLXSW_REG_SBPR_MODE_STATIC, 0),
	MLXSW_SP_SB_PR(MLXSW_REG_SBPR_MODE_STATIC, 0),
	MLXSW_SP_SB_PR(MLXSW_REG_SBPR_MODE_STATIC, 0),
	MLXSW_SP_SB_PR_EXT(MLXSW_REG_SBPR_MODE_STATIC, MLXSW_SP_SB_INFI,
			   true, true),
	MLXSW_SP_SB_PR_EXT(MLXSW_REG_SBPR_MODE_DYNAMIC,
			   MLXSW_SP2_SB_PR_CPU_SIZE, true, false),
	MLXSW_SP_SB_PR_EXT(MLXSW_REG_SBPR_MODE_DYNAMIC,
			   MLXSW_SP2_SB_PR_CPU_SIZE, true, false),
पूर्ण;

अटल पूर्णांक mlxsw_sp_sb_prs_init(काष्ठा mlxsw_sp *mlxsw_sp,
				स्थिर काष्ठा mlxsw_sp_sb_pr *prs,
				स्थिर काष्ठा mlxsw_sp_sb_pool_des *pool_dess,
				माप_प्रकार prs_len)
अणु
	/* Round करोwn, unlike mlxsw_sp_bytes_cells(). */
	u32 sb_cells = भाग_u64(mlxsw_sp->sb->sb_size, mlxsw_sp->sb->cell_size);
	u32 rest_cells[2] = अणुsb_cells, sb_cellsपूर्ण;
	पूर्णांक i;
	पूर्णांक err;

	/* Calculate how much space to give to the "REST" pools in either
	 * direction.
	 */
	क्रम (i = 0; i < prs_len; i++) अणु
		क्रमागत mlxsw_reg_sbxx_dir dir = pool_dess[i].dir;
		u32 size = prs[i].size;
		u32 size_cells;

		अगर (size == MLXSW_SP_SB_INFI || size == MLXSW_SP_SB_REST)
			जारी;

		size_cells = mlxsw_sp_bytes_cells(mlxsw_sp, size);
		अगर (WARN_ON_ONCE(size_cells > rest_cells[dir]))
			जारी;

		rest_cells[dir] -= size_cells;
	पूर्ण

	क्रम (i = 0; i < prs_len; i++) अणु
		u32 size = prs[i].size;
		u32 size_cells;

		अगर (size == MLXSW_SP_SB_INFI) अणु
			err = mlxsw_sp_sb_pr_ग_लिखो(mlxsw_sp, i, prs[i].mode,
						   0, true);
		पूर्ण अन्यथा अगर (size == MLXSW_SP_SB_REST) अणु
			size_cells = rest_cells[pool_dess[i].dir];
			err = mlxsw_sp_sb_pr_ग_लिखो(mlxsw_sp, i, prs[i].mode,
						   size_cells, false);
		पूर्ण अन्यथा अणु
			size_cells = mlxsw_sp_bytes_cells(mlxsw_sp, size);
			err = mlxsw_sp_sb_pr_ग_लिखो(mlxsw_sp, i, prs[i].mode,
						   size_cells, false);
		पूर्ण
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा MLXSW_SP_SB_CM(_min_buff, _max_buff, _pool)	\
	अणु						\
		.min_buff = _min_buff,			\
		.max_buff = _max_buff,			\
		.pool_index = _pool,			\
	पूर्ण

#घोषणा MLXSW_SP_SB_CM_ING(_min_buff, _max_buff)	\
	अणु						\
		.min_buff = _min_buff,			\
		.max_buff = _max_buff,			\
		.pool_index = MLXSW_SP_SB_POOL_ING,	\
	पूर्ण

#घोषणा MLXSW_SP_SB_CM_EGR(_min_buff, _max_buff)	\
	अणु						\
		.min_buff = _min_buff,			\
		.max_buff = _max_buff,			\
		.pool_index = MLXSW_SP_SB_POOL_EGR,	\
	पूर्ण

#घोषणा MLXSW_SP_SB_CM_EGR_MC(_min_buff, _max_buff)	\
	अणु						\
		.min_buff = _min_buff,			\
		.max_buff = _max_buff,			\
		.pool_index = MLXSW_SP_SB_POOL_EGR_MC,	\
		.मुक्तze_pool = true,			\
		.मुक्तze_thresh = true,			\
	पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_sb_cm mlxsw_sp1_sb_cms_ingress[] = अणु
	MLXSW_SP_SB_CM_ING(10000, 8),
	MLXSW_SP_SB_CM_ING(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
	MLXSW_SP_SB_CM_ING(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
	MLXSW_SP_SB_CM_ING(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
	MLXSW_SP_SB_CM_ING(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
	MLXSW_SP_SB_CM_ING(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
	MLXSW_SP_SB_CM_ING(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
	MLXSW_SP_SB_CM_ING(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
	MLXSW_SP_SB_CM_ING(0, 0), /* dummy, this PG करोes not exist */
	MLXSW_SP_SB_CM(10000, 8, MLXSW_SP_SB_POOL_ING_CPU),
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_sb_cm mlxsw_sp2_sb_cms_ingress[] = अणु
	MLXSW_SP_SB_CM_ING(0, 7),
	MLXSW_SP_SB_CM_ING(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
	MLXSW_SP_SB_CM_ING(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
	MLXSW_SP_SB_CM_ING(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
	MLXSW_SP_SB_CM_ING(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
	MLXSW_SP_SB_CM_ING(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
	MLXSW_SP_SB_CM_ING(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
	MLXSW_SP_SB_CM_ING(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
	MLXSW_SP_SB_CM_ING(0, 0), /* dummy, this PG करोes not exist */
	MLXSW_SP_SB_CM(10000, 8, MLXSW_SP_SB_POOL_ING_CPU),
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_sb_cm mlxsw_sp1_sb_cms_egress[] = अणु
	MLXSW_SP_SB_CM_EGR(1500, 9),
	MLXSW_SP_SB_CM_EGR(1500, 9),
	MLXSW_SP_SB_CM_EGR(1500, 9),
	MLXSW_SP_SB_CM_EGR(1500, 9),
	MLXSW_SP_SB_CM_EGR(1500, 9),
	MLXSW_SP_SB_CM_EGR(1500, 9),
	MLXSW_SP_SB_CM_EGR(1500, 9),
	MLXSW_SP_SB_CM_EGR(1500, 9),
	MLXSW_SP_SB_CM_EGR_MC(0, MLXSW_SP_SB_INFI),
	MLXSW_SP_SB_CM_EGR_MC(0, MLXSW_SP_SB_INFI),
	MLXSW_SP_SB_CM_EGR_MC(0, MLXSW_SP_SB_INFI),
	MLXSW_SP_SB_CM_EGR_MC(0, MLXSW_SP_SB_INFI),
	MLXSW_SP_SB_CM_EGR_MC(0, MLXSW_SP_SB_INFI),
	MLXSW_SP_SB_CM_EGR_MC(0, MLXSW_SP_SB_INFI),
	MLXSW_SP_SB_CM_EGR_MC(0, MLXSW_SP_SB_INFI),
	MLXSW_SP_SB_CM_EGR_MC(0, MLXSW_SP_SB_INFI),
	MLXSW_SP_SB_CM_EGR(1, 0xff),
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_sb_cm mlxsw_sp2_sb_cms_egress[] = अणु
	MLXSW_SP_SB_CM_EGR(0, 7),
	MLXSW_SP_SB_CM_EGR(0, 7),
	MLXSW_SP_SB_CM_EGR(0, 7),
	MLXSW_SP_SB_CM_EGR(0, 7),
	MLXSW_SP_SB_CM_EGR(0, 7),
	MLXSW_SP_SB_CM_EGR(0, 7),
	MLXSW_SP_SB_CM_EGR(0, 7),
	MLXSW_SP_SB_CM_EGR(0, 7),
	MLXSW_SP_SB_CM_EGR_MC(0, MLXSW_SP_SB_INFI),
	MLXSW_SP_SB_CM_EGR_MC(0, MLXSW_SP_SB_INFI),
	MLXSW_SP_SB_CM_EGR_MC(0, MLXSW_SP_SB_INFI),
	MLXSW_SP_SB_CM_EGR_MC(0, MLXSW_SP_SB_INFI),
	MLXSW_SP_SB_CM_EGR_MC(0, MLXSW_SP_SB_INFI),
	MLXSW_SP_SB_CM_EGR_MC(0, MLXSW_SP_SB_INFI),
	MLXSW_SP_SB_CM_EGR_MC(0, MLXSW_SP_SB_INFI),
	MLXSW_SP_SB_CM_EGR_MC(0, MLXSW_SP_SB_INFI),
	MLXSW_SP_SB_CM_EGR(1, 0xff),
पूर्ण;

#घोषणा MLXSW_SP_CPU_PORT_SB_CM MLXSW_SP_SB_CM(0, 0, MLXSW_SP_SB_POOL_EGR_CPU)

अटल स्थिर काष्ठा mlxsw_sp_sb_cm mlxsw_sp_cpu_port_sb_cms[] = अणु
	MLXSW_SP_SB_CM(1000, 8, MLXSW_SP_SB_POOL_EGR_CPU),
	MLXSW_SP_SB_CM(1000, 8, MLXSW_SP_SB_POOL_EGR_CPU),
	MLXSW_SP_SB_CM(1000, 8, MLXSW_SP_SB_POOL_EGR_CPU),
	MLXSW_SP_SB_CM(1000, 8, MLXSW_SP_SB_POOL_EGR_CPU),
	MLXSW_SP_SB_CM(1000, 8, MLXSW_SP_SB_POOL_EGR_CPU),
	MLXSW_SP_SB_CM(1000, 8, MLXSW_SP_SB_POOL_EGR_CPU),
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_SB_CM(1000, 8, MLXSW_SP_SB_POOL_EGR_CPU),
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
	MLXSW_SP_CPU_PORT_SB_CM,
पूर्ण;

अटल bool
mlxsw_sp_sb_pool_is_अटल(काष्ठा mlxsw_sp *mlxsw_sp, u16 pool_index)
अणु
	काष्ठा mlxsw_sp_sb_pr *pr = mlxsw_sp_sb_pr_get(mlxsw_sp, pool_index);

	वापस pr->mode == MLXSW_REG_SBPR_MODE_STATIC;
पूर्ण

अटल पूर्णांक __mlxsw_sp_sb_cms_init(काष्ठा mlxsw_sp *mlxsw_sp, u8 local_port,
				  क्रमागत mlxsw_reg_sbxx_dir dir,
				  स्थिर काष्ठा mlxsw_sp_sb_cm *cms,
				  माप_प्रकार cms_len)
अणु
	स्थिर काष्ठा mlxsw_sp_sb_vals *sb_vals = mlxsw_sp->sb_vals;
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < cms_len; i++) अणु
		स्थिर काष्ठा mlxsw_sp_sb_cm *cm;
		u32 min_buff;
		u32 max_buff;

		अगर (i == 8 && dir == MLXSW_REG_SBXX_सूची_INGRESS)
			जारी; /* PG number 8 करोes not exist, skip it */
		cm = &cms[i];
		अगर (WARN_ON(sb_vals->pool_dess[cm->pool_index].dir != dir))
			जारी;

		min_buff = mlxsw_sp_bytes_cells(mlxsw_sp, cm->min_buff);
		max_buff = cm->max_buff;
		अगर (max_buff == MLXSW_SP_SB_INFI) अणु
			err = mlxsw_sp_sb_cm_ग_लिखो(mlxsw_sp, local_port, i,
						   min_buff, 0,
						   true, cm->pool_index);
		पूर्ण अन्यथा अणु
			अगर (mlxsw_sp_sb_pool_is_अटल(mlxsw_sp,
						       cm->pool_index))
				max_buff = mlxsw_sp_bytes_cells(mlxsw_sp,
								max_buff);
			err = mlxsw_sp_sb_cm_ग_लिखो(mlxsw_sp, local_port, i,
						   min_buff, max_buff,
						   false, cm->pool_index);
		पूर्ण
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_sb_cms_init(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	पूर्णांक err;

	err = __mlxsw_sp_sb_cms_init(mlxsw_sp,
				     mlxsw_sp_port->local_port,
				     MLXSW_REG_SBXX_सूची_INGRESS,
				     mlxsw_sp->sb_vals->cms_ingress,
				     mlxsw_sp->sb_vals->cms_ingress_count);
	अगर (err)
		वापस err;
	वापस __mlxsw_sp_sb_cms_init(mlxsw_sp_port->mlxsw_sp,
				      mlxsw_sp_port->local_port,
				      MLXSW_REG_SBXX_सूची_EGRESS,
				      mlxsw_sp->sb_vals->cms_egress,
				      mlxsw_sp->sb_vals->cms_egress_count);
पूर्ण

अटल पूर्णांक mlxsw_sp_cpu_port_sb_cms_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	वापस __mlxsw_sp_sb_cms_init(mlxsw_sp, 0, MLXSW_REG_SBXX_सूची_EGRESS,
				      mlxsw_sp->sb_vals->cms_cpu,
				      mlxsw_sp->sb_vals->cms_cpu_count);
पूर्ण

#घोषणा MLXSW_SP_SB_PM(_min_buff, _max_buff)	\
	अणु					\
		.min_buff = _min_buff,		\
		.max_buff = _max_buff,		\
	पूर्ण

/* Order according to mlxsw_sp1_sb_pool_dess */
अटल स्थिर काष्ठा mlxsw_sp_sb_pm mlxsw_sp1_sb_pms[] = अणु
	MLXSW_SP_SB_PM(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MAX),
	MLXSW_SP_SB_PM(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
	MLXSW_SP_SB_PM(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
	MLXSW_SP_SB_PM(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
	MLXSW_SP_SB_PM(0, 7),
	MLXSW_SP_SB_PM(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
	MLXSW_SP_SB_PM(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
	MLXSW_SP_SB_PM(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
	MLXSW_SP_SB_PM(10000, 90000),
	MLXSW_SP_SB_PM(0, 8),	/* 50% occupancy */
	MLXSW_SP_SB_PM(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
पूर्ण;

/* Order according to mlxsw_sp2_sb_pool_dess */
अटल स्थिर काष्ठा mlxsw_sp_sb_pm mlxsw_sp2_sb_pms[] = अणु
	MLXSW_SP_SB_PM(0, 7),
	MLXSW_SP_SB_PM(0, 0),
	MLXSW_SP_SB_PM(0, 0),
	MLXSW_SP_SB_PM(0, 0),
	MLXSW_SP_SB_PM(0, 7),
	MLXSW_SP_SB_PM(0, 0),
	MLXSW_SP_SB_PM(0, 0),
	MLXSW_SP_SB_PM(0, 0),
	MLXSW_SP_SB_PM(10000, 90000),
	MLXSW_SP_SB_PM(0, 8),	/* 50% occupancy */
	MLXSW_SP_SB_PM(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN),
पूर्ण;

/* Order according to mlxsw_sp*_sb_pool_dess */
अटल स्थिर काष्ठा mlxsw_sp_sb_pm mlxsw_sp_cpu_port_sb_pms[] = अणु
	MLXSW_SP_SB_PM(0, 0),
	MLXSW_SP_SB_PM(0, 0),
	MLXSW_SP_SB_PM(0, 0),
	MLXSW_SP_SB_PM(0, 0),
	MLXSW_SP_SB_PM(0, 0),
	MLXSW_SP_SB_PM(0, 0),
	MLXSW_SP_SB_PM(0, 0),
	MLXSW_SP_SB_PM(0, 0),
	MLXSW_SP_SB_PM(0, 90000),
	MLXSW_SP_SB_PM(0, 0),
	MLXSW_SP_SB_PM(0, MLXSW_REG_SBXX_DYN_MAX_BUFF_MAX),
पूर्ण;

अटल पूर्णांक mlxsw_sp_sb_pms_init(काष्ठा mlxsw_sp *mlxsw_sp, u8 local_port,
				स्थिर काष्ठा mlxsw_sp_sb_pm *pms,
				bool skip_ingress)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < mlxsw_sp->sb_vals->pool_count; i++) अणु
		स्थिर काष्ठा mlxsw_sp_sb_pm *pm = &pms[i];
		स्थिर काष्ठा mlxsw_sp_sb_pool_des *des;
		u32 max_buff;
		u32 min_buff;

		des = &mlxsw_sp->sb_vals->pool_dess[i];
		अगर (skip_ingress && des->dir == MLXSW_REG_SBXX_सूची_INGRESS)
			जारी;

		min_buff = mlxsw_sp_bytes_cells(mlxsw_sp, pm->min_buff);
		max_buff = pm->max_buff;
		अगर (mlxsw_sp_sb_pool_is_अटल(mlxsw_sp, i))
			max_buff = mlxsw_sp_bytes_cells(mlxsw_sp, max_buff);
		err = mlxsw_sp_sb_pm_ग_लिखो(mlxsw_sp, local_port, i, min_buff,
					   max_buff);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_sb_pms_init(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;

	वापस mlxsw_sp_sb_pms_init(mlxsw_sp, mlxsw_sp_port->local_port,
				    mlxsw_sp->sb_vals->pms, false);
पूर्ण

अटल पूर्णांक mlxsw_sp_cpu_port_sb_pms_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	वापस mlxsw_sp_sb_pms_init(mlxsw_sp, 0, mlxsw_sp->sb_vals->pms_cpu,
				    true);
पूर्ण

#घोषणा MLXSW_SP_SB_MM(_min_buff, _max_buff)		\
	अणु						\
		.min_buff = _min_buff,			\
		.max_buff = _max_buff,			\
		.pool_index = MLXSW_SP_SB_POOL_EGR,	\
	पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_sb_mm mlxsw_sp_sb_mms[] = अणु
	MLXSW_SP_SB_MM(0, 6),
	MLXSW_SP_SB_MM(0, 6),
	MLXSW_SP_SB_MM(0, 6),
	MLXSW_SP_SB_MM(0, 6),
	MLXSW_SP_SB_MM(0, 6),
	MLXSW_SP_SB_MM(0, 6),
	MLXSW_SP_SB_MM(0, 6),
	MLXSW_SP_SB_MM(0, 6),
	MLXSW_SP_SB_MM(0, 6),
	MLXSW_SP_SB_MM(0, 6),
	MLXSW_SP_SB_MM(0, 6),
	MLXSW_SP_SB_MM(0, 6),
	MLXSW_SP_SB_MM(0, 6),
	MLXSW_SP_SB_MM(0, 6),
	MLXSW_SP_SB_MM(0, 6),
पूर्ण;

अटल पूर्णांक mlxsw_sp_sb_mms_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अक्षर sbmm_pl[MLXSW_REG_SBMM_LEN];
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < mlxsw_sp->sb_vals->mms_count; i++) अणु
		स्थिर काष्ठा mlxsw_sp_sb_pool_des *des;
		स्थिर काष्ठा mlxsw_sp_sb_mm *mc;
		u32 min_buff;

		mc = &mlxsw_sp->sb_vals->mms[i];
		des = &mlxsw_sp->sb_vals->pool_dess[mc->pool_index];
		/* All pools used by sb_mm's are initialized using dynamic
		 * thresholds, thereक्रमe 'max_buff' isn't specअगरied in cells.
		 */
		min_buff = mlxsw_sp_bytes_cells(mlxsw_sp, mc->min_buff);
		mlxsw_reg_sbmm_pack(sbmm_pl, i, min_buff, mc->max_buff,
				    des->pool);
		err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(sbmm), sbmm_pl);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_pool_count(काष्ठा mlxsw_sp *mlxsw_sp,
				u16 *p_ingress_len, u16 *p_egress_len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mlxsw_sp->sb_vals->pool_count; ++i) अणु
		अगर (mlxsw_sp->sb_vals->pool_dess[i].dir ==
		    MLXSW_REG_SBXX_सूची_INGRESS)
			(*p_ingress_len)++;
		अन्यथा
			(*p_egress_len)++;
	पूर्ण

	WARN(*p_egress_len == 0, "No egress pools\n");
पूर्ण

स्थिर काष्ठा mlxsw_sp_sb_vals mlxsw_sp1_sb_vals = अणु
	.pool_count = ARRAY_SIZE(mlxsw_sp1_sb_pool_dess),
	.pool_dess = mlxsw_sp1_sb_pool_dess,
	.pms = mlxsw_sp1_sb_pms,
	.pms_cpu = mlxsw_sp_cpu_port_sb_pms,
	.prs = mlxsw_sp1_sb_prs,
	.mms = mlxsw_sp_sb_mms,
	.cms_ingress = mlxsw_sp1_sb_cms_ingress,
	.cms_egress = mlxsw_sp1_sb_cms_egress,
	.cms_cpu = mlxsw_sp_cpu_port_sb_cms,
	.mms_count = ARRAY_SIZE(mlxsw_sp_sb_mms),
	.cms_ingress_count = ARRAY_SIZE(mlxsw_sp1_sb_cms_ingress),
	.cms_egress_count = ARRAY_SIZE(mlxsw_sp1_sb_cms_egress),
	.cms_cpu_count = ARRAY_SIZE(mlxsw_sp_cpu_port_sb_cms),
पूर्ण;

स्थिर काष्ठा mlxsw_sp_sb_vals mlxsw_sp2_sb_vals = अणु
	.pool_count = ARRAY_SIZE(mlxsw_sp2_sb_pool_dess),
	.pool_dess = mlxsw_sp2_sb_pool_dess,
	.pms = mlxsw_sp2_sb_pms,
	.pms_cpu = mlxsw_sp_cpu_port_sb_pms,
	.prs = mlxsw_sp2_sb_prs,
	.mms = mlxsw_sp_sb_mms,
	.cms_ingress = mlxsw_sp2_sb_cms_ingress,
	.cms_egress = mlxsw_sp2_sb_cms_egress,
	.cms_cpu = mlxsw_sp_cpu_port_sb_cms,
	.mms_count = ARRAY_SIZE(mlxsw_sp_sb_mms),
	.cms_ingress_count = ARRAY_SIZE(mlxsw_sp2_sb_cms_ingress),
	.cms_egress_count = ARRAY_SIZE(mlxsw_sp2_sb_cms_egress),
	.cms_cpu_count = ARRAY_SIZE(mlxsw_sp_cpu_port_sb_cms),
पूर्ण;

अटल u32 mlxsw_sp1_pb_पूर्णांक_buf_size_get(पूर्णांक mtu, u32 speed)
अणु
	वापस mtu * 5 / 2;
पूर्ण

अटल u32 __mlxsw_sp_pb_पूर्णांक_buf_size_get(पूर्णांक mtu, u32 speed, u32 buffer_factor)
अणु
	वापस 3 * mtu + buffer_factor * speed / 1000;
पूर्ण

#घोषणा MLXSW_SP2_SPAN_EG_MIRROR_BUFFER_FACTOR 38

अटल u32 mlxsw_sp2_pb_पूर्णांक_buf_size_get(पूर्णांक mtu, u32 speed)
अणु
	पूर्णांक factor = MLXSW_SP2_SPAN_EG_MIRROR_BUFFER_FACTOR;

	वापस __mlxsw_sp_pb_पूर्णांक_buf_size_get(mtu, speed, factor);
पूर्ण

#घोषणा MLXSW_SP3_SPAN_EG_MIRROR_BUFFER_FACTOR 50

अटल u32 mlxsw_sp3_pb_पूर्णांक_buf_size_get(पूर्णांक mtu, u32 speed)
अणु
	पूर्णांक factor = MLXSW_SP3_SPAN_EG_MIRROR_BUFFER_FACTOR;

	वापस __mlxsw_sp_pb_पूर्णांक_buf_size_get(mtu, speed, factor);
पूर्ण

स्थिर काष्ठा mlxsw_sp_sb_ops mlxsw_sp1_sb_ops = अणु
	.पूर्णांक_buf_size_get = mlxsw_sp1_pb_पूर्णांक_buf_size_get,
पूर्ण;

स्थिर काष्ठा mlxsw_sp_sb_ops mlxsw_sp2_sb_ops = अणु
	.पूर्णांक_buf_size_get = mlxsw_sp2_pb_पूर्णांक_buf_size_get,
पूर्ण;

स्थिर काष्ठा mlxsw_sp_sb_ops mlxsw_sp3_sb_ops = अणु
	.पूर्णांक_buf_size_get = mlxsw_sp3_pb_पूर्णांक_buf_size_get,
पूर्ण;

पूर्णांक mlxsw_sp_buffers_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	u32 max_headroom_size;
	u16 ing_pool_count = 0;
	u16 eg_pool_count = 0;
	पूर्णांक err;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, CELL_SIZE))
		वापस -EIO;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, GUARANTEED_SHARED_BUFFER))
		वापस -EIO;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, MAX_HEADROOM_SIZE))
		वापस -EIO;

	mlxsw_sp->sb = kzalloc(माप(*mlxsw_sp->sb), GFP_KERNEL);
	अगर (!mlxsw_sp->sb)
		वापस -ENOMEM;
	mlxsw_sp->sb->cell_size = MLXSW_CORE_RES_GET(mlxsw_sp->core, CELL_SIZE);
	mlxsw_sp->sb->sb_size = MLXSW_CORE_RES_GET(mlxsw_sp->core,
						   GUARANTEED_SHARED_BUFFER);
	max_headroom_size = MLXSW_CORE_RES_GET(mlxsw_sp->core,
					       MAX_HEADROOM_SIZE);
	/* Round करोwn, because this limit must not be overstepped. */
	mlxsw_sp->sb->max_headroom_cells = max_headroom_size /
						mlxsw_sp->sb->cell_size;

	err = mlxsw_sp_sb_ports_init(mlxsw_sp);
	अगर (err)
		जाओ err_sb_ports_init;
	err = mlxsw_sp_sb_prs_init(mlxsw_sp, mlxsw_sp->sb_vals->prs,
				   mlxsw_sp->sb_vals->pool_dess,
				   mlxsw_sp->sb_vals->pool_count);
	अगर (err)
		जाओ err_sb_prs_init;
	err = mlxsw_sp_cpu_port_sb_cms_init(mlxsw_sp);
	अगर (err)
		जाओ err_sb_cpu_port_sb_cms_init;
	err = mlxsw_sp_cpu_port_sb_pms_init(mlxsw_sp);
	अगर (err)
		जाओ err_sb_cpu_port_pms_init;
	err = mlxsw_sp_sb_mms_init(mlxsw_sp);
	अगर (err)
		जाओ err_sb_mms_init;
	mlxsw_sp_pool_count(mlxsw_sp, &ing_pool_count, &eg_pool_count);
	err = devlink_sb_रेजिस्टर(priv_to_devlink(mlxsw_sp->core), 0,
				  mlxsw_sp->sb->sb_size,
				  ing_pool_count,
				  eg_pool_count,
				  MLXSW_SP_SB_ING_TC_COUNT,
				  MLXSW_SP_SB_EG_TC_COUNT);
	अगर (err)
		जाओ err_devlink_sb_रेजिस्टर;

	वापस 0;

err_devlink_sb_रेजिस्टर:
err_sb_mms_init:
err_sb_cpu_port_pms_init:
err_sb_cpu_port_sb_cms_init:
err_sb_prs_init:
	mlxsw_sp_sb_ports_fini(mlxsw_sp);
err_sb_ports_init:
	kमुक्त(mlxsw_sp->sb);
	वापस err;
पूर्ण

व्योम mlxsw_sp_buffers_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	devlink_sb_unरेजिस्टर(priv_to_devlink(mlxsw_sp->core), 0);
	mlxsw_sp_sb_ports_fini(mlxsw_sp);
	kमुक्त(mlxsw_sp->sb);
पूर्ण

पूर्णांक mlxsw_sp_port_buffers_init(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	पूर्णांक err;

	mlxsw_sp_port->hdroom = kzalloc(माप(*mlxsw_sp_port->hdroom), GFP_KERNEL);
	अगर (!mlxsw_sp_port->hdroom)
		वापस -ENOMEM;
	mlxsw_sp_port->hdroom->mtu = mlxsw_sp_port->dev->mtu;

	err = mlxsw_sp_port_headroom_init(mlxsw_sp_port);
	अगर (err)
		जाओ err_headroom_init;
	err = mlxsw_sp_port_sb_cms_init(mlxsw_sp_port);
	अगर (err)
		जाओ err_port_sb_cms_init;
	err = mlxsw_sp_port_sb_pms_init(mlxsw_sp_port);
	अगर (err)
		जाओ err_port_sb_pms_init;
	वापस 0;

err_port_sb_pms_init:
err_port_sb_cms_init:
err_headroom_init:
	kमुक्त(mlxsw_sp_port->hdroom);
	वापस err;
पूर्ण

व्योम mlxsw_sp_port_buffers_fini(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	kमुक्त(mlxsw_sp_port->hdroom);
पूर्ण

पूर्णांक mlxsw_sp_sb_pool_get(काष्ठा mlxsw_core *mlxsw_core,
			 अचिन्हित पूर्णांक sb_index, u16 pool_index,
			 काष्ठा devlink_sb_pool_info *pool_info)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);
	क्रमागत mlxsw_reg_sbxx_dir dir;
	काष्ठा mlxsw_sp_sb_pr *pr;

	dir = mlxsw_sp->sb_vals->pool_dess[pool_index].dir;
	pr = mlxsw_sp_sb_pr_get(mlxsw_sp, pool_index);
	pool_info->pool_type = (क्रमागत devlink_sb_pool_type) dir;
	pool_info->size = mlxsw_sp_cells_bytes(mlxsw_sp, pr->size);
	pool_info->threshold_type = (क्रमागत devlink_sb_threshold_type) pr->mode;
	pool_info->cell_size = mlxsw_sp->sb->cell_size;
	वापस 0;
पूर्ण

पूर्णांक mlxsw_sp_sb_pool_set(काष्ठा mlxsw_core *mlxsw_core,
			 अचिन्हित पूर्णांक sb_index, u16 pool_index, u32 size,
			 क्रमागत devlink_sb_threshold_type threshold_type,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);
	u32 pool_size = mlxsw_sp_bytes_cells(mlxsw_sp, size);
	स्थिर काष्ठा mlxsw_sp_sb_pr *pr;
	क्रमागत mlxsw_reg_sbpr_mode mode;

	mode = (क्रमागत mlxsw_reg_sbpr_mode) threshold_type;
	pr = &mlxsw_sp->sb_vals->prs[pool_index];

	अगर (size > MLXSW_CORE_RES_GET(mlxsw_sp->core,
				      GUARANTEED_SHARED_BUFFER)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Exceeded shared buffer size");
		वापस -EINVAL;
	पूर्ण

	अगर (pr->मुक्तze_mode && pr->mode != mode) अणु
		NL_SET_ERR_MSG_MOD(extack, "Changing this pool's threshold type is forbidden");
		वापस -EINVAL;
	पूर्ण

	अगर (pr->मुक्तze_size && pr->size != size) अणु
		NL_SET_ERR_MSG_MOD(extack, "Changing this pool's size is forbidden");
		वापस -EINVAL;
	पूर्ण

	वापस mlxsw_sp_sb_pr_ग_लिखो(mlxsw_sp, pool_index, mode,
				    pool_size, false);
पूर्ण

#घोषणा MLXSW_SP_SB_THRESHOLD_TO_ALPHA_OFFSET (-2) /* 3->1, 16->14 */

अटल u32 mlxsw_sp_sb_threshold_out(काष्ठा mlxsw_sp *mlxsw_sp, u16 pool_index,
				     u32 max_buff)
अणु
	काष्ठा mlxsw_sp_sb_pr *pr = mlxsw_sp_sb_pr_get(mlxsw_sp, pool_index);

	अगर (pr->mode == MLXSW_REG_SBPR_MODE_DYNAMIC)
		वापस max_buff - MLXSW_SP_SB_THRESHOLD_TO_ALPHA_OFFSET;
	वापस mlxsw_sp_cells_bytes(mlxsw_sp, max_buff);
पूर्ण

अटल पूर्णांक mlxsw_sp_sb_threshold_in(काष्ठा mlxsw_sp *mlxsw_sp, u16 pool_index,
				    u32 threshold, u32 *p_max_buff,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_sb_pr *pr = mlxsw_sp_sb_pr_get(mlxsw_sp, pool_index);

	अगर (pr->mode == MLXSW_REG_SBPR_MODE_DYNAMIC) अणु
		पूर्णांक val;

		val = threshold + MLXSW_SP_SB_THRESHOLD_TO_ALPHA_OFFSET;
		अगर (val < MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN ||
		    val > MLXSW_REG_SBXX_DYN_MAX_BUFF_MAX) अणु
			NL_SET_ERR_MSG_MOD(extack, "Invalid dynamic threshold value");
			वापस -EINVAL;
		पूर्ण
		*p_max_buff = val;
	पूर्ण अन्यथा अणु
		*p_max_buff = mlxsw_sp_bytes_cells(mlxsw_sp, threshold);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक mlxsw_sp_sb_port_pool_get(काष्ठा mlxsw_core_port *mlxsw_core_port,
			      अचिन्हित पूर्णांक sb_index, u16 pool_index,
			      u32 *p_threshold)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port =
			mlxsw_core_port_driver_priv(mlxsw_core_port);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	u8 local_port = mlxsw_sp_port->local_port;
	काष्ठा mlxsw_sp_sb_pm *pm = mlxsw_sp_sb_pm_get(mlxsw_sp, local_port,
						       pool_index);

	*p_threshold = mlxsw_sp_sb_threshold_out(mlxsw_sp, pool_index,
						 pm->max_buff);
	वापस 0;
पूर्ण

पूर्णांक mlxsw_sp_sb_port_pool_set(काष्ठा mlxsw_core_port *mlxsw_core_port,
			      अचिन्हित पूर्णांक sb_index, u16 pool_index,
			      u32 threshold, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port =
			mlxsw_core_port_driver_priv(mlxsw_core_port);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	u8 local_port = mlxsw_sp_port->local_port;
	u32 max_buff;
	पूर्णांक err;

	अगर (local_port == MLXSW_PORT_CPU_PORT) अणु
		NL_SET_ERR_MSG_MOD(extack, "Changing CPU port's threshold is forbidden");
		वापस -EINVAL;
	पूर्ण

	err = mlxsw_sp_sb_threshold_in(mlxsw_sp, pool_index,
				       threshold, &max_buff, extack);
	अगर (err)
		वापस err;

	वापस mlxsw_sp_sb_pm_ग_लिखो(mlxsw_sp, local_port, pool_index,
				    0, max_buff);
पूर्ण

पूर्णांक mlxsw_sp_sb_tc_pool_bind_get(काष्ठा mlxsw_core_port *mlxsw_core_port,
				 अचिन्हित पूर्णांक sb_index, u16 tc_index,
				 क्रमागत devlink_sb_pool_type pool_type,
				 u16 *p_pool_index, u32 *p_threshold)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port =
			mlxsw_core_port_driver_priv(mlxsw_core_port);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	u8 local_port = mlxsw_sp_port->local_port;
	u8 pg_buff = tc_index;
	क्रमागत mlxsw_reg_sbxx_dir dir = (क्रमागत mlxsw_reg_sbxx_dir) pool_type;
	काष्ठा mlxsw_sp_sb_cm *cm = mlxsw_sp_sb_cm_get(mlxsw_sp, local_port,
						       pg_buff, dir);

	*p_threshold = mlxsw_sp_sb_threshold_out(mlxsw_sp, cm->pool_index,
						 cm->max_buff);
	*p_pool_index = cm->pool_index;
	वापस 0;
पूर्ण

पूर्णांक mlxsw_sp_sb_tc_pool_bind_set(काष्ठा mlxsw_core_port *mlxsw_core_port,
				 अचिन्हित पूर्णांक sb_index, u16 tc_index,
				 क्रमागत devlink_sb_pool_type pool_type,
				 u16 pool_index, u32 threshold,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port =
			mlxsw_core_port_driver_priv(mlxsw_core_port);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	u8 local_port = mlxsw_sp_port->local_port;
	स्थिर काष्ठा mlxsw_sp_sb_cm *cm;
	u8 pg_buff = tc_index;
	क्रमागत mlxsw_reg_sbxx_dir dir = (क्रमागत mlxsw_reg_sbxx_dir) pool_type;
	u32 max_buff;
	पूर्णांक err;

	अगर (local_port == MLXSW_PORT_CPU_PORT) अणु
		NL_SET_ERR_MSG_MOD(extack, "Changing CPU port's binding is forbidden");
		वापस -EINVAL;
	पूर्ण

	अगर (dir != mlxsw_sp->sb_vals->pool_dess[pool_index].dir) अणु
		NL_SET_ERR_MSG_MOD(extack, "Binding egress TC to ingress pool and vice versa is forbidden");
		वापस -EINVAL;
	पूर्ण

	अगर (dir == MLXSW_REG_SBXX_सूची_INGRESS)
		cm = &mlxsw_sp->sb_vals->cms_ingress[tc_index];
	अन्यथा
		cm = &mlxsw_sp->sb_vals->cms_egress[tc_index];

	अगर (cm->मुक्तze_pool && cm->pool_index != pool_index) अणु
		NL_SET_ERR_MSG_MOD(extack, "Binding this TC to a different pool is forbidden");
		वापस -EINVAL;
	पूर्ण

	अगर (cm->मुक्तze_thresh && cm->max_buff != threshold) अणु
		NL_SET_ERR_MSG_MOD(extack, "Changing this TC's threshold is forbidden");
		वापस -EINVAL;
	पूर्ण

	err = mlxsw_sp_sb_threshold_in(mlxsw_sp, pool_index,
				       threshold, &max_buff, extack);
	अगर (err)
		वापस err;

	वापस mlxsw_sp_sb_cm_ग_लिखो(mlxsw_sp, local_port, pg_buff,
				    0, max_buff, false, pool_index);
पूर्ण

#घोषणा MASKED_COUNT_MAX \
	(MLXSW_REG_SBSR_REC_MAX_COUNT / \
	 (MLXSW_SP_SB_ING_TC_COUNT + MLXSW_SP_SB_EG_TC_COUNT))

काष्ठा mlxsw_sp_sb_sr_occ_query_cb_ctx अणु
	u8 masked_count;
	u8 local_port_1;
पूर्ण;

अटल व्योम mlxsw_sp_sb_sr_occ_query_cb(काष्ठा mlxsw_core *mlxsw_core,
					अक्षर *sbsr_pl, माप_प्रकार sbsr_pl_len,
					अचिन्हित दीर्घ cb_priv)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);
	काष्ठा mlxsw_sp_sb_sr_occ_query_cb_ctx cb_ctx;
	u8 masked_count;
	u8 local_port;
	पूर्णांक rec_index = 0;
	काष्ठा mlxsw_sp_sb_cm *cm;
	पूर्णांक i;

	स_नकल(&cb_ctx, &cb_priv, माप(cb_ctx));

	masked_count = 0;
	क्रम (local_port = cb_ctx.local_port_1;
	     local_port < mlxsw_core_max_ports(mlxsw_core); local_port++) अणु
		अगर (!mlxsw_sp->ports[local_port])
			जारी;
		अगर (local_port == MLXSW_PORT_CPU_PORT) अणु
			/* Ingress quotas are not supported क्रम the CPU port */
			masked_count++;
			जारी;
		पूर्ण
		क्रम (i = 0; i < MLXSW_SP_SB_ING_TC_COUNT; i++) अणु
			cm = mlxsw_sp_sb_cm_get(mlxsw_sp, local_port, i,
						MLXSW_REG_SBXX_सूची_INGRESS);
			mlxsw_reg_sbsr_rec_unpack(sbsr_pl, rec_index++,
						  &cm->occ.cur, &cm->occ.max);
		पूर्ण
		अगर (++masked_count == cb_ctx.masked_count)
			अवरोध;
	पूर्ण
	masked_count = 0;
	क्रम (local_port = cb_ctx.local_port_1;
	     local_port < mlxsw_core_max_ports(mlxsw_core); local_port++) अणु
		अगर (!mlxsw_sp->ports[local_port])
			जारी;
		क्रम (i = 0; i < MLXSW_SP_SB_EG_TC_COUNT; i++) अणु
			cm = mlxsw_sp_sb_cm_get(mlxsw_sp, local_port, i,
						MLXSW_REG_SBXX_सूची_EGRESS);
			mlxsw_reg_sbsr_rec_unpack(sbsr_pl, rec_index++,
						  &cm->occ.cur, &cm->occ.max);
		पूर्ण
		अगर (++masked_count == cb_ctx.masked_count)
			अवरोध;
	पूर्ण
पूर्ण

पूर्णांक mlxsw_sp_sb_occ_snapshot(काष्ठा mlxsw_core *mlxsw_core,
			     अचिन्हित पूर्णांक sb_index)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);
	काष्ठा mlxsw_sp_sb_sr_occ_query_cb_ctx cb_ctx;
	अचिन्हित दीर्घ cb_priv;
	LIST_HEAD(bulk_list);
	अक्षर *sbsr_pl;
	u8 masked_count;
	u8 local_port_1;
	u8 local_port;
	पूर्णांक i;
	पूर्णांक err;
	पूर्णांक err2;

	sbsr_pl = kदो_स्मृति(MLXSW_REG_SBSR_LEN, GFP_KERNEL);
	अगर (!sbsr_pl)
		वापस -ENOMEM;

	local_port = MLXSW_PORT_CPU_PORT;
next_batch:
	local_port_1 = local_port;
	masked_count = 0;
	mlxsw_reg_sbsr_pack(sbsr_pl, false);
	क्रम (i = 0; i < MLXSW_SP_SB_ING_TC_COUNT; i++)
		mlxsw_reg_sbsr_pg_buff_mask_set(sbsr_pl, i, 1);
	क्रम (i = 0; i < MLXSW_SP_SB_EG_TC_COUNT; i++)
		mlxsw_reg_sbsr_tclass_mask_set(sbsr_pl, i, 1);
	क्रम (; local_port < mlxsw_core_max_ports(mlxsw_core); local_port++) अणु
		अगर (!mlxsw_sp->ports[local_port])
			जारी;
		अगर (local_port != MLXSW_PORT_CPU_PORT) अणु
			/* Ingress quotas are not supported क्रम the CPU port */
			mlxsw_reg_sbsr_ingress_port_mask_set(sbsr_pl,
							     local_port, 1);
		पूर्ण
		mlxsw_reg_sbsr_egress_port_mask_set(sbsr_pl, local_port, 1);
		क्रम (i = 0; i < mlxsw_sp->sb_vals->pool_count; i++) अणु
			err = mlxsw_sp_sb_pm_occ_query(mlxsw_sp, local_port, i,
						       &bulk_list);
			अगर (err)
				जाओ out;
		पूर्ण
		अगर (++masked_count == MASKED_COUNT_MAX)
			जाओ करो_query;
	पूर्ण

करो_query:
	cb_ctx.masked_count = masked_count;
	cb_ctx.local_port_1 = local_port_1;
	स_नकल(&cb_priv, &cb_ctx, माप(cb_ctx));
	err = mlxsw_reg_trans_query(mlxsw_core, MLXSW_REG(sbsr), sbsr_pl,
				    &bulk_list, mlxsw_sp_sb_sr_occ_query_cb,
				    cb_priv);
	अगर (err)
		जाओ out;
	अगर (local_port < mlxsw_core_max_ports(mlxsw_core)) अणु
		local_port++;
		जाओ next_batch;
	पूर्ण

out:
	err2 = mlxsw_reg_trans_bulk_रुको(&bulk_list);
	अगर (!err)
		err = err2;
	kमुक्त(sbsr_pl);
	वापस err;
पूर्ण

पूर्णांक mlxsw_sp_sb_occ_max_clear(काष्ठा mlxsw_core *mlxsw_core,
			      अचिन्हित पूर्णांक sb_index)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);
	LIST_HEAD(bulk_list);
	अक्षर *sbsr_pl;
	अचिन्हित पूर्णांक masked_count;
	u8 local_port;
	पूर्णांक i;
	पूर्णांक err;
	पूर्णांक err2;

	sbsr_pl = kदो_स्मृति(MLXSW_REG_SBSR_LEN, GFP_KERNEL);
	अगर (!sbsr_pl)
		वापस -ENOMEM;

	local_port = MLXSW_PORT_CPU_PORT;
next_batch:
	masked_count = 0;
	mlxsw_reg_sbsr_pack(sbsr_pl, true);
	क्रम (i = 0; i < MLXSW_SP_SB_ING_TC_COUNT; i++)
		mlxsw_reg_sbsr_pg_buff_mask_set(sbsr_pl, i, 1);
	क्रम (i = 0; i < MLXSW_SP_SB_EG_TC_COUNT; i++)
		mlxsw_reg_sbsr_tclass_mask_set(sbsr_pl, i, 1);
	क्रम (; local_port < mlxsw_core_max_ports(mlxsw_core); local_port++) अणु
		अगर (!mlxsw_sp->ports[local_port])
			जारी;
		अगर (local_port != MLXSW_PORT_CPU_PORT) अणु
			/* Ingress quotas are not supported क्रम the CPU port */
			mlxsw_reg_sbsr_ingress_port_mask_set(sbsr_pl,
							     local_port, 1);
		पूर्ण
		mlxsw_reg_sbsr_egress_port_mask_set(sbsr_pl, local_port, 1);
		क्रम (i = 0; i < mlxsw_sp->sb_vals->pool_count; i++) अणु
			err = mlxsw_sp_sb_pm_occ_clear(mlxsw_sp, local_port, i,
						       &bulk_list);
			अगर (err)
				जाओ out;
		पूर्ण
		अगर (++masked_count == MASKED_COUNT_MAX)
			जाओ करो_query;
	पूर्ण

करो_query:
	err = mlxsw_reg_trans_query(mlxsw_core, MLXSW_REG(sbsr), sbsr_pl,
				    &bulk_list, शून्य, 0);
	अगर (err)
		जाओ out;
	अगर (local_port < mlxsw_core_max_ports(mlxsw_core)) अणु
		local_port++;
		जाओ next_batch;
	पूर्ण

out:
	err2 = mlxsw_reg_trans_bulk_रुको(&bulk_list);
	अगर (!err)
		err = err2;
	kमुक्त(sbsr_pl);
	वापस err;
पूर्ण

पूर्णांक mlxsw_sp_sb_occ_port_pool_get(काष्ठा mlxsw_core_port *mlxsw_core_port,
				  अचिन्हित पूर्णांक sb_index, u16 pool_index,
				  u32 *p_cur, u32 *p_max)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port =
			mlxsw_core_port_driver_priv(mlxsw_core_port);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	u8 local_port = mlxsw_sp_port->local_port;
	काष्ठा mlxsw_sp_sb_pm *pm = mlxsw_sp_sb_pm_get(mlxsw_sp, local_port,
						       pool_index);

	*p_cur = mlxsw_sp_cells_bytes(mlxsw_sp, pm->occ.cur);
	*p_max = mlxsw_sp_cells_bytes(mlxsw_sp, pm->occ.max);
	वापस 0;
पूर्ण

पूर्णांक mlxsw_sp_sb_occ_tc_port_bind_get(काष्ठा mlxsw_core_port *mlxsw_core_port,
				     अचिन्हित पूर्णांक sb_index, u16 tc_index,
				     क्रमागत devlink_sb_pool_type pool_type,
				     u32 *p_cur, u32 *p_max)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port =
			mlxsw_core_port_driver_priv(mlxsw_core_port);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	u8 local_port = mlxsw_sp_port->local_port;
	u8 pg_buff = tc_index;
	क्रमागत mlxsw_reg_sbxx_dir dir = (क्रमागत mlxsw_reg_sbxx_dir) pool_type;
	काष्ठा mlxsw_sp_sb_cm *cm = mlxsw_sp_sb_cm_get(mlxsw_sp, local_port,
						       pg_buff, dir);

	*p_cur = mlxsw_sp_cells_bytes(mlxsw_sp, cm->occ.cur);
	*p_max = mlxsw_sp_cells_bytes(mlxsw_sp, cm->occ.max);
	वापस 0;
पूर्ण
