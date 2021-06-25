<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/slab.h>

#समावेश "qlge.h"

/* Read a NIC रेजिस्टर from the alternate function. */
अटल u32 qlge_पढ़ो_other_func_reg(काष्ठा qlge_adapter *qdev,
				    u32 reg)
अणु
	u32 रेजिस्टर_to_पढ़ो;
	u32 reg_val;
	अचिन्हित पूर्णांक status = 0;

	रेजिस्टर_to_पढ़ो = MPI_NIC_REG_BLOCK
				| MPI_NIC_READ
				| (qdev->alt_func << MPI_NIC_FUNCTION_SHIFT)
				| reg;
	status = qlge_पढ़ो_mpi_reg(qdev, रेजिस्टर_to_पढ़ो, &reg_val);
	अगर (status != 0)
		वापस 0xffffffff;

	वापस reg_val;
पूर्ण

/* Write a NIC रेजिस्टर from the alternate function. */
अटल पूर्णांक qlge_ग_लिखो_other_func_reg(काष्ठा qlge_adapter *qdev,
				     u32 reg, u32 reg_val)
अणु
	u32 रेजिस्टर_to_पढ़ो;

	रेजिस्टर_to_पढ़ो = MPI_NIC_REG_BLOCK
				| MPI_NIC_READ
				| (qdev->alt_func << MPI_NIC_FUNCTION_SHIFT)
				| reg;

	वापस qlge_ग_लिखो_mpi_reg(qdev, रेजिस्टर_to_पढ़ो, reg_val);
पूर्ण

अटल पूर्णांक qlge_रुको_other_func_reg_rdy(काष्ठा qlge_adapter *qdev, u32 reg,
					u32 bit, u32 err_bit)
अणु
	u32 temp;
	पूर्णांक count;

	क्रम (count = 10; count; count--) अणु
		temp = qlge_पढ़ो_other_func_reg(qdev, reg);

		/* check क्रम errors */
		अगर (temp & err_bit)
			वापस -1;
		अन्यथा अगर (temp & bit)
			वापस 0;
		mdelay(10);
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक qlge_पढ़ो_other_func_serdes_reg(काष्ठा qlge_adapter *qdev, u32 reg,
					   u32 *data)
अणु
	पूर्णांक status;

	/* रुको क्रम reg to come पढ़ोy */
	status = qlge_रुको_other_func_reg_rdy(qdev, XG_SERDES_ADDR / 4,
					      XG_SERDES_ADDR_RDY, 0);
	अगर (status)
		जाओ निकास;

	/* set up क्रम reg पढ़ो */
	qlge_ग_लिखो_other_func_reg(qdev, XG_SERDES_ADDR / 4, reg | PROC_ADDR_R);

	/* रुको क्रम reg to come पढ़ोy */
	status = qlge_रुको_other_func_reg_rdy(qdev, XG_SERDES_ADDR / 4,
					      XG_SERDES_ADDR_RDY, 0);
	अगर (status)
		जाओ निकास;

	/* get the data */
	*data = qlge_पढ़ो_other_func_reg(qdev, (XG_SERDES_DATA / 4));
निकास:
	वापस status;
पूर्ण

/* Read out the SERDES रेजिस्टरs */
अटल पूर्णांक qlge_पढ़ो_serdes_reg(काष्ठा qlge_adapter *qdev, u32 reg, u32 *data)
अणु
	पूर्णांक status;

	/* रुको क्रम reg to come पढ़ोy */
	status = qlge_रुको_reg_rdy(qdev, XG_SERDES_ADDR, XG_SERDES_ADDR_RDY, 0);
	अगर (status)
		जाओ निकास;

	/* set up क्रम reg पढ़ो */
	qlge_ग_लिखो32(qdev, XG_SERDES_ADDR, reg | PROC_ADDR_R);

	/* रुको क्रम reg to come पढ़ोy */
	status = qlge_रुको_reg_rdy(qdev, XG_SERDES_ADDR, XG_SERDES_ADDR_RDY, 0);
	अगर (status)
		जाओ निकास;

	/* get the data */
	*data = qlge_पढ़ो32(qdev, XG_SERDES_DATA);
निकास:
	वापस status;
पूर्ण

अटल व्योम qlge_get_both_serdes(काष्ठा qlge_adapter *qdev, u32 addr,
				 u32 *direct_ptr, u32 *indirect_ptr,
				 bool direct_valid, bool indirect_valid)
अणु
	अचिन्हित पूर्णांक status;

	status = 1;
	अगर (direct_valid)
		status = qlge_पढ़ो_serdes_reg(qdev, addr, direct_ptr);
	/* Dead fill any failures or invalids. */
	अगर (status)
		*direct_ptr = 0xDEADBEEF;

	status = 1;
	अगर (indirect_valid)
		status = qlge_पढ़ो_other_func_serdes_reg(qdev, addr,
							 indirect_ptr);
	/* Dead fill any failures or invalids. */
	अगर (status)
		*indirect_ptr = 0xDEADBEEF;
पूर्ण

अटल पूर्णांक qlge_get_serdes_regs(काष्ठा qlge_adapter *qdev,
				काष्ठा qlge_mpi_coredump *mpi_coredump)
अणु
	पूर्णांक status;
	bool xfi_direct_valid = false, xfi_indirect_valid = false;
	bool xaui_direct_valid = true, xaui_indirect_valid = true;
	अचिन्हित पूर्णांक i;
	u32 *direct_ptr, temp;
	u32 *indirect_ptr;

	/* The XAUI needs to be पढ़ो out per port */
	status = qlge_पढ़ो_other_func_serdes_reg(qdev,
						 XG_SERDES_XAUI_HSS_PCS_START,
						 &temp);
	अगर (status)
		temp = XG_SERDES_ADDR_XAUI_PWR_DOWN;

	अगर ((temp & XG_SERDES_ADDR_XAUI_PWR_DOWN) ==
				XG_SERDES_ADDR_XAUI_PWR_DOWN)
		xaui_indirect_valid = false;

	status = qlge_पढ़ो_serdes_reg(qdev, XG_SERDES_XAUI_HSS_PCS_START, &temp);

	अगर (status)
		temp = XG_SERDES_ADDR_XAUI_PWR_DOWN;

	अगर ((temp & XG_SERDES_ADDR_XAUI_PWR_DOWN) ==
				XG_SERDES_ADDR_XAUI_PWR_DOWN)
		xaui_direct_valid = false;

	/*
	 * XFI रेजिस्टर is shared so only need to पढ़ो one
	 * functions and then check the bits.
	 */
	status = qlge_पढ़ो_serdes_reg(qdev, XG_SERDES_ADDR_STS, &temp);
	अगर (status)
		temp = 0;

	अगर ((temp & XG_SERDES_ADDR_XFI1_PWR_UP) ==
					XG_SERDES_ADDR_XFI1_PWR_UP) अणु
		/* now see अगर i'm NIC 1 or NIC 2 */
		अगर (qdev->func & 1)
			/* I'm NIC 2, so the indirect (NIC1) xfi is up. */
			xfi_indirect_valid = true;
		अन्यथा
			xfi_direct_valid = true;
	पूर्ण
	अगर ((temp & XG_SERDES_ADDR_XFI2_PWR_UP) ==
					XG_SERDES_ADDR_XFI2_PWR_UP) अणु
		/* now see अगर i'm NIC 1 or NIC 2 */
		अगर (qdev->func & 1)
			/* I'm NIC 2, so the indirect (NIC1) xfi is up. */
			xfi_direct_valid = true;
		अन्यथा
			xfi_indirect_valid = true;
	पूर्ण

	/* Get XAUI_AN रेजिस्टर block. */
	अगर (qdev->func & 1) अणु
		/* Function 2 is direct	*/
		direct_ptr = mpi_coredump->serdes2_xaui_an;
		indirect_ptr = mpi_coredump->serdes_xaui_an;
	पूर्ण अन्यथा अणु
		/* Function 1 is direct	*/
		direct_ptr = mpi_coredump->serdes_xaui_an;
		indirect_ptr = mpi_coredump->serdes2_xaui_an;
	पूर्ण

	क्रम (i = 0; i <= 0x000000034; i += 4, direct_ptr++, indirect_ptr++)
		qlge_get_both_serdes(qdev, i, direct_ptr, indirect_ptr,
				     xaui_direct_valid, xaui_indirect_valid);

	/* Get XAUI_HSS_PCS रेजिस्टर block. */
	अगर (qdev->func & 1) अणु
		direct_ptr =
			mpi_coredump->serdes2_xaui_hss_pcs;
		indirect_ptr =
			mpi_coredump->serdes_xaui_hss_pcs;
	पूर्ण अन्यथा अणु
		direct_ptr =
			mpi_coredump->serdes_xaui_hss_pcs;
		indirect_ptr =
			mpi_coredump->serdes2_xaui_hss_pcs;
	पूर्ण

	क्रम (i = 0x800; i <= 0x880; i += 4, direct_ptr++, indirect_ptr++)
		qlge_get_both_serdes(qdev, i, direct_ptr, indirect_ptr,
				     xaui_direct_valid, xaui_indirect_valid);

	/* Get XAUI_XFI_AN रेजिस्टर block. */
	अगर (qdev->func & 1) अणु
		direct_ptr = mpi_coredump->serdes2_xfi_an;
		indirect_ptr = mpi_coredump->serdes_xfi_an;
	पूर्ण अन्यथा अणु
		direct_ptr = mpi_coredump->serdes_xfi_an;
		indirect_ptr = mpi_coredump->serdes2_xfi_an;
	पूर्ण

	क्रम (i = 0x1000; i <= 0x1034; i += 4, direct_ptr++, indirect_ptr++)
		qlge_get_both_serdes(qdev, i, direct_ptr, indirect_ptr,
				     xfi_direct_valid, xfi_indirect_valid);

	/* Get XAUI_XFI_TRAIN रेजिस्टर block. */
	अगर (qdev->func & 1) अणु
		direct_ptr = mpi_coredump->serdes2_xfi_train;
		indirect_ptr =
			mpi_coredump->serdes_xfi_train;
	पूर्ण अन्यथा अणु
		direct_ptr = mpi_coredump->serdes_xfi_train;
		indirect_ptr =
			mpi_coredump->serdes2_xfi_train;
	पूर्ण

	क्रम (i = 0x1050; i <= 0x107c; i += 4, direct_ptr++, indirect_ptr++)
		qlge_get_both_serdes(qdev, i, direct_ptr, indirect_ptr,
				     xfi_direct_valid, xfi_indirect_valid);

	/* Get XAUI_XFI_HSS_PCS रेजिस्टर block. */
	अगर (qdev->func & 1) अणु
		direct_ptr =
			mpi_coredump->serdes2_xfi_hss_pcs;
		indirect_ptr =
			mpi_coredump->serdes_xfi_hss_pcs;
	पूर्ण अन्यथा अणु
		direct_ptr =
			mpi_coredump->serdes_xfi_hss_pcs;
		indirect_ptr =
			mpi_coredump->serdes2_xfi_hss_pcs;
	पूर्ण

	क्रम (i = 0x1800; i <= 0x1838; i += 4, direct_ptr++, indirect_ptr++)
		qlge_get_both_serdes(qdev, i, direct_ptr, indirect_ptr,
				     xfi_direct_valid, xfi_indirect_valid);

	/* Get XAUI_XFI_HSS_TX रेजिस्टर block. */
	अगर (qdev->func & 1) अणु
		direct_ptr =
			mpi_coredump->serdes2_xfi_hss_tx;
		indirect_ptr =
			mpi_coredump->serdes_xfi_hss_tx;
	पूर्ण अन्यथा अणु
		direct_ptr = mpi_coredump->serdes_xfi_hss_tx;
		indirect_ptr =
			mpi_coredump->serdes2_xfi_hss_tx;
	पूर्ण
	क्रम (i = 0x1c00; i <= 0x1c1f; i++, direct_ptr++, indirect_ptr++)
		qlge_get_both_serdes(qdev, i, direct_ptr, indirect_ptr,
				     xfi_direct_valid, xfi_indirect_valid);

	/* Get XAUI_XFI_HSS_RX रेजिस्टर block. */
	अगर (qdev->func & 1) अणु
		direct_ptr =
			mpi_coredump->serdes2_xfi_hss_rx;
		indirect_ptr =
			mpi_coredump->serdes_xfi_hss_rx;
	पूर्ण अन्यथा अणु
		direct_ptr = mpi_coredump->serdes_xfi_hss_rx;
		indirect_ptr =
			mpi_coredump->serdes2_xfi_hss_rx;
	पूर्ण

	क्रम (i = 0x1c40; i <= 0x1c5f; i++, direct_ptr++, indirect_ptr++)
		qlge_get_both_serdes(qdev, i, direct_ptr, indirect_ptr,
				     xfi_direct_valid, xfi_indirect_valid);

	/* Get XAUI_XFI_HSS_PLL रेजिस्टर block. */
	अगर (qdev->func & 1) अणु
		direct_ptr =
			mpi_coredump->serdes2_xfi_hss_pll;
		indirect_ptr =
			mpi_coredump->serdes_xfi_hss_pll;
	पूर्ण अन्यथा अणु
		direct_ptr =
			mpi_coredump->serdes_xfi_hss_pll;
		indirect_ptr =
			mpi_coredump->serdes2_xfi_hss_pll;
	पूर्ण
	क्रम (i = 0x1e00; i <= 0x1e1f; i++, direct_ptr++, indirect_ptr++)
		qlge_get_both_serdes(qdev, i, direct_ptr, indirect_ptr,
				     xfi_direct_valid, xfi_indirect_valid);
	वापस 0;
पूर्ण

अटल पूर्णांक qlge_पढ़ो_other_func_xgmac_reg(काष्ठा qlge_adapter *qdev, u32 reg,
					  u32 *data)
अणु
	पूर्णांक status = 0;

	/* रुको क्रम reg to come पढ़ोy */
	status = qlge_रुको_other_func_reg_rdy(qdev, XGMAC_ADDR / 4,
					      XGMAC_ADDR_RDY, XGMAC_ADDR_XME);
	अगर (status)
		जाओ निकास;

	/* set up क्रम reg पढ़ो */
	qlge_ग_लिखो_other_func_reg(qdev, XGMAC_ADDR / 4, reg | XGMAC_ADDR_R);

	/* रुको क्रम reg to come पढ़ोy */
	status = qlge_रुको_other_func_reg_rdy(qdev, XGMAC_ADDR / 4,
					      XGMAC_ADDR_RDY, XGMAC_ADDR_XME);
	अगर (status)
		जाओ निकास;

	/* get the data */
	*data = qlge_पढ़ो_other_func_reg(qdev, XGMAC_DATA / 4);
निकास:
	वापस status;
पूर्ण

/* Read the 400 xgmac control/statistics रेजिस्टरs
 * skipping unused locations.
 */
अटल पूर्णांक qlge_get_xgmac_regs(काष्ठा qlge_adapter *qdev, u32 *buf,
			       अचिन्हित पूर्णांक other_function)
अणु
	पूर्णांक status = 0;
	पूर्णांक i;

	क्रम (i = PAUSE_SRC_LO; i < XGMAC_REGISTER_END; i += 4, buf++) अणु
		/* We're पढ़ोing 400 xgmac रेजिस्टरs, but we filter out
		 * several locations that are non-responsive to पढ़ोs.
		 */
		अगर ((i == 0x00000114) ||
		    (i == 0x00000118) ||
			(i == 0x0000013c) ||
			(i == 0x00000140) ||
			(i > 0x00000150 && i < 0x000001fc) ||
			(i > 0x00000278 && i < 0x000002a0) ||
			(i > 0x000002c0 && i < 0x000002cf) ||
			(i > 0x000002dc && i < 0x000002f0) ||
			(i > 0x000003c8 && i < 0x00000400) ||
			(i > 0x00000400 && i < 0x00000410) ||
			(i > 0x00000410 && i < 0x00000420) ||
			(i > 0x00000420 && i < 0x00000430) ||
			(i > 0x00000430 && i < 0x00000440) ||
			(i > 0x00000440 && i < 0x00000450) ||
			(i > 0x00000450 && i < 0x00000500) ||
			(i > 0x0000054c && i < 0x00000568) ||
			(i > 0x000005c8 && i < 0x00000600)) अणु
			अगर (other_function)
				status =
				qlge_पढ़ो_other_func_xgmac_reg(qdev, i, buf);
			अन्यथा
				status = qlge_पढ़ो_xgmac_reg(qdev, i, buf);

			अगर (status)
				*buf = 0xdeadbeef;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक qlge_get_ets_regs(काष्ठा qlge_adapter *qdev, u32 *buf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++, buf++) अणु
		qlge_ग_लिखो32(qdev, NIC_ETS, i << 29 | 0x08000000);
		*buf = qlge_पढ़ो32(qdev, NIC_ETS);
	पूर्ण

	क्रम (i = 0; i < 2; i++, buf++) अणु
		qlge_ग_लिखो32(qdev, CNA_ETS, i << 29 | 0x08000000);
		*buf = qlge_पढ़ो32(qdev, CNA_ETS);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qlge_get_पूर्णांकr_states(काष्ठा qlge_adapter *qdev, u32 *buf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < qdev->rx_ring_count; i++, buf++) अणु
		qlge_ग_लिखो32(qdev, INTR_EN,
			     qdev->पूर्णांकr_context[i].पूर्णांकr_पढ़ो_mask);
		*buf = qlge_पढ़ो32(qdev, INTR_EN);
	पूर्ण
पूर्ण

अटल पूर्णांक qlge_get_cam_entries(काष्ठा qlge_adapter *qdev, u32 *buf)
अणु
	पूर्णांक i, status;
	u32 value[3];

	status = qlge_sem_spinlock(qdev, SEM_MAC_ADDR_MASK);
	अगर (status)
		वापस status;

	क्रम (i = 0; i < 16; i++) अणु
		status = qlge_get_mac_addr_reg(qdev,
					       MAC_ADDR_TYPE_CAM_MAC, i, value);
		अगर (status) अणु
			netअगर_err(qdev, drv, qdev->ndev,
				  "Failed read of mac index register\n");
			जाओ err;
		पूर्ण
		*buf++ = value[0];	/* lower MAC address */
		*buf++ = value[1];	/* upper MAC address */
		*buf++ = value[2];	/* output */
	पूर्ण
	क्रम (i = 0; i < 32; i++) अणु
		status = qlge_get_mac_addr_reg(qdev, MAC_ADDR_TYPE_MULTI_MAC,
					       i, value);
		अगर (status) अणु
			netअगर_err(qdev, drv, qdev->ndev,
				  "Failed read of mac index register\n");
			जाओ err;
		पूर्ण
		*buf++ = value[0];	/* lower Mcast address */
		*buf++ = value[1];	/* upper Mcast address */
	पूर्ण
err:
	qlge_sem_unlock(qdev, SEM_MAC_ADDR_MASK);
	वापस status;
पूर्ण

अटल पूर्णांक qlge_get_routing_entries(काष्ठा qlge_adapter *qdev, u32 *buf)
अणु
	पूर्णांक status;
	u32 value, i;

	status = qlge_sem_spinlock(qdev, SEM_RT_IDX_MASK);
	अगर (status)
		वापस status;

	क्रम (i = 0; i < 16; i++) अणु
		status = qlge_get_routing_reg(qdev, i, &value);
		अगर (status) अणु
			netअगर_err(qdev, drv, qdev->ndev,
				  "Failed read of routing index register\n");
			जाओ err;
		पूर्ण अन्यथा अणु
			*buf++ = value;
		पूर्ण
	पूर्ण
err:
	qlge_sem_unlock(qdev, SEM_RT_IDX_MASK);
	वापस status;
पूर्ण

/* Read the MPI Processor shaकरोw रेजिस्टरs */
अटल पूर्णांक qlge_get_mpi_shaकरोw_regs(काष्ठा qlge_adapter *qdev, u32 *buf)
अणु
	u32 i;
	पूर्णांक status;

	क्रम (i = 0; i < MPI_CORE_SH_REGS_CNT; i++, buf++) अणु
		status = qlge_ग_लिखो_mpi_reg(qdev,
					    RISC_124,
					    (SHADOW_OFFSET | i << SHADOW_REG_SHIFT));
		अगर (status)
			जाओ end;
		status = qlge_पढ़ो_mpi_reg(qdev, RISC_127, buf);
		अगर (status)
			जाओ end;
	पूर्ण
end:
	वापस status;
पूर्ण

/* Read the MPI Processor core रेजिस्टरs */
अटल पूर्णांक qlge_get_mpi_regs(काष्ठा qlge_adapter *qdev, u32 *buf,
			     u32 offset, u32 count)
अणु
	पूर्णांक i, status = 0;

	क्रम (i = 0; i < count; i++, buf++) अणु
		status = qlge_पढ़ो_mpi_reg(qdev, offset + i, buf);
		अगर (status)
			वापस status;
	पूर्ण
	वापस status;
पूर्ण

/* Read the ASIC probe dump */
अटल अचिन्हित पूर्णांक *qlge_get_probe(काष्ठा qlge_adapter *qdev, u32 घड़ी,
				    u32 valid, u32 *buf)
अणु
	u32 module, mux_sel, probe, lo_val, hi_val;

	क्रम (module = 0; module < PRB_MX_ADDR_MAX_MODS; module++) अणु
		अगर (!((valid >> module) & 1))
			जारी;
		क्रम (mux_sel = 0; mux_sel < PRB_MX_ADDR_MAX_MUX; mux_sel++) अणु
			probe = घड़ी
				| PRB_MX_ADDR_ARE
				| mux_sel
				| (module << PRB_MX_ADDR_MOD_SEL_SHIFT);
			qlge_ग_लिखो32(qdev, PRB_MX_ADDR, probe);
			lo_val = qlge_पढ़ो32(qdev, PRB_MX_DATA);
			अगर (mux_sel == 0) अणु
				*buf = probe;
				buf++;
			पूर्ण
			probe |= PRB_MX_ADDR_UP;
			qlge_ग_लिखो32(qdev, PRB_MX_ADDR, probe);
			hi_val = qlge_पढ़ो32(qdev, PRB_MX_DATA);
			*buf = lo_val;
			buf++;
			*buf = hi_val;
			buf++;
		पूर्ण
	पूर्ण
	वापस buf;
पूर्ण

अटल पूर्णांक qlge_get_probe_dump(काष्ठा qlge_adapter *qdev, अचिन्हित पूर्णांक *buf)
अणु
	/* First we have to enable the probe mux */
	qlge_ग_लिखो_mpi_reg(qdev, MPI_TEST_FUNC_PRB_CTL, MPI_TEST_FUNC_PRB_EN);
	buf = qlge_get_probe(qdev, PRB_MX_ADDR_SYS_CLOCK,
			     PRB_MX_ADDR_VALID_SYS_MOD, buf);
	buf = qlge_get_probe(qdev, PRB_MX_ADDR_PCI_CLOCK,
			     PRB_MX_ADDR_VALID_PCI_MOD, buf);
	buf = qlge_get_probe(qdev, PRB_MX_ADDR_XGM_CLOCK,
			     PRB_MX_ADDR_VALID_XGM_MOD, buf);
	buf = qlge_get_probe(qdev, PRB_MX_ADDR_FC_CLOCK,
			     PRB_MX_ADDR_VALID_FC_MOD, buf);
	वापस 0;
पूर्ण

/* Read out the routing index रेजिस्टरs */
अटल पूर्णांक qlge_get_routing_index_रेजिस्टरs(काष्ठा qlge_adapter *qdev, u32 *buf)
अणु
	पूर्णांक status;
	u32 type, index, index_max;
	u32 result_index;
	u32 result_data;
	u32 val;

	status = qlge_sem_spinlock(qdev, SEM_RT_IDX_MASK);
	अगर (status)
		वापस status;

	क्रम (type = 0; type < 4; type++) अणु
		अगर (type < 2)
			index_max = 8;
		अन्यथा
			index_max = 16;
		क्रम (index = 0; index < index_max; index++) अणु
			val = RT_IDX_RS
				| (type << RT_IDX_TYPE_SHIFT)
				| (index << RT_IDX_IDX_SHIFT);
			qlge_ग_लिखो32(qdev, RT_IDX, val);
			result_index = 0;
			जबतक ((result_index & RT_IDX_MR) == 0)
				result_index = qlge_पढ़ो32(qdev, RT_IDX);
			result_data = qlge_पढ़ो32(qdev, RT_DATA);
			*buf = type;
			buf++;
			*buf = index;
			buf++;
			*buf = result_index;
			buf++;
			*buf = result_data;
			buf++;
		पूर्ण
	पूर्ण
	qlge_sem_unlock(qdev, SEM_RT_IDX_MASK);
	वापस status;
पूर्ण

/* Read out the MAC protocol रेजिस्टरs */
अटल व्योम qlge_get_mac_protocol_रेजिस्टरs(काष्ठा qlge_adapter *qdev, u32 *buf)
अणु
	u32 result_index, result_data;
	u32 type;
	u32 index;
	u32 offset;
	u32 val;
	u32 initial_val = MAC_ADDR_RS;
	u32 max_index;
	u32 max_offset;

	क्रम (type = 0; type < MAC_ADDR_TYPE_COUNT; type++) अणु
		चयन (type) अणु
		हाल 0: /* CAM */
			initial_val |= MAC_ADDR_ADR;
			max_index = MAC_ADDR_MAX_CAM_ENTRIES;
			max_offset = MAC_ADDR_MAX_CAM_WCOUNT;
			अवरोध;
		हाल 1: /* Multicast MAC Address */
			max_index = MAC_ADDR_MAX_CAM_WCOUNT;
			max_offset = MAC_ADDR_MAX_CAM_WCOUNT;
			अवरोध;
		हाल 2: /* VLAN filter mask */
		हाल 3: /* MC filter mask */
			max_index = MAC_ADDR_MAX_CAM_WCOUNT;
			max_offset = MAC_ADDR_MAX_CAM_WCOUNT;
			अवरोध;
		हाल 4: /* FC MAC addresses */
			max_index = MAC_ADDR_MAX_FC_MAC_ENTRIES;
			max_offset = MAC_ADDR_MAX_FC_MAC_WCOUNT;
			अवरोध;
		हाल 5: /* Mgmt MAC addresses */
			max_index = MAC_ADDR_MAX_MGMT_MAC_ENTRIES;
			max_offset = MAC_ADDR_MAX_MGMT_MAC_WCOUNT;
			अवरोध;
		हाल 6: /* Mgmt VLAN addresses */
			max_index = MAC_ADDR_MAX_MGMT_VLAN_ENTRIES;
			max_offset = MAC_ADDR_MAX_MGMT_VLAN_WCOUNT;
			अवरोध;
		हाल 7: /* Mgmt IPv4 address */
			max_index = MAC_ADDR_MAX_MGMT_V4_ENTRIES;
			max_offset = MAC_ADDR_MAX_MGMT_V4_WCOUNT;
			अवरोध;
		हाल 8: /* Mgmt IPv6 address */
			max_index = MAC_ADDR_MAX_MGMT_V6_ENTRIES;
			max_offset = MAC_ADDR_MAX_MGMT_V6_WCOUNT;
			अवरोध;
		हाल 9: /* Mgmt TCP/UDP Dest port */
			max_index = MAC_ADDR_MAX_MGMT_TU_DP_ENTRIES;
			max_offset = MAC_ADDR_MAX_MGMT_TU_DP_WCOUNT;
			अवरोध;
		शेष:
			netdev_err(qdev->ndev, "Bad type!!! 0x%08x\n", type);
			max_index = 0;
			max_offset = 0;
			अवरोध;
		पूर्ण
		क्रम (index = 0; index < max_index; index++) अणु
			क्रम (offset = 0; offset < max_offset; offset++) अणु
				val = initial_val
					| (type << MAC_ADDR_TYPE_SHIFT)
					| (index << MAC_ADDR_IDX_SHIFT)
					| (offset);
				qlge_ग_लिखो32(qdev, MAC_ADDR_IDX, val);
				result_index = 0;
				जबतक ((result_index & MAC_ADDR_MR) == 0) अणु
					result_index = qlge_पढ़ो32(qdev,
								   MAC_ADDR_IDX);
				पूर्ण
				result_data = qlge_पढ़ो32(qdev, MAC_ADDR_DATA);
				*buf = result_index;
				buf++;
				*buf = result_data;
				buf++;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qlge_get_sem_रेजिस्टरs(काष्ठा qlge_adapter *qdev, u32 *buf)
अणु
	u32 func_num, reg, reg_val;
	पूर्णांक status;

	क्रम (func_num = 0; func_num < MAX_SEMAPHORE_FUNCTIONS ; func_num++) अणु
		reg = MPI_NIC_REG_BLOCK
			| (func_num << MPI_NIC_FUNCTION_SHIFT)
			| (SEM / 4);
		status = qlge_पढ़ो_mpi_reg(qdev, reg, &reg_val);
		*buf = reg_val;
		/* अगर the पढ़ो failed then dead fill the element. */
		अगर (!status)
			*buf = 0xdeadbeef;
		buf++;
	पूर्ण
पूर्ण

/* Create a coredump segment header */
अटल व्योम qlge_build_coredump_seg_header(काष्ठा mpi_coredump_segment_header *seg_hdr,
					   u32 seg_number, u32 seg_size, u8 *desc)
अणु
	स_रखो(seg_hdr, 0, माप(काष्ठा mpi_coredump_segment_header));
	seg_hdr->cookie = MPI_COREDUMP_COOKIE;
	seg_hdr->seg_num = seg_number;
	seg_hdr->seg_size = seg_size;
	म_नकलन(seg_hdr->description, desc, (माप(seg_hdr->description)) - 1);
पूर्ण

/*
 * This function should be called when a coredump / probedump
 * is to be extracted from the HBA. It is assumed there is a
 * qdev काष्ठाure that contains the base address of the रेजिस्टर
 * space क्रम this function as well as a coredump काष्ठाure that
 * will contain the dump.
 */
पूर्णांक qlge_core_dump(काष्ठा qlge_adapter *qdev, काष्ठा qlge_mpi_coredump *mpi_coredump)
अणु
	पूर्णांक status;
	पूर्णांक i;

	अगर (!mpi_coredump) अणु
		netअगर_err(qdev, drv, qdev->ndev, "No memory allocated\n");
		वापस -EINVAL;
	पूर्ण

	/* Try to get the spinlock, but करोnt worry अगर
	 * it isn't available.  If the firmware died it
	 * might be holding the sem.
	 */
	qlge_sem_spinlock(qdev, SEM_PROC_REG_MASK);

	status = qlge_छोड़ो_mpi_risc(qdev);
	अगर (status) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Failed RISC pause. Status = 0x%.08x\n", status);
		जाओ err;
	पूर्ण

	/* Insert the global header */
	स_रखो(&(mpi_coredump->mpi_global_header), 0,
	       माप(काष्ठा mpi_coredump_global_header));
	mpi_coredump->mpi_global_header.cookie = MPI_COREDUMP_COOKIE;
	mpi_coredump->mpi_global_header.header_size =
		माप(काष्ठा mpi_coredump_global_header);
	mpi_coredump->mpi_global_header.image_size =
		माप(काष्ठा qlge_mpi_coredump);
	म_नकलन(mpi_coredump->mpi_global_header.id_string, "MPI Coredump",
		माप(mpi_coredump->mpi_global_header.id_string));

	/* Get generic NIC reg dump */
	qlge_build_coredump_seg_header(&mpi_coredump->nic_regs_seg_hdr,
				       NIC1_CONTROL_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->nic_regs), "NIC1 Registers");

	qlge_build_coredump_seg_header(&mpi_coredump->nic2_regs_seg_hdr,
				       NIC2_CONTROL_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->nic2_regs), "NIC2 Registers");

	/* Get XGMac रेजिस्टरs. (Segment 18, Rev C. step 21) */
	qlge_build_coredump_seg_header(&mpi_coredump->xgmac1_seg_hdr,
				       NIC1_XGMAC_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->xgmac1), "NIC1 XGMac Registers");

	qlge_build_coredump_seg_header(&mpi_coredump->xgmac2_seg_hdr,
				       NIC2_XGMAC_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->xgmac2), "NIC2 XGMac Registers");

	अगर (qdev->func & 1) अणु
		/* Odd means our function is NIC 2 */
		क्रम (i = 0; i < NIC_REGS_DUMP_WORD_COUNT; i++)
			mpi_coredump->nic2_regs[i] =
				qlge_पढ़ो32(qdev, i * माप(u32));

		क्रम (i = 0; i < NIC_REGS_DUMP_WORD_COUNT; i++)
			mpi_coredump->nic_regs[i] =
				qlge_पढ़ो_other_func_reg(qdev, (i * माप(u32)) / 4);

		qlge_get_xgmac_regs(qdev, &mpi_coredump->xgmac2[0], 0);
		qlge_get_xgmac_regs(qdev, &mpi_coredump->xgmac1[0], 1);
	पूर्ण अन्यथा अणु
		/* Even means our function is NIC 1 */
		क्रम (i = 0; i < NIC_REGS_DUMP_WORD_COUNT; i++)
			mpi_coredump->nic_regs[i] =
				qlge_पढ़ो32(qdev, i * माप(u32));
		क्रम (i = 0; i < NIC_REGS_DUMP_WORD_COUNT; i++)
			mpi_coredump->nic2_regs[i] =
				qlge_पढ़ो_other_func_reg(qdev, (i * माप(u32)) / 4);

		qlge_get_xgmac_regs(qdev, &mpi_coredump->xgmac1[0], 0);
		qlge_get_xgmac_regs(qdev, &mpi_coredump->xgmac2[0], 1);
	पूर्ण

	/* Rev C. Step 20a */
	qlge_build_coredump_seg_header(&mpi_coredump->xaui_an_hdr,
				       XAUI_AN_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->serdes_xaui_an),
				       "XAUI AN Registers");

	/* Rev C. Step 20b */
	qlge_build_coredump_seg_header(&mpi_coredump->xaui_hss_pcs_hdr,
				       XAUI_HSS_PCS_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->serdes_xaui_hss_pcs),
				       "XAUI HSS PCS Registers");

	qlge_build_coredump_seg_header(&mpi_coredump->xfi_an_hdr, XFI_AN_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->serdes_xfi_an),
				       "XFI AN Registers");

	qlge_build_coredump_seg_header(&mpi_coredump->xfi_train_hdr,
				       XFI_TRAIN_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->serdes_xfi_train),
				       "XFI TRAIN Registers");

	qlge_build_coredump_seg_header(&mpi_coredump->xfi_hss_pcs_hdr,
				       XFI_HSS_PCS_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->serdes_xfi_hss_pcs),
				       "XFI HSS PCS Registers");

	qlge_build_coredump_seg_header(&mpi_coredump->xfi_hss_tx_hdr,
				       XFI_HSS_TX_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->serdes_xfi_hss_tx),
				       "XFI HSS TX Registers");

	qlge_build_coredump_seg_header(&mpi_coredump->xfi_hss_rx_hdr,
				       XFI_HSS_RX_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->serdes_xfi_hss_rx),
				       "XFI HSS RX Registers");

	qlge_build_coredump_seg_header(&mpi_coredump->xfi_hss_pll_hdr,
				       XFI_HSS_PLL_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->serdes_xfi_hss_pll),
				       "XFI HSS PLL Registers");

	qlge_build_coredump_seg_header(&mpi_coredump->xaui2_an_hdr,
				       XAUI2_AN_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->serdes2_xaui_an),
				       "XAUI2 AN Registers");

	qlge_build_coredump_seg_header(&mpi_coredump->xaui2_hss_pcs_hdr,
				       XAUI2_HSS_PCS_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->serdes2_xaui_hss_pcs),
				       "XAUI2 HSS PCS Registers");

	qlge_build_coredump_seg_header(&mpi_coredump->xfi2_an_hdr,
				       XFI2_AN_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->serdes2_xfi_an),
				       "XFI2 AN Registers");

	qlge_build_coredump_seg_header(&mpi_coredump->xfi2_train_hdr,
				       XFI2_TRAIN_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->serdes2_xfi_train),
				       "XFI2 TRAIN Registers");

	qlge_build_coredump_seg_header(&mpi_coredump->xfi2_hss_pcs_hdr,
				       XFI2_HSS_PCS_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->serdes2_xfi_hss_pcs),
				       "XFI2 HSS PCS Registers");

	qlge_build_coredump_seg_header(&mpi_coredump->xfi2_hss_tx_hdr,
				       XFI2_HSS_TX_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->serdes2_xfi_hss_tx),
				       "XFI2 HSS TX Registers");

	qlge_build_coredump_seg_header(&mpi_coredump->xfi2_hss_rx_hdr,
				       XFI2_HSS_RX_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->serdes2_xfi_hss_rx),
				       "XFI2 HSS RX Registers");

	qlge_build_coredump_seg_header(&mpi_coredump->xfi2_hss_pll_hdr,
				       XFI2_HSS_PLL_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->serdes2_xfi_hss_pll),
				       "XFI2 HSS PLL Registers");

	status = qlge_get_serdes_regs(qdev, mpi_coredump);
	अगर (status) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Failed Dump of Serdes Registers. Status = 0x%.08x\n",
			  status);
		जाओ err;
	पूर्ण

	qlge_build_coredump_seg_header(&mpi_coredump->core_regs_seg_hdr,
				       CORE_SEG_NUM,
				       माप(mpi_coredump->core_regs_seg_hdr) +
				       माप(mpi_coredump->mpi_core_regs) +
				       माप(mpi_coredump->mpi_core_sh_regs),
				       "Core Registers");

	/* Get the MPI Core Registers */
	status = qlge_get_mpi_regs(qdev, &mpi_coredump->mpi_core_regs[0],
				   MPI_CORE_REGS_ADDR, MPI_CORE_REGS_CNT);
	अगर (status)
		जाओ err;
	/* Get the 16 MPI shaकरोw रेजिस्टरs */
	status = qlge_get_mpi_shaकरोw_regs(qdev,
					  &mpi_coredump->mpi_core_sh_regs[0]);
	अगर (status)
		जाओ err;

	/* Get the Test Logic Registers */
	qlge_build_coredump_seg_header(&mpi_coredump->test_logic_regs_seg_hdr,
				       TEST_LOGIC_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->test_logic_regs),
				       "Test Logic Regs");
	status = qlge_get_mpi_regs(qdev, &mpi_coredump->test_logic_regs[0],
				   TEST_REGS_ADDR, TEST_REGS_CNT);
	अगर (status)
		जाओ err;

	/* Get the RMII Registers */
	qlge_build_coredump_seg_header(&mpi_coredump->rmii_regs_seg_hdr,
				       RMII_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->rmii_regs),
				       "RMII Registers");
	status = qlge_get_mpi_regs(qdev, &mpi_coredump->rmii_regs[0],
				   RMII_REGS_ADDR, RMII_REGS_CNT);
	अगर (status)
		जाओ err;

	/* Get the FCMAC1 Registers */
	qlge_build_coredump_seg_header(&mpi_coredump->fcmac1_regs_seg_hdr,
				       FCMAC1_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->fcmac1_regs),
				       "FCMAC1 Registers");
	status = qlge_get_mpi_regs(qdev, &mpi_coredump->fcmac1_regs[0],
				   FCMAC1_REGS_ADDR, FCMAC_REGS_CNT);
	अगर (status)
		जाओ err;

	/* Get the FCMAC2 Registers */

	qlge_build_coredump_seg_header(&mpi_coredump->fcmac2_regs_seg_hdr,
				       FCMAC2_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->fcmac2_regs),
				       "FCMAC2 Registers");

	status = qlge_get_mpi_regs(qdev, &mpi_coredump->fcmac2_regs[0],
				   FCMAC2_REGS_ADDR, FCMAC_REGS_CNT);
	अगर (status)
		जाओ err;

	/* Get the FC1 MBX Registers */
	qlge_build_coredump_seg_header(&mpi_coredump->fc1_mbx_regs_seg_hdr,
				       FC1_MBOX_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->fc1_mbx_regs),
				       "FC1 MBox Regs");
	status = qlge_get_mpi_regs(qdev, &mpi_coredump->fc1_mbx_regs[0],
				   FC1_MBX_REGS_ADDR, FC_MBX_REGS_CNT);
	अगर (status)
		जाओ err;

	/* Get the IDE Registers */
	qlge_build_coredump_seg_header(&mpi_coredump->ide_regs_seg_hdr,
				       IDE_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->ide_regs),
				       "IDE Registers");
	status = qlge_get_mpi_regs(qdev, &mpi_coredump->ide_regs[0],
				   IDE_REGS_ADDR, IDE_REGS_CNT);
	अगर (status)
		जाओ err;

	/* Get the NIC1 MBX Registers */
	qlge_build_coredump_seg_header(&mpi_coredump->nic1_mbx_regs_seg_hdr,
				       NIC1_MBOX_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->nic1_mbx_regs),
				       "NIC1 MBox Regs");
	status = qlge_get_mpi_regs(qdev, &mpi_coredump->nic1_mbx_regs[0],
				   NIC1_MBX_REGS_ADDR, NIC_MBX_REGS_CNT);
	अगर (status)
		जाओ err;

	/* Get the SMBus Registers */
	qlge_build_coredump_seg_header(&mpi_coredump->smbus_regs_seg_hdr,
				       SMBUS_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->smbus_regs),
				       "SMBus Registers");
	status = qlge_get_mpi_regs(qdev, &mpi_coredump->smbus_regs[0],
				   SMBUS_REGS_ADDR, SMBUS_REGS_CNT);
	अगर (status)
		जाओ err;

	/* Get the FC2 MBX Registers */
	qlge_build_coredump_seg_header(&mpi_coredump->fc2_mbx_regs_seg_hdr,
				       FC2_MBOX_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->fc2_mbx_regs),
				       "FC2 MBox Regs");
	status = qlge_get_mpi_regs(qdev, &mpi_coredump->fc2_mbx_regs[0],
				   FC2_MBX_REGS_ADDR, FC_MBX_REGS_CNT);
	अगर (status)
		जाओ err;

	/* Get the NIC2 MBX Registers */
	qlge_build_coredump_seg_header(&mpi_coredump->nic2_mbx_regs_seg_hdr,
				       NIC2_MBOX_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->nic2_mbx_regs),
				       "NIC2 MBox Regs");
	status = qlge_get_mpi_regs(qdev, &mpi_coredump->nic2_mbx_regs[0],
				   NIC2_MBX_REGS_ADDR, NIC_MBX_REGS_CNT);
	अगर (status)
		जाओ err;

	/* Get the I2C Registers */
	qlge_build_coredump_seg_header(&mpi_coredump->i2c_regs_seg_hdr,
				       I2C_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->i2c_regs),
				       "I2C Registers");
	status = qlge_get_mpi_regs(qdev, &mpi_coredump->i2c_regs[0],
				   I2C_REGS_ADDR, I2C_REGS_CNT);
	अगर (status)
		जाओ err;

	/* Get the MEMC Registers */
	qlge_build_coredump_seg_header(&mpi_coredump->memc_regs_seg_hdr,
				       MEMC_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->memc_regs),
				       "MEMC Registers");
	status = qlge_get_mpi_regs(qdev, &mpi_coredump->memc_regs[0],
				   MEMC_REGS_ADDR, MEMC_REGS_CNT);
	अगर (status)
		जाओ err;

	/* Get the PBus Registers */
	qlge_build_coredump_seg_header(&mpi_coredump->pbus_regs_seg_hdr,
				       PBUS_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->pbus_regs),
				       "PBUS Registers");
	status = qlge_get_mpi_regs(qdev, &mpi_coredump->pbus_regs[0],
				   PBUS_REGS_ADDR, PBUS_REGS_CNT);
	अगर (status)
		जाओ err;

	/* Get the MDE Registers */
	qlge_build_coredump_seg_header(&mpi_coredump->mde_regs_seg_hdr,
				       MDE_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->mde_regs),
				       "MDE Registers");
	status = qlge_get_mpi_regs(qdev, &mpi_coredump->mde_regs[0],
				   MDE_REGS_ADDR, MDE_REGS_CNT);
	अगर (status)
		जाओ err;

	qlge_build_coredump_seg_header(&mpi_coredump->misc_nic_seg_hdr,
				       MISC_NIC_INFO_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->misc_nic_info),
				       "MISC NIC INFO");
	mpi_coredump->misc_nic_info.rx_ring_count = qdev->rx_ring_count;
	mpi_coredump->misc_nic_info.tx_ring_count = qdev->tx_ring_count;
	mpi_coredump->misc_nic_info.पूर्णांकr_count = qdev->पूर्णांकr_count;
	mpi_coredump->misc_nic_info.function = qdev->func;

	/* Segment 31 */
	/* Get indexed रेजिस्टर values. */
	qlge_build_coredump_seg_header(&mpi_coredump->पूर्णांकr_states_seg_hdr,
				       INTR_STATES_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->पूर्णांकr_states),
				       "INTR States");
	qlge_get_पूर्णांकr_states(qdev, &mpi_coredump->पूर्णांकr_states[0]);

	qlge_build_coredump_seg_header(&mpi_coredump->cam_entries_seg_hdr,
				       CAM_ENTRIES_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->cam_entries),
				       "CAM Entries");
	status = qlge_get_cam_entries(qdev, &mpi_coredump->cam_entries[0]);
	अगर (status)
		जाओ err;

	qlge_build_coredump_seg_header(&mpi_coredump->nic_routing_words_seg_hdr,
				       ROUTING_WORDS_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->nic_routing_words),
				       "Routing Words");
	status = qlge_get_routing_entries(qdev,
					  &mpi_coredump->nic_routing_words[0]);
	अगर (status)
		जाओ err;

	/* Segment 34 (Rev C. step 23) */
	qlge_build_coredump_seg_header(&mpi_coredump->ets_seg_hdr,
				       ETS_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->ets),
				       "ETS Registers");
	status = qlge_get_ets_regs(qdev, &mpi_coredump->ets[0]);
	अगर (status)
		जाओ err;

	qlge_build_coredump_seg_header(&mpi_coredump->probe_dump_seg_hdr,
				       PROBE_DUMP_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->probe_dump),
				       "Probe Dump");
	qlge_get_probe_dump(qdev, &mpi_coredump->probe_dump[0]);

	qlge_build_coredump_seg_header(&mpi_coredump->routing_reg_seg_hdr,
				       ROUTING_INDEX_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->routing_regs),
				       "Routing Regs");
	status = qlge_get_routing_index_रेजिस्टरs(qdev,
						  &mpi_coredump->routing_regs[0]);
	अगर (status)
		जाओ err;

	qlge_build_coredump_seg_header(&mpi_coredump->mac_prot_reg_seg_hdr,
				       MAC_PROTOCOL_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->mac_prot_regs),
				       "MAC Prot Regs");
	qlge_get_mac_protocol_रेजिस्टरs(qdev, &mpi_coredump->mac_prot_regs[0]);

	/* Get the semaphore रेजिस्टरs क्रम all 5 functions */
	qlge_build_coredump_seg_header(&mpi_coredump->sem_regs_seg_hdr,
				       SEM_REGS_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header) +
				       माप(mpi_coredump->sem_regs),	"Sem Registers");

	qlge_get_sem_रेजिस्टरs(qdev, &mpi_coredump->sem_regs[0]);

	/* Prevent the mpi restarting जबतक we dump the memory.*/
	qlge_ग_लिखो_mpi_reg(qdev, MPI_TEST_FUNC_RST_STS, MPI_TEST_FUNC_RST_FRC);

	/* clear the छोड़ो */
	status = qlge_unछोड़ो_mpi_risc(qdev);
	अगर (status) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Failed RISC unpause. Status = 0x%.08x\n", status);
		जाओ err;
	पूर्ण

	/* Reset the RISC so we can dump RAM */
	status = qlge_hard_reset_mpi_risc(qdev);
	अगर (status) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Failed RISC reset. Status = 0x%.08x\n", status);
		जाओ err;
	पूर्ण

	qlge_build_coredump_seg_header(&mpi_coredump->code_ram_seg_hdr,
				       WCS_RAM_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->code_ram),
				       "WCS RAM");
	status = qlge_dump_risc_ram_area(qdev, &mpi_coredump->code_ram[0],
					 CODE_RAM_ADDR, CODE_RAM_CNT);
	अगर (status) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Failed Dump of CODE RAM. Status = 0x%.08x\n",
			  status);
		जाओ err;
	पूर्ण

	/* Insert the segment header */
	qlge_build_coredump_seg_header(&mpi_coredump->memc_ram_seg_hdr,
				       MEMC_RAM_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->memc_ram),
				       "MEMC RAM");
	status = qlge_dump_risc_ram_area(qdev, &mpi_coredump->memc_ram[0],
					 MEMC_RAM_ADDR, MEMC_RAM_CNT);
	अगर (status) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Failed Dump of MEMC RAM. Status = 0x%.08x\n",
			  status);
		जाओ err;
	पूर्ण
err:
	qlge_sem_unlock(qdev, SEM_PROC_REG_MASK); /* करोes flush too */
	वापस status;
पूर्ण

अटल व्योम qlge_get_core_dump(काष्ठा qlge_adapter *qdev)
अणु
	अगर (!qlge_own_firmware(qdev)) अणु
		netअगर_err(qdev, drv, qdev->ndev, "Don't own firmware!\n");
		वापस;
	पूर्ण

	अगर (!netअगर_running(qdev->ndev)) अणु
		netअगर_err(qdev, अगरup, qdev->ndev,
			  "Force Coredump can only be done from interface that is up\n");
		वापस;
	पूर्ण
	qlge_queue_fw_error(qdev);
पूर्ण

अटल व्योम qlge_gen_reg_dump(काष्ठा qlge_adapter *qdev,
			      काष्ठा qlge_reg_dump *mpi_coredump)
अणु
	पूर्णांक i, status;

	स_रखो(&(mpi_coredump->mpi_global_header), 0,
	       माप(काष्ठा mpi_coredump_global_header));
	mpi_coredump->mpi_global_header.cookie = MPI_COREDUMP_COOKIE;
	mpi_coredump->mpi_global_header.header_size =
		माप(काष्ठा mpi_coredump_global_header);
	mpi_coredump->mpi_global_header.image_size =
		माप(काष्ठा qlge_reg_dump);
	म_नकलन(mpi_coredump->mpi_global_header.id_string, "MPI Coredump",
		माप(mpi_coredump->mpi_global_header.id_string));

	/* segment 16 */
	qlge_build_coredump_seg_header(&mpi_coredump->misc_nic_seg_hdr,
				       MISC_NIC_INFO_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->misc_nic_info),
				       "MISC NIC INFO");
	mpi_coredump->misc_nic_info.rx_ring_count = qdev->rx_ring_count;
	mpi_coredump->misc_nic_info.tx_ring_count = qdev->tx_ring_count;
	mpi_coredump->misc_nic_info.पूर्णांकr_count = qdev->पूर्णांकr_count;
	mpi_coredump->misc_nic_info.function = qdev->func;

	/* Segment 16, Rev C. Step 18 */
	qlge_build_coredump_seg_header(&mpi_coredump->nic_regs_seg_hdr,
				       NIC1_CONTROL_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->nic_regs),
				       "NIC Registers");
	/* Get generic reg dump */
	क्रम (i = 0; i < 64; i++)
		mpi_coredump->nic_regs[i] = qlge_पढ़ो32(qdev, i * माप(u32));

	/* Segment 31 */
	/* Get indexed रेजिस्टर values. */
	qlge_build_coredump_seg_header(&mpi_coredump->पूर्णांकr_states_seg_hdr,
				       INTR_STATES_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->पूर्णांकr_states),
				       "INTR States");
	qlge_get_पूर्णांकr_states(qdev, &mpi_coredump->पूर्णांकr_states[0]);

	qlge_build_coredump_seg_header(&mpi_coredump->cam_entries_seg_hdr,
				       CAM_ENTRIES_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->cam_entries),
				       "CAM Entries");
	status = qlge_get_cam_entries(qdev, &mpi_coredump->cam_entries[0]);
	अगर (status)
		वापस;

	qlge_build_coredump_seg_header(&mpi_coredump->nic_routing_words_seg_hdr,
				       ROUTING_WORDS_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->nic_routing_words),
				       "Routing Words");
	status = qlge_get_routing_entries(qdev,
					  &mpi_coredump->nic_routing_words[0]);
	अगर (status)
		वापस;

	/* Segment 34 (Rev C. step 23) */
	qlge_build_coredump_seg_header(&mpi_coredump->ets_seg_hdr,
				       ETS_SEG_NUM,
				       माप(काष्ठा mpi_coredump_segment_header)
				       + माप(mpi_coredump->ets),
				       "ETS Registers");
	status = qlge_get_ets_regs(qdev, &mpi_coredump->ets[0]);
	अगर (status)
		वापस;
पूर्ण

व्योम qlge_get_dump(काष्ठा qlge_adapter *qdev, व्योम *buff)
अणु
	/*
	 * If the dump has alपढ़ोy been taken and is stored
	 * in our पूर्णांकernal buffer and अगर क्रमce dump is set then
	 * just start the spool to dump it to the log file
	 * and also, take a snapshot of the general regs
	 * to the user's buffer or अन्यथा take complete dump
	 * to the user's buffer अगर क्रमce is not set.
	 */

	अगर (!test_bit(QL_FRC_COREDUMP, &qdev->flags)) अणु
		अगर (!qlge_core_dump(qdev, buff))
			qlge_soft_reset_mpi_risc(qdev);
		अन्यथा
			netअगर_err(qdev, drv, qdev->ndev, "coredump failed!\n");
	पूर्ण अन्यथा अणु
		qlge_gen_reg_dump(qdev, buff);
		qlge_get_core_dump(qdev);
	पूर्ण
पूर्ण
