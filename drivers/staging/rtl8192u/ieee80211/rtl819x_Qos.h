<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __INC_QOS_TYPE_H
#घोषणा __INC_QOS_TYPE_H

/*
 * ACI/AIFSN Field.
 * Ref: WMM spec 2.2.2: WME Parameter Element, p.12.
 * Note: 1 Byte Length
 */
काष्ठा aci_aअगरsn अणु
	u8	aअगरsn:4;
	u8	acm:1;
	u8	aci:2;
	u8:1;
पूर्ण;

/*
 * Direction Field Values.
 * Ref: WMM spec 2.2.11: WME TSPEC Element, p.18.
 */
क्रमागत direction_value अणु
	सूची_UP			= 0,		// 0x00	// UpLink
	सूची_DOWN		= 1,		// 0x01	// DownLink
	सूची_सूचीECT		= 2,		// 0x10	// DirectLink
	सूची_BI_सूची		= 3,		// 0x11	// Bi-Direction
पूर्ण;

/*
 * TS Info field in WMM TSPEC Element.
 * Ref:
 *	1. WMM spec 2.2.11: WME TSPEC Element, p.18.
 *	2. 8185 QoS code: QOS_TSINFO [def. in QoS_mp.h]
 * Note: माप 3 Bytes
 */
काष्ठा qos_tsinfo अणु
	u16		uc_traffic_type:1;	        //WMM is reserved
	u16		uc_tsid:4;
	u16		uc_direction:2;
	u16		uc_access_policy:2;	        //WMM: bit8=0, bit7=1
	u16		uc_aggregation:1;	        //WMM is reserved
	u16		uc_psb:1;		        //WMMSA is APSD
	u16		uc_up:3;
	u16		uc_ts_info_ack_policy:2;	//WMM is reserved
	u8		uc_schedule:1;		        //WMM is reserved
	u8:7;
पूर्ण;

/*
 * WMM TSPEC Body.
 * Ref: WMM spec 2.2.11: WME TSPEC Element, p.16.
 * Note: माप 55 bytes
 */
काष्ठा tspec_body अणु
	काष्ठा qos_tsinfo	ts_info;	//u8	TSInfo[3];
	u16	nominal_msd_usize;
	u16	max_msd_usize;
	u32	min_service_itv;
	u32	max_service_itv;
	u32	inactivity_itv;
	u32	suspen_itv;
	u32	service_start_समय;
	u32	min_data_rate;
	u32	mean_data_rate;
	u32	peak_data_rate;
	u32	max_burst_size;
	u32	delay_bound;
	u32	min_phy_rate;
	u16	surplus_bandwidth_allowance;
	u16	medium_समय;
पूर्ण;

/*
 *      802.11 Management frame Status Code field
 */
काष्ठा octet_string अणु
	u8		*octet;
	u16             length;
पूर्ण;

#घोषणा is_ac_valid(ac)			(((ac) <= 7) ? true : false)

#पूर्ण_अगर // #अगर_अघोषित __INC_QOS_TYPE_H
