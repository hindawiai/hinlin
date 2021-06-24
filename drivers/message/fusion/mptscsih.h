<शैली गुरु>
/*
 *  linux/drivers/message/fusion/mptscsih.h
 *      High perक्रमmance SCSI / Fibre Channel SCSI Host device driver.
 *      For use with PCI chip/adapter(s):
 *          LSIFC9xx/LSI409xx Fibre Channel
 *      running LSI Fusion MPT (Message Passing Technology) firmware.
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

#अगर_अघोषित SCSIHOST_H_INCLUDED
#घोषणा SCSIHOST_H_INCLUDED

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	SCSI Public stuff...
 */

#घोषणा MPT_SCANDV_GOOD			(0x00000000) /* must be 0 */
#घोषणा MPT_SCANDV_DID_RESET		(0x00000001)
#घोषणा MPT_SCANDV_SENSE		(0x00000002)
#घोषणा MPT_SCANDV_SOME_ERROR		(0x00000004)
#घोषणा MPT_SCANDV_SELECTION_TIMEOUT	(0x00000008)
#घोषणा MPT_SCANDV_ISSUE_SENSE		(0x00000010)
#घोषणा MPT_SCANDV_FALLBACK		(0x00000020)
#घोषणा MPT_SCANDV_BUSY			(0x00000040)

#घोषणा MPT_SCANDV_MAX_RETRIES		(10)

#घोषणा MPT_ICFLAG_BUF_CAP	0x01	/* ReadBuffer Read Capacity क्रमmat */
#घोषणा MPT_ICFLAG_ECHO		0x02	/* ReadBuffer Echo buffer क्रमmat */
#घोषणा MPT_ICFLAG_EBOS		0x04	/* ReadBuffer Echo buffer has EBOS */
#घोषणा MPT_ICFLAG_PHYS_DISK	0x08	/* Any SCSI IO but करो Phys Disk Format */
#घोषणा MPT_ICFLAG_TAGGED_CMD	0x10	/* Do tagged IO */
#घोषणा MPT_ICFLAG_DID_RESET	0x20	/* Bus Reset occurred with this command */
#घोषणा MPT_ICFLAG_RESERVED	0x40	/* Reserved has been issued */

#घोषणा MPT_SCSI_CMD_PER_DEV_HIGH	64
#घोषणा MPT_SCSI_CMD_PER_DEV_LOW	32

#घोषणा MPT_SCSI_CMD_PER_LUN		7

#घोषणा MPT_SCSI_MAX_SECTORS    8192

/* SCSI driver setup काष्ठाure. Settings can be overridden
 * by command line options.
 */
#घोषणा MPTSCSIH_DOMAIN_VALIDATION      1
#घोषणा MPTSCSIH_MAX_WIDTH              1
#घोषणा MPTSCSIH_MIN_SYNC               0x08
#घोषणा MPTSCSIH_SAF_TE                 0
#घोषणा MPTSCSIH_PT_CLEAR               0

#पूर्ण_अगर


प्रकार काष्ठा _पूर्णांकernal_cmd अणु
	अक्षर		*data;		/* data poपूर्णांकer */
	dma_addr_t	data_dma;	/* data dma address */
	पूर्णांक		size;		/* transfer size */
	u8		cmd;		/* SCSI Op Code */
	u8		channel;	/* bus number */
	u8		id;		/* SCSI ID (भव) */
	u64		lun;
	u8		flags;		/* Bit Field - See above */
	u8		physDiskNum;	/* Phys disk number, -1 अन्यथा */
	u8		rsvd2;
	u8		rsvd;
पूर्ण INTERNAL_CMD;

बाह्य व्योम mptscsih_हटाओ(काष्ठा pci_dev *);
बाह्य व्योम mptscsih_shutकरोwn(काष्ठा pci_dev *);
#अगर_घोषित CONFIG_PM
बाह्य पूर्णांक mptscsih_suspend(काष्ठा pci_dev *pdev, pm_message_t state);
बाह्य पूर्णांक mptscsih_resume(काष्ठा pci_dev *pdev);
#पूर्ण_अगर
बाह्य पूर्णांक mptscsih_show_info(काष्ठा seq_file *, काष्ठा Scsi_Host *);
बाह्य स्थिर अक्षर * mptscsih_info(काष्ठा Scsi_Host *SChost);
बाह्य पूर्णांक mptscsih_qcmd(काष्ठा scsi_cmnd *SCpnt);
बाह्य पूर्णांक mptscsih_IssueTaskMgmt(MPT_SCSI_HOST *hd, u8 type, u8 channel,
	u8 id, u64 lun, पूर्णांक ctx2पात, uदीर्घ समयout);
बाह्य व्योम mptscsih_slave_destroy(काष्ठा scsi_device *device);
बाह्य पूर्णांक mptscsih_slave_configure(काष्ठा scsi_device *device);
बाह्य पूर्णांक mptscsih_पात(काष्ठा scsi_cmnd * SCpnt);
बाह्य पूर्णांक mptscsih_dev_reset(काष्ठा scsi_cmnd * SCpnt);
बाह्य पूर्णांक mptscsih_bus_reset(काष्ठा scsi_cmnd * SCpnt);
बाह्य पूर्णांक mptscsih_host_reset(काष्ठा scsi_cmnd *SCpnt);
बाह्य पूर्णांक mptscsih_bios_param(काष्ठा scsi_device * sdev, काष्ठा block_device *bdev, sector_t capacity, पूर्णांक geom[]);
बाह्य पूर्णांक mptscsih_io_करोne(MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf, MPT_FRAME_HDR *r);
बाह्य पूर्णांक mptscsih_taskmgmt_complete(MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf, MPT_FRAME_HDR *r);
बाह्य पूर्णांक mptscsih_scandv_complete(MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf, MPT_FRAME_HDR *r);
बाह्य पूर्णांक mptscsih_event_process(MPT_ADAPTER *ioc, EventNotअगरicationReply_t *pEvReply);
बाह्य पूर्णांक mptscsih_ioc_reset(MPT_ADAPTER *ioc, पूर्णांक post_reset);
बाह्य पूर्णांक mptscsih_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक qdepth);
बाह्य u8 mptscsih_raid_id_to_num(MPT_ADAPTER *ioc, u8 channel, u8 id);
बाह्य पूर्णांक mptscsih_is_phys_disk(MPT_ADAPTER *ioc, u8 channel, u8 id);
बाह्य काष्ठा device_attribute *mptscsih_host_attrs[];
बाह्य काष्ठा scsi_cmnd	*mptscsih_get_scsi_lookup(MPT_ADAPTER *ioc, पूर्णांक i);
बाह्य व्योम mptscsih_taskmgmt_response_code(MPT_ADAPTER *ioc, u8 response_code);
बाह्य व्योम mptscsih_flush_running_cmds(MPT_SCSI_HOST *hd);
