<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015 MediaTek Inc.
 * Author:
 *  Zhigang.Wei <zhigang.wei@mediatek.com>
 *  Chunfeng.Yun <chunfeng.yun@mediatek.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "xhci.h"
#समावेश "xhci-mtk.h"

#घोषणा SSP_BW_BOUNDARY	130000
#घोषणा SS_BW_BOUNDARY	51000
/* table 5-5. High-speed Isoc Transaction Limits in usb_20 spec */
#घोषणा HS_BW_BOUNDARY	6144
/* usb2 spec section11.18.1: at most 188 FS bytes per microframe */
#घोषणा FS_PAYLOAD_MAX 188
/*
 * max number of microframes क्रम split transfer,
 * क्रम fs isoc in : 1 ss + 1 idle + 7 cs
 */
#घोषणा TT_MICROFRAMES_MAX 9

#घोषणा DBG_BUF_EN	64

/* schedule error type */
#घोषणा ESCH_SS_Y6		1001
#घोषणा ESCH_SS_OVERLAP		1002
#घोषणा ESCH_CS_OVERFLOW	1003
#घोषणा ESCH_BW_OVERFLOW	1004
#घोषणा ESCH_FIXME		1005

/* mtk scheduler biपंचांगasks */
#घोषणा EP_BPKTS(p)	((p) & 0x7f)
#घोषणा EP_BCSCOUNT(p)	(((p) & 0x7) << 8)
#घोषणा EP_BBM(p)	((p) << 11)
#घोषणा EP_BOFFSET(p)	((p) & 0x3fff)
#घोषणा EP_BREPEAT(p)	(((p) & 0x7fff) << 16)

अटल अक्षर *sch_error_string(पूर्णांक err_num)
अणु
	चयन (err_num) अणु
	हाल ESCH_SS_Y6:
		वापस "Can't schedule Start-Split in Y6";
	हाल ESCH_SS_OVERLAP:
		वापस "Can't find a suitable Start-Split location";
	हाल ESCH_CS_OVERFLOW:
		वापस "The last Complete-Split is greater than 7";
	हाल ESCH_BW_OVERFLOW:
		वापस "Bandwidth exceeds the maximum limit";
	हाल ESCH_FIXME:
		वापस "FIXME, to be resolved";
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

अटल पूर्णांक is_fs_or_ls(क्रमागत usb_device_speed speed)
अणु
	वापस speed == USB_SPEED_FULL || speed == USB_SPEED_LOW;
पूर्ण

अटल स्थिर अक्षर *
decode_ep(काष्ठा usb_host_endpoपूर्णांक *ep, क्रमागत usb_device_speed speed)
अणु
	अटल अक्षर buf[DBG_BUF_EN];
	काष्ठा usb_endpoपूर्णांक_descriptor *epd = &ep->desc;
	अचिन्हित पूर्णांक पूर्णांकerval;
	स्थिर अक्षर *unit;

	पूर्णांकerval = usb_decode_पूर्णांकerval(epd, speed);
	अगर (पूर्णांकerval % 1000) अणु
		unit = "us";
	पूर्ण अन्यथा अणु
		unit = "ms";
		पूर्णांकerval /= 1000;
	पूर्ण

	snम_लिखो(buf, DBG_BUF_EN, "%s ep%d%s %s, mpkt:%d, interval:%d/%d%s\n",
		 usb_speed_string(speed), usb_endpoपूर्णांक_num(epd),
		 usb_endpoपूर्णांक_dir_in(epd) ? "in" : "out",
		 usb_ep_type_string(usb_endpoपूर्णांक_type(epd)),
		 usb_endpoपूर्णांक_maxp(epd), epd->bInterval, पूर्णांकerval, unit);

	वापस buf;
पूर्ण

अटल u32 get_bw_boundary(क्रमागत usb_device_speed speed)
अणु
	u32 boundary;

	चयन (speed) अणु
	हाल USB_SPEED_SUPER_PLUS:
		boundary = SSP_BW_BOUNDARY;
		अवरोध;
	हाल USB_SPEED_SUPER:
		boundary = SS_BW_BOUNDARY;
		अवरोध;
	शेष:
		boundary = HS_BW_BOUNDARY;
		अवरोध;
	पूर्ण

	वापस boundary;
पूर्ण

/*
* get the bandwidth करोमुख्य which @ep beदीर्घs to.
*
* the bandwidth करोमुख्य array is saved to @sch_array of काष्ठा xhci_hcd_mtk,
* each HS root port is treated as a single bandwidth करोमुख्य,
* but each SS root port is treated as two bandwidth करोमुख्यs, one क्रम IN eps,
* one क्रम OUT eps.
* @real_port value is defined as follow according to xHCI spec:
* 1 क्रम SSport0, ..., N+1 क्रम SSportN, N+2 क्रम HSport0, N+3 क्रम HSport1, etc
* so the bandwidth करोमुख्य array is organized as follow क्रम simplअगरication:
* SSport0-OUT, SSport0-IN, ..., SSportX-OUT, SSportX-IN, HSport0, ..., HSportY
*/
अटल काष्ठा mu3h_sch_bw_info *
get_bw_info(काष्ठा xhci_hcd_mtk *mtk, काष्ठा usb_device *udev,
	    काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(mtk->hcd);
	काष्ठा xhci_virt_device *virt_dev;
	पूर्णांक bw_index;

	virt_dev = xhci->devs[udev->slot_id];

	अगर (udev->speed >= USB_SPEED_SUPER) अणु
		अगर (usb_endpoपूर्णांक_dir_out(&ep->desc))
			bw_index = (virt_dev->real_port - 1) * 2;
		अन्यथा
			bw_index = (virt_dev->real_port - 1) * 2 + 1;
	पूर्ण अन्यथा अणु
		/* add one more क्रम each SS port */
		bw_index = virt_dev->real_port + xhci->usb3_rhub.num_ports - 1;
	पूर्ण

	वापस &mtk->sch_array[bw_index];
पूर्ण

अटल u32 get_esit(काष्ठा xhci_ep_ctx *ep_ctx)
अणु
	u32 esit;

	esit = 1 << CTX_TO_EP_INTERVAL(le32_to_cpu(ep_ctx->ep_info));
	अगर (esit > XHCI_MTK_MAX_ESIT)
		esit = XHCI_MTK_MAX_ESIT;

	वापस esit;
पूर्ण

अटल काष्ठा mu3h_sch_tt *find_tt(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_tt *utt = udev->tt;
	काष्ठा mu3h_sch_tt *tt, **tt_index, **ptt;
	bool allocated_index = false;

	अगर (!utt)
		वापस शून्य;	/* Not below a TT */

	/*
	 * Find/create our data काष्ठाure.
	 * For hubs with a single TT, we get it directly.
	 * For hubs with multiple TTs, there's an extra level of poपूर्णांकers.
	 */
	tt_index = शून्य;
	अगर (utt->multi) अणु
		tt_index = utt->hcpriv;
		अगर (!tt_index) अणु	/* Create the index array */
			tt_index = kसुस्मृति(utt->hub->maxchild,
					माप(*tt_index), GFP_KERNEL);
			अगर (!tt_index)
				वापस ERR_PTR(-ENOMEM);
			utt->hcpriv = tt_index;
			allocated_index = true;
		पूर्ण
		ptt = &tt_index[udev->ttport - 1];
	पूर्ण अन्यथा अणु
		ptt = (काष्ठा mu3h_sch_tt **) &utt->hcpriv;
	पूर्ण

	tt = *ptt;
	अगर (!tt) अणु	/* Create the mu3h_sch_tt */
		tt = kzalloc(माप(*tt), GFP_KERNEL);
		अगर (!tt) अणु
			अगर (allocated_index) अणु
				utt->hcpriv = शून्य;
				kमुक्त(tt_index);
			पूर्ण
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
		INIT_LIST_HEAD(&tt->ep_list);
		*ptt = tt;
	पूर्ण

	वापस tt;
पूर्ण

/* Release the TT above udev, अगर it's not in use */
अटल व्योम drop_tt(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_tt *utt = udev->tt;
	काष्ठा mu3h_sch_tt *tt, **tt_index, **ptt;
	पूर्णांक i, cnt;

	अगर (!utt || !utt->hcpriv)
		वापस;		/* Not below a TT, or never allocated */

	cnt = 0;
	अगर (utt->multi) अणु
		tt_index = utt->hcpriv;
		ptt = &tt_index[udev->ttport - 1];
		/*  How many entries are left in tt_index? */
		क्रम (i = 0; i < utt->hub->maxchild; ++i)
			cnt += !!tt_index[i];
	पूर्ण अन्यथा अणु
		tt_index = शून्य;
		ptt = (काष्ठा mu3h_sch_tt **)&utt->hcpriv;
	पूर्ण

	tt = *ptt;
	अगर (!tt || !list_empty(&tt->ep_list))
		वापस;		/* never allocated , or still in use*/

	*ptt = शून्य;
	kमुक्त(tt);

	अगर (cnt == 1) अणु
		utt->hcpriv = शून्य;
		kमुक्त(tt_index);
	पूर्ण
पूर्ण

अटल काष्ठा mu3h_sch_ep_info *create_sch_ep(काष्ठा usb_device *udev,
	काष्ठा usb_host_endpoपूर्णांक *ep, काष्ठा xhci_ep_ctx *ep_ctx)
अणु
	काष्ठा mu3h_sch_ep_info *sch_ep;
	काष्ठा mu3h_sch_tt *tt = शून्य;
	u32 len_bw_budget_table;
	माप_प्रकार mem_size;

	अगर (is_fs_or_ls(udev->speed))
		len_bw_budget_table = TT_MICROFRAMES_MAX;
	अन्यथा अगर ((udev->speed >= USB_SPEED_SUPER)
			&& usb_endpoपूर्णांक_xfer_isoc(&ep->desc))
		len_bw_budget_table = get_esit(ep_ctx);
	अन्यथा
		len_bw_budget_table = 1;

	mem_size = माप(काष्ठा mu3h_sch_ep_info) +
			len_bw_budget_table * माप(u32);
	sch_ep = kzalloc(mem_size, GFP_KERNEL);
	अगर (!sch_ep)
		वापस ERR_PTR(-ENOMEM);

	अगर (is_fs_or_ls(udev->speed)) अणु
		tt = find_tt(udev);
		अगर (IS_ERR(tt)) अणु
			kमुक्त(sch_ep);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण

	sch_ep->sch_tt = tt;
	sch_ep->ep = ep;
	sch_ep->speed = udev->speed;
	INIT_LIST_HEAD(&sch_ep->endpoपूर्णांक);
	INIT_LIST_HEAD(&sch_ep->tt_endpoपूर्णांक);

	वापस sch_ep;
पूर्ण

अटल व्योम setup_sch_info(काष्ठा xhci_ep_ctx *ep_ctx,
			   काष्ठा mu3h_sch_ep_info *sch_ep)
अणु
	u32 ep_type;
	u32 maxpkt;
	u32 max_burst;
	u32 mult;
	u32 esit_pkts;
	u32 max_esit_payload;
	u32 *bwb_table = sch_ep->bw_budget_table;
	पूर्णांक i;

	ep_type = CTX_TO_EP_TYPE(le32_to_cpu(ep_ctx->ep_info2));
	maxpkt = MAX_PACKET_DECODED(le32_to_cpu(ep_ctx->ep_info2));
	max_burst = CTX_TO_MAX_BURST(le32_to_cpu(ep_ctx->ep_info2));
	mult = CTX_TO_EP_MULT(le32_to_cpu(ep_ctx->ep_info));
	max_esit_payload =
		(CTX_TO_MAX_ESIT_PAYLOAD_HI(
			le32_to_cpu(ep_ctx->ep_info)) << 16) |
		 CTX_TO_MAX_ESIT_PAYLOAD(le32_to_cpu(ep_ctx->tx_info));

	sch_ep->esit = get_esit(ep_ctx);
	sch_ep->ep_type = ep_type;
	sch_ep->maxpkt = maxpkt;
	sch_ep->offset = 0;
	sch_ep->burst_mode = 0;
	sch_ep->repeat = 0;

	अगर (sch_ep->speed == USB_SPEED_HIGH) अणु
		sch_ep->cs_count = 0;

		/*
		 * usb_20 spec section5.9
		 * a single microframe is enough क्रम HS synchromous endpoपूर्णांकs
		 * in a पूर्णांकerval
		 */
		sch_ep->num_budget_microframes = 1;

		/*
		 * xHCI spec section6.2.3.4
		 * @max_burst is the number of additional transactions
		 * opportunities per microframe
		 */
		sch_ep->pkts = max_burst + 1;
		sch_ep->bw_cost_per_microframe = maxpkt * sch_ep->pkts;
		bwb_table[0] = sch_ep->bw_cost_per_microframe;
	पूर्ण अन्यथा अगर (sch_ep->speed >= USB_SPEED_SUPER) अणु
		/* usb3_r1 spec section4.4.7 & 4.4.8 */
		sch_ep->cs_count = 0;
		sch_ep->burst_mode = 1;
		/*
		 * some device's (d)wBytesPerInterval is set as 0,
		 * then max_esit_payload is 0, so evaluate esit_pkts from
		 * mult and burst
		 */
		esit_pkts = DIV_ROUND_UP(max_esit_payload, maxpkt);
		अगर (esit_pkts == 0)
			esit_pkts = (mult + 1) * (max_burst + 1);

		अगर (ep_type == INT_IN_EP || ep_type == INT_OUT_EP) अणु
			sch_ep->pkts = esit_pkts;
			sch_ep->num_budget_microframes = 1;
			bwb_table[0] = maxpkt * sch_ep->pkts;
		पूर्ण

		अगर (ep_type == ISOC_IN_EP || ep_type == ISOC_OUT_EP) अणु

			अगर (sch_ep->esit == 1)
				sch_ep->pkts = esit_pkts;
			अन्यथा अगर (esit_pkts <= sch_ep->esit)
				sch_ep->pkts = 1;
			अन्यथा
				sch_ep->pkts = roundup_घात_of_two(esit_pkts)
					/ sch_ep->esit;

			sch_ep->num_budget_microframes =
				DIV_ROUND_UP(esit_pkts, sch_ep->pkts);

			sch_ep->repeat = !!(sch_ep->num_budget_microframes > 1);
			sch_ep->bw_cost_per_microframe = maxpkt * sch_ep->pkts;

			क्रम (i = 0; i < sch_ep->num_budget_microframes - 1; i++)
				bwb_table[i] = sch_ep->bw_cost_per_microframe;

			/* last one <= bw_cost_per_microframe */
			bwb_table[i] = maxpkt * esit_pkts
				       - i * sch_ep->bw_cost_per_microframe;
		पूर्ण
	पूर्ण अन्यथा अगर (is_fs_or_ls(sch_ep->speed)) अणु
		sch_ep->pkts = 1; /* at most one packet क्रम each microframe */

		/*
		 * num_budget_microframes and cs_count will be updated when
		 * check TT क्रम INT_OUT_EP, ISOC/INT_IN_EP type
		 */
		sch_ep->cs_count = DIV_ROUND_UP(maxpkt, FS_PAYLOAD_MAX);
		sch_ep->num_budget_microframes = sch_ep->cs_count;
		sch_ep->bw_cost_per_microframe =
			(maxpkt < FS_PAYLOAD_MAX) ? maxpkt : FS_PAYLOAD_MAX;

		/* init budget table */
		अगर (ep_type == ISOC_OUT_EP) अणु
			क्रम (i = 0; i < sch_ep->num_budget_microframes; i++)
				bwb_table[i] =	sch_ep->bw_cost_per_microframe;
		पूर्ण अन्यथा अगर (ep_type == INT_OUT_EP) अणु
			/* only first one consumes bandwidth, others as zero */
			bwb_table[0] = sch_ep->bw_cost_per_microframe;
		पूर्ण अन्यथा अणु /* INT_IN_EP or ISOC_IN_EP */
			bwb_table[0] = 0; /* start split */
			bwb_table[1] = 0; /* idle */
			/*
			 * due to cs_count will be updated according to cs
			 * position, assign all reमुख्यder budget array
			 * elements as @bw_cost_per_microframe, but only first
			 * @num_budget_microframes elements will be used later
			 */
			क्रम (i = 2; i < TT_MICROFRAMES_MAX; i++)
				bwb_table[i] =	sch_ep->bw_cost_per_microframe;
		पूर्ण
	पूर्ण
पूर्ण

/* Get maximum bandwidth when we schedule at offset slot. */
अटल u32 get_max_bw(काष्ठा mu3h_sch_bw_info *sch_bw,
	काष्ठा mu3h_sch_ep_info *sch_ep, u32 offset)
अणु
	u32 num_esit;
	u32 max_bw = 0;
	u32 bw;
	पूर्णांक i;
	पूर्णांक j;

	num_esit = XHCI_MTK_MAX_ESIT / sch_ep->esit;
	क्रम (i = 0; i < num_esit; i++) अणु
		u32 base = offset + i * sch_ep->esit;

		क्रम (j = 0; j < sch_ep->num_budget_microframes; j++) अणु
			bw = sch_bw->bus_bw[base + j] +
					sch_ep->bw_budget_table[j];
			अगर (bw > max_bw)
				max_bw = bw;
		पूर्ण
	पूर्ण
	वापस max_bw;
पूर्ण

अटल व्योम update_bus_bw(काष्ठा mu3h_sch_bw_info *sch_bw,
	काष्ठा mu3h_sch_ep_info *sch_ep, bool used)
अणु
	u32 num_esit;
	u32 base;
	पूर्णांक i;
	पूर्णांक j;

	num_esit = XHCI_MTK_MAX_ESIT / sch_ep->esit;
	क्रम (i = 0; i < num_esit; i++) अणु
		base = sch_ep->offset + i * sch_ep->esit;
		क्रम (j = 0; j < sch_ep->num_budget_microframes; j++) अणु
			अगर (used)
				sch_bw->bus_bw[base + j] +=
					sch_ep->bw_budget_table[j];
			अन्यथा
				sch_bw->bus_bw[base + j] -=
					sch_ep->bw_budget_table[j];
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक check_fs_bus_bw(काष्ठा mu3h_sch_ep_info *sch_ep, पूर्णांक offset)
अणु
	काष्ठा mu3h_sch_tt *tt = sch_ep->sch_tt;
	u32 num_esit, पंचांगp;
	पूर्णांक base;
	पूर्णांक i, j;

	num_esit = XHCI_MTK_MAX_ESIT / sch_ep->esit;
	क्रम (i = 0; i < num_esit; i++) अणु
		base = offset + i * sch_ep->esit;

		/*
		 * Compared with hs bus, no matter what ep type,
		 * the hub will always delay one uframe to send data
		 */
		क्रम (j = 0; j < sch_ep->cs_count; j++) अणु
			पंचांगp = tt->fs_bus_bw[base + j] + sch_ep->bw_cost_per_microframe;
			अगर (पंचांगp > FS_PAYLOAD_MAX)
				वापस -ESCH_BW_OVERFLOW;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_sch_tt(काष्ठा mu3h_sch_ep_info *sch_ep, u32 offset)
अणु
	काष्ठा mu3h_sch_tt *tt = sch_ep->sch_tt;
	u32 extra_cs_count;
	u32 start_ss, last_ss;
	u32 start_cs, last_cs;
	पूर्णांक i;

	start_ss = offset % 8;

	अगर (sch_ep->ep_type == ISOC_OUT_EP) अणु
		last_ss = start_ss + sch_ep->cs_count - 1;

		/*
		 * usb_20 spec section11.18:
		 * must never schedule Start-Split in Y6
		 */
		अगर (!(start_ss == 7 || last_ss < 6))
			वापस -ESCH_SS_Y6;

		क्रम (i = 0; i < sch_ep->cs_count; i++)
			अगर (test_bit(offset + i, tt->ss_bit_map))
				वापस -ESCH_SS_OVERLAP;

	पूर्ण अन्यथा अणु
		u32 cs_count = DIV_ROUND_UP(sch_ep->maxpkt, FS_PAYLOAD_MAX);

		/*
		 * usb_20 spec section11.18:
		 * must never schedule Start-Split in Y6
		 */
		अगर (start_ss == 6)
			वापस -ESCH_SS_Y6;

		/* one uframe क्रम ss + one uframe क्रम idle */
		start_cs = (start_ss + 2) % 8;
		last_cs = start_cs + cs_count - 1;

		अगर (last_cs > 7)
			वापस -ESCH_CS_OVERFLOW;

		अगर (sch_ep->ep_type == ISOC_IN_EP)
			extra_cs_count = (last_cs == 7) ? 1 : 2;
		अन्यथा /*  ep_type : INTR IN / INTR OUT */
			extra_cs_count = 1;

		cs_count += extra_cs_count;
		अगर (cs_count > 7)
			cs_count = 7; /* HW limit */

		अगर (test_bit(offset, tt->ss_bit_map))
			वापस -ESCH_SS_OVERLAP;

		sch_ep->cs_count = cs_count;
		/* one क्रम ss, the other क्रम idle */
		sch_ep->num_budget_microframes = cs_count + 2;

		/*
		 * अगर पूर्णांकerval=1, maxp >752, num_budge_micoframe is larger
		 * than sch_ep->esit, will overstep boundary
		 */
		अगर (sch_ep->num_budget_microframes > sch_ep->esit)
			sch_ep->num_budget_microframes = sch_ep->esit;
	पूर्ण

	वापस check_fs_bus_bw(sch_ep, offset);
पूर्ण

अटल व्योम update_sch_tt(काष्ठा mu3h_sch_ep_info *sch_ep, bool used)
अणु
	काष्ठा mu3h_sch_tt *tt = sch_ep->sch_tt;
	u32 base, num_esit;
	पूर्णांक bw_updated;
	पूर्णांक bits;
	पूर्णांक i, j;

	num_esit = XHCI_MTK_MAX_ESIT / sch_ep->esit;
	bits = (sch_ep->ep_type == ISOC_OUT_EP) ? sch_ep->cs_count : 1;

	अगर (used)
		bw_updated = sch_ep->bw_cost_per_microframe;
	अन्यथा
		bw_updated = -sch_ep->bw_cost_per_microframe;

	क्रम (i = 0; i < num_esit; i++) अणु
		base = sch_ep->offset + i * sch_ep->esit;

		क्रम (j = 0; j < bits; j++) अणु
			अगर (used)
				set_bit(base + j, tt->ss_bit_map);
			अन्यथा
				clear_bit(base + j, tt->ss_bit_map);
		पूर्ण

		क्रम (j = 0; j < sch_ep->cs_count; j++)
			tt->fs_bus_bw[base + j] += bw_updated;
	पूर्ण

	अगर (used)
		list_add_tail(&sch_ep->tt_endpoपूर्णांक, &tt->ep_list);
	अन्यथा
		list_del(&sch_ep->tt_endpoपूर्णांक);
पूर्ण

अटल पूर्णांक load_ep_bw(काष्ठा mu3h_sch_bw_info *sch_bw,
		      काष्ठा mu3h_sch_ep_info *sch_ep, bool loaded)
अणु
	अगर (sch_ep->sch_tt)
		update_sch_tt(sch_ep, loaded);

	/* update bus bandwidth info */
	update_bus_bw(sch_bw, sch_ep, loaded);
	sch_ep->allocated = loaded;

	वापस 0;
पूर्ण

अटल u32 get_esit_boundary(काष्ठा mu3h_sch_ep_info *sch_ep)
अणु
	u32 boundary = sch_ep->esit;

	अगर (sch_ep->sch_tt) अणु /* LS/FS with TT */
		/* tune क्रम CS */
		अगर (sch_ep->ep_type != ISOC_OUT_EP)
			boundary++;
		अन्यथा अगर (boundary > 1) /* normally esit >= 8 क्रम FS/LS */
			boundary--;
	पूर्ण

	वापस boundary;
पूर्ण

अटल पूर्णांक check_sch_bw(काष्ठा mu3h_sch_bw_info *sch_bw,
			काष्ठा mu3h_sch_ep_info *sch_ep)
अणु
	u32 offset;
	u32 min_bw;
	u32 min_index;
	u32 worst_bw;
	u32 bw_boundary;
	u32 esit_boundary;
	u32 min_num_budget;
	u32 min_cs_count;
	पूर्णांक ret = 0;

	/*
	 * Search through all possible schedule microframes.
	 * and find a microframe where its worst bandwidth is minimum.
	 */
	min_bw = ~0;
	min_index = 0;
	min_cs_count = sch_ep->cs_count;
	min_num_budget = sch_ep->num_budget_microframes;
	esit_boundary = get_esit_boundary(sch_ep);
	क्रम (offset = 0; offset < sch_ep->esit; offset++) अणु
		अगर (sch_ep->sch_tt) अणु
			ret = check_sch_tt(sch_ep, offset);
			अगर (ret)
				जारी;
		पूर्ण

		अगर ((offset + sch_ep->num_budget_microframes) > esit_boundary)
			अवरोध;

		worst_bw = get_max_bw(sch_bw, sch_ep, offset);
		अगर (min_bw > worst_bw) अणु
			min_bw = worst_bw;
			min_index = offset;
			min_cs_count = sch_ep->cs_count;
			min_num_budget = sch_ep->num_budget_microframes;
		पूर्ण
		अगर (min_bw == 0)
			अवरोध;
	पूर्ण

	bw_boundary = get_bw_boundary(sch_ep->speed);
	/* check bandwidth */
	अगर (min_bw > bw_boundary)
		वापस ret ? ret : -ESCH_BW_OVERFLOW;

	sch_ep->offset = min_index;
	sch_ep->cs_count = min_cs_count;
	sch_ep->num_budget_microframes = min_num_budget;

	वापस load_ep_bw(sch_bw, sch_ep, true);
पूर्ण

अटल व्योम destroy_sch_ep(काष्ठा usb_device *udev,
	काष्ठा mu3h_sch_bw_info *sch_bw, काष्ठा mu3h_sch_ep_info *sch_ep)
अणु
	/* only release ep bw check passed by check_sch_bw() */
	अगर (sch_ep->allocated)
		load_ep_bw(sch_bw, sch_ep, false);

	अगर (sch_ep->sch_tt)
		drop_tt(udev);

	list_del(&sch_ep->endpoपूर्णांक);
	kमुक्त(sch_ep);
पूर्ण

अटल bool need_bw_sch(काष्ठा usb_host_endpoपूर्णांक *ep,
	क्रमागत usb_device_speed speed, पूर्णांक has_tt)
अणु
	/* only क्रम periodic endpoपूर्णांकs */
	अगर (usb_endpoपूर्णांक_xfer_control(&ep->desc)
		|| usb_endpoपूर्णांक_xfer_bulk(&ep->desc))
		वापस false;

	/*
	 * क्रम LS & FS periodic endpoपूर्णांकs which its device is not behind
	 * a TT are also ignored, root-hub will schedule them directly,
	 * but need set @bpkts field of endpoपूर्णांक context to 1.
	 */
	अगर (is_fs_or_ls(speed) && !has_tt)
		वापस false;

	/* skip endpoपूर्णांक with zero maxpkt */
	अगर (usb_endpoपूर्णांक_maxp(&ep->desc) == 0)
		वापस false;

	वापस true;
पूर्ण

पूर्णांक xhci_mtk_sch_init(काष्ठा xhci_hcd_mtk *mtk)
अणु
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(mtk->hcd);
	काष्ठा mu3h_sch_bw_info *sch_array;
	पूर्णांक num_usb_bus;
	पूर्णांक i;

	/* ss IN and OUT are separated */
	num_usb_bus = xhci->usb3_rhub.num_ports * 2 + xhci->usb2_rhub.num_ports;

	sch_array = kसुस्मृति(num_usb_bus, माप(*sch_array), GFP_KERNEL);
	अगर (sch_array == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_usb_bus; i++)
		INIT_LIST_HEAD(&sch_array[i].bw_ep_list);

	mtk->sch_array = sch_array;

	INIT_LIST_HEAD(&mtk->bw_ep_chk_list);

	वापस 0;
पूर्ण

व्योम xhci_mtk_sch_निकास(काष्ठा xhci_hcd_mtk *mtk)
अणु
	kमुक्त(mtk->sch_array);
पूर्ण

अटल पूर्णांक add_ep_quirk(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
			काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा xhci_hcd_mtk *mtk = hcd_to_mtk(hcd);
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);
	काष्ठा xhci_ep_ctx *ep_ctx;
	काष्ठा xhci_virt_device *virt_dev;
	काष्ठा mu3h_sch_ep_info *sch_ep;
	अचिन्हित पूर्णांक ep_index;

	virt_dev = xhci->devs[udev->slot_id];
	ep_index = xhci_get_endpoपूर्णांक_index(&ep->desc);
	ep_ctx = xhci_get_ep_ctx(xhci, virt_dev->in_ctx, ep_index);

	xhci_dbg(xhci, "%s %s\n", __func__, decode_ep(ep, udev->speed));

	अगर (!need_bw_sch(ep, udev->speed, !!virt_dev->tt_info)) अणु
		/*
		 * set @bpkts to 1 अगर it is LS or FS periodic endpoपूर्णांक, and its
		 * device करोes not connected through an बाह्यal HS hub
		 */
		अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(&ep->desc)
			|| usb_endpoपूर्णांक_xfer_isoc(&ep->desc))
			ep_ctx->reserved[0] = cpu_to_le32(EP_BPKTS(1));

		वापस 0;
	पूर्ण

	sch_ep = create_sch_ep(udev, ep, ep_ctx);
	अगर (IS_ERR_OR_शून्य(sch_ep))
		वापस -ENOMEM;

	setup_sch_info(ep_ctx, sch_ep);

	list_add_tail(&sch_ep->endpoपूर्णांक, &mtk->bw_ep_chk_list);

	वापस 0;
पूर्ण

अटल व्योम drop_ep_quirk(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
			  काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा xhci_hcd_mtk *mtk = hcd_to_mtk(hcd);
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);
	काष्ठा xhci_virt_device *virt_dev;
	काष्ठा mu3h_sch_bw_info *sch_bw;
	काष्ठा mu3h_sch_ep_info *sch_ep, *पंचांगp;

	virt_dev = xhci->devs[udev->slot_id];

	xhci_dbg(xhci, "%s %s\n", __func__, decode_ep(ep, udev->speed));

	अगर (!need_bw_sch(ep, udev->speed, !!virt_dev->tt_info))
		वापस;

	sch_bw = get_bw_info(mtk, udev, ep);

	list_क्रम_each_entry_safe(sch_ep, पंचांगp, &sch_bw->bw_ep_list, endpoपूर्णांक) अणु
		अगर (sch_ep->ep == ep) अणु
			destroy_sch_ep(udev, sch_bw, sch_ep);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक xhci_mtk_check_bandwidth(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev)
अणु
	काष्ठा xhci_hcd_mtk *mtk = hcd_to_mtk(hcd);
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);
	काष्ठा xhci_virt_device *virt_dev = xhci->devs[udev->slot_id];
	काष्ठा mu3h_sch_bw_info *sch_bw;
	काष्ठा mu3h_sch_ep_info *sch_ep, *पंचांगp;
	पूर्णांक ret;

	xhci_dbg(xhci, "%s() udev %s\n", __func__, dev_name(&udev->dev));

	list_क्रम_each_entry(sch_ep, &mtk->bw_ep_chk_list, endpoपूर्णांक) अणु
		sch_bw = get_bw_info(mtk, udev, sch_ep->ep);

		ret = check_sch_bw(sch_bw, sch_ep);
		अगर (ret) अणु
			xhci_err(xhci, "Not enough bandwidth! (%s)\n",
				 sch_error_string(-ret));
			वापस -ENOSPC;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_safe(sch_ep, पंचांगp, &mtk->bw_ep_chk_list, endpoपूर्णांक) अणु
		काष्ठा xhci_ep_ctx *ep_ctx;
		काष्ठा usb_host_endpoपूर्णांक *ep = sch_ep->ep;
		अचिन्हित पूर्णांक ep_index = xhci_get_endpoपूर्णांक_index(&ep->desc);

		sch_bw = get_bw_info(mtk, udev, ep);
		list_move_tail(&sch_ep->endpoपूर्णांक, &sch_bw->bw_ep_list);

		ep_ctx = xhci_get_ep_ctx(xhci, virt_dev->in_ctx, ep_index);
		ep_ctx->reserved[0] = cpu_to_le32(EP_BPKTS(sch_ep->pkts)
			| EP_BCSCOUNT(sch_ep->cs_count)
			| EP_BBM(sch_ep->burst_mode));
		ep_ctx->reserved[1] = cpu_to_le32(EP_BOFFSET(sch_ep->offset)
			| EP_BREPEAT(sch_ep->repeat));

		xhci_dbg(xhci, " PKTS:%x, CSCOUNT:%x, BM:%x, OFFSET:%x, REPEAT:%x\n",
			sch_ep->pkts, sch_ep->cs_count, sch_ep->burst_mode,
			sch_ep->offset, sch_ep->repeat);
	पूर्ण

	वापस xhci_check_bandwidth(hcd, udev);
पूर्ण

व्योम xhci_mtk_reset_bandwidth(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev)
अणु
	काष्ठा xhci_hcd_mtk *mtk = hcd_to_mtk(hcd);
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);
	काष्ठा mu3h_sch_bw_info *sch_bw;
	काष्ठा mu3h_sch_ep_info *sch_ep, *पंचांगp;

	xhci_dbg(xhci, "%s() udev %s\n", __func__, dev_name(&udev->dev));

	list_क्रम_each_entry_safe(sch_ep, पंचांगp, &mtk->bw_ep_chk_list, endpoपूर्णांक) अणु
		sch_bw = get_bw_info(mtk, udev, sch_ep->ep);
		destroy_sch_ep(udev, sch_bw, sch_ep);
	पूर्ण

	xhci_reset_bandwidth(hcd, udev);
पूर्ण

पूर्णांक xhci_mtk_add_ep(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
		    काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	पूर्णांक ret;

	ret = xhci_add_endpoपूर्णांक(hcd, udev, ep);
	अगर (ret)
		वापस ret;

	अगर (ep->hcpriv)
		ret = add_ep_quirk(hcd, udev, ep);

	वापस ret;
पूर्ण

पूर्णांक xhci_mtk_drop_ep(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
		     काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	पूर्णांक ret;

	ret = xhci_drop_endpoपूर्णांक(hcd, udev, ep);
	अगर (ret)
		वापस ret;

	अगर (ep->hcpriv)
		drop_ep_quirk(hcd, udev, ep);

	वापस 0;
पूर्ण
