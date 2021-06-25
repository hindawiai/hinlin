<शैली गुरु>
/*
 * Copyright 2008-2010 Cisco Systems, Inc.  All rights reserved.
 * Copyright 2007 Nuova Systems, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#अगर_अघोषित _VNIC_DEVCMD_H_
#घोषणा _VNIC_DEVCMD_H_

#घोषणा _CMD_NBITS      14
#घोषणा _CMD_VTYPEBITS	10
#घोषणा _CMD_FLAGSBITS  6
#घोषणा _CMD_सूचीBITS	2

#घोषणा _CMD_NMASK      ((1 << _CMD_NBITS)-1)
#घोषणा _CMD_VTYPEMASK  ((1 << _CMD_VTYPEBITS)-1)
#घोषणा _CMD_FLAGSMASK  ((1 << _CMD_FLAGSBITS)-1)
#घोषणा _CMD_सूचीMASK    ((1 << _CMD_सूचीBITS)-1)

#घोषणा _CMD_NSHIFT     0
#घोषणा _CMD_VTYPESHIFT (_CMD_NSHIFT+_CMD_NBITS)
#घोषणा _CMD_FLAGSSHIFT (_CMD_VTYPESHIFT+_CMD_VTYPEBITS)
#घोषणा _CMD_सूचीSHIFT   (_CMD_FLAGSSHIFT+_CMD_FLAGSBITS)

/*
 * Direction bits (from host perspective).
 */
#घोषणा _CMD_सूची_NONE   0U
#घोषणा _CMD_सूची_WRITE  1U
#घोषणा _CMD_सूची_READ   2U
#घोषणा _CMD_सूची_RW     (_CMD_सूची_WRITE | _CMD_सूची_READ)

/*
 * Flag bits.
 */
#घोषणा _CMD_FLAGS_NONE 0U
#घोषणा _CMD_FLAGS_NOWAIT 1U

/*
 * vNIC type bits.
 */
#घोषणा _CMD_VTYPE_NONE  0U
#घोषणा _CMD_VTYPE_ENET  1U
#घोषणा _CMD_VTYPE_FC    2U
#घोषणा _CMD_VTYPE_SCSI  4U
#घोषणा _CMD_VTYPE_ALL   (_CMD_VTYPE_ENET | _CMD_VTYPE_FC | _CMD_VTYPE_SCSI)

/*
 * Used to create cmds..
*/
#घोषणा _CMDCF(dir, flags, vtype, nr)  \
	(((dir)   << _CMD_सूचीSHIFT) | \
	((flags) << _CMD_FLAGSSHIFT) | \
	((vtype) << _CMD_VTYPESHIFT) | \
	((nr)    << _CMD_NSHIFT))
#घोषणा _CMDC(dir, vtype, nr)    _CMDCF(dir, 0, vtype, nr)
#घोषणा _CMDCNW(dir, vtype, nr)  _CMDCF(dir, _CMD_FLAGS_NOWAIT, vtype, nr)

/*
 * Used to decode cmds..
*/
#घोषणा _CMD_सूची(cmd)            (((cmd) >> _CMD_सूचीSHIFT) & _CMD_सूचीMASK)
#घोषणा _CMD_FLAGS(cmd)          (((cmd) >> _CMD_FLAGSSHIFT) & _CMD_FLAGSMASK)
#घोषणा _CMD_VTYPE(cmd)          (((cmd) >> _CMD_VTYPESHIFT) & _CMD_VTYPEMASK)
#घोषणा _CMD_N(cmd)              (((cmd) >> _CMD_NSHIFT) & _CMD_NMASK)

क्रमागत vnic_devcmd_cmd अणु
	CMD_NONE                = _CMDC(_CMD_सूची_NONE, _CMD_VTYPE_NONE, 0),

	/*
	 * mcpu fw info in mem:
	 * in:
	 *   (u64)a0=paddr to काष्ठा vnic_devcmd_fw_info
	 * action:
	 *   Fills in काष्ठा vnic_devcmd_fw_info (128 bytes)
	 * note:
	 *   An old definition of CMD_MCPU_FW_INFO
	 */
	CMD_MCPU_FW_INFO_OLD    = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 1),

	/*
	 * mcpu fw info in mem:
	 * in:
	 *   (u64)a0=paddr to काष्ठा vnic_devcmd_fw_info
	 *   (u16)a1=size of the काष्ठाure
	 * out:
	 *	 (u16)a1=0                          क्रम in:a1 = 0,
	 *	         data size actually written क्रम other values.
	 * action:
	 *   Fills in first 128 bytes of vnic_devcmd_fw_info क्रम in:a1 = 0,
	 *            first in:a1 bytes               क्रम 0 < in:a1 <= 132,
	 *            132 bytes                       क्रम other values of in:a1.
	 * note:
	 *   CMD_MCPU_FW_INFO and CMD_MCPU_FW_INFO_OLD have the same क्रमागत 1
	 *   क्रम source compatibility.
	 */
	CMD_MCPU_FW_INFO        = _CMDC(_CMD_सूची_RW, _CMD_VTYPE_ALL, 1),

	/* dev-specअगरic block member:
	 *    in: (u16)a0=offset,(u8)a1=size
	 *    out: a0=value */
	CMD_DEV_SPEC            = _CMDC(_CMD_सूची_RW, _CMD_VTYPE_ALL, 2),

	/* stats clear */
	CMD_STATS_CLEAR         = _CMDCNW(_CMD_सूची_NONE, _CMD_VTYPE_ALL, 3),

	/* stats dump in mem: (u64)a0=paddr to stats area,
	 *                    (u16)a1=माप stats area */
	CMD_STATS_DUMP          = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 4),

	/* set Rx packet filter: (u32)a0=filters (see CMD_PFILTER_*) */
	CMD_PACKET_FILTER	= _CMDCNW(_CMD_सूची_WRITE, _CMD_VTYPE_ENET, 7),

	/* set Rx packet filter क्रम all: (u32)a0=filters (see CMD_PFILTER_*) */
	CMD_PACKET_FILTER_ALL   = _CMDCNW(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 7),

	/* hang detection notअगरication */
	CMD_HANG_NOTIFY         = _CMDC(_CMD_सूची_NONE, _CMD_VTYPE_ALL, 8),

	/* MAC address in (u48)a0 */
	CMD_GET_MAC_ADDR        = _CMDC(_CMD_सूची_READ,
					_CMD_VTYPE_ENET | _CMD_VTYPE_FC, 9),

	/* add addr from (u48)a0 */
	CMD_ADDR_ADD            = _CMDCNW(_CMD_सूची_WRITE,
					_CMD_VTYPE_ENET | _CMD_VTYPE_FC, 12),

	/* del addr from (u48)a0 */
	CMD_ADDR_DEL            = _CMDCNW(_CMD_सूची_WRITE,
					_CMD_VTYPE_ENET | _CMD_VTYPE_FC, 13),

	/* add VLAN id in (u16)a0 */
	CMD_VLAN_ADD            = _CMDCNW(_CMD_सूची_WRITE, _CMD_VTYPE_ENET, 14),

	/* del VLAN id in (u16)a0 */
	CMD_VLAN_DEL            = _CMDCNW(_CMD_सूची_WRITE, _CMD_VTYPE_ENET, 15),

	/* nic_cfg (no रुको, always succeeds)
	 * in: (u32)a0
	 *
	 * Capability query:
	 * out: (u64) a0 = 1 अगर a1 is valid
	 *	(u64) a1 = (NIC_CFG bits supported) | (flags << 32)
	 *
	 * flags are CMD_NIC_CFG_CAPF_xxx
	 */
	CMD_NIC_CFG             = _CMDCNW(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 16),
	/* nic_cfg_chk (will वापस error अगर flags are invalid)
	 * in: (u32)a0
	 *
	 * Capability query:
	 * out: (u64) a0 = 1 अगर a1 is valid
	 *	(u64) a1 = (NIC_CFG bits supported) | (flags << 32)
	 *
	 * flags are CMD_NIC_CFG_CAPF_xxx
	 */
	CMD_NIC_CFG_CHK		= _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 16),

	/* जोड़ vnic_rss_key in mem: (u64)a0=paddr, (u16)a1=len */
	CMD_RSS_KEY             = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ENET, 17),

	/* जोड़ vnic_rss_cpu in mem: (u64)a0=paddr, (u16)a1=len */
	CMD_RSS_CPU             = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ENET, 18),

	/* initiate softreset */
	CMD_SOFT_RESET          = _CMDCNW(_CMD_सूची_NONE, _CMD_VTYPE_ALL, 19),

	/* softreset status:
	 *    out: a0=0 reset complete, a0=1 reset in progress */
	CMD_SOFT_RESET_STATUS   = _CMDC(_CMD_सूची_READ, _CMD_VTYPE_ALL, 20),

	/* set काष्ठा vnic_devcmd_notअगरy buffer in mem:
	 * in:
	 *   (u64)a0=paddr to notअगरy (set paddr=0 to unset)
	 *   (u32)a1 & 0x00000000ffffffff=माप(काष्ठा vnic_devcmd_notअगरy)
	 *   (u16)a1 & 0x0000ffff00000000=पूर्णांकr num (-1 क्रम no पूर्णांकr)
	 * out:
	 *   (u32)a1 = effective size
	 */
	CMD_NOTIFY              = _CMDC(_CMD_सूची_RW, _CMD_VTYPE_ALL, 21),

	/* UNDI API: (u64)a0=paddr to s_PXENV_UNDI_ काष्ठा,
	 *           (u8)a1=PXENV_UNDI_xxx */
	CMD_UNDI                = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ENET, 22),

	/* initiate खोलो sequence (u32)a0=flags (see CMD_OPENF_*) */
	CMD_OPEN		= _CMDCNW(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 23),

	/* खोलो status:
	 *    out: a0=0 खोलो complete, a0=1 खोलो in progress */
	CMD_OPEN_STATUS		= _CMDC(_CMD_सूची_READ, _CMD_VTYPE_ALL, 24),

	/* बंद vnic */
	CMD_CLOSE		= _CMDC(_CMD_सूची_NONE, _CMD_VTYPE_ALL, 25),

	/* initialize भव link: (u32)a0=flags (see CMD_INITF_*) */
/***** Replaced by CMD_INIT *****/
	CMD_INIT_v1		= _CMDCNW(_CMD_सूची_READ, _CMD_VTYPE_ALL, 26),

	/* variant of CMD_INIT, with provisioning info
	 *     (u64)a0=paddr of vnic_devcmd_provinfo
	 *     (u32)a1=माप provision info */
	CMD_INIT_PROV_INFO	= _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ENET, 27),

	/* enable भव link */
	CMD_ENABLE		= _CMDCNW(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 28),

	/* enable भव link, रुकोing variant. */
	CMD_ENABLE_WAIT		= _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 28),

	/* disable भव link */
	CMD_DISABLE		= _CMDC(_CMD_सूची_NONE, _CMD_VTYPE_ALL, 29),

	/* stats dump sum of all vnic stats on same uplink in mem:
	 *     (u64)a0=paddr
	 *     (u16)a1=माप stats area */
	CMD_STATS_DUMP_ALL	= _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 30),

	/* init status:
	 *    out: a0=0 init complete, a0=1 init in progress
	 *         अगर a0=0, a1=त्रुटि_सं */
	CMD_INIT_STATUS		= _CMDC(_CMD_सूची_READ, _CMD_VTYPE_ALL, 31),

	/* INT13 API: (u64)a0=paddr to vnic_पूर्णांक13_params काष्ठा
	 *            (u32)a1=INT13_CMD_xxx */
	CMD_INT13               = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_FC, 32),

	/* logical uplink enable/disable: (u64)a0: 0/1=disable/enable */
	CMD_LOGICAL_UPLINK      = _CMDCNW(_CMD_सूची_WRITE, _CMD_VTYPE_ENET, 33),

	/* unकरो initialize of भव link */
	CMD_DEINIT		= _CMDCNW(_CMD_सूची_NONE, _CMD_VTYPE_ALL, 34),

	/* initialize भव link: (u32)a0=flags (see CMD_INITF_*) */
	CMD_INIT		= _CMDCNW(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 35),

	/* check fw capability of a cmd:
	 * in:  (u32)a0=cmd
	 * out: (u32)a0=त्रुटि_सं, 0:valid cmd, a1=supported VNIC_STF_* bits */
	CMD_CAPABILITY		= _CMDC(_CMD_सूची_RW, _CMD_VTYPE_ALL, 36),

	/* persistent binding info
	 * in:  (u64)a0=paddr of arg
	 *      (u32)a1=CMD_PERBI_XXX */
	CMD_PERBI		= _CMDC(_CMD_सूची_RW, _CMD_VTYPE_FC, 37),

	/* Interrupt Assert Register functionality
	 * in: (u16)a0=पूर्णांकerrupt number to निश्चित
	 */
	CMD_IAR			= _CMDCNW(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 38),

	/* initiate hangreset, like softreset after hang detected */
	CMD_HANG_RESET		= _CMDC(_CMD_सूची_NONE, _CMD_VTYPE_ALL, 39),

	/* hangreset status:
	 *    out: a0=0 reset complete, a0=1 reset in progress */
	CMD_HANG_RESET_STATUS   = _CMDC(_CMD_सूची_READ, _CMD_VTYPE_ALL, 40),

	/*
	 * Set hw ingress packet vlan reग_लिखो mode:
	 * in:  (u32)a0=new vlan reग_लिखो mode
	 * out: (u32)a0=old vlan reग_लिखो mode */
	CMD_IG_VLAN_REWRITE_MODE = _CMDC(_CMD_सूची_RW, _CMD_VTYPE_ENET, 41),

	/*
	 * in:  (u16)a0=bdf of target vnic
	 *      (u32)a1=cmd to proxy
	 *      a2-a15=args to cmd in a1
	 * out: (u32)a0=status of proxied cmd
	 *      a1-a15=out args of proxied cmd */
	CMD_PROXY_BY_BDF =	_CMDC(_CMD_सूची_RW, _CMD_VTYPE_ALL, 42),

	/*
	 * As क्रम BY_BDF except a0 is index of hvnlink subordinate vnic
	 * or SR-IOV भव vnic
	 */
	CMD_PROXY_BY_INDEX =    _CMDC(_CMD_सूची_RW, _CMD_VTYPE_ALL, 43),

	/*
	 * For HPP toggle:
	 * adapter-info-get
	 * in:  (u64)a0=phsical address of buffer passed in from caller.
	 *      (u16)a1=size of buffer specअगरied in a0.
	 * out: (u64)a0=phsical address of buffer passed in from caller.
	 *      (u16)a1=actual bytes from VIF-CONFIG-INFO TLV, or
	 *              0 अगर no VIF-CONFIG-INFO TLV was ever received. */
	CMD_CONFIG_INFO_GET     = _CMDC(_CMD_सूची_RW, _CMD_VTYPE_ALL, 44),

	/* INT13 API: (u64)a0=paddr to vnic_पूर्णांक13_params काष्ठा
	 *            (u32)a1=INT13_CMD_xxx
	 */
	CMD_INT13_ALL = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 45),

	/* Set शेष vlan:
	 * in: (u16)a0=new शेष vlan
	 *     (u16)a1=zero क्रम overriding vlan with param a0,
	 *		       non-zero क्रम resetting vlan to the शेष
	 * out: (u16)a0=old शेष vlan
	 */
	CMD_SET_DEFAULT_VLAN = _CMDC(_CMD_सूची_RW, _CMD_VTYPE_ALL, 46),

	/* init_prov_info2:
	 * Variant of CMD_INIT_PROV_INFO, where it will not try to enable
	 * the vnic until CMD_ENABLE2 is issued.
	 *     (u64)a0=paddr of vnic_devcmd_provinfo
	 *     (u32)a1=माप provision info
	 */
	CMD_INIT_PROV_INFO2  = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ENET, 47),

	/* enable2:
	 *      (u32)a0=0                  ==> standby
	 *             =CMD_ENABLE2_ACTIVE ==> active
	 */
	CMD_ENABLE2 = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ENET, 48),

	/*
	 * cmd_status:
	 *     Returns the status of the specअगरied command
	 * Input:
	 *     a0 = command क्रम which status is being queried.
	 *          Possible values are:
	 *              CMD_SOFT_RESET
	 *              CMD_HANG_RESET
	 *              CMD_OPEN
	 *              CMD_INIT
	 *              CMD_INIT_PROV_INFO
	 *              CMD_DEINIT
	 *              CMD_INIT_PROV_INFO2
	 *              CMD_ENABLE2
	 * Output:
	 *     अगर status == STAT_ERROR
	 *        a0 = ERR_ENOTSUPPORTED - status क्रम command in a0 is
	 *                                 not supported
	 *     अगर status == STAT_NONE
	 *        a0 = status of the devcmd specअगरied in a0 as follows.
	 *             ERR_SUCCESS   - command in a0 completed successfully
	 *             ERR_EINPROGRESS - command in a0 is still in progress
	 */
	CMD_STATUS = _CMDC(_CMD_सूची_RW, _CMD_VTYPE_ALL, 49),

	/*
	 * Returns पूर्णांकerrupt coalescing समयr conversion factors.
	 * After calling this devcmd, ENIC driver can convert
	 * पूर्णांकerrupt coalescing समयr in usec पूर्णांकo CPU cycles as follows:
	 *
	 *   पूर्णांकr_समयr_cycles = पूर्णांकr_समयr_usec * multiplier / भागisor
	 *
	 * Interrupt coalescing समयr in usecs can be obtained from
	 * CPU cycles as follows:
	 *
	 *   पूर्णांकr_समयr_usec = पूर्णांकr_समयr_cycles * भागisor / multiplier
	 *
	 * in: none
	 * out: (u32)a0 = multiplier
	 *      (u32)a1 = भागisor
	 *      (u32)a2 = maximum समयr value in usec
	 */
	CMD_INTR_COAL_CONVERT = _CMDC(_CMD_सूची_READ, _CMD_VTYPE_ALL, 50),

	/*
	 * Set the predefined mac address as शेष
	 * in:
	 *   (u48)a0 = mac addr
	 */
	CMD_SET_MAC_ADDR = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ENET, 55),

	/* Update the provisioning info of the given VIF
	 *     (u64)a0=paddr of vnic_devcmd_provinfo
	 *     (u32)a1=माप provision info
	 */
	CMD_PROV_INFO_UPDATE = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ENET, 56),

	/* Initialization क्रम the devcmd2 पूर्णांकerface.
	 * in: (u64) a0 = host result buffer physical address
	 * in: (u16) a1 = number of entries in result buffer
	 */
	CMD_INITIALIZE_DEVCMD2 = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 57),

	/* Add a filter.
	 * in: (u64) a0= filter address
	 *     (u32) a1= size of filter
	 * out: (u32) a0=filter identअगरier
	 */
	CMD_ADD_FILTER = _CMDC(_CMD_सूची_RW, _CMD_VTYPE_ENET, 58),

	/* Delete a filter.
	 * in: (u32) a0=filter identअगरier
	 */
	CMD_DEL_FILTER = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ENET, 59),

	/* Enable a Queue Pair in User space NIC
	 * in: (u32) a0=Queue Pair number
	 *     (u32) a1= command
	 */
	CMD_QP_ENABLE = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ENET, 60),

	/* Disable a Queue Pair in User space NIC
	 * in: (u32) a0=Queue Pair number
	 *     (u32) a1= command
	 */
	CMD_QP_DISABLE = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ENET, 61),

	/* Stats dump Queue Pair in User space NIC
	 * in: (u32) a0=Queue Pair number
	 *     (u64) a1=host buffer addr क्रम status dump
	 *     (u32) a2=length of the buffer
	 */
	CMD_QP_STATS_DUMP = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ENET, 62),

	/* Clear stats क्रम Queue Pair in User space NIC
	 * in: (u32) a0=Queue Pair number
	 */
	CMD_QP_STATS_CLEAR = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ENET, 63),

	/* Use this devcmd क्रम agreeing on the highest common version supported
	 * by both driver and fw क्रम features who need such a facility.
	 * in:	(u64) a0 = feature (driver requests क्रम the supported versions
	 *	on this feature)
	 * out: (u64) a0 = biपंचांगap of all supported versions क्रम that feature
	 */
	CMD_GET_SUPP_FEATURE_VER = _CMDC(_CMD_सूची_RW, _CMD_VTYPE_ENET, 69),

	/* Control (Enable/Disable) overlay offloads on the given vnic
	 * in: (u8) a0 = OVERLAY_FEATURE_NVGRE : NVGRE
	 *	    a0 = OVERLAY_FEATURE_VXLAN : VxLAN
	 * in: (u8) a1 = OVERLAY_OFFLOAD_ENABLE : Enable or
	 *	    a1 = OVERLAY_OFFLOAD_DISABLE : Disable or
	 *	    a1 = OVERLAY_OFFLOAD_ENABLE_V2 : Enable with version 2
	 */
	CMD_OVERLAY_OFFLOAD_CTRL = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ENET, 72),

	/* Configuration of overlay offloads feature on a given vNIC
	 * in: (u8) a0 = DEVCMD_OVERLAY_NVGRE : NVGRE
	 *	    a0 = DEVCMD_OVERLAY_VXLAN : VxLAN
	 * in: (u8) a1 = VXLAN_PORT_UPDATE : VxLAN
	 * in: (u16) a2 = अचिन्हित लघु पूर्णांक port inक्रमmation
	 */
	CMD_OVERLAY_OFFLOAD_CFG = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ENET, 73),
पूर्ण;

/* CMD_ENABLE2 flags */
#घोषणा CMD_ENABLE2_STANDBY 0x0
#घोषणा CMD_ENABLE2_ACTIVE  0x1

/* flags क्रम CMD_OPEN */
#घोषणा CMD_OPENF_OPROM		0x1	/* खोलो coming from option rom */
#घोषणा CMD_OPENF_IG_DESCCACHE	0x2	/* Do not flush IG DESC cache */

/* flags क्रम CMD_INIT */
#घोषणा CMD_INITF_DEFAULT_MAC	0x1	/* init with शेष mac addr */

/* flags क्रम CMD_PACKET_FILTER */
#घोषणा CMD_PFILTER_सूचीECTED		0x01
#घोषणा CMD_PFILTER_MULTICAST		0x02
#घोषणा CMD_PFILTER_BROADCAST		0x04
#घोषणा CMD_PFILTER_PROMISCUOUS		0x08
#घोषणा CMD_PFILTER_ALL_MULTICAST	0x10

/* Commands क्रम CMD_QP_ENABLE/CM_QP_DISABLE */
#घोषणा CMD_QP_RQWQ                     0x0

/* reग_लिखो modes क्रम CMD_IG_VLAN_REWRITE_MODE */
#घोषणा IG_VLAN_REWRITE_MODE_DEFAULT_TRUNK              0
#घोषणा IG_VLAN_REWRITE_MODE_UNTAG_DEFAULT_VLAN         1
#घोषणा IG_VLAN_REWRITE_MODE_PRIORITY_TAG_DEFAULT_VLAN  2
#घोषणा IG_VLAN_REWRITE_MODE_PASS_THRU                  3

क्रमागत vnic_devcmd_status अणु
	STAT_NONE = 0,
	STAT_BUSY = 1 << 0,	/* cmd in progress */
	STAT_ERROR = 1 << 1,	/* last cmd caused error (code in a0) */
पूर्ण;

क्रमागत vnic_devcmd_error अणु
	ERR_SUCCESS = 0,
	ERR_EINVAL = 1,
	ERR_EFAULT = 2,
	ERR_EPERM = 3,
	ERR_EBUSY = 4,
	ERR_ECMDUNKNOWN = 5,
	ERR_EBADSTATE = 6,
	ERR_ENOMEM = 7,
	ERR_ETIMEDOUT = 8,
	ERR_ELINKDOWN = 9,
	ERR_EMAXRES = 10,
	ERR_ENOTSUPPORTED = 11,
	ERR_EINPROGRESS = 12,
	ERR_MAX
पूर्ण;

/*
 * note: hw_version and asic_rev refer to the same thing,
 *       but have dअगरferent क्रमmats. hw_version is
 *       a 32-byte string (e.g. "A2") and asic_rev is
 *       a 16-bit पूर्णांकeger (e.g. 0xA2).
 */
काष्ठा vnic_devcmd_fw_info अणु
	अक्षर fw_version[32];
	अक्षर fw_build[32];
	अक्षर hw_version[32];
	अक्षर hw_serial_number[32];
	u16 asic_type;
	u16 asic_rev;
पूर्ण;

काष्ठा vnic_devcmd_notअगरy अणु
	u32 csum;		/* checksum over following words */

	u32 link_state;		/* link up == 1 */
	u32 port_speed;		/* effective port speed (rate limit) */
	u32 mtu;		/* MTU */
	u32 msglvl;		/* requested driver msg lvl */
	u32 uअगर;		/* uplink पूर्णांकerface */
	u32 status;		/* status bits (see VNIC_STF_*) */
	u32 error;		/* error code (see ERR_*) क्रम first ERR */
	u32 link_करोwn_cnt;	/* running count of link करोwn transitions */
	u32 perbi_rebuild_cnt;	/* running count of perbi rebuilds */
पूर्ण;
#घोषणा VNIC_STF_FATAL_ERR	0x0001	/* fatal fw error */
#घोषणा VNIC_STF_STD_PAUSE	0x0002	/* standard link-level छोड़ो on */
#घोषणा VNIC_STF_PFC_PAUSE	0x0004	/* priority flow control छोड़ो on */
/* all supported status flags */
#घोषणा VNIC_STF_ALL		(VNIC_STF_FATAL_ERR |\
				 VNIC_STF_STD_PAUSE |\
				 VNIC_STF_PFC_PAUSE |\
				 0)

काष्ठा vnic_devcmd_provinfo अणु
	u8 oui[3];
	u8 type;
	u8 data[];
पूर्ण;

/* These are used in flags field of dअगरferent filters to denote
 * valid fields used.
 */
#घोषणा FILTER_FIELD_VALID(fld) (1 << (fld - 1))

#घोषणा FILTER_FIELDS_USNIC ( \
			FILTER_FIELD_VALID(1) | \
			FILTER_FIELD_VALID(2) | \
			FILTER_FIELD_VALID(3) | \
			FILTER_FIELD_VALID(4))

#घोषणा FILTER_FIELDS_IPV4_5TUPLE ( \
			FILTER_FIELD_VALID(1) | \
			FILTER_FIELD_VALID(2) | \
			FILTER_FIELD_VALID(3) | \
			FILTER_FIELD_VALID(4) | \
			FILTER_FIELD_VALID(5))

#घोषणा FILTER_FIELDS_MAC_VLAN ( \
			FILTER_FIELD_VALID(1) | \
			FILTER_FIELD_VALID(2))

#घोषणा FILTER_FIELD_USNIC_VLAN    FILTER_FIELD_VALID(1)
#घोषणा FILTER_FIELD_USNIC_ETHTYPE FILTER_FIELD_VALID(2)
#घोषणा FILTER_FIELD_USNIC_PROTO   FILTER_FIELD_VALID(3)
#घोषणा FILTER_FIELD_USNIC_ID      FILTER_FIELD_VALID(4)

काष्ठा filter_usnic_id अणु
	u32 flags;
	u16 vlan;
	u16 ethtype;
	u8 proto_version;
	u32 usnic_id;
पूर्ण __packed;

#घोषणा FILTER_FIELD_5TUP_PROTO  FILTER_FIELD_VALID(1)
#घोषणा FILTER_FIELD_5TUP_SRC_AD FILTER_FIELD_VALID(2)
#घोषणा FILTER_FIELD_5TUP_DST_AD FILTER_FIELD_VALID(3)
#घोषणा FILTER_FIELD_5TUP_SRC_PT FILTER_FIELD_VALID(4)
#घोषणा FILTER_FIELD_5TUP_DST_PT FILTER_FIELD_VALID(5)

/* Enums क्रम the protocol field. */
क्रमागत protocol_e अणु
	PROTO_UDP = 0,
	PROTO_TCP = 1,
पूर्ण;

काष्ठा filter_ipv4_5tuple अणु
	u32 flags;
	u32 protocol;
	u32 src_addr;
	u32 dst_addr;
	u16 src_port;
	u16 dst_port;
पूर्ण __packed;

#घोषणा FILTER_FIELD_VMQ_VLAN   FILTER_FIELD_VALID(1)
#घोषणा FILTER_FIELD_VMQ_MAC    FILTER_FIELD_VALID(2)

काष्ठा filter_mac_vlan अणु
	u32 flags;
	u16 vlan;
	u8 mac_addr[6];
पूर्ण __packed;

/* Specअगरies the filter_action type. */
क्रमागत अणु
	FILTER_ACTION_RQ_STEERING = 0,
	FILTER_ACTION_MAX
पूर्ण;

काष्ठा filter_action अणु
	u32 type;
	जोड़ अणु
		u32 rq_idx;
	पूर्ण u;
पूर्ण __packed;

/* Specअगरies the filter type. */
क्रमागत filter_type अणु
	FILTER_USNIC_ID = 0,
	FILTER_IPV4_5TUPLE = 1,
	FILTER_MAC_VLAN = 2,
	FILTER_MAX
पूर्ण;

काष्ठा filter अणु
	u32 type;
	जोड़ अणु
		काष्ठा filter_usnic_id usnic;
		काष्ठा filter_ipv4_5tuple ipv4;
		काष्ठा filter_mac_vlan mac_vlan;
	पूर्ण u;
पूर्ण __packed;

क्रमागत अणु
	CLSF_TLV_FILTER = 0,
	CLSF_TLV_ACTION = 1,
पूर्ण;

/* Maximum size of buffer to CMD_ADD_FILTER */
#घोषणा FILTER_MAX_BUF_SIZE 100

काष्ठा filter_tlv अणु
	u32 type;
	u32 length;
	u32 val[];
पूर्ण;

क्रमागत अणु
	CLSF_ADD = 0,
	CLSF_DEL = 1,
पूर्ण;

/*
 * Writing cmd रेजिस्टर causes STAT_BUSY to get set in status रेजिस्टर.
 * When cmd completes, STAT_BUSY will be cleared.
 *
 * If cmd completed successfully STAT_ERROR will be clear
 * and args रेजिस्टरs contain cmd-specअगरic results.
 *
 * If cmd error, STAT_ERROR will be set and args[0] contains error code.
 *
 * status रेजिस्टर is पढ़ो-only.  While STAT_BUSY is set,
 * all other रेजिस्टर contents are पढ़ो-only.
 */

/* Make माप(vnic_devcmd) a घातer-of-2 क्रम I/O BAR. */
#घोषणा VNIC_DEVCMD_NARGS 15
काष्ठा vnic_devcmd अणु
	u32 status;			/* RO */
	u32 cmd;			/* RW */
	u64 args[VNIC_DEVCMD_NARGS];	/* RW cmd args (little-endian) */
पूर्ण;

#घोषणा DEVCMD2_FNORESULT	0x1	/* Don't copy result to host */

#घोषणा VNIC_DEVCMD2_NARGS	VNIC_DEVCMD_NARGS
काष्ठा vnic_devcmd2 अणु
	u16 pad;
	u16 flags;
	u32 cmd;
	u64 args[VNIC_DEVCMD2_NARGS];
पूर्ण;

#घोषणा VNIC_DEVCMD2_NRESULTS	VNIC_DEVCMD_NARGS
काष्ठा devcmd2_result अणु
	u64 results[VNIC_DEVCMD2_NRESULTS];
	u32 pad;
	u16 completed_index;
	u8  error;
	u8  color;
पूर्ण;

#घोषणा DEVCMD2_RING_SIZE	32
#घोषणा DEVCMD2_DESC_SIZE	128

क्रमागत overlay_feature_t अणु
	OVERLAY_FEATURE_NVGRE = 1,
	OVERLAY_FEATURE_VXLAN,
	OVERLAY_FEATURE_MAX,
पूर्ण;

क्रमागत overlay_ofld_cmd अणु
	OVERLAY_OFFLOAD_ENABLE,
	OVERLAY_OFFLOAD_DISABLE,
	OVERLAY_OFFLOAD_ENABLE_P2,
	OVERLAY_OFFLOAD_MAX,
पूर्ण;

#घोषणा OVERLAY_CFG_VXLAN_PORT_UPDATE	0

#घोषणा ENIC_VXLAN_INNER_IPV6		BIT(0)
#घोषणा ENIC_VXLAN_OUTER_IPV6		BIT(1)
#घोषणा ENIC_VXLAN_MULTI_WQ		BIT(2)

/* Use this क्रमागत to get the supported versions क्रम each of these features
 * If you need to use the devcmd_get_supported_feature_version(), add
 * the new feature पूर्णांकo this क्रमागत and install function handler in devcmd.c
 */
क्रमागत vic_feature_t अणु
	VIC_FEATURE_VXLAN,
	VIC_FEATURE_RDMA,
	VIC_FEATURE_VXLAN_PATCH,
	VIC_FEATURE_MAX,
पूर्ण;

#पूर्ण_अगर /* _VNIC_DEVCMD_H_ */
