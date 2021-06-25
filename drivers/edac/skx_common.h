<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common codes क्रम both the skx_edac driver and Intel 10nm server EDAC driver.
 * Originally split out from the skx_edac driver.
 *
 * Copyright (c) 2018, Intel Corporation.
 */

#अगर_अघोषित _SKX_COMM_EDAC_H
#घोषणा _SKX_COMM_EDAC_H

#घोषणा MSG_SIZE		1024

/*
 * Debug macros
 */
#घोषणा skx_prपूर्णांकk(level, fmt, arg...)			\
	edac_prपूर्णांकk(level, "skx", fmt, ##arg)

#घोषणा skx_mc_prपूर्णांकk(mci, level, fmt, arg...)		\
	edac_mc_chipset_prपूर्णांकk(mci, level, "skx", fmt, ##arg)

/*
 * Get a bit field at रेजिस्टर value <v>, from bit <lo> to bit <hi>
 */
#घोषणा GET_BITFIELD(v, lo, hi) \
	(((v) & GENMASK_ULL((hi), (lo))) >> (lo))

#घोषणा SKX_NUM_IMC		2	/* Memory controllers per socket */
#घोषणा SKX_NUM_CHANNELS	3	/* Channels per memory controller */
#घोषणा SKX_NUM_DIMMS		2	/* Max DIMMS per channel */

#घोषणा I10NM_NUM_IMC		4
#घोषणा I10NM_NUM_CHANNELS	2
#घोषणा I10NM_NUM_DIMMS		2

#घोषणा MAX(a, b)	((a) > (b) ? (a) : (b))
#घोषणा NUM_IMC		MAX(SKX_NUM_IMC, I10NM_NUM_IMC)
#घोषणा NUM_CHANNELS	MAX(SKX_NUM_CHANNELS, I10NM_NUM_CHANNELS)
#घोषणा NUM_DIMMS	MAX(SKX_NUM_DIMMS, I10NM_NUM_DIMMS)

#घोषणा IS_DIMM_PRESENT(r)		GET_BITFIELD(r, 15, 15)
#घोषणा IS_NVDIMM_PRESENT(r, i)		GET_BITFIELD(r, i, i)

/*
 * Each cpu socket contains some pci devices that provide global
 * inक्रमmation, and also some that are local to each of the two
 * memory controllers on the die.
 */
काष्ठा skx_dev अणु
	काष्ठा list_head list;
	u8 bus[4];
	पूर्णांक seg;
	काष्ठा pci_dev *sad_all;
	काष्ठा pci_dev *util_all;
	काष्ठा pci_dev *uracu; /* क्रम i10nm CPU */
	u32 mcroute;
	काष्ठा skx_imc अणु
		काष्ठा mem_ctl_info *mci;
		काष्ठा pci_dev *mdev; /* क्रम i10nm CPU */
		व्योम __iomem *mbase;  /* क्रम i10nm CPU */
		पूर्णांक chan_mmio_sz;     /* क्रम i10nm CPU */
		u8 mc;	/* प्रणाली wide mc# */
		u8 lmc;	/* socket relative mc# */
		u8 src_id, node_id;
		काष्ठा skx_channel अणु
			काष्ठा pci_dev	*cdev;
			काष्ठा pci_dev	*edev;
			काष्ठा skx_dimm अणु
				u8 बंद_pg;
				u8 bank_xor_enable;
				u8 fine_grain_bank;
				u8 rowbits;
				u8 colbits;
			पूर्ण dimms[NUM_DIMMS];
		पूर्ण chan[NUM_CHANNELS];
	पूर्ण imc[NUM_IMC];
पूर्ण;

काष्ठा skx_pvt अणु
	काष्ठा skx_imc	*imc;
पूर्ण;

क्रमागत type अणु
	SKX,
	I10NM,
	SPR
पूर्ण;

क्रमागत अणु
	INDEX_SOCKET,
	INDEX_MEMCTRL,
	INDEX_CHANNEL,
	INDEX_DIMM,
	INDEX_MAX
पूर्ण;

काष्ठा decoded_addr अणु
	काष्ठा skx_dev *dev;
	u64	addr;
	पूर्णांक	socket;
	पूर्णांक	imc;
	पूर्णांक	channel;
	u64	chan_addr;
	पूर्णांक	sktways;
	पूर्णांक	chanways;
	पूर्णांक	dimm;
	पूर्णांक	rank;
	पूर्णांक	channel_rank;
	u64	rank_address;
	पूर्णांक	row;
	पूर्णांक	column;
	पूर्णांक	bank_address;
	पूर्णांक	bank_group;
पूर्ण;

काष्ठा res_config अणु
	क्रमागत type type;
	/* Configuration agent device ID */
	अचिन्हित पूर्णांक decs_did;
	/* Default bus number configuration रेजिस्टर offset */
	पूर्णांक busno_cfg_offset;
	/* Per DDR channel memory-mapped I/O size */
	पूर्णांक ddr_chan_mmio_sz;
	bool support_ddr5;
पूर्ण;

प्रकार पूर्णांक (*get_dimm_config_f)(काष्ठा mem_ctl_info *mci,
				 काष्ठा res_config *cfg);
प्रकार bool (*skx_decode_f)(काष्ठा decoded_addr *res);
प्रकार व्योम (*skx_show_retry_log_f)(काष्ठा decoded_addr *res, अक्षर *msg, पूर्णांक len);

पूर्णांक __init skx_adxl_get(व्योम);
व्योम __निकास skx_adxl_put(व्योम);
व्योम skx_set_decode(skx_decode_f decode, skx_show_retry_log_f show_retry_log);

पूर्णांक skx_get_src_id(काष्ठा skx_dev *d, पूर्णांक off, u8 *id);
पूर्णांक skx_get_node_id(काष्ठा skx_dev *d, u8 *id);

पूर्णांक skx_get_all_bus_mappings(काष्ठा res_config *cfg, काष्ठा list_head **list);

पूर्णांक skx_get_hi_lo(अचिन्हित पूर्णांक did, पूर्णांक off[], u64 *tolm, u64 *tohm);

पूर्णांक skx_get_dimm_info(u32 mtr, u32 mcmtr, u32 amap, काष्ठा dimm_info *dimm,
		      काष्ठा skx_imc *imc, पूर्णांक chan, पूर्णांक dimmno,
		      काष्ठा res_config *cfg);

पूर्णांक skx_get_nvdimm_info(काष्ठा dimm_info *dimm, काष्ठा skx_imc *imc,
			पूर्णांक chan, पूर्णांक dimmno, स्थिर अक्षर *mod_str);

पूर्णांक skx_रेजिस्टर_mci(काष्ठा skx_imc *imc, काष्ठा pci_dev *pdev,
		     स्थिर अक्षर *ctl_name, स्थिर अक्षर *mod_str,
		     get_dimm_config_f get_dimm_config,
		     काष्ठा res_config *cfg);

पूर्णांक skx_mce_check_error(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
			व्योम *data);

व्योम skx_हटाओ(व्योम);

#पूर्ण_अगर /* _SKX_COMM_EDAC_H */
