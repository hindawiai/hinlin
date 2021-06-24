<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2015 MediaTek Inc.
 * Author:
 *  Zhigang.Wei <zhigang.wei@mediatek.com>
 *  Chunfeng.Yun <chunfeng.yun@mediatek.com>
 */

#अगर_अघोषित _XHCI_MTK_H_
#घोषणा _XHCI_MTK_H_

#समावेश <linux/clk.h>

#समावेश "xhci.h"

#घोषणा BULK_CLKS_NUM	5

/**
 * To simplअगरy scheduler algorithm, set a upper limit क्रम ESIT,
 * अगर a synchromous ep's ESIT is larger than @XHCI_MTK_MAX_ESIT,
 * round करोwn to the limit value, that means allocating more
 * bandwidth to it.
 */
#घोषणा XHCI_MTK_MAX_ESIT	64

/**
 * @ss_bit_map: used to aव्योम start split microframes overlay
 * @fs_bus_bw: array to keep track of bandwidth alपढ़ोy used क्रम FS
 * @ep_list: Endpoपूर्णांकs using this TT
 */
काष्ठा mu3h_sch_tt अणु
	DECLARE_BITMAP(ss_bit_map, XHCI_MTK_MAX_ESIT);
	u32 fs_bus_bw[XHCI_MTK_MAX_ESIT];
	काष्ठा list_head ep_list;
पूर्ण;

/**
 * काष्ठा mu3h_sch_bw_info: schedule inक्रमmation क्रम bandwidth करोमुख्य
 *
 * @bus_bw: array to keep track of bandwidth alपढ़ोy used at each uframes
 * @bw_ep_list: eps in the bandwidth करोमुख्य
 *
 * treat a HS root port as a bandwidth करोमुख्य, but treat a SS root port as
 * two bandwidth करोमुख्यs, one क्रम IN eps and another क्रम OUT eps.
 */
काष्ठा mu3h_sch_bw_info अणु
	u32 bus_bw[XHCI_MTK_MAX_ESIT];
	काष्ठा list_head bw_ep_list;
पूर्ण;

/**
 * काष्ठा mu3h_sch_ep_info: schedule inक्रमmation क्रम endpoपूर्णांक
 *
 * @esit: unit is 125us, equal to 2 << Interval field in ep-context
 * @num_budget_microframes: number of continuous uframes
 *		(@repeat==1) scheduled within the पूर्णांकerval
 * @bw_cost_per_microframe: bandwidth cost per microframe
 * @endpoपूर्णांक: linked पूर्णांकo bandwidth करोमुख्य which it beदीर्घs to
 * @tt_endpoपूर्णांक: linked पूर्णांकo mu3h_sch_tt's list which it beदीर्घs to
 * @sch_tt: mu3h_sch_tt linked पूर्णांकo
 * @ep_type: endpoपूर्णांक type
 * @maxpkt: max packet size of endpoपूर्णांक
 * @ep: address of usb_host_endpoपूर्णांक काष्ठा
 * @allocated: the bandwidth is aपढ़ोy allocated from bus_bw
 * @offset: which uframe of the पूर्णांकerval that transfer should be
 *		scheduled first समय within the पूर्णांकerval
 * @repeat: the समय gap between two uframes that transfers are
 *		scheduled within a पूर्णांकerval. in the simple algorithm, only
 *		assign 0 or 1 to it; 0 means using only one uframe in a
 *		पूर्णांकerval, and 1 means using @num_budget_microframes
 *		continuous uframes
 * @pkts: number of packets to be transferred in the scheduled uframes
 * @cs_count: number of CS that host will trigger
 * @burst_mode: burst mode क्रम scheduling. 0: normal burst mode,
 *		distribute the bMaxBurst+1 packets क्रम a single burst
 *		according to @pkts and @repeat, repeate the burst multiple
 *		बार; 1: distribute the (bMaxBurst+1)*(Mult+1) packets
 *		according to @pkts and @repeat. normal mode is used by
 *		शेष
 * @bw_budget_table: table to record bandwidth budget per microframe
 */
काष्ठा mu3h_sch_ep_info अणु
	u32 esit;
	u32 num_budget_microframes;
	u32 bw_cost_per_microframe;
	काष्ठा list_head endpoपूर्णांक;
	काष्ठा list_head tt_endpoपूर्णांक;
	काष्ठा mu3h_sch_tt *sch_tt;
	u32 ep_type;
	u32 maxpkt;
	काष्ठा usb_host_endpoपूर्णांक *ep;
	क्रमागत usb_device_speed speed;
	bool allocated;
	/*
	 * mtk xHCI scheduling inक्रमmation put पूर्णांकo reserved DWs
	 * in ep context
	 */
	u32 offset;
	u32 repeat;
	u32 pkts;
	u32 cs_count;
	u32 burst_mode;
	u32 bw_budget_table[];
पूर्ण;

#घोषणा MU3C_U3_PORT_MAX 4
#घोषणा MU3C_U2_PORT_MAX 5

/**
 * काष्ठा mu3c_ippc_regs: MTK ssusb ip port control रेजिस्टरs
 * @ip_pw_ctr0~3: ip घातer and घड़ी control रेजिस्टरs
 * @ip_pw_sts1~2: ip घातer and घड़ी status रेजिस्टरs
 * @ip_xhci_cap: ip xHCI capability रेजिस्टर
 * @u3_ctrl_p[x]: ip usb3 port x control रेजिस्टर, only low 4bytes are used
 * @u2_ctrl_p[x]: ip usb2 port x control रेजिस्टर, only low 4bytes are used
 * @u2_phy_pll: usb2 phy pll control रेजिस्टर
 */
काष्ठा mu3c_ippc_regs अणु
	__le32 ip_pw_ctr0;
	__le32 ip_pw_ctr1;
	__le32 ip_pw_ctr2;
	__le32 ip_pw_ctr3;
	__le32 ip_pw_sts1;
	__le32 ip_pw_sts2;
	__le32 reserved0[3];
	__le32 ip_xhci_cap;
	__le32 reserved1[2];
	__le64 u3_ctrl_p[MU3C_U3_PORT_MAX];
	__le64 u2_ctrl_p[MU3C_U2_PORT_MAX];
	__le32 reserved2;
	__le32 u2_phy_pll;
	__le32 reserved3[33]; /* 0x80 ~ 0xff */
पूर्ण;

काष्ठा xhci_hcd_mtk अणु
	काष्ठा device *dev;
	काष्ठा usb_hcd *hcd;
	काष्ठा mu3h_sch_bw_info *sch_array;
	काष्ठा list_head bw_ep_chk_list;
	काष्ठा mu3c_ippc_regs __iomem *ippc_regs;
	bool has_ippc;
	पूर्णांक num_u2_ports;
	पूर्णांक num_u3_ports;
	पूर्णांक u3p_dis_msk;
	काष्ठा regulator *vusb33;
	काष्ठा regulator *vbus;
	काष्ठा clk_bulk_data clks[BULK_CLKS_NUM];
	bool lpm_support;
	bool u2_lpm_disable;
	/* usb remote wakeup */
	bool uwk_en;
	काष्ठा regmap *uwk;
	u32 uwk_reg_base;
	u32 uwk_vers;
पूर्ण;

अटल अंतरभूत काष्ठा xhci_hcd_mtk *hcd_to_mtk(काष्ठा usb_hcd *hcd)
अणु
	वापस dev_get_drvdata(hcd->self.controller);
पूर्ण

पूर्णांक xhci_mtk_sch_init(काष्ठा xhci_hcd_mtk *mtk);
व्योम xhci_mtk_sch_निकास(काष्ठा xhci_hcd_mtk *mtk);
पूर्णांक xhci_mtk_add_ep(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
		    काष्ठा usb_host_endpoपूर्णांक *ep);
पूर्णांक xhci_mtk_drop_ep(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
		     काष्ठा usb_host_endpoपूर्णांक *ep);
पूर्णांक xhci_mtk_check_bandwidth(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev);
व्योम xhci_mtk_reset_bandwidth(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev);

#पूर्ण_अगर		/* _XHCI_MTK_H_ */
