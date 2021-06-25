<शैली गुरु>
/*
 * Platक्रमm inक्रमmation definitions क्रम the
 * universal Freescale Ethernet driver.
 *
 * Copyright (c) 2003 Intracom S.A. 
 *  by Pantelis Antoniou <panto@पूर्णांकracom.gr>
 *
 * 2005 (c) MontaVista Software, Inc. 
 * Vitaly Bordug <vbordug@ru.mvista.com>
 *
 * This file is licensed under the terms of the GNU General Public License 
 * version 2. This program is licensed "as is" without any warranty of any 
 * kind, whether express or implied.
 */

#अगर_अघोषित FS_ENET_PD_H
#घोषणा FS_ENET_PD_H

#समावेश <linux/clk.h>
#समावेश <linux/माला.स>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/अगर_ether.h>
#समावेश <यंत्र/types.h>

#घोषणा FS_ENET_NAME	"fs_enet"

क्रमागत fs_id अणु
	fsid_fec1,
	fsid_fec2,
	fsid_fcc1,
	fsid_fcc2,
	fsid_fcc3,
	fsid_scc1,
	fsid_scc2,
	fsid_scc3,
	fsid_scc4,
पूर्ण;

#घोषणा FS_MAX_INDEX	9

अटल अंतरभूत पूर्णांक fs_get_fec_index(क्रमागत fs_id id)
अणु
	अगर (id >= fsid_fec1 && id <= fsid_fec2)
		वापस id - fsid_fec1;
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक fs_get_fcc_index(क्रमागत fs_id id)
अणु
	अगर (id >= fsid_fcc1 && id <= fsid_fcc3)
		वापस id - fsid_fcc1;
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक fs_get_scc_index(क्रमागत fs_id id)
अणु
	अगर (id >= fsid_scc1 && id <= fsid_scc4)
		वापस id - fsid_scc1;
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक fs_fec_index2id(पूर्णांक index)
अणु
	पूर्णांक id = fsid_fec1 + index - 1;
	अगर (id >= fsid_fec1 && id <= fsid_fec2)
		वापस id;
	वापस FS_MAX_INDEX;
		पूर्ण

अटल अंतरभूत पूर्णांक fs_fcc_index2id(पूर्णांक index)
अणु
	पूर्णांक id = fsid_fcc1 + index - 1;
	अगर (id >= fsid_fcc1 && id <= fsid_fcc3)
		वापस id;
	वापस FS_MAX_INDEX;
पूर्ण

अटल अंतरभूत पूर्णांक fs_scc_index2id(पूर्णांक index)
अणु
	पूर्णांक id = fsid_scc1 + index - 1;
	अगर (id >= fsid_scc1 && id <= fsid_scc4)
		वापस id;
	वापस FS_MAX_INDEX;
पूर्ण

क्रमागत fs_mii_method अणु
	fsmii_fixed,
	fsmii_fec,
	fsmii_bitbang,
पूर्ण;

क्रमागत fs_ioport अणु
	fsiop_porta,
	fsiop_portb,
	fsiop_portc,
	fsiop_portd,
	fsiop_porte,
पूर्ण;

काष्ठा fs_mii_bit अणु
	u32 offset;
	u8 bit;
	u8 polarity;
पूर्ण;
काष्ठा fs_mii_bb_platक्रमm_info अणु
	काष्ठा fs_mii_bit 	mdio_dir;
	काष्ठा fs_mii_bit 	mdio_dat;
	काष्ठा fs_mii_bit	mdc_dat;
	पूर्णांक delay;	/* delay in us         */
	पूर्णांक irq[32]; 	/* irqs per phy's */
पूर्ण;

काष्ठा fs_platक्रमm_info अणु

	व्योम(*init_ioports)(काष्ठा fs_platक्रमm_info *);
	/* device specअगरic inक्रमmation */
	पूर्णांक fs_no;		/* controller index            */
	अक्षर fs_type[4];	/* controller type             */

	u32 cp_page;		/* CPM page */
	u32 cp_block;		/* CPM sblock */
	u32 cp_command;		/* CPM page/sblock/mcn */

	u32 clk_trx;		/* some stuff क्रम pins & mux configuration*/
	u32 clk_rx;
	u32 clk_tx;
	u32 clk_route;
	u32 clk_mask;

	u32 mem_offset;
	u32 dpram_offset;
	u32 fcc_regs_c;
	
	u32 device_flags;

	काष्ठा device_node *phy_node;
	स्थिर काष्ठा fs_mii_bus_info *bus_info;

	पूर्णांक rx_ring, tx_ring;	/* number of buffers on rx     */
	__u8 macaddr[ETH_ALEN];	/* mac address                 */
	पूर्णांक rx_copyअवरोध;	/* limit we copy small frames  */
	पूर्णांक napi_weight;	/* NAPI weight                 */

	पूर्णांक use_rmii;		/* use RMII mode 	       */
	पूर्णांक has_phy;            /* अगर the network is phy container as well...*/

	काष्ठा clk *clk_per;	/* 'per' घड़ी क्रम रेजिस्टर access */
पूर्ण;
काष्ठा fs_mii_fec_platक्रमm_info अणु
	u32 irq[32];
	u32 mii_speed;
पूर्ण;

अटल अंतरभूत पूर्णांक fs_get_id(काष्ठा fs_platक्रमm_info *fpi)
अणु
	अगर(म_माला(fpi->fs_type, "SCC"))
		वापस fs_scc_index2id(fpi->fs_no);
	अगर(म_माला(fpi->fs_type, "FCC"))
		वापस fs_fcc_index2id(fpi->fs_no);
	अगर(म_माला(fpi->fs_type, "FEC"))
		वापस fs_fec_index2id(fpi->fs_no);
	वापस fpi->fs_no;
पूर्ण

#पूर्ण_अगर
