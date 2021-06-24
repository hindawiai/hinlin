<शैली गुरु>
/*
 *  linux/drivers/message/fusion/mptspi.c
 *      For use with LSI PCI chip/adapter(s)
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
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kdev_t.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>	/* क्रम mdelay */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/reboot.h>	/* notअगरier code */
#समावेश <linux/workqueue.h>
#समावेश <linux/raid_class.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_spi.h>
#समावेश <scsi/scsi_dbg.h>

#समावेश "mptbase.h"
#समावेश "mptscsih.h"

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#घोषणा my_NAME		"Fusion MPT SPI Host driver"
#घोषणा my_VERSION	MPT_LINUX_VERSION_COMMON
#घोषणा MYNAM		"mptspi"

MODULE_AUTHOR(MODULEAUTHOR);
MODULE_DESCRIPTION(my_NAME);
MODULE_LICENSE("GPL");
MODULE_VERSION(my_VERSION);

/* Command line args */
अटल पूर्णांक mpt_saf_te = MPTSCSIH_SAF_TE;
module_param(mpt_saf_te, पूर्णांक, 0);
MODULE_PARM_DESC(mpt_saf_te, " Force enabling SEP Processor: enable=1  (default=MPTSCSIH_SAF_TE=0)");

अटल व्योम mptspi_ग_लिखो_offset(काष्ठा scsi_target *, पूर्णांक);
अटल व्योम mptspi_ग_लिखो_width(काष्ठा scsi_target *, पूर्णांक);
अटल पूर्णांक mptspi_ग_लिखो_spi_device_pg1(काष्ठा scsi_target *,
				       काष्ठा _CONFIG_PAGE_SCSI_DEVICE_1 *);

अटल काष्ठा scsi_transport_ढाँचा *mptspi_transport_ढाँचा = शून्य;

अटल u8	mptspiDoneCtx = MPT_MAX_PROTOCOL_DRIVERS;
अटल u8	mptspiTaskCtx = MPT_MAX_PROTOCOL_DRIVERS;
अटल u8	mptspiInternalCtx = MPT_MAX_PROTOCOL_DRIVERS; /* Used only क्रम पूर्णांकernal commands */

/**
 * 	mptspi_setTargetNegoParms  - Update the target negotiation parameters
 *	@hd: Poपूर्णांकer to a SCSI Host Structure
 *	@target: per target निजी data
 *	@sdev: SCSI device
 *
 * 	Update the target negotiation parameters based on the the Inquiry
 *	data, adapter capabilities, and NVRAM settings.
 **/
अटल व्योम
mptspi_setTargetNegoParms(MPT_SCSI_HOST *hd, VirtTarget *target,
			    काष्ठा scsi_device *sdev)
अणु
	MPT_ADAPTER *ioc = hd->ioc;
	SpiCfgData *pspi_data = &ioc->spi_data;
	पूर्णांक  id = (पूर्णांक) target->id;
	पूर्णांक  nvram;
	u8 width = MPT_NARROW;
	u8 factor = MPT_ASYNC;
	u8 offset = 0;
	u8 nfactor;
	u8 noQas = 1;

	target->negoFlags = pspi_data->noQas;

	अगर (sdev->scsi_level < SCSI_2) अणु
		width = 0;
		factor = MPT_ULTRA2;
		offset = pspi_data->maxSyncOffset;
		target->tflags &= ~MPT_TARGET_FLAGS_Q_YES;
	पूर्ण अन्यथा अणु
		अगर (scsi_device_wide(sdev))
			width = 1;

		अगर (scsi_device_sync(sdev)) अणु
			factor = pspi_data->minSyncFactor;
			अगर (!scsi_device_dt(sdev))
					factor = MPT_ULTRA2;
			अन्यथा अणु
				अगर (!scsi_device_ius(sdev) &&
				    !scsi_device_qas(sdev))
					factor = MPT_ULTRA160;
				अन्यथा अणु
					factor = MPT_ULTRA320;
					अगर (scsi_device_qas(sdev)) अणु
						ddvprपूर्णांकk(ioc,
						prपूर्णांकk(MYIOC_s_DEBUG_FMT "Enabling QAS due to "
						"byte56=%02x on id=%d!\n", ioc->name,
						scsi_device_qas(sdev), id));
						noQas = 0;
					पूर्ण
					अगर (sdev->type == TYPE_TAPE &&
					    scsi_device_ius(sdev))
						target->negoFlags |= MPT_TAPE_NEGO_IDP;
				पूर्ण
			पूर्ण
			offset = pspi_data->maxSyncOffset;

			/* If RAID, never disable QAS
			 * अन्यथा अगर non RAID, करो not disable
			 *   QAS अगर bit 1 is set
			 * bit 1 QAS support, non-raid only
			 * bit 0 IU support
			 */
			अगर (target->raidVolume == 1)
				noQas = 0;
		पूर्ण अन्यथा अणु
			factor = MPT_ASYNC;
			offset = 0;
		पूर्ण
	पूर्ण

	अगर (!sdev->tagged_supported)
		target->tflags &= ~MPT_TARGET_FLAGS_Q_YES;

	/* Update tflags based on NVRAM settings. (SCSI only)
	 */
	अगर (pspi_data->nvram && (pspi_data->nvram[id] != MPT_HOST_NVRAM_INVALID)) अणु
		nvram = pspi_data->nvram[id];
		nfactor = (nvram & MPT_NVRAM_SYNC_MASK) >> 8;

		अगर (width)
			width = nvram & MPT_NVRAM_WIDE_DISABLE ? 0 : 1;

		अगर (offset > 0) अणु
			/* Ensure factor is set to the
			 * maximum of: adapter, nvram, inquiry
			 */
			अगर (nfactor) अणु
				अगर (nfactor < pspi_data->minSyncFactor )
					nfactor = pspi_data->minSyncFactor;

				factor = max(factor, nfactor);
				अगर (factor == MPT_ASYNC)
					offset = 0;
			पूर्ण अन्यथा अणु
				offset = 0;
				factor = MPT_ASYNC;
		पूर्ण
		पूर्ण अन्यथा अणु
			factor = MPT_ASYNC;
		पूर्ण
	पूर्ण

	/* Make sure data is consistent
	 */
	अगर ((!width) && (factor < MPT_ULTRA2))
		factor = MPT_ULTRA2;

	/* Save the data to the target काष्ठाure.
	 */
	target->minSyncFactor = factor;
	target->maxOffset = offset;
	target->maxWidth = width;

	spi_min_period(scsi_target(sdev)) = factor;
	spi_max_offset(scsi_target(sdev)) = offset;
	spi_max_width(scsi_target(sdev)) = width;

	target->tflags |= MPT_TARGET_FLAGS_VALID_NEGO;

	/* Disable unused features.
	 */
	अगर (!width)
		target->negoFlags |= MPT_TARGET_NO_NEGO_WIDE;

	अगर (!offset)
		target->negoFlags |= MPT_TARGET_NO_NEGO_SYNC;

	अगर ( factor > MPT_ULTRA320 )
		noQas = 0;

	अगर (noQas && (pspi_data->noQas == 0)) अणु
		pspi_data->noQas |= MPT_TARGET_NO_NEGO_QAS;
		target->negoFlags |= MPT_TARGET_NO_NEGO_QAS;

		/* Disable QAS in a mixed configuration हाल
		 */

		ddvprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			"Disabling QAS due to noQas=%02x on id=%d!\n", ioc->name, noQas, id));
	पूर्ण
पूर्ण

/**
 * 	mptspi_ग_लिखोIOCPage4  - ग_लिखो IOC Page 4
 *	@hd: Poपूर्णांकer to a SCSI Host Structure
 *	@channel: channel number
 *	@id: ग_लिखो IOC Page4 क्रम this ID & Bus
 *
 *	Return: -EAGAIN अगर unable to obtain a Message Frame
 *		or 0 अगर success.
 *
 *	Remark: We करो not रुको क्रम a वापस, ग_लिखो pages sequentially.
 **/
अटल पूर्णांक
mptspi_ग_लिखोIOCPage4(MPT_SCSI_HOST *hd, u8 channel , u8 id)
अणु
	MPT_ADAPTER		*ioc = hd->ioc;
	Config_t		*pReq;
	IOCPage4_t		*IOCPage4Ptr;
	MPT_FRAME_HDR		*mf;
	dma_addr_t		 dataDma;
	u32			 flagsLength;
	पूर्णांक			 ii;

	/* Get a MF क्रम this command.
	 */
	अगर ((mf = mpt_get_msg_frame(ioc->DoneCtx, ioc)) == शून्य) अणु
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_WARN_FMT
				"writeIOCPage4 : no msg frames!\n",ioc->name));
		वापस -EAGAIN;
	पूर्ण

	/* Set the request and the data poपूर्णांकers.
	 * Place data at end of MF.
	 */
	pReq = (Config_t *)mf;

	/* Complete the request frame (same क्रम all requests).
	 */
	pReq->Action = MPI_CONFIG_ACTION_PAGE_WRITE_CURRENT;
	pReq->Reserved = 0;
	pReq->ChainOffset = 0;
	pReq->Function = MPI_FUNCTION_CONFIG;
	pReq->ExtPageLength = 0;
	pReq->ExtPageType = 0;
	pReq->MsgFlags = 0;
	क्रम (ii=0; ii < 8; ii++) अणु
		pReq->Reserved2[ii] = 0;
	पूर्ण

	IOCPage4Ptr = ioc->spi_data.pIocPg4;
	dataDma = ioc->spi_data.IocPg4_dma;
	ii = IOCPage4Ptr->ActiveSEP++;
	IOCPage4Ptr->SEP[ii].SEPTargetID = id;
	IOCPage4Ptr->SEP[ii].SEPBus = channel;
	pReq->Header = IOCPage4Ptr->Header;
	pReq->PageAddress = cpu_to_le32(id | (channel << 8 ));

	/* Add a SGE to the config request.
	 */
	flagsLength = MPT_SGE_FLAGS_SSIMPLE_WRITE |
		(IOCPage4Ptr->Header.PageLength + ii) * 4;

	ioc->add_sge((अक्षर *)&pReq->PageBufferSGE, flagsLength, dataDma);

	ddvprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		"writeIOCPage4: MaxSEP=%d ActiveSEP=%d id=%d bus=%d\n",
		ioc->name, IOCPage4Ptr->MaxSEP, IOCPage4Ptr->ActiveSEP, id, channel));

	mpt_put_msg_frame(ioc->DoneCtx, ioc, mf);

	वापस 0;
पूर्ण

/**
 *	mptspi_initTarget - Target, LUN alloc/मुक्त functionality.
 *	@hd: Poपूर्णांकer to MPT_SCSI_HOST काष्ठाure
 *	@vtarget: per target निजी data
 *	@sdev: SCSI device
 *
 *	NOTE: It's only SAFE to call this routine अगर data poपूर्णांकs to
 *	sane & valid STANDARD INQUIRY data!
 *
 *	Allocate and initialize memory क्रम this target.
 *	Save inquiry data.
 *
 **/
अटल व्योम
mptspi_initTarget(MPT_SCSI_HOST *hd, VirtTarget *vtarget,
		    काष्ठा scsi_device *sdev)
अणु

	/* Is LUN supported? If so, upper 2 bits will be 0
	* in first byte of inquiry data.
	*/
	अगर (sdev->inq_periph_qual != 0)
		वापस;

	अगर (vtarget == शून्य)
		वापस;

	vtarget->type = sdev->type;

	अगर ((sdev->type == TYPE_PROCESSOR) && (hd->ioc->spi_data.Saf_Te)) अणु
		/* Treat all Processors as SAF-TE अगर
		 * command line option is set */
		vtarget->tflags |= MPT_TARGET_FLAGS_SAF_TE_ISSUED;
		mptspi_ग_लिखोIOCPage4(hd, vtarget->channel, vtarget->id);
	पूर्णअन्यथा अगर ((sdev->type == TYPE_PROCESSOR) &&
		!(vtarget->tflags & MPT_TARGET_FLAGS_SAF_TE_ISSUED )) अणु
		अगर (sdev->inquiry_len > 49 ) अणु
			अगर (sdev->inquiry[44] == 'S' &&
			    sdev->inquiry[45] == 'A' &&
			    sdev->inquiry[46] == 'F' &&
			    sdev->inquiry[47] == '-' &&
			    sdev->inquiry[48] == 'T' &&
			    sdev->inquiry[49] == 'E' ) अणु
				vtarget->tflags |= MPT_TARGET_FLAGS_SAF_TE_ISSUED;
				mptspi_ग_लिखोIOCPage4(hd, vtarget->channel, vtarget->id);
			पूर्ण
		पूर्ण
	पूर्ण
	mptspi_setTargetNegoParms(hd, vtarget, sdev);
पूर्ण

/**
 *	mptspi_is_raid - Determines whether target is beदीर्घing to volume
 *	@hd: Poपूर्णांकer to a SCSI HOST काष्ठाure
 *	@id: target device id
 *
 *	Return:
 *		non-zero = true
 *		zero = false
 *
 */
अटल पूर्णांक
mptspi_is_raid(काष्ठा _MPT_SCSI_HOST *hd, u32 id)
अणु
	पूर्णांक i, rc = 0;
	MPT_ADAPTER *ioc = hd->ioc;

	अगर (!ioc->raid_data.pIocPg2)
		जाओ out;

	अगर (!ioc->raid_data.pIocPg2->NumActiveVolumes)
		जाओ out;
	क्रम (i=0; i < ioc->raid_data.pIocPg2->NumActiveVolumes; i++) अणु
		अगर (ioc->raid_data.pIocPg2->RaidVolume[i].VolumeID == id) अणु
			rc = 1;
			जाओ out;
		पूर्ण
	पूर्ण

 out:
	वापस rc;
पूर्ण

अटल पूर्णांक mptspi_target_alloc(काष्ठा scsi_target *starget)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(&starget->dev);
	काष्ठा _MPT_SCSI_HOST *hd = shost_priv(shost);
	VirtTarget		*vtarget;
	MPT_ADAPTER *ioc;

	अगर (hd == शून्य)
		वापस -ENODEV;

	ioc = hd->ioc;
	vtarget = kzalloc(माप(VirtTarget), GFP_KERNEL);
	अगर (!vtarget)
		वापस -ENOMEM;

	vtarget->ioc_id = ioc->id;
	vtarget->tflags = MPT_TARGET_FLAGS_Q_YES;
	vtarget->id = (u8)starget->id;
	vtarget->channel = (u8)starget->channel;
	vtarget->starget = starget;
	starget->hostdata = vtarget;

	अगर (starget->channel == 1) अणु
		अगर (mptscsih_is_phys_disk(ioc, 0, starget->id) == 0)
			वापस 0;
		vtarget->tflags |= MPT_TARGET_FLAGS_RAID_COMPONENT;
		/* The real channel क्रम this device is zero */
		vtarget->channel = 0;
		/* The actual physdisknum (क्रम RAID passthrough) */
		vtarget->id = mptscsih_raid_id_to_num(ioc, 0,
		    starget->id);
	पूर्ण

	अगर (starget->channel == 0 &&
	    mptspi_is_raid(hd, starget->id)) अणु
		vtarget->raidVolume = 1;
		ddvprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "RAID Volume @ channel=%d id=%d\n", ioc->name, starget->channel,
		    starget->id));
	पूर्ण

	अगर (ioc->spi_data.nvram &&
	    ioc->spi_data.nvram[starget->id] != MPT_HOST_NVRAM_INVALID) अणु
		u32 nvram = ioc->spi_data.nvram[starget->id];
		spi_min_period(starget) = (nvram & MPT_NVRAM_SYNC_MASK) >> MPT_NVRAM_SYNC_SHIFT;
		spi_max_width(starget) = nvram & MPT_NVRAM_WIDE_DISABLE ? 0 : 1;
	पूर्ण अन्यथा अणु
		spi_min_period(starget) = ioc->spi_data.minSyncFactor;
		spi_max_width(starget) = ioc->spi_data.maxBusWidth;
	पूर्ण
	spi_max_offset(starget) = ioc->spi_data.maxSyncOffset;

	spi_offset(starget) = 0;
	spi_period(starget) = 0xFF;
	mptspi_ग_लिखो_width(starget, 0);

	वापस 0;
पूर्ण

अटल व्योम
mptspi_target_destroy(काष्ठा scsi_target *starget)
अणु
	kमुक्त(starget->hostdata);
	starget->hostdata = शून्य;
पूर्ण

/**
 *	mptspi_prपूर्णांक_ग_लिखो_nego - negotiation parameters debug info that is being sent
 *	@hd: Poपूर्णांकer to a SCSI HOST काष्ठाure
 *	@starget: SCSI target
 *	@ii: negotiation parameters
 *
 */
अटल व्योम
mptspi_prपूर्णांक_ग_लिखो_nego(काष्ठा _MPT_SCSI_HOST *hd, काष्ठा scsi_target *starget, u32 ii)
अणु
	ddvprपूर्णांकk(hd->ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "id=%d Requested = 0x%08x"
	    " ( %s factor = 0x%02x @ offset = 0x%02x %s%s%s%s%s%s%s%s)\n",
	    hd->ioc->name, starget->id, ii,
	    ii & MPI_SCSIDEVPAGE0_NP_WIDE ? "Wide ": "",
	    ((ii >> 8) & 0xFF), ((ii >> 16) & 0xFF),
	    ii & MPI_SCSIDEVPAGE0_NP_IU ? "IU ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_DT ? "DT ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_QAS ? "QAS ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_HOLD_MCS ? "HOLDMCS ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_WR_FLOW ? "WRFLOW ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_RD_STRM ? "RDSTRM ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_RTI ? "RTI ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_PCOMP_EN ? "PCOMP ": ""));
पूर्ण

/**
 *	mptspi_prपूर्णांक_पढ़ो_nego - negotiation parameters debug info that is being पढ़ो
 *	@hd: Poपूर्णांकer to a SCSI HOST काष्ठाure
 *	@starget: SCSI target
 *	@ii: negotiation parameters
 *
 */
अटल व्योम
mptspi_prपूर्णांक_पढ़ो_nego(काष्ठा _MPT_SCSI_HOST *hd, काष्ठा scsi_target *starget, u32 ii)
अणु
	ddvprपूर्णांकk(hd->ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "id=%d Read = 0x%08x"
	    " ( %s factor = 0x%02x @ offset = 0x%02x %s%s%s%s%s%s%s%s)\n",
	    hd->ioc->name, starget->id, ii,
	    ii & MPI_SCSIDEVPAGE0_NP_WIDE ? "Wide ": "",
	    ((ii >> 8) & 0xFF), ((ii >> 16) & 0xFF),
	    ii & MPI_SCSIDEVPAGE0_NP_IU ? "IU ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_DT ? "DT ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_QAS ? "QAS ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_HOLD_MCS ? "HOLDMCS ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_WR_FLOW ? "WRFLOW ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_RD_STRM ? "RDSTRM ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_RTI ? "RTI ": "",
	    ii & MPI_SCSIDEVPAGE0_NP_PCOMP_EN ? "PCOMP ": ""));
पूर्ण

अटल पूर्णांक mptspi_पढ़ो_spi_device_pg0(काष्ठा scsi_target *starget,
			     काष्ठा _CONFIG_PAGE_SCSI_DEVICE_0 *pass_pg0)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(&starget->dev);
	काष्ठा _MPT_SCSI_HOST *hd = shost_priv(shost);
	काष्ठा _MPT_ADAPTER *ioc = hd->ioc;
	काष्ठा _CONFIG_PAGE_SCSI_DEVICE_0 *spi_dev_pg0;
	dma_addr_t spi_dev_pg0_dma;
	पूर्णांक size;
	काष्ठा _x_config_parms cfg;
	काष्ठा _CONFIG_PAGE_HEADER hdr;
	पूर्णांक err = -EBUSY;

	/* No SPI parameters क्रम RAID devices */
	अगर (starget->channel == 0 &&
	    mptspi_is_raid(hd, starget->id))
		वापस -1;

	size = ioc->spi_data.sdp0length * 4;
	/*
	अगर (ioc->spi_data.sdp0length & 1)
		size += size + 4;
	size += 2048;
	*/

	spi_dev_pg0 = dma_alloc_coherent(&ioc->pcidev->dev, size, &spi_dev_pg0_dma, GFP_KERNEL);
	अगर (spi_dev_pg0 == शून्य) अणु
		starget_prपूर्णांकk(KERN_ERR, starget, MYIOC_s_FMT
		    "dma_alloc_coherent for parameters failed\n", ioc->name);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&hdr, 0, माप(hdr));

	hdr.PageVersion = ioc->spi_data.sdp0version;
	hdr.PageLength = ioc->spi_data.sdp0length;
	hdr.PageNumber = 0;
	hdr.PageType = MPI_CONFIG_PAGETYPE_SCSI_DEVICE;

	स_रखो(&cfg, 0, माप(cfg));

	cfg.cfghdr.hdr = &hdr;
	cfg.physAddr = spi_dev_pg0_dma;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;
	cfg.dir = 0;
	cfg.pageAddr = starget->id;
	cfg.समयout = 60;

	अगर (mpt_config(ioc, &cfg)) अणु
		starget_prपूर्णांकk(KERN_ERR, starget, MYIOC_s_FMT "mpt_config failed\n", ioc->name);
		जाओ out_मुक्त;
	पूर्ण
	err = 0;
	स_नकल(pass_pg0, spi_dev_pg0, size);

	mptspi_prपूर्णांक_पढ़ो_nego(hd, starget, le32_to_cpu(spi_dev_pg0->NegotiatedParameters));

 out_मुक्त:
	dma_मुक्त_coherent(&ioc->pcidev->dev, size, spi_dev_pg0, spi_dev_pg0_dma);
	वापस err;
पूर्ण

अटल u32 mptspi_getRP(काष्ठा scsi_target *starget)
अणु
	u32 nego = 0;

	nego |= spi_iu(starget) ? MPI_SCSIDEVPAGE1_RP_IU : 0;
	nego |= spi_dt(starget) ? MPI_SCSIDEVPAGE1_RP_DT : 0;
	nego |= spi_qas(starget) ? MPI_SCSIDEVPAGE1_RP_QAS : 0;
	nego |= spi_hold_mcs(starget) ? MPI_SCSIDEVPAGE1_RP_HOLD_MCS : 0;
	nego |= spi_wr_flow(starget) ? MPI_SCSIDEVPAGE1_RP_WR_FLOW : 0;
	nego |= spi_rd_strm(starget) ? MPI_SCSIDEVPAGE1_RP_RD_STRM : 0;
	nego |= spi_rti(starget) ? MPI_SCSIDEVPAGE1_RP_RTI : 0;
	nego |= spi_pcomp_en(starget) ? MPI_SCSIDEVPAGE1_RP_PCOMP_EN : 0;

	nego |= (spi_period(starget) <<  MPI_SCSIDEVPAGE1_RP_SHIFT_MIN_SYNC_PERIOD) & MPI_SCSIDEVPAGE1_RP_MIN_SYNC_PERIOD_MASK;
	nego |= (spi_offset(starget) << MPI_SCSIDEVPAGE1_RP_SHIFT_MAX_SYNC_OFFSET) & MPI_SCSIDEVPAGE1_RP_MAX_SYNC_OFFSET_MASK;
	nego |= spi_width(starget) ?  MPI_SCSIDEVPAGE1_RP_WIDE : 0;

	वापस nego;
पूर्ण

अटल व्योम mptspi_पढ़ो_parameters(काष्ठा scsi_target *starget)
अणु
	पूर्णांक nego;
	काष्ठा _CONFIG_PAGE_SCSI_DEVICE_0 spi_dev_pg0;

	mptspi_पढ़ो_spi_device_pg0(starget, &spi_dev_pg0);

	nego = le32_to_cpu(spi_dev_pg0.NegotiatedParameters);

	spi_iu(starget) = (nego & MPI_SCSIDEVPAGE0_NP_IU) ? 1 : 0;
	spi_dt(starget) = (nego & MPI_SCSIDEVPAGE0_NP_DT) ? 1 : 0;
	spi_qas(starget) = (nego & MPI_SCSIDEVPAGE0_NP_QAS) ? 1 : 0;
	spi_wr_flow(starget) = (nego & MPI_SCSIDEVPAGE0_NP_WR_FLOW) ? 1 : 0;
	spi_rd_strm(starget) = (nego & MPI_SCSIDEVPAGE0_NP_RD_STRM) ? 1 : 0;
	spi_rti(starget) = (nego & MPI_SCSIDEVPAGE0_NP_RTI) ? 1 : 0;
	spi_pcomp_en(starget) = (nego & MPI_SCSIDEVPAGE0_NP_PCOMP_EN) ? 1 : 0;
	spi_hold_mcs(starget) = (nego & MPI_SCSIDEVPAGE0_NP_HOLD_MCS) ? 1 : 0;
	spi_period(starget) = (nego & MPI_SCSIDEVPAGE0_NP_NEG_SYNC_PERIOD_MASK) >> MPI_SCSIDEVPAGE0_NP_SHIFT_SYNC_PERIOD;
	spi_offset(starget) = (nego & MPI_SCSIDEVPAGE0_NP_NEG_SYNC_OFFSET_MASK) >> MPI_SCSIDEVPAGE0_NP_SHIFT_SYNC_OFFSET;
	spi_width(starget) = (nego & MPI_SCSIDEVPAGE0_NP_WIDE) ? 1 : 0;
पूर्ण

अटल पूर्णांक
mptscsih_quiesce_raid(MPT_SCSI_HOST *hd, पूर्णांक quiesce, u8 channel, u8 id)
अणु
	MPT_ADAPTER	*ioc = hd->ioc;
	MpiRaidActionRequest_t	*pReq;
	MPT_FRAME_HDR		*mf;
	पूर्णांक			ret;
	अचिन्हित दीर्घ 	 	समयleft;

	mutex_lock(&ioc->पूर्णांकernal_cmds.mutex);

	/* Get and Populate a मुक्त Frame
	 */
	अगर ((mf = mpt_get_msg_frame(ioc->InternalCtx, ioc)) == शून्य) अणु
		dfailprपूर्णांकk(hd->ioc, prपूर्णांकk(MYIOC_s_WARN_FMT
			"%s: no msg frames!\n", ioc->name, __func__));
		ret = -EAGAIN;
		जाओ out;
	पूर्ण
	pReq = (MpiRaidActionRequest_t *)mf;
	अगर (quiesce)
		pReq->Action = MPI_RAID_ACTION_QUIESCE_PHYS_IO;
	अन्यथा
		pReq->Action = MPI_RAID_ACTION_ENABLE_PHYS_IO;
	pReq->Reserved1 = 0;
	pReq->ChainOffset = 0;
	pReq->Function = MPI_FUNCTION_RAID_ACTION;
	pReq->VolumeID = id;
	pReq->VolumeBus = channel;
	pReq->PhysDiskNum = 0;
	pReq->MsgFlags = 0;
	pReq->Reserved2 = 0;
	pReq->ActionDataWord = 0; /* Reserved क्रम this action */

	ioc->add_sge((अक्षर *)&pReq->ActionDataSGE,
		MPT_SGE_FLAGS_SSIMPLE_READ | 0, (dma_addr_t) -1);

	ddvprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "RAID Volume action=%x channel=%d id=%d\n",
			ioc->name, pReq->Action, channel, id));

	INITIALIZE_MGMT_STATUS(ioc->पूर्णांकernal_cmds.status)
	mpt_put_msg_frame(ioc->InternalCtx, ioc, mf);
	समयleft = रुको_क्रम_completion_समयout(&ioc->पूर्णांकernal_cmds.करोne, 10*HZ);
	अगर (!(ioc->पूर्णांकernal_cmds.status & MPT_MGMT_STATUS_COMMAND_GOOD)) अणु
		ret = -ETIME;
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "%s: TIMED OUT!\n",
		    ioc->name, __func__));
		अगर (ioc->पूर्णांकernal_cmds.status & MPT_MGMT_STATUS_DID_IOCRESET)
			जाओ out;
		अगर (!समयleft) अणु
			prपूर्णांकk(MYIOC_s_WARN_FMT "Issuing Reset from %s!!\n",
			    ioc->name, __func__);
			mpt_HardResetHandler(ioc, CAN_SLEEP);
			mpt_मुक्त_msg_frame(ioc, mf);
		पूर्ण
		जाओ out;
	पूर्ण

	ret = ioc->पूर्णांकernal_cmds.completion_code;

 out:
	CLEAR_MGMT_STATUS(ioc->पूर्णांकernal_cmds.status)
	mutex_unlock(&ioc->पूर्णांकernal_cmds.mutex);
	वापस ret;
पूर्ण

अटल व्योम mptspi_dv_device(काष्ठा _MPT_SCSI_HOST *hd,
			     काष्ठा scsi_device *sdev)
अणु
	VirtTarget *vtarget = scsi_target(sdev)->hostdata;
	MPT_ADAPTER *ioc = hd->ioc;

	/* no DV on RAID devices */
	अगर (sdev->channel == 0 &&
	    mptspi_is_raid(hd, sdev->id))
		वापस;

	/* If this is a piece of a RAID, then quiesce first */
	अगर (sdev->channel == 1 &&
	    mptscsih_quiesce_raid(hd, 1, vtarget->channel, vtarget->id) < 0) अणु
		starget_prपूर्णांकk(KERN_ERR, scsi_target(sdev), MYIOC_s_FMT
		    "Integrated RAID quiesce failed\n", ioc->name);
		वापस;
	पूर्ण

	hd->spi_pending |= (1 << sdev->id);
	spi_dv_device(sdev);
	hd->spi_pending &= ~(1 << sdev->id);

	अगर (sdev->channel == 1 &&
	    mptscsih_quiesce_raid(hd, 0, vtarget->channel, vtarget->id) < 0)
		starget_prपूर्णांकk(KERN_ERR, scsi_target(sdev), MYIOC_s_FMT
		    "Integrated RAID resume failed\n", ioc->name);

	mptspi_पढ़ो_parameters(sdev->sdev_target);
	spi_display_xfer_agreement(sdev->sdev_target);
	mptspi_पढ़ो_parameters(sdev->sdev_target);
पूर्ण

अटल पूर्णांक mptspi_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	MPT_SCSI_HOST *hd = shost_priv(sdev->host);
	VirtTarget		*vtarget;
	VirtDevice		*vdevice;
	काष्ठा scsi_target 	*starget;
	MPT_ADAPTER *ioc = hd->ioc;

	अगर (sdev->channel == 1 &&
		mptscsih_is_phys_disk(ioc, 0, sdev->id) == 0)
			वापस -ENXIO;

	vdevice = kzalloc(माप(VirtDevice), GFP_KERNEL);
	अगर (!vdevice) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "slave_alloc kmalloc(%zd) FAILED!\n",
				ioc->name, माप(VirtDevice));
		वापस -ENOMEM;
	पूर्ण

	vdevice->lun = sdev->lun;
	sdev->hostdata = vdevice;

	starget = scsi_target(sdev);
	vtarget = starget->hostdata;
	vdevice->vtarget = vtarget;
	vtarget->num_luns++;

	अगर (sdev->channel == 1)
		sdev->no_uld_attach = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mptspi_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा _MPT_SCSI_HOST *hd = shost_priv(sdev->host);
	VirtTarget *vtarget = scsi_target(sdev)->hostdata;
	पूर्णांक ret;

	mptspi_initTarget(hd, vtarget, sdev);

	ret = mptscsih_slave_configure(sdev);

	अगर (ret)
		वापस ret;

	ddvprपूर्णांकk(hd->ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "id=%d min_period=0x%02x"
		" max_offset=0x%02x max_width=%d\n", hd->ioc->name,
		sdev->id, spi_min_period(scsi_target(sdev)),
		spi_max_offset(scsi_target(sdev)),
		spi_max_width(scsi_target(sdev))));

	अगर ((sdev->channel == 1 ||
	     !(mptspi_is_raid(hd, sdev->id))) &&
	    !spi_initial_dv(sdev->sdev_target))
		mptspi_dv_device(hd, sdev);

	वापस 0;
पूर्ण

अटल पूर्णांक
mptspi_qcmd(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *SCpnt)
अणु
	काष्ठा _MPT_SCSI_HOST *hd = shost_priv(shost);
	VirtDevice	*vdevice = SCpnt->device->hostdata;
	MPT_ADAPTER *ioc = hd->ioc;

	अगर (!vdevice || !vdevice->vtarget) अणु
		SCpnt->result = DID_NO_CONNECT << 16;
		SCpnt->scsi_करोne(SCpnt);
		वापस 0;
	पूर्ण

	अगर (SCpnt->device->channel == 1 &&
		mptscsih_is_phys_disk(ioc, 0, SCpnt->device->id) == 0) अणु
		SCpnt->result = DID_NO_CONNECT << 16;
		SCpnt->scsi_करोne(SCpnt);
		वापस 0;
	पूर्ण

	अगर (spi_dv_pending(scsi_target(SCpnt->device)))
		ddvprपूर्णांकk(ioc, scsi_prपूर्णांक_command(SCpnt));

	वापस mptscsih_qcmd(SCpnt);
पूर्ण

अटल व्योम mptspi_slave_destroy(काष्ठा scsi_device *sdev)
अणु
	काष्ठा scsi_target *starget = scsi_target(sdev);
	VirtTarget *vtarget = starget->hostdata;
	VirtDevice *vdevice = sdev->hostdata;

	/* Will this be the last lun on a non-raid device? */
	अगर (vtarget->num_luns == 1 && vdevice->configured_lun) अणु
		काष्ठा _CONFIG_PAGE_SCSI_DEVICE_1 pg1;

		/* Async Narrow */
		pg1.RequestedParameters = 0;
		pg1.Reserved = 0;
		pg1.Configuration = 0;

		mptspi_ग_लिखो_spi_device_pg1(starget, &pg1);
	पूर्ण

	mptscsih_slave_destroy(sdev);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा mptspi_driver_ढाँचा = अणु
	.module				= THIS_MODULE,
	.proc_name			= "mptspi",
	.show_info			= mptscsih_show_info,
	.name				= "MPT SPI Host",
	.info				= mptscsih_info,
	.queuecommand			= mptspi_qcmd,
	.target_alloc			= mptspi_target_alloc,
	.slave_alloc			= mptspi_slave_alloc,
	.slave_configure		= mptspi_slave_configure,
	.target_destroy			= mptspi_target_destroy,
	.slave_destroy			= mptspi_slave_destroy,
	.change_queue_depth 		= mptscsih_change_queue_depth,
	.eh_पात_handler		= mptscsih_पात,
	.eh_device_reset_handler	= mptscsih_dev_reset,
	.eh_bus_reset_handler		= mptscsih_bus_reset,
	.eh_host_reset_handler		= mptscsih_host_reset,
	.bios_param			= mptscsih_bios_param,
	.can_queue			= MPT_SCSI_CAN_QUEUE,
	.this_id			= -1,
	.sg_tablesize			= MPT_SCSI_SG_DEPTH,
	.max_sectors			= 8192,
	.cmd_per_lun			= 7,
	.shost_attrs			= mptscsih_host_attrs,
पूर्ण;

अटल पूर्णांक mptspi_ग_लिखो_spi_device_pg1(काष्ठा scsi_target *starget,
			       काष्ठा _CONFIG_PAGE_SCSI_DEVICE_1 *pass_pg1)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(&starget->dev);
	काष्ठा _MPT_SCSI_HOST *hd = shost_priv(shost);
	काष्ठा _MPT_ADAPTER *ioc = hd->ioc;
	काष्ठा _CONFIG_PAGE_SCSI_DEVICE_1 *pg1;
	dma_addr_t pg1_dma;
	पूर्णांक size;
	काष्ठा _x_config_parms cfg;
	काष्ठा _CONFIG_PAGE_HEADER hdr;
	पूर्णांक err = -EBUSY;
	u32 nego_parms;
	u32 period;
	काष्ठा scsi_device *sdev;
	पूर्णांक i;

	/* करोn't allow updating nego parameters on RAID devices */
	अगर (starget->channel == 0 &&
	    mptspi_is_raid(hd, starget->id))
		वापस -1;

	size = ioc->spi_data.sdp1length * 4;

	pg1 = dma_alloc_coherent(&ioc->pcidev->dev, size, &pg1_dma, GFP_KERNEL);
	अगर (pg1 == शून्य) अणु
		starget_prपूर्णांकk(KERN_ERR, starget, MYIOC_s_FMT
		    "dma_alloc_coherent for parameters failed\n", ioc->name);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&hdr, 0, माप(hdr));

	hdr.PageVersion = ioc->spi_data.sdp1version;
	hdr.PageLength = ioc->spi_data.sdp1length;
	hdr.PageNumber = 1;
	hdr.PageType = MPI_CONFIG_PAGETYPE_SCSI_DEVICE;

	स_रखो(&cfg, 0, माप(cfg));

	cfg.cfghdr.hdr = &hdr;
	cfg.physAddr = pg1_dma;
	cfg.action = MPI_CONFIG_ACTION_PAGE_WRITE_CURRENT;
	cfg.dir = 1;
	cfg.pageAddr = starget->id;

	स_नकल(pg1, pass_pg1, size);

	pg1->Header.PageVersion = hdr.PageVersion;
	pg1->Header.PageLength = hdr.PageLength;
	pg1->Header.PageNumber = hdr.PageNumber;
	pg1->Header.PageType = hdr.PageType;

	nego_parms = le32_to_cpu(pg1->RequestedParameters);
	period = (nego_parms & MPI_SCSIDEVPAGE1_RP_MIN_SYNC_PERIOD_MASK) >>
		MPI_SCSIDEVPAGE1_RP_SHIFT_MIN_SYNC_PERIOD;
	अगर (period == 8) अणु
		/* Turn on अंतरभूत data padding क्रम TAPE when running U320 */
		क्रम (i = 0 ; i < 16; i++) अणु
			sdev = scsi_device_lookup_by_target(starget, i);
			अगर (sdev && sdev->type == TYPE_TAPE) अणु
				sdev_prपूर्णांकk(KERN_DEBUG, sdev, MYIOC_s_FMT
					    "IDP:ON\n", ioc->name);
				nego_parms |= MPI_SCSIDEVPAGE1_RP_IDP;
				pg1->RequestedParameters =
				    cpu_to_le32(nego_parms);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	mptspi_prपूर्णांक_ग_लिखो_nego(hd, starget, le32_to_cpu(pg1->RequestedParameters));

	अगर (mpt_config(ioc, &cfg)) अणु
		starget_prपूर्णांकk(KERN_ERR, starget, MYIOC_s_FMT
		    "mpt_config failed\n", ioc->name);
		जाओ out_मुक्त;
	पूर्ण
	err = 0;

 out_मुक्त:
	dma_मुक्त_coherent(&ioc->pcidev->dev, size, pg1, pg1_dma);
	वापस err;
पूर्ण

अटल व्योम mptspi_ग_लिखो_offset(काष्ठा scsi_target *starget, पूर्णांक offset)
अणु
	काष्ठा _CONFIG_PAGE_SCSI_DEVICE_1 pg1;
	u32 nego;

	अगर (offset < 0)
		offset = 0;

	अगर (offset > 255)
		offset = 255;

	अगर (spi_offset(starget) == -1)
		mptspi_पढ़ो_parameters(starget);

	spi_offset(starget) = offset;

	nego = mptspi_getRP(starget);

	pg1.RequestedParameters = cpu_to_le32(nego);
	pg1.Reserved = 0;
	pg1.Configuration = 0;

	mptspi_ग_लिखो_spi_device_pg1(starget, &pg1);
पूर्ण

अटल व्योम mptspi_ग_लिखो_period(काष्ठा scsi_target *starget, पूर्णांक period)
अणु
	काष्ठा _CONFIG_PAGE_SCSI_DEVICE_1 pg1;
	u32 nego;

	अगर (period < 8)
		period = 8;

	अगर (period > 255)
		period = 255;

	अगर (spi_period(starget) == -1)
		mptspi_पढ़ो_parameters(starget);

	अगर (period == 8) अणु
		spi_iu(starget) = 1;
		spi_dt(starget) = 1;
	पूर्ण अन्यथा अगर (period == 9) अणु
		spi_dt(starget) = 1;
	पूर्ण

	spi_period(starget) = period;

	nego = mptspi_getRP(starget);

	pg1.RequestedParameters = cpu_to_le32(nego);
	pg1.Reserved = 0;
	pg1.Configuration = 0;

	mptspi_ग_लिखो_spi_device_pg1(starget, &pg1);
पूर्ण

अटल व्योम mptspi_ग_लिखो_dt(काष्ठा scsi_target *starget, पूर्णांक dt)
अणु
	काष्ठा _CONFIG_PAGE_SCSI_DEVICE_1 pg1;
	u32 nego;

	अगर (spi_period(starget) == -1)
		mptspi_पढ़ो_parameters(starget);

	अगर (!dt && spi_period(starget) < 10)
		spi_period(starget) = 10;

	spi_dt(starget) = dt;

	nego = mptspi_getRP(starget);


	pg1.RequestedParameters = cpu_to_le32(nego);
	pg1.Reserved = 0;
	pg1.Configuration = 0;

	mptspi_ग_लिखो_spi_device_pg1(starget, &pg1);
पूर्ण

अटल व्योम mptspi_ग_लिखो_iu(काष्ठा scsi_target *starget, पूर्णांक iu)
अणु
	काष्ठा _CONFIG_PAGE_SCSI_DEVICE_1 pg1;
	u32 nego;

	अगर (spi_period(starget) == -1)
		mptspi_पढ़ो_parameters(starget);

	अगर (!iu && spi_period(starget) < 9)
		spi_period(starget) = 9;

	spi_iu(starget) = iu;

	nego = mptspi_getRP(starget);

	pg1.RequestedParameters = cpu_to_le32(nego);
	pg1.Reserved = 0;
	pg1.Configuration = 0;

	mptspi_ग_लिखो_spi_device_pg1(starget, &pg1);
पूर्ण

#घोषणा MPTSPI_SIMPLE_TRANSPORT_PARM(parm) 				\
अटल व्योम mptspi_ग_लिखो_##parm(काष्ठा scsi_target *starget, पूर्णांक parm)\
अणु									\
	काष्ठा _CONFIG_PAGE_SCSI_DEVICE_1 pg1;				\
	u32 nego;							\
									\
	spi_##parm(starget) = parm;					\
									\
	nego = mptspi_getRP(starget);					\
									\
	pg1.RequestedParameters = cpu_to_le32(nego);			\
	pg1.Reserved = 0;						\
	pg1.Configuration = 0;						\
									\
	mptspi_ग_लिखो_spi_device_pg1(starget, &pg1);				\
पूर्ण

MPTSPI_SIMPLE_TRANSPORT_PARM(rd_strm)
MPTSPI_SIMPLE_TRANSPORT_PARM(wr_flow)
MPTSPI_SIMPLE_TRANSPORT_PARM(rti)
MPTSPI_SIMPLE_TRANSPORT_PARM(hold_mcs)
MPTSPI_SIMPLE_TRANSPORT_PARM(pcomp_en)

अटल व्योम mptspi_ग_लिखो_qas(काष्ठा scsi_target *starget, पूर्णांक qas)
अणु
	काष्ठा _CONFIG_PAGE_SCSI_DEVICE_1 pg1;
	काष्ठा Scsi_Host *shost = dev_to_shost(&starget->dev);
	काष्ठा _MPT_SCSI_HOST *hd = shost_priv(shost);
	VirtTarget *vtarget = starget->hostdata;
	u32 nego;

	अगर ((vtarget->negoFlags & MPT_TARGET_NO_NEGO_QAS) ||
	    hd->ioc->spi_data.noQas)
		spi_qas(starget) = 0;
	अन्यथा
		spi_qas(starget) = qas;

	nego = mptspi_getRP(starget);

	pg1.RequestedParameters = cpu_to_le32(nego);
	pg1.Reserved = 0;
	pg1.Configuration = 0;

	mptspi_ग_लिखो_spi_device_pg1(starget, &pg1);
पूर्ण

अटल व्योम mptspi_ग_लिखो_width(काष्ठा scsi_target *starget, पूर्णांक width)
अणु
	काष्ठा _CONFIG_PAGE_SCSI_DEVICE_1 pg1;
	u32 nego;

	अगर (!width) अणु
		spi_dt(starget) = 0;
		अगर (spi_period(starget) < 10)
			spi_period(starget) = 10;
	पूर्ण

	spi_width(starget) = width;

	nego = mptspi_getRP(starget);

	pg1.RequestedParameters = cpu_to_le32(nego);
	pg1.Reserved = 0;
	pg1.Configuration = 0;

	mptspi_ग_लिखो_spi_device_pg1(starget, &pg1);
पूर्ण

काष्ठा work_queue_wrapper अणु
	काष्ठा work_काष्ठा	work;
	काष्ठा _MPT_SCSI_HOST	*hd;
	पूर्णांक			disk;
पूर्ण;

अटल व्योम mpt_work_wrapper(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा work_queue_wrapper *wqw =
		container_of(work, काष्ठा work_queue_wrapper, work);
	काष्ठा _MPT_SCSI_HOST *hd = wqw->hd;
	MPT_ADAPTER *ioc = hd->ioc;
	काष्ठा Scsi_Host *shost = ioc->sh;
	काष्ठा scsi_device *sdev;
	पूर्णांक disk = wqw->disk;
	काष्ठा _CONFIG_PAGE_IOC_3 *pg3;

	kमुक्त(wqw);

	mpt_findImVolumes(ioc);
	pg3 = ioc->raid_data.pIocPg3;
	अगर (!pg3)
		वापस;

	shost_क्रम_each_device(sdev,shost) अणु
		काष्ठा scsi_target *starget = scsi_target(sdev);
		VirtTarget *vtarget = starget->hostdata;

		/* only want to search RAID components */
		अगर (sdev->channel != 1)
			जारी;

		/* The id is the raid PhysDiskNum, even अगर
		 * starget->id is the actual target address */
		अगर(vtarget->id != disk)
			जारी;

		starget_prपूर्णांकk(KERN_INFO, vtarget->starget, MYIOC_s_FMT
		    "Integrated RAID requests DV of new device\n", ioc->name);
		mptspi_dv_device(hd, sdev);
	पूर्ण
	shost_prपूर्णांकk(KERN_INFO, shost, MYIOC_s_FMT
	    "Integrated RAID detects new device %d\n", ioc->name, disk);
	scsi_scan_target(&ioc->sh->shost_gendev, 1, disk, 0, SCSI_SCAN_RESCAN);
पूर्ण


अटल व्योम mpt_dv_raid(काष्ठा _MPT_SCSI_HOST *hd, पूर्णांक disk)
अणु
	काष्ठा work_queue_wrapper *wqw = kदो_स्मृति(माप(*wqw), GFP_ATOMIC);
	MPT_ADAPTER *ioc = hd->ioc;

	अगर (!wqw) अणु
		shost_prपूर्णांकk(KERN_ERR, ioc->sh, MYIOC_s_FMT
		    "Failed to act on RAID event for physical disk %d\n",
		    ioc->name, disk);
		वापस;
	पूर्ण
	INIT_WORK(&wqw->work, mpt_work_wrapper);
	wqw->hd = hd;
	wqw->disk = disk;

	schedule_work(&wqw->work);
पूर्ण

अटल पूर्णांक
mptspi_event_process(MPT_ADAPTER *ioc, EventNotअगरicationReply_t *pEvReply)
अणु
	u8 event = le32_to_cpu(pEvReply->Event) & 0xFF;
	काष्ठा _MPT_SCSI_HOST *hd = shost_priv(ioc->sh);

	अगर (ioc->bus_type != SPI)
		वापस 0;

	अगर (hd && event ==  MPI_EVENT_INTEGRATED_RAID) अणु
		पूर्णांक reason
			= (le32_to_cpu(pEvReply->Data[0]) & 0x00FF0000) >> 16;

		अगर (reason == MPI_EVENT_RAID_RC_DOMAIN_VAL_NEEDED) अणु
			पूर्णांक disk = (le32_to_cpu(pEvReply->Data[0]) & 0xFF000000) >> 24;
			mpt_dv_raid(hd, disk);
		पूर्ण
	पूर्ण
	वापस mptscsih_event_process(ioc, pEvReply);
पूर्ण

अटल पूर्णांक
mptspi_deny_binding(काष्ठा scsi_target *starget)
अणु
	काष्ठा _MPT_SCSI_HOST *hd =
		(काष्ठा _MPT_SCSI_HOST *)dev_to_shost(starget->dev.parent)->hostdata;
	वापस ((mptspi_is_raid(hd, starget->id)) &&
		starget->channel == 0) ? 1 : 0;
पूर्ण

अटल काष्ठा spi_function_ढाँचा mptspi_transport_functions = अणु
	.get_offset	= mptspi_पढ़ो_parameters,
	.set_offset	= mptspi_ग_लिखो_offset,
	.show_offset	= 1,
	.get_period	= mptspi_पढ़ो_parameters,
	.set_period	= mptspi_ग_लिखो_period,
	.show_period	= 1,
	.get_width	= mptspi_पढ़ो_parameters,
	.set_width	= mptspi_ग_लिखो_width,
	.show_width	= 1,
	.get_iu		= mptspi_पढ़ो_parameters,
	.set_iu		= mptspi_ग_लिखो_iu,
	.show_iu	= 1,
	.get_dt		= mptspi_पढ़ो_parameters,
	.set_dt		= mptspi_ग_लिखो_dt,
	.show_dt	= 1,
	.get_qas	= mptspi_पढ़ो_parameters,
	.set_qas	= mptspi_ग_लिखो_qas,
	.show_qas	= 1,
	.get_wr_flow	= mptspi_पढ़ो_parameters,
	.set_wr_flow	= mptspi_ग_लिखो_wr_flow,
	.show_wr_flow	= 1,
	.get_rd_strm	= mptspi_पढ़ो_parameters,
	.set_rd_strm	= mptspi_ग_लिखो_rd_strm,
	.show_rd_strm	= 1,
	.get_rti	= mptspi_पढ़ो_parameters,
	.set_rti	= mptspi_ग_लिखो_rti,
	.show_rti	= 1,
	.get_pcomp_en	= mptspi_पढ़ो_parameters,
	.set_pcomp_en	= mptspi_ग_लिखो_pcomp_en,
	.show_pcomp_en	= 1,
	.get_hold_mcs	= mptspi_पढ़ो_parameters,
	.set_hold_mcs	= mptspi_ग_लिखो_hold_mcs,
	.show_hold_mcs	= 1,
	.deny_binding	= mptspi_deny_binding,
पूर्ण;

/****************************************************************************
 * Supported hardware
 */

अटल काष्ठा pci_device_id mptspi_pci_table[] = अणु
	अणु PCI_VENDOR_ID_LSI_LOGIC, MPI_MANUFACTPAGE_DEVID_53C1030,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु PCI_VENDOR_ID_ATTO, MPI_MANUFACTPAGE_DEVID_53C1030,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, MPI_MANUFACTPAGE_DEVID_53C1035,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु0पूर्ण	/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(pci, mptspi_pci_table);


/*
 * renegotiate क्रम a given target
 */
अटल व्योम
mptspi_dv_renegotiate_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा work_queue_wrapper *wqw =
		container_of(work, काष्ठा work_queue_wrapper, work);
	काष्ठा _MPT_SCSI_HOST *hd = wqw->hd;
	काष्ठा scsi_device *sdev;
	काष्ठा scsi_target *starget;
	काष्ठा _CONFIG_PAGE_SCSI_DEVICE_1 pg1;
	u32 nego;
	MPT_ADAPTER *ioc = hd->ioc;

	kमुक्त(wqw);

	अगर (hd->spi_pending) अणु
		shost_क्रम_each_device(sdev, ioc->sh) अणु
			अगर  (hd->spi_pending & (1 << sdev->id))
				जारी;
			starget = scsi_target(sdev);
			nego = mptspi_getRP(starget);
			pg1.RequestedParameters = cpu_to_le32(nego);
			pg1.Reserved = 0;
			pg1.Configuration = 0;
			mptspi_ग_लिखो_spi_device_pg1(starget, &pg1);
		पूर्ण
	पूर्ण अन्यथा अणु
		shost_क्रम_each_device(sdev, ioc->sh)
			mptspi_dv_device(hd, sdev);
	पूर्ण
पूर्ण

अटल व्योम
mptspi_dv_renegotiate(काष्ठा _MPT_SCSI_HOST *hd)
अणु
	काष्ठा work_queue_wrapper *wqw = kदो_स्मृति(माप(*wqw), GFP_ATOMIC);

	अगर (!wqw)
		वापस;

	INIT_WORK(&wqw->work, mptspi_dv_renegotiate_work);
	wqw->hd = hd;

	schedule_work(&wqw->work);
पूर्ण

/*
 * spi module reset handler
 */
अटल पूर्णांक
mptspi_ioc_reset(MPT_ADAPTER *ioc, पूर्णांक reset_phase)
अणु
	पूर्णांक rc;

	rc = mptscsih_ioc_reset(ioc, reset_phase);
	अगर ((ioc->bus_type != SPI) || (!rc))
		वापस rc;

	/* only try to करो a renegotiation अगर we're properly set up
	 * अगर we get an ioc fault on bringup, ioc->sh will be शून्य */
	अगर (reset_phase == MPT_IOC_POST_RESET &&
	    ioc->sh) अणु
		काष्ठा _MPT_SCSI_HOST *hd = shost_priv(ioc->sh);

		mptspi_dv_renegotiate(hd);
	पूर्ण

	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_PM
/*
 * spi module resume handler
 */
अटल पूर्णांक
mptspi_resume(काष्ठा pci_dev *pdev)
अणु
	MPT_ADAPTER 	*ioc = pci_get_drvdata(pdev);
	काष्ठा _MPT_SCSI_HOST *hd = shost_priv(ioc->sh);
	पूर्णांक rc;

	rc = mptscsih_resume(pdev);
	mptspi_dv_renegotiate(hd);

	वापस rc;
पूर्ण
#पूर्ण_अगर

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	mptspi_probe - Installs scsi devices per bus.
 *	@pdev: Poपूर्णांकer to pci_dev काष्ठाure
 *
 *	Returns 0 क्रम success, non-zero क्रम failure.
 *
 */
अटल पूर्णांक
mptspi_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा Scsi_Host	*sh;
	MPT_SCSI_HOST		*hd;
	MPT_ADAPTER 		*ioc;
	अचिन्हित दीर्घ		 flags;
	पूर्णांक			 ii;
	पूर्णांक			 numSGE = 0;
	पूर्णांक			 scale;
	पूर्णांक			 ioc_cap;
	पूर्णांक			error=0;
	पूर्णांक			r;

	अगर ((r = mpt_attach(pdev,id)) != 0)
		वापस r;

	ioc = pci_get_drvdata(pdev);
	ioc->DoneCtx = mptspiDoneCtx;
	ioc->TaskCtx = mptspiTaskCtx;
	ioc->InternalCtx = mptspiInternalCtx;

	/*  Added sanity check on पढ़ोiness of the MPT adapter.
	 */
	अगर (ioc->last_state != MPI_IOC_STATE_OPERATIONAL) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT
		  "Skipping because it's not operational!\n",
		  ioc->name);
		error = -ENODEV;
		जाओ out_mptspi_probe;
	पूर्ण

	अगर (!ioc->active) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT "Skipping because it's disabled!\n",
		  ioc->name);
		error = -ENODEV;
		जाओ out_mptspi_probe;
	पूर्ण

	/*  Sanity check - ensure at least 1 port is INITIATOR capable
	 */
	ioc_cap = 0;
	क्रम (ii=0; ii < ioc->facts.NumberOfPorts; ii++) अणु
		अगर (ioc->pfacts[ii].ProtocolFlags &
		    MPI_PORTFACTS_PROTOCOL_INITIATOR)
			ioc_cap ++;
	पूर्ण

	अगर (!ioc_cap) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT
			"Skipping ioc=%p because SCSI Initiator mode is NOT enabled!\n",
			ioc->name, ioc);
		वापस 0;
	पूर्ण

	sh = scsi_host_alloc(&mptspi_driver_ढाँचा, माप(MPT_SCSI_HOST));

	अगर (!sh) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT
			"Unable to register controller with SCSI subsystem\n",
			ioc->name);
		error = -1;
		जाओ out_mptspi_probe;
        पूर्ण

	/* VMWare emulation करोesn't properly implement WRITE_SAME
	 */
	अगर (pdev->subप्रणाली_venकरोr == 0x15AD)
		sh->no_ग_लिखो_same = 1;

	spin_lock_irqsave(&ioc->FreeQlock, flags);

	/* Attach the SCSI Host to the IOC काष्ठाure
	 */
	ioc->sh = sh;

	sh->io_port = 0;
	sh->n_io_port = 0;
	sh->irq = 0;

	/* set 16 byte cdb's */
	sh->max_cmd_len = 16;

	/* Yikes!  This is important!
	 * Otherwise, by शेष, linux
	 * only scans target IDs 0-7!
	 * pfactsN->MaxDevices unreliable
	 * (not supported in early
	 *	versions of the FW).
	 * max_id = 1 + actual max id,
	 * max_lun = 1 + actual last lun,
	 *	see hosts.h :o(
	 */
	sh->max_id = ioc->devices_per_bus;

	sh->max_lun = MPT_LAST_LUN + 1;
	/*
	 * If RAID Firmware Detected, setup भव channel
	 */
	अगर (ioc->ir_firmware)
		sh->max_channel = 1;
	अन्यथा
		sh->max_channel = 0;
	sh->this_id = ioc->pfacts[0].PortSCSIID;

	/* Required entry.
	 */
	sh->unique_id = ioc->id;

	/* Verअगरy that we won't exceed the maximum
	 * number of chain buffers
	 * We can optimize:  ZZ = req_sz/माप(SGE)
	 * For 32bit SGE's:
	 *  numSGE = 1 + (ZZ-1)*(maxChain -1) + ZZ
	 *               + (req_sz - 64)/माप(SGE)
	 * A slightly dअगरferent algorithm is required क्रम
	 * 64bit SGEs.
	 */
	scale = ioc->req_sz/ioc->SGE_size;
	अगर (ioc->sg_addr_size == माप(u64)) अणु
		numSGE = (scale - 1) *
		  (ioc->facts.MaxChainDepth-1) + scale +
		  (ioc->req_sz - 60) / ioc->SGE_size;
	पूर्ण अन्यथा अणु
		numSGE = 1 + (scale - 1) *
		  (ioc->facts.MaxChainDepth-1) + scale +
		  (ioc->req_sz - 64) / ioc->SGE_size;
	पूर्ण

	अगर (numSGE < sh->sg_tablesize) अणु
		/* Reset this value */
		dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		  "Resetting sg_tablesize to %d from %d\n",
		  ioc->name, numSGE, sh->sg_tablesize));
		sh->sg_tablesize = numSGE;
	पूर्ण

	spin_unlock_irqrestore(&ioc->FreeQlock, flags);

	hd = shost_priv(sh);
	hd->ioc = ioc;

	/* SCSI needs scsi_cmnd lookup table!
	 * (with size equal to req_depth*PtrSz!)
	 */
	ioc->ScsiLookup = kसुस्मृति(ioc->req_depth, माप(व्योम *), GFP_ATOMIC);
	अगर (!ioc->ScsiLookup) अणु
		error = -ENOMEM;
		जाओ out_mptspi_probe;
	पूर्ण
	spin_lock_init(&ioc->scsi_lookup_lock);

	dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "ScsiLookup @ %p\n",
		 ioc->name, ioc->ScsiLookup));

	ioc->spi_data.Saf_Te = mpt_saf_te;
	ddvprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		"saf_te %x\n",
		ioc->name,
		mpt_saf_te));
	ioc->spi_data.noQas = 0;

	hd->last_queue_full = 0;
	hd->spi_pending = 0;

	/* Some versions of the firmware करोn't support page 0; without
	 * that we can't get the parameters */
	अगर (ioc->spi_data.sdp0length != 0)
		sh->transportt = mptspi_transport_ढाँचा;

	error = scsi_add_host (sh, &ioc->pcidev->dev);
	अगर(error) अणु
		dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
		  "scsi_add_host failed\n", ioc->name));
		जाओ out_mptspi_probe;
	पूर्ण

	/*
	 * issue पूर्णांकernal bus reset
	 */
	अगर (ioc->spi_data.bus_reset)
		mptscsih_IssueTaskMgmt(hd,
		    MPI_SCSITASKMGMT_TASKTYPE_RESET_BUS,
		    0, 0, 0, 0, 5);

	scsi_scan_host(sh);
	वापस 0;

out_mptspi_probe:

	mptscsih_हटाओ(pdev);
	वापस error;
पूर्ण

अटल व्योम mptspi_हटाओ(काष्ठा pci_dev *pdev)
अणु
	MPT_ADAPTER *ioc = pci_get_drvdata(pdev);

	scsi_हटाओ_host(ioc->sh);
	mptscsih_हटाओ(pdev);
पूर्ण

अटल काष्ठा pci_driver mptspi_driver = अणु
	.name		= "mptspi",
	.id_table	= mptspi_pci_table,
	.probe		= mptspi_probe,
	.हटाओ		= mptspi_हटाओ,
	.shutकरोwn	= mptscsih_shutकरोwn,
#अगर_घोषित CONFIG_PM
	.suspend	= mptscsih_suspend,
	.resume		= mptspi_resume,
#पूर्ण_अगर
पूर्ण;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptspi_init - Register MPT adapter(s) as SCSI host(s) with SCSI mid-layer.
 *
 *	Returns 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक __init
mptspi_init(व्योम)
अणु
	पूर्णांक error;

	show_mpपंचांगod_ver(my_NAME, my_VERSION);

	mptspi_transport_ढाँचा = spi_attach_transport(&mptspi_transport_functions);
	अगर (!mptspi_transport_ढाँचा)
		वापस -ENODEV;

	mptspiDoneCtx = mpt_रेजिस्टर(mptscsih_io_करोne, MPTSPI_DRIVER,
	    "mptscsih_io_done");
	mptspiTaskCtx = mpt_रेजिस्टर(mptscsih_taskmgmt_complete, MPTSPI_DRIVER,
	    "mptscsih_taskmgmt_complete");
	mptspiInternalCtx = mpt_रेजिस्टर(mptscsih_scandv_complete,
	    MPTSPI_DRIVER, "mptscsih_scandv_complete");

	mpt_event_रेजिस्टर(mptspiDoneCtx, mptspi_event_process);
	mpt_reset_रेजिस्टर(mptspiDoneCtx, mptspi_ioc_reset);

	error = pci_रेजिस्टर_driver(&mptspi_driver);
	अगर (error)
		spi_release_transport(mptspi_transport_ढाँचा);

	वापस error;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptspi_निकास - Unरेजिस्टरs MPT adapter(s)
 */
अटल व्योम __निकास
mptspi_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&mptspi_driver);

	mpt_reset_deरेजिस्टर(mptspiDoneCtx);
	mpt_event_deरेजिस्टर(mptspiDoneCtx);

	mpt_deरेजिस्टर(mptspiInternalCtx);
	mpt_deरेजिस्टर(mptspiTaskCtx);
	mpt_deरेजिस्टर(mptspiDoneCtx);
	spi_release_transport(mptspi_transport_ढाँचा);
पूर्ण

module_init(mptspi_init);
module_निकास(mptspi_निकास);
