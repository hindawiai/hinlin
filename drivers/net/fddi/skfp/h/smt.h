<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/******************************************************************************
 *
 *	(C)Copyright 1998,1999 SysKonnect,
 *	a business unit of Schneider & Koch & Co. Datenप्रणालीe GmbH.
 *
 *	The inक्रमmation in this file is provided "AS IS" without warranty.
 *
 ******************************************************************************/

/*
 *	SMT 7.2 frame definitions
 */

#अगर_अघोषित	_SMT_
#घोषणा _SMT_

/* #घोषणा SMT5_10 */
#घोषणा SMT6_10
#घोषणा SMT7_20

#घोषणा	OPT_PMF		/* अगर parameter management is supported */
#घोषणा	OPT_SRF		/* अगर status report is supported */

/*
 * SMT frame version 5.1
 */

#घोषणा SMT_VID	0x0001			/* V 5.1 .. 6.1 */
#घोषणा SMT_VID_2 0x0002		/* V 7.2 */

काष्ठा smt_sid अणु
	u_अक्षर	sid_oem[2] ;			/* implementation spec. */
	काष्ठा fddi_addr sid_node ;		/* node address */
पूर्ण ;

प्रकार u_अक्षर	t_station_id[8] ;

/*
 * note on alignment :
 * माप(काष्ठा smt_header) = 32
 * all parameters are दीर्घ aligned
 * अगर काष्ठा smt_header starts at offset 0, all दीर्घs are aligned correctly
 * (FC starts at offset 3)
 */
_packed काष्ठा smt_header अणु
	काष्ठा fddi_addr    	smt_dest ;	/* destination address */
	काष्ठा fddi_addr	smt_source ;	/* source address */
	u_अक्षर			smt_class ;	/* NIF, SIF ... */
	u_अक्षर			smt_type ;	/* req., response .. */
	u_लघु			smt_version ;	/* version id */
	u_पूर्णांक			smt_tid ;	/* transaction ID */
	काष्ठा smt_sid		smt_sid ;	/* station ID */
	u_लघु			smt_pad ;	/* pad with 0 */
	u_लघु			smt_len ;	/* length of info field */
पूर्ण ;
#घोषणा SWAP_SMTHEADER	"662sl8ss"

#अगर	0
/*
 * MAC FC values
 */
#घोषणा FC_SMT_INFO	0x41		/* SMT info */
#घोषणा FC_SMT_NSA	0x4f		/* SMT Next Station Addressing */
#पूर्ण_अगर


/*
 * type codes
 */
#घोषणा SMT_ANNOUNCE	0x01		/* announcement */
#घोषणा SMT_REQUEST	0x02		/* request */
#घोषणा SMT_REPLY	0x03		/* reply */

/*
 * class codes
 */
#घोषणा SMT_NIF		0x01		/* neighbor inक्रमmation frames */
#घोषणा SMT_SIF_CONFIG	0x02		/* station inक्रमmation configuration */
#घोषणा SMT_SIF_OPER	0x03		/* station inक्रमmation operation */
#घोषणा SMT_ECF		0x04		/* echo frames */
#घोषणा SMT_RAF		0x05		/* resource allocation */
#घोषणा SMT_RDF		0x06		/* request denied */
#घोषणा SMT_SRF		0x07		/* status report */
#घोषणा SMT_PMF_GET	0x08		/* parameter management get */
#घोषणा SMT_PMF_SET	0x09		/* parameter management set */
#घोषणा SMT_ESF		0xff		/* extended service */

#घोषणा SMT_MAX_ECHO_LEN	4458	/* max length of SMT Echo */
#अगर	defined(CONC) || defined(CONC_II)
#घोषणा SMT_TEST_ECHO_LEN	50	/* test length of SMT Echo */
#अन्यथा
#घोषणा SMT_TEST_ECHO_LEN	SMT_MAX_ECHO_LEN	/* test length */
#पूर्ण_अगर

#घोषणा SMT_MAX_INFO_LEN	(4352-20)	/* max length क्रम SMT info */


/*
 * parameter types
 */

काष्ठा smt_para अणु
	u_लघु	p_type ;		/* type */
	u_लघु	p_len ;			/* length of parameter */
पूर्ण ;

#घोषणा PARA_LEN	(माप(काष्ठा smt_para))

#घोषणा SMTSETPARA(p,t)		(p)->para.p_type = (t),\
				(p)->para.p_len = माप(*(p)) - PARA_LEN

/*
 * P01 : Upstream Neighbor Address, UNA
 */
#घोषणा SMT_P_UNA	0x0001		/* upstream neighbor address */
#घोषणा SWAP_SMT_P_UNA	"s6"

काष्ठा smt_p_una अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_लघु	una_pad ;
	काष्ठा fddi_addr una_node ;	/* node address, zero अगर unknown */
पूर्ण ;

/*
 * P02 : Station Descriptor
 */
#घोषणा SMT_P_SDE	0x0002		/* station descriptor */
#घोषणा SWAP_SMT_P_SDE	"1111"

#घोषणा SMT_SDE_STATION		0	/* end node */
#घोषणा SMT_SDE_CONCENTRATOR	1	/* concentrator */

काष्ठा smt_p_sde अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_अक्षर	sde_type ;		/* station type */
	u_अक्षर	sde_mac_count ;		/* number of MACs */
	u_अक्षर	sde_non_master ;	/* number of A,B or S ports */
	u_अक्षर	sde_master ;		/* number of S ports on conc. */
पूर्ण ;

/*
 * P03 : Station State
 */
#घोषणा SMT_P_STATE	0x0003		/* station state */
#घोषणा SWAP_SMT_P_STATE	"scc"

काष्ठा smt_p_state अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_लघु	st_pad ;
	u_अक्षर	st_topology ;		/* topology */
	u_अक्षर	st_dupl_addr ;		/* duplicate address detected */
पूर्ण ;
#घोषणा SMT_ST_WRAPPED		(1<<0)	/* station wrapped */
#घोषणा SMT_ST_UNATTACHED	(1<<1)	/* unattached concentrator */
#घोषणा SMT_ST_TWISTED_A	(1<<2)	/* A-A connection, twisted ring */
#घोषणा SMT_ST_TWISTED_B	(1<<3)	/* B-B connection, twisted ring */
#घोषणा SMT_ST_ROOTED_S		(1<<4)	/* rooted station */
#घोषणा SMT_ST_SRF		(1<<5)	/* SRF protocol supported */
#घोषणा SMT_ST_SYNC_SERVICE	(1<<6)	/* use synchronous bandwidth */

#घोषणा SMT_ST_MY_DUPA		(1<<0)	/* my station detected dupl. */
#घोषणा SMT_ST_UNA_DUPA		(1<<1)	/* my UNA detected duplicate */

/*
 * P04 : बारtamp
 */
#घोषणा SMT_P_TIMESTAMP	0x0004		/* समय stamp */
#घोषणा SWAP_SMT_P_TIMESTAMP	"8"
काष्ठा smt_p_बारtamp अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_अक्षर	ts_समय[8] ;		/* समय, resolution 80nS, unique */
पूर्ण ;

/*
 * P05 : station policies
 */
#घोषणा SMT_P_POLICY	0x0005		/* station policies */
#घोषणा SWAP_SMT_P_POLICY	"ss"

काष्ठा smt_p_policy अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_लघु	pl_config ;
	u_लघु pl_connect ;		/* bit string POLICY_AA ... */
पूर्ण ;
#घोषणा SMT_PL_HOLD		1	/* hold policy supported (Dual MAC) */

/*
 * P06 : latency equivalent
 */
#घोषणा SMT_P_LATENCY	0x0006		/* latency */
#घोषणा SWAP_SMT_P_LATENCY	"ssss"

/*
 * note: latency has two phy entries by definition
 * क्रम a SAS, the 2nd one is null
 */
काष्ठा smt_p_latency अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_लघु	lt_phyout_idx1 ;	/* index */
	u_लघु	lt_latency1 ;		/* latency , unit : byte घड़ी */
	u_लघु	lt_phyout_idx2 ;	/* 0 अगर SAS */
	u_लघु	lt_latency2 ;		/* 0 अगर SAS */
पूर्ण ;

/*
 * P07 : MAC neighbors
 */
#घोषणा SMT_P_NEIGHBORS	0x0007		/* MAC neighbor description */
#घोषणा SWAP_SMT_P_NEIGHBORS	"ss66"

काष्ठा smt_p_neighbor अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_लघु	nb_mib_index ;		/* MIB index */
	u_लघु	nb_mac_index ;		/* n+1 .. n+m, m = #MACs, n = #PHYs */
	काष्ठा fddi_addr nb_una ;	/* UNA , 0 क्रम unknown */
	काष्ठा fddi_addr nb_dna ;	/* DNA , 0 क्रम unknown */
पूर्ण ;

/*
 * PHY record
 */
#घोषणा SMT_PHY_A	0		/* A port */
#घोषणा SMT_PHY_B	1		/* B port */
#घोषणा SMT_PHY_S	2		/* slave port */
#घोषणा SMT_PHY_M	3		/* master port */

#घोषणा SMT_CS_DISABLED	0		/* connect state : disabled */
#घोषणा SMT_CS_CONNECTING	1	/* connect state : connecting */
#घोषणा SMT_CS_STANDBY	2		/* connect state : stand by */
#घोषणा SMT_CS_ACTIVE	3		/* connect state : active */

#घोषणा SMT_RM_NONE	0
#घोषणा SMT_RM_MAC	1

काष्ठा smt_phy_rec अणु
	u_लघु	phy_mib_index ;		/* MIB index */
	u_अक्षर	phy_type ;		/* A/B/S/M */
	u_अक्षर	phy_connect_state ;	/* disabled/connecting/active */
	u_अक्षर	phy_remote_type ;	/* A/B/S/M */
	u_अक्षर	phy_remote_mac ;	/* none/remote */
	u_लघु	phy_resource_idx ;	/* 1 .. n */
पूर्ण ;

/*
 * MAC record
 */
काष्ठा smt_mac_rec अणु
	काष्ठा fddi_addr mac_addr ;		/* MAC address */
	u_लघु		mac_resource_idx ;	/* n+1 .. n+m */
पूर्ण ;

/*
 * P08 : path descriptors
 * should be really an array ; however our environment has a fixed number of
 * PHYs and MACs
 */
#घोषणा SMT_P_PATH	0x0008			/* path descriptor */
#घोषणा SWAP_SMT_P_PATH	"[6s]"

काष्ठा smt_p_path अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	काष्ठा smt_phy_rec	pd_phy[2] ;	/* PHY A */
	काष्ठा smt_mac_rec	pd_mac ;	/* MAC record */
पूर्ण ;

/*
 * P09 : MAC status
 */
#घोषणा SMT_P_MAC_STATUS	0x0009		/* MAC status */
#घोषणा SWAP_SMT_P_MAC_STATUS	"sslllllllll"

काष्ठा smt_p_mac_status अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_लघु st_mib_index ;		/* MIB index */
	u_लघु	st_mac_index ;		/* n+1 .. n+m */
	u_पूर्णांक	st_t_req ;		/* T_Req */
	u_पूर्णांक	st_t_neg ;		/* T_Neg */
	u_पूर्णांक	st_t_max ;		/* T_Max */
	u_पूर्णांक	st_tvx_value ;		/* TVX_Value */
	u_पूर्णांक	st_t_min ;		/* T_Min */
	u_पूर्णांक	st_sba ;		/* synchr. bandwidth alloc */
	u_पूर्णांक	st_frame_ct ;		/* frame counter */
	u_पूर्णांक	st_error_ct ;		/* error counter */
	u_पूर्णांक	st_lost_ct ;		/* lost frames counter */
पूर्ण ;

/*
 * P0A : PHY link error rate monitoring
 */
#घोषणा SMT_P_LEM	0x000a		/* link error monitor */
#घोषणा SWAP_SMT_P_LEM	"ssccccll"
/*
 * units of lem_cutoff,lem_alarm,lem_estimate : 10**-x
 */
काष्ठा smt_p_lem अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_लघु	lem_mib_index ;		/* MIB index */
	u_लघु	lem_phy_index ;		/* 1 .. n */
	u_अक्षर	lem_pad2 ;		/* be nice and make it even . */
	u_अक्षर	lem_cutoff ;		/* 0x4 .. 0xf, शेष 0x7 */
	u_अक्षर	lem_alarm ;		/* 0x4 .. 0xf, शेष 0x8 */
	u_अक्षर	lem_estimate ;		/* 0x0 .. 0xff */
	u_पूर्णांक	lem_reject_ct ;		/* 0x00000000 .. 0xffffffff */
	u_पूर्णांक	lem_ct ;		/* 0x00000000 .. 0xffffffff */
पूर्ण ;

/*
 * P0B : MAC frame counters
 */
#घोषणा SMT_P_MAC_COUNTER 0x000b	/* MAC frame counters */
#घोषणा SWAP_SMT_P_MAC_COUNTER	"ssll"

काष्ठा smt_p_mac_counter अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_लघु	mc_mib_index ;		/* MIB index */
	u_लघु	mc_index ;		/* mac index */
	u_पूर्णांक	mc_receive_ct ;		/* receive counter */
	u_पूर्णांक	mc_transmit_ct ;	/* transmit counter */
पूर्ण ;

/*
 * P0C : MAC frame not copied counter
 */
#घोषणा SMT_P_MAC_FNC	0x000c		/* MAC frame not copied counter */
#घोषणा SWAP_SMT_P_MAC_FNC	"ssl"

काष्ठा smt_p_mac_fnc अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_लघु	nc_mib_index ;		/* MIB index */
	u_लघु	nc_index ;		/* mac index */
	u_पूर्णांक	nc_counter ;		/* not copied counter */
पूर्ण ;


/*
 * P0D : MAC priority values
 */
#घोषणा SMT_P_PRIORITY	0x000d		/* MAC priority values */
#घोषणा SWAP_SMT_P_PRIORITY	"ssl"

काष्ठा smt_p_priority अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_लघु	pr_mib_index ;		/* MIB index */
	u_लघु	pr_index ;		/* mac index */
	u_पूर्णांक	pr_priority[7] ;	/* priority values */
पूर्ण ;

/*
 * P0E : PHY elasticity buffer status
 */
#घोषणा SMT_P_EB	0x000e		/* PHY EB status */
#घोषणा SWAP_SMT_P_EB	"ssl"

काष्ठा smt_p_eb अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_लघु	eb_mib_index ;		/* MIB index */
	u_लघु	eb_index ;		/* phy index */
	u_पूर्णांक	eb_error_ct ;		/* # of eb overflows */
पूर्ण ;

/*
 * P0F : manufacturer field
 */
#घोषणा SMT_P_MANUFACTURER	0x000f	/* manufacturer field */
#घोषणा SWAP_SMT_P_MANUFACTURER	""

काष्ठा smp_p_manufacturer अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_अक्षर mf_data[32] ;		/* OUI + arbitrary data */
पूर्ण ;

/*
 * P10 : user field
 */
#घोषणा SMT_P_USER		0x0010	/* manufacturer field */
#घोषणा SWAP_SMT_P_USER	""

काष्ठा smp_p_user अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_अक्षर us_data[32] ;		/* arbitrary data */
पूर्ण ;



/*
 * P11 : echo data
 */
#घोषणा SMT_P_ECHODATA	0x0011		/* echo data */
#घोषणा SWAP_SMT_P_ECHODATA	""

काष्ठा smt_p_echo अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_अक्षर	ec_data[SMT_MAX_ECHO_LEN-4] ;	/* echo data */
पूर्ण ;

/*
 * P12 : reason code
 */
#घोषणा SMT_P_REASON	0x0012		/* reason code */
#घोषणा SWAP_SMT_P_REASON	"l"

काष्ठा smt_p_reason अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_पूर्णांक	rdf_reason ;		/* CLASS/VERSION */
पूर्ण ;
#घोषणा SMT_RDF_CLASS	0x00000001	/* class not supported */
#घोषणा SMT_RDF_VERSION	0x00000002	/* version not supported */
#घोषणा SMT_RDF_SUCCESS	0x00000003	/* success (PMF) */
#घोषणा SMT_RDF_BADSET	0x00000004	/* bad set count (PMF) */
#घोषणा SMT_RDF_ILLEGAL 0x00000005	/* पढ़ो only (PMF) */
#घोषणा SMT_RDF_NOPARAM	0x6		/* parameter not supported (PMF) */
#घोषणा SMT_RDF_RANGE	0x8		/* out of range */
#घोषणा SMT_RDF_AUTHOR	0x9		/* not authorized */
#घोषणा SMT_RDF_LENGTH	0x0a		/* length error */
#घोषणा SMT_RDF_TOOLONG	0x0b		/* length error */
#घोषणा SMT_RDF_SBA	0x0d		/* SBA denied */

/*
 * P13 : refused frame beginning
 */
#घोषणा SMT_P_REFUSED	0x0013		/* refused frame beginning */
#घोषणा SWAP_SMT_P_REFUSED	"l"

काष्ठा smt_p_refused अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_पूर्णांक	ref_fc ;		/* 3 bytes 0 + FC */
	काष्ठा smt_header	ref_header ;	/* refused header */
पूर्ण ;

/*
 * P14 : supported SMT versions
 */
#घोषणा SMT_P_VERSION	0x0014		/* SMT supported versions */
#घोषणा SWAP_SMT_P_VERSION	"sccss"

काष्ठा smt_p_version अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_लघु	v_pad ;
	u_अक्षर	v_n ;			/* 1 .. 0xff, #versions */
	u_अक्षर	v_index ;		/* 1 .. 0xff, index of op. v. */
	u_लघु	v_version[1] ;		/* list of min. 1 version */
	u_लघु	v_pad2 ;		/* pad अगर necessary */
पूर्ण ;

/*
 * P15 : Resource Type
 */
#घोषणा	SWAP_SMT_P0015		"l"

काष्ठा smt_p_0015 अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_पूर्णांक		res_type ;	/* resource type */
पूर्ण ;

#घोषणा	SYNC_BW		0x00000001L	/* Synchronous Bandwidth */

/*
 * P16 : SBA Command
 */
#घोषणा	SWAP_SMT_P0016		"l"

काष्ठा smt_p_0016 अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_पूर्णांक		sba_cmd ;	/* command क्रम the SBA */
पूर्ण ;

#घोषणा	REQUEST_ALLOCATION	0x1	/* req allocation of sync bandwidth */
#घोषणा	REPORT_ALLOCATION	0x2	/* rep of sync bandwidth allocation */
#घोषणा	CHANGE_ALLOCATION	0x3	/* क्रमces a station using sync band-*/
					/* width to change its current allo-*/
					/* cation */

/*
 * P17 : SBA Payload Request
 */
#घोषणा	SWAP_SMT_P0017		"l"

काष्ठा smt_p_0017 अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	पूर्णांक		sba_pl_req ;	/* total sync bandwidth measured in */
पूर्ण ;					/* bytes per 125 us */

/*
 * P18 : SBA Overhead Request
 */
#घोषणा	SWAP_SMT_P0018		"l"

काष्ठा smt_p_0018 अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	पूर्णांक		sba_ov_req ;	/* total sync bandwidth req क्रम overhead*/
पूर्ण ;					/* measured in bytes per T_Neg */

/*
 * P19 : SBA Allocation Address
 */
#घोषणा	SWAP_SMT_P0019		"s6"

काष्ठा smt_p_0019 अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_लघु		sba_pad ;
	काष्ठा fddi_addr alloc_addr ;	/* Allocation Address */
पूर्ण ;

/*
 * P1A : SBA Category
 */
#घोषणा	SWAP_SMT_P001A		"l"

काष्ठा smt_p_001a अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_पूर्णांक		category ;	/* Allocator defined classअगरication */
पूर्ण ;

/*
 * P1B : Maximum T_Neg
 */
#घोषणा	SWAP_SMT_P001B		"l"

काष्ठा smt_p_001b अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_पूर्णांक		max_t_neg ;	/* दीर्घest T_NEG क्रम the sync service*/
पूर्ण ;

/*
 * P1C : Minimum SBA Segment Size
 */
#घोषणा	SWAP_SMT_P001C		"l"

काष्ठा smt_p_001c अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_पूर्णांक		min_seg_siz ;	/* smallest number of bytes per frame*/
पूर्ण ;

/*
 * P1D : SBA Allocatable
 */
#घोषणा	SWAP_SMT_P001D		"l"

काष्ठा smt_p_001d अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_पूर्णांक		allocatable ;	/* total sync bw available क्रम alloc */
पूर्ण ;

/*
 * P20 0B : frame status capabilities
 * NOTE: not in swap table, is used by smt.c AND PMF table
 */
#घोषणा SMT_P_FSC	0x200b
/* #घोषणा SWAP_SMT_P_FSC	"ssss" */

काष्ठा smt_p_fsc अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_लघु	fsc_pad0 ;
	u_लघु	fsc_mac_index ;		/* mac index 1 .. ff */
	u_लघु	fsc_pad1 ;
	u_लघु	fsc_value ;		/* FSC_TYPE[0-2] */
पूर्ण ;

#घोषणा FSC_TYPE0	0		/* "normal" node (A/C handling) */
#घोषणा FSC_TYPE1	1		/* Special A/C indicator क्रमwarding */
#घोषणा FSC_TYPE2	2		/* Special A/C indicator क्रमwarding */

/*
 * P00 21 : user defined authorization (see pmf.c)
 */
#घोषणा SMT_P_AUTHOR	0x0021

/*
 * notअगरication parameters
 */
#घोषणा SWAP_SMT_P1048	"ll"
काष्ठा smt_p_1048 अणु
	u_पूर्णांक p1048_flag ;
	u_पूर्णांक p1048_cf_state ;
पूर्ण ;

/*
 * NOTE: all 2xxx 3xxx and 4xxx must include the INDEX in the swap string,
 *	even so the INDEX is NOT part of the काष्ठा.
 *	INDEX is alपढ़ोy swapped in pmf.c, क्रमmat in string is '4'
 */
#घोषणा SWAP_SMT_P208C	"4lss66"
काष्ठा smt_p_208c अणु
	u_पूर्णांक			p208c_flag ;
	u_लघु			p208c_pad ;
	u_लघु			p208c_dupcondition ;
	काष्ठा	fddi_addr	p208c_fddiदीर्घ ;
	काष्ठा	fddi_addr	p208c_fddiunaदीर्घ ;
पूर्ण ;

#घोषणा SWAP_SMT_P208D	"4lllll"
काष्ठा smt_p_208d अणु
	u_पूर्णांक			p208d_flag ;
	u_पूर्णांक			p208d_frame_ct ;
	u_पूर्णांक			p208d_error_ct ;
	u_पूर्णांक			p208d_lost_ct ;
	u_पूर्णांक			p208d_ratio ;
पूर्ण ;

#घोषणा SWAP_SMT_P208E	"4llll"
काष्ठा smt_p_208e अणु
	u_पूर्णांक			p208e_flag ;
	u_पूर्णांक			p208e_not_copied ;
	u_पूर्णांक			p208e_copied ;
	u_पूर्णांक			p208e_not_copied_ratio ;
पूर्ण ;

#घोषणा SWAP_SMT_P208F	"4ll6666s6"

काष्ठा smt_p_208f अणु
	u_पूर्णांक			p208f_multiple ;
	u_पूर्णांक			p208f_nacondition ;
	काष्ठा fddi_addr	p208f_old_una ;
	काष्ठा fddi_addr	p208f_new_una ;
	काष्ठा fddi_addr	p208f_old_dna ;
	काष्ठा fddi_addr	p208f_new_dna ;
	u_लघु			p208f_curren_path ;
	काष्ठा fddi_addr	p208f_smt_address ;
पूर्ण ;

#घोषणा SWAP_SMT_P2090	"4lssl"

काष्ठा smt_p_2090 अणु
	u_पूर्णांक			p2090_multiple ;
	u_लघु			p2090_availablepaths ;
	u_लघु			p2090_currentpath ;
	u_पूर्णांक			p2090_requestedpaths ;
पूर्ण ;

/*
 * NOTE:
 * special kludge क्रम parameters 320b,320f,3210
 * these parameters are part of RAF frames
 * RAF frames are parsed in SBA.C and must be swapped
 * PMF.C has special code to aव्योम द्विगुन swapping
 */
#अगर_घोषित	LITTLE_ENDIAN
#घोषणा SBAPATHINDEX	(0x01000000L)
#अन्यथा
#घोषणा SBAPATHINDEX	(0x01L)
#पूर्ण_अगर

#घोषणा	SWAP_SMT_P320B	"42s"

काष्ठा	smt_p_320b अणु
	काष्ठा smt_para para ;	/* generic parameter header */
	u_पूर्णांक	mib_index ;
	u_लघु path_pad ;
	u_लघु	path_index ;
पूर्ण ;

#घोषणा	SWAP_SMT_P320F	"4l"

काष्ठा	smt_p_320f अणु
	काष्ठा smt_para para ;	/* generic parameter header */
	u_पूर्णांक	mib_index ;
	u_पूर्णांक	mib_payload ;
पूर्ण ;

#घोषणा	SWAP_SMT_P3210	"4l"

काष्ठा	smt_p_3210 अणु
	काष्ठा smt_para para ;	/* generic parameter header */
	u_पूर्णांक	mib_index ;
	u_पूर्णांक	mib_overhead ;
पूर्ण ;

#घोषणा SWAP_SMT_P4050	"4l1111ll"

काष्ठा smt_p_4050 अणु
	u_पूर्णांक			p4050_flag ;
	u_अक्षर			p4050_pad ;
	u_अक्षर			p4050_cutoff ;
	u_अक्षर			p4050_alarm ;
	u_अक्षर			p4050_estimate ;
	u_पूर्णांक			p4050_reject_ct ;
	u_पूर्णांक			p4050_ct ;
पूर्ण ;

#घोषणा SWAP_SMT_P4051	"4lssss"
काष्ठा smt_p_4051 अणु
	u_पूर्णांक			p4051_multiple ;
	u_लघु			p4051_porttype ;
	u_लघु			p4051_connectstate ;
	u_लघु			p4051_pc_neighbor ;
	u_लघु			p4051_pc_withhold ;
पूर्ण ;

#घोषणा SWAP_SMT_P4052	"4ll"
काष्ठा smt_p_4052 अणु
	u_पूर्णांक			p4052_flag ;
	u_पूर्णांक			p4052_eberrorcount ;
पूर्ण ;

#घोषणा SWAP_SMT_P4053	"4lsslss"

काष्ठा smt_p_4053 अणु
	u_पूर्णांक			p4053_multiple ;
	u_लघु			p4053_availablepaths ;
	u_लघु			p4053_currentpath ;
	u_पूर्णांक			p4053_requestedpaths ;
	u_लघु			p4053_mytype ;
	u_लघु			p4053_neighbortype ;
पूर्ण ;


#घोषणा SMT_P_SETCOUNT	0x1035
#घोषणा SWAP_SMT_P_SETCOUNT	"l8"

काष्ठा smt_p_setcount अणु
	काष्ठा smt_para	para ;		/* generic parameter header */
	u_पूर्णांक		count ;
	u_अक्षर		बारtamp[8] ;
पूर्ण ;

/*
 * SMT FRAMES
 */

/*
 * NIF : neighbor inक्रमmation frames
 */
काष्ठा smt_nअगर अणु
	काष्ठा smt_header	smt ;		/* generic header */
	काष्ठा smt_p_una	una ;		/* UNA */
	काष्ठा smt_p_sde	sde ;		/* station descriptor */
	काष्ठा smt_p_state	state ;		/* station state */
#अगर_घोषित	SMT6_10
	काष्ठा smt_p_fsc	fsc ;		/* frame status cap. */
#पूर्ण_अगर
पूर्ण ;

/*
 * SIF : station inक्रमmation frames
 */
काष्ठा smt_sअगर_config अणु
	काष्ठा smt_header	smt ;		/* generic header */
	काष्ठा smt_p_बारtamp	ts ;		/* समय stamp */
	काष्ठा smt_p_sde	sde ;		/* station descriptor */
	काष्ठा smt_p_version	version ;	/* supported versions */
	काष्ठा smt_p_state	state ;		/* station state */
	काष्ठा smt_p_policy	policy ;	/* station policy */
	काष्ठा smt_p_latency	latency ;	/* path latency */
	काष्ठा smt_p_neighbor	neighbor ;	/* neighbors, we have only one*/
#अगर_घोषित	OPT_PMF
	काष्ठा smt_p_setcount	setcount ;	 /* Set Count mandatory */
#पूर्ण_अगर
	/* WARNING : path MUST BE LAST FIELD !!! (see smt.c:smt_fill_path) */
	काष्ठा smt_p_path	path ;		/* path descriptor */
पूर्ण ;
#घोषणा SIZखातापूर्ण_SMT_SIF_CONFIG	(माप(काष्ठा smt_sअगर_config)- \
				 माप(काष्ठा smt_p_path))

काष्ठा smt_sअगर_operation अणु
	काष्ठा smt_header	smt ;		/* generic header */
	काष्ठा smt_p_बारtamp	ts ;		/* समय stamp */
	काष्ठा smt_p_mac_status	status ;	/* mac status */
	काष्ठा smt_p_mac_counter mc ;		/* MAC counter */
	काष्ठा smt_p_mac_fnc 	fnc ;		/* MAC frame not copied */
	काष्ठा smp_p_manufacturer man ;		/* manufacturer field */
	काष्ठा smp_p_user	user ;		/* user field */
#अगर_घोषित	OPT_PMF
	काष्ठा smt_p_setcount	setcount ;	 /* Set Count mandatory */
#पूर्ण_अगर
	/* must be last */
	काष्ठा smt_p_lem	lem[];		/* phy lem status */
पूर्ण ;

/*
 * ECF : echo frame
 */
काष्ठा smt_ecf अणु
	काष्ठा smt_header	smt ;		/* generic header */
	काष्ठा smt_p_echo	ec_echo ;	/* echo parameter */
पूर्ण ;
#घोषणा SMT_ECF_LEN	(माप(काष्ठा smt_header)+माप(काष्ठा smt_para))

/*
 * RDF : request denied frame
 */
काष्ठा smt_rdf अणु
	काष्ठा smt_header	smt ;		/* generic header */
	काष्ठा smt_p_reason	reason ;	/* reason code */
	काष्ठा smt_p_version	version ;	/* supported versions */
	काष्ठा smt_p_refused	refused ;	/* refused frame fragment */
पूर्ण ;

/*
 * SBA Request Allocation Response Frame
 */
काष्ठा smt_sba_alc_res अणु
	काष्ठा smt_header	smt ;		/* generic header */
	काष्ठा smt_p_0015	s_type ;	/* resource type */
	काष्ठा smt_p_0016	cmd ;		/* SBA command */
	काष्ठा smt_p_reason	reason ;	/* reason code */
	काष्ठा smt_p_320b	path ;		/* path type */
	काष्ठा smt_p_320f	payload ;	/* current SBA payload */
	काष्ठा smt_p_3210	overhead ;	/* current SBA overhead */
	काष्ठा smt_p_0019	a_addr ;	/* Allocation Address */
	काष्ठा smt_p_001a	cat ;		/* Category - from the request */
	काष्ठा smt_p_001d	alloc ;		/* SBA Allocatable */
पूर्ण ;

/*
 * SBA Request Allocation Request Frame
 */
काष्ठा smt_sba_alc_req अणु
	काष्ठा smt_header	smt ;		/* generic header */
	काष्ठा smt_p_0015	s_type ;	/* resource type */
	काष्ठा smt_p_0016	cmd ;		/* SBA command */
	काष्ठा smt_p_320b	path ;		/* path type */
	काष्ठा smt_p_0017	pl_req ;	/* requested payload */
	काष्ठा smt_p_0018	ov_req ;	/* requested SBA overhead */
	काष्ठा smt_p_320f	payload ;	/* current SBA payload */
	काष्ठा smt_p_3210	overhead ;	/* current SBA overhead */
	काष्ठा smt_p_0019	a_addr ;	/* Allocation Address */
	काष्ठा smt_p_001a	cat ;		/* Category - from the request */
	काष्ठा smt_p_001b	tneg ;		/* max T-NEG */
	काष्ठा smt_p_001c	segm ;		/* minimum segment size */
पूर्ण ;

/*
 * SBA Change Allocation Request Frame
 */
काष्ठा smt_sba_chg अणु
	काष्ठा smt_header	smt ;		/* generic header */
	काष्ठा smt_p_0015	s_type ;	/* resource type */
	काष्ठा smt_p_0016	cmd ;		/* SBA command */
	काष्ठा smt_p_320b	path ;		/* path type */
	काष्ठा smt_p_320f	payload ;	/* current SBA payload */
	काष्ठा smt_p_3210	overhead ;	/* current SBA overhead */
	काष्ठा smt_p_001a	cat ;		/* Category - from the request */
पूर्ण ;

/*
 * SBA Report Allocation Request Frame
 */
काष्ठा smt_sba_rep_req अणु
	काष्ठा smt_header	smt ;		/* generic header */
	काष्ठा smt_p_0015	s_type ;	/* resource type */
	काष्ठा smt_p_0016	cmd ;		/* SBA command */
पूर्ण ;

/*
 * SBA Report Allocation Response Frame
 */
काष्ठा smt_sba_rep_res अणु
	काष्ठा smt_header	smt ;		/* generic header */
	काष्ठा smt_p_0015	s_type ;	/* resource type */
	काष्ठा smt_p_0016	cmd ;		/* SBA command */
	काष्ठा smt_p_320b	path ;		/* path type */
	काष्ठा smt_p_320f	payload ;	/* current SBA payload */
	काष्ठा smt_p_3210	overhead ;	/* current SBA overhead */
पूर्ण ;

/*
 * actions
 */
#घोषणा SMT_STATION_ACTION	1
#घोषणा SMT_STATION_ACTION_CONNECT	0
#घोषणा SMT_STATION_ACTION_DISCONNECT	1
#घोषणा SMT_STATION_ACTION_PATHTEST	2
#घोषणा SMT_STATION_ACTION_SELFTEST	3
#घोषणा SMT_STATION_ACTION_DISABLE_A	4
#घोषणा SMT_STATION_ACTION_DISABLE_B	5
#घोषणा SMT_STATION_ACTION_DISABLE_M	6

#घोषणा SMT_PORT_ACTION		2
#घोषणा SMT_PORT_ACTION_MAINT	0
#घोषणा SMT_PORT_ACTION_ENABLE	1
#घोषणा SMT_PORT_ACTION_DISABLE	2
#घोषणा SMT_PORT_ACTION_START	3
#घोषणा SMT_PORT_ACTION_STOP	4

#पूर्ण_अगर	/* _SMT_ */
