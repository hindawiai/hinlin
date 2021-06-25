<शैली गुरु>
/*
 * Copyright 2014 Cisco Systems, Inc.  All rights reserved.
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

	/* mcpu fw info in mem: (u64)a0=paddr to काष्ठा vnic_devcmd_fw_info */
	CMD_MCPU_FW_INFO        = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 1),

	/* dev-specअगरic block member:
	 *    in: (u16)a0=offset,(u8)a1=size
	 *    out: a0=value */
	CMD_DEV_SPEC            = _CMDC(_CMD_सूची_RW, _CMD_VTYPE_ALL, 2),

	/* stats clear */
	CMD_STATS_CLEAR         = _CMDCNW(_CMD_सूची_NONE, _CMD_VTYPE_ALL, 3),

	/* stats dump in mem: (u64)a0=paddr to stats area,
	 *                    (u16)a1=माप stats area */
	CMD_STATS_DUMP          = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 4),

	/* nic_cfg in (u32)a0 */
	CMD_NIC_CFG             = _CMDCNW(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 16),

	/* set काष्ठा vnic_devcmd_notअगरy buffer in mem:
	 * in:
	 *   (u64)a0=paddr to notअगरy (set paddr=0 to unset)
	 *   (u32)a1 & 0x00000000ffffffff=माप(काष्ठा vnic_devcmd_notअगरy)
	 *   (u16)a1 & 0x0000ffff00000000=पूर्णांकr num (-1 क्रम no पूर्णांकr)
	 * out:
	 *   (u32)a1 = effective size
	 */
	CMD_NOTIFY              = _CMDC(_CMD_सूची_RW, _CMD_VTYPE_ALL, 21),

	/* initiate खोलो sequence (u32)a0=flags (see CMD_OPENF_*) */
	CMD_OPEN		= _CMDCNW(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 23),

	/* खोलो status:
	 *    out: a0=0 खोलो complete, a0=1 खोलो in progress */
	CMD_OPEN_STATUS		= _CMDC(_CMD_सूची_READ, _CMD_VTYPE_ALL, 24),

	/* बंद vnic */
	CMD_CLOSE		= _CMDC(_CMD_सूची_NONE, _CMD_VTYPE_ALL, 25),

	/* initialize भव link: (u32)a0=flags (see CMD_INITF_*) */
	CMD_INIT		= _CMDCNW(_CMD_सूची_READ, _CMD_VTYPE_ALL, 26),

	/* enable भव link */
	CMD_ENABLE		= _CMDCNW(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 28),

	/* enable भव link, रुकोing variant. */
	CMD_ENABLE_WAIT		= _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 28),

	/* disable भव link */
	CMD_DISABLE		= _CMDC(_CMD_सूची_NONE, _CMD_VTYPE_ALL, 29),

	/* stats dump all vnics on uplink in mem: (u64)a0=paddr (u32)a1=uअगर */
	CMD_STATS_DUMP_ALL	= _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 30),

	/* init status:
	 *    out: a0=0 init complete, a0=1 init in progress
	 *         अगर a0=0, a1=त्रुटि_सं */
	CMD_INIT_STATUS		= _CMDC(_CMD_सूची_READ, _CMD_VTYPE_ALL, 31),

	/* unकरो initialize of भव link */
	CMD_DEINIT		= _CMDCNW(_CMD_सूची_NONE, _CMD_VTYPE_ALL, 34),

	/* check fw capability of a cmd:
	 * in:  (u32)a0=cmd
	 * out: (u32)a0=त्रुटि_सं, 0:valid cmd, a1=supported VNIC_STF_* bits */
	CMD_CAPABILITY      = _CMDC(_CMD_सूची_RW, _CMD_VTYPE_ALL, 36),

	/*
	 * Initialization क्रम the devcmd2 पूर्णांकerface.
	 * in: (u64) a0=host result buffer physical address
	 * in: (u16) a1=number of entries in result buffer
	 */
	CMD_INITIALIZE_DEVCMD2 = _CMDC(_CMD_सूची_WRITE, _CMD_VTYPE_ALL, 57)
पूर्ण;

/* flags क्रम CMD_OPEN */
#घोषणा CMD_OPENF_OPROM		0x1	/* खोलो coming from option rom */

/* flags क्रम CMD_INIT */
#घोषणा CMD_INITF_DEFAULT_MAC	0x1	/* init with शेष mac addr */

/* flags क्रम CMD_PACKET_FILTER */
#घोषणा CMD_PFILTER_सूचीECTED		0x01
#घोषणा CMD_PFILTER_MULTICAST		0x02
#घोषणा CMD_PFILTER_BROADCAST		0x04
#घोषणा CMD_PFILTER_PROMISCUOUS		0x08
#घोषणा CMD_PFILTER_ALL_MULTICAST	0x10

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
पूर्ण;

काष्ठा vnic_devcmd_fw_info अणु
	अक्षर fw_version[32];
	अक्षर fw_build[32];
	अक्षर hw_version[32];
	अक्षर hw_serial_number[32];
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
पूर्ण;
#घोषणा VNIC_STF_FATAL_ERR	0x0001	/* fatal fw error */

काष्ठा vnic_devcmd_provinfo अणु
	u8 oui[3];
	u8 type;
	u8 data[];
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


/*
 * Version 2 of the पूर्णांकerface.
 *
 * Some things are carried over, notably the vnic_devcmd_cmd क्रमागत.
 */

/*
 * Flags क्रम vnic_devcmd2.flags
 */

#घोषणा DEVCMD2_FNORESULT       0x1     /* Don't copy result to host */

#घोषणा VNIC_DEVCMD2_NARGS      VNIC_DEVCMD_NARGS
काष्ठा vnic_devcmd2 अणु
	u16 pad;
	u16 flags;
	u32 cmd;                /* same command #घोषणाs as original */
	u64 args[VNIC_DEVCMD2_NARGS];
पूर्ण;

#घोषणा VNIC_DEVCMD2_NRESULTS   VNIC_DEVCMD_NARGS
काष्ठा devcmd2_result अणु
	u64 results[VNIC_DEVCMD2_NRESULTS];
	u32 pad;
	u16 completed_index;    /* पूर्णांकo copy WQ */
	u8  error;              /* same error codes as original */
	u8  color;              /* 0 or 1 as with completion queues */
पूर्ण;

#घोषणा DEVCMD2_RING_SIZE   32
#घोषणा DEVCMD2_DESC_SIZE   128

#घोषणा DEVCMD2_RESULTS_SIZE_MAX   ((1 << 16) - 1)

#पूर्ण_अगर /* _VNIC_DEVCMD_H_ */
