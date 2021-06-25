<शैली गुरु>
/*
 *  linux/drivers/message/fusion/mptsas.h
 *      High perक्रमmance SCSI + LAN / Fibre Channel device drivers.
 *      For use with PCI chip/adapter(s):
 *          LSIFC9xx/LSI409xx Fibre Channel
 *      running LSI MPT (Message Passing Technology) firmware.
 *
 *  Copyright (c) 1999-2008 LSI Corporation
 *  (mailto:DL-MPTFusionLinux@lsi.com)
 *
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
    This program is मुक्त software; you can redistribute it and/or modअगरy
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; version 2 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License क्रम more details.

    NO WARRANTY
    THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT
    LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
    MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is
    solely responsible क्रम determining the appropriateness of using and
    distributing the Program and assumes all risks associated with its
    exercise of rights under this Agreement, including but not limited to
    the risks and costs of program errors, damage to or loss of data,
    programs or equipment, and unavailability or पूर्णांकerruption of operations.

    DISCLAIMER OF LIABILITY
    NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
    सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
    TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
    USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
    HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES

    You should have received a copy of the GNU General Public License
    aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#अगर_अघोषित MPTSAS_H_INCLUDED
#घोषणा MPTSAS_H_INCLUDED
/*अणु-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

काष्ठा mptsas_target_reset_event अणु
	काष्ठा list_head 	list;
	EVENT_DATA_SAS_DEVICE_STATUS_CHANGE sas_event_data;
	u8	target_reset_issued;
	अचिन्हित दीर्घ	 समय_count;
पूर्ण;

क्रमागत mptsas_hotplug_action अणु
	MPTSAS_ADD_DEVICE,
	MPTSAS_DEL_DEVICE,
	MPTSAS_ADD_RAID,
	MPTSAS_DEL_RAID,
	MPTSAS_ADD_PHYSDISK,
	MPTSAS_ADD_PHYSDISK_REPROBE,
	MPTSAS_DEL_PHYSDISK,
	MPTSAS_DEL_PHYSDISK_REPROBE,
	MPTSAS_ADD_INACTIVE_VOLUME,
	MPTSAS_IGNORE_EVENT,
पूर्ण;

काष्ठा mptsas_mappingअणु
	u8			id;
	u8			channel;
पूर्ण;

काष्ठा mptsas_device_info अणु
	काष्ठा list_head 	list;
	काष्ठा mptsas_mapping	os;	/* operating प्रणाली mapping*/
	काष्ठा mptsas_mapping	fw;	/* firmware mapping */
	u64			sas_address;
	u32			device_info; /* specअगरic bits क्रम devices */
	u16			slot;		/* enclosure slot id */
	u64			enclosure_logical_id; /*enclosure address */
	u8			is_logical_volume; /* is this logical volume */
	/* this beदीर्घs to volume */
	u8			is_hidden_raid_component;
	/* this valid when is_hidden_raid_component set */
	u8			volume_id;
	/* cached data क्रम a हटाओd device */
	u8			is_cached;
पूर्ण;

काष्ठा mptsas_hotplug_event अणु
	MPT_ADAPTER		*ioc;
	क्रमागत mptsas_hotplug_action event_type;
	u64			sas_address;
	u8			channel;
	u8			id;
	u32			device_info;
	u16			handle;
	u8			phy_id;
	u8			phys_disk_num;		/* hrc - unique index*/
	काष्ठा scsi_device	*sdev;
पूर्ण;

काष्ठा fw_event_work अणु
	काष्ठा list_head 	list;
	काष्ठा delayed_work	 work;
	पूर्णांक			users;
	MPT_ADAPTER	*ioc;
	u32			event;
	u8			retries;
	अक्षर			event_data[] __aligned(4);
पूर्ण;

काष्ठा mptsas_discovery_event अणु
	काष्ठा work_काष्ठा	work;
	MPT_ADAPTER		*ioc;
पूर्ण;

/*
 * SAS topology काष्ठाures
 *
 * The MPT Fusion firmware पूर्णांकerface spपढ़ोs inक्रमmation about the
 * SAS topology over many manufacture pages, thus we need some data
 * काष्ठाure to collect it and process it क्रम the SAS transport class.
 */

काष्ठा mptsas_devinfo अणु
	u16	handle;		/* unique id to address this device */
	u16	handle_parent;	/* unique id to address parent device */
	u16	handle_enclosure; /* enclosure identअगरier of the enclosure */
	u16	slot;		/* physical slot in enclosure */
	u8	phy_id;		/* phy number of parent device */
	u8	port_id;	/* sas physical port this device
				   is assoc'd with */
	u8	id;		/* logical target id of this device */
	u32	phys_disk_num;	/* phys disk id, क्रम csmi-ioctls */
	u8	channel;	/* logical bus number of this device */
	u64	sas_address;    /* WWN of this device,
				   SATA is asचिन्हित by HBA,expander */
	u32	device_info;	/* bitfield detailed info about this device */
	u16	flags;		/* sas device pg0 flags */
पूर्ण;

/*
 * Specअगरic details on ports, wide/narrow
 */
काष्ठा mptsas_portinfo_detailsअणु
	u16	num_phys;	/* number of phys beदीर्घ to this port */
	u64	phy_biपंचांगask; 	/* TODO, extend support क्रम 255 phys */
	काष्ठा sas_rphy *rphy;	/* transport layer rphy object */
	काष्ठा sas_port *port;	/* transport layer port object */
	काष्ठा scsi_target *starget;
	काष्ठा mptsas_portinfo *port_info;
पूर्ण;

काष्ठा mptsas_phyinfo अणु
	u16	handle;			/* unique id to address this */
	u8	phy_id; 		/* phy index */
	u8	port_id; 		/* firmware port identअगरier */
	u8	negotiated_link_rate;	/* nego'd link rate क्रम this phy */
	u8	hw_link_rate; 		/* hardware max/min phys link rate */
	u8	programmed_link_rate;	/* programmed max/min phy link rate */
	u8	sas_port_add_phy;	/* flag to request sas_port_add_phy*/
	काष्ठा mptsas_devinfo identअगरy;	/* poपूर्णांक to phy device info */
	काष्ठा mptsas_devinfo attached;	/* poपूर्णांक to attached device info */
	काष्ठा sas_phy *phy;		/* transport layer phy object */
	काष्ठा mptsas_portinfo *portinfo;
	काष्ठा mptsas_portinfo_details * port_details;
पूर्ण;

काष्ठा mptsas_portinfo अणु
	काष्ठा list_head list;
	u16		num_phys;	/* number of phys */
	काष्ठा mptsas_phyinfo *phy_info;
पूर्ण;

काष्ठा mptsas_enclosure अणु
	u64	enclosure_logical_id;	/* The WWN क्रम the enclosure */
	u16	enclosure_handle;	/* unique id to address this */
	u16	flags;			/* details enclosure management */
	u16	num_slot;		/* num slots */
	u16	start_slot;		/* first slot */
	u8	start_id;		/* starting logical target id */
	u8	start_channel;		/* starting logical channel id */
	u8	sep_id;			/* SEP device logical target id */
	u8	sep_channel;		/* SEP channel logical channel id */
पूर्ण;

/*पूर्ण-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#पूर्ण_अगर
