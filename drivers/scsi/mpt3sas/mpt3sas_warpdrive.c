<शैली गुरु>
/*
 * Scsi Host Layer क्रम MPT (Message Passing Technology) based controllers
 *
 * Copyright (C) 2012-2014  LSI Corporation
 * Copyright (C) 2013-2015 Avago Technologies
 *  (mailto: MPT-FusionLinux.pdl@avagotech.com)
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * NO WARRANTY
 * THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT
 * LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is
 * solely responsible क्रम determining the appropriateness of using and
 * distributing the Program and assumes all risks associated with its
 * exercise of rights under this Agreement, including but not limited to
 * the risks and costs of program errors, damage to or loss of data,
 * programs or equipment, and unavailability or पूर्णांकerruption of operations.

 * DISCLAIMER OF LIABILITY
 * NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
 * HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES

 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "mpt3sas_base.h"

/**
 * _warpdrive_disable_ddio - Disable direct I/O क्रम all the volumes
 * @ioc: per adapter object
 */
अटल व्योम
_warpdrive_disable_ddio(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi2RaidVolPage1_t vol_pg1;
	Mpi2ConfigReply_t mpi_reply;
	काष्ठा _raid_device *raid_device;
	u16 handle;
	u16 ioc_status;
	अचिन्हित दीर्घ flags;

	handle = 0xFFFF;
	जबतक (!(mpt3sas_config_get_raid_volume_pg1(ioc, &mpi_reply,
	    &vol_pg1, MPI2_RAID_VOLUME_PGAD_FORM_GET_NEXT_HANDLE, handle))) अणु
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		अगर (ioc_status == MPI2_IOCSTATUS_CONFIG_INVALID_PAGE)
			अवरोध;
		handle = le16_to_cpu(vol_pg1.DevHandle);
		spin_lock_irqsave(&ioc->raid_device_lock, flags);
		raid_device = mpt3sas_raid_device_find_by_handle(ioc, handle);
		अगर (raid_device)
			raid_device->direct_io_enabled = 0;
		spin_unlock_irqrestore(&ioc->raid_device_lock, flags);
	पूर्ण
	वापस;
पूर्ण


/**
 * mpt3sas_get_num_volumes - Get number of volumes in the ioc
 * @ioc: per adapter object
 */
u8
mpt3sas_get_num_volumes(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi2RaidVolPage1_t vol_pg1;
	Mpi2ConfigReply_t mpi_reply;
	u16 handle;
	u8 vol_cnt = 0;
	u16 ioc_status;

	handle = 0xFFFF;
	जबतक (!(mpt3sas_config_get_raid_volume_pg1(ioc, &mpi_reply,
	    &vol_pg1, MPI2_RAID_VOLUME_PGAD_FORM_GET_NEXT_HANDLE, handle))) अणु
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		अगर (ioc_status == MPI2_IOCSTATUS_CONFIG_INVALID_PAGE)
			अवरोध;
		vol_cnt++;
		handle = le16_to_cpu(vol_pg1.DevHandle);
	पूर्ण
	वापस vol_cnt;
पूर्ण


/**
 * mpt3sas_init_warpdrive_properties - Set properties क्रम warpdrive direct I/O.
 * @ioc: per adapter object
 * @raid_device: the raid_device object
 */
व्योम
mpt3sas_init_warpdrive_properties(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _raid_device *raid_device)
अणु
	Mpi2RaidVolPage0_t *vol_pg0;
	Mpi2RaidPhysDiskPage0_t pd_pg0;
	Mpi2ConfigReply_t mpi_reply;
	u16 sz;
	u8 num_pds, count;
	अचिन्हित दीर्घ stripe_sz, block_sz;
	u8 stripe_exp, block_exp;
	u64 dev_max_lba;

	अगर (!ioc->is_warpdrive)
		वापस;

	अगर (ioc->mfg_pg10_hide_flag ==  MFG_PAGE10_EXPOSE_ALL_DISKS) अणु
		ioc_info(ioc, "WarpDrive : Direct IO is disabled globally as drives are exposed\n");
		वापस;
	पूर्ण
	अगर (mpt3sas_get_num_volumes(ioc) > 1) अणु
		_warpdrive_disable_ddio(ioc);
		ioc_info(ioc, "WarpDrive : Direct IO is disabled globally as number of drives > 1\n");
		वापस;
	पूर्ण
	अगर ((mpt3sas_config_get_number_pds(ioc, raid_device->handle,
	    &num_pds)) || !num_pds) अणु
		ioc_info(ioc, "WarpDrive : Direct IO is disabled Failure in computing number of drives\n");
		वापस;
	पूर्ण

	sz = दुरत्व(Mpi2RaidVolPage0_t, PhysDisk) + (num_pds *
	    माप(Mpi2RaidVol0PhysDisk_t));
	vol_pg0 = kzalloc(sz, GFP_KERNEL);
	अगर (!vol_pg0) अणु
		ioc_info(ioc, "WarpDrive : Direct IO is disabled Memory allocation failure for RVPG0\n");
		वापस;
	पूर्ण

	अगर ((mpt3sas_config_get_raid_volume_pg0(ioc, &mpi_reply, vol_pg0,
	     MPI2_RAID_VOLUME_PGAD_FORM_HANDLE, raid_device->handle, sz))) अणु
		ioc_info(ioc, "WarpDrive : Direct IO is disabled Failure in retrieving RVPG0\n");
		kमुक्त(vol_pg0);
		वापस;
	पूर्ण

	/*
	 * WARPDRIVE:If number of physical disks in a volume exceeds the max pds
	 * assumed क्रम WARPDRIVE, disable direct I/O
	 */
	अगर (num_pds > MPT_MAX_WARPDRIVE_PDS) अणु
		ioc_warn(ioc, "WarpDrive : Direct IO is disabled for the drive with handle(0x%04x): num_mem=%d, max_mem_allowed=%d\n",
			 raid_device->handle, num_pds, MPT_MAX_WARPDRIVE_PDS);
		kमुक्त(vol_pg0);
		वापस;
	पूर्ण
	क्रम (count = 0; count < num_pds; count++) अणु
		अगर (mpt3sas_config_get_phys_disk_pg0(ioc, &mpi_reply,
		    &pd_pg0, MPI2_PHYSDISK_PGAD_FORM_PHYSDISKNUM,
		    vol_pg0->PhysDisk[count].PhysDiskNum) ||
		    le16_to_cpu(pd_pg0.DevHandle) ==
		    MPT3SAS_INVALID_DEVICE_HANDLE) अणु
			ioc_info(ioc, "WarpDrive : Direct IO is disabled for the drive with handle(0x%04x) member handle retrieval failed for member number=%d\n",
				 raid_device->handle,
				 vol_pg0->PhysDisk[count].PhysDiskNum);
			जाओ out_error;
		पूर्ण
		/* Disable direct I/O अगर member drive lba exceeds 4 bytes */
		dev_max_lba = le64_to_cpu(pd_pg0.DeviceMaxLBA);
		अगर (dev_max_lba >> 32) अणु
			ioc_info(ioc, "WarpDrive : Direct IO is disabled for the drive with handle(0x%04x) member handle (0x%04x) unsupported max lba 0x%016llx\n",
				 raid_device->handle,
				 le16_to_cpu(pd_pg0.DevHandle),
				 (u64)dev_max_lba);
			जाओ out_error;
		पूर्ण

		raid_device->pd_handle[count] = le16_to_cpu(pd_pg0.DevHandle);
	पूर्ण

	/*
	 * Assumption क्रम WD: Direct I/O is not supported अगर the volume is
	 * not RAID0
	 */
	अगर (raid_device->volume_type != MPI2_RAID_VOL_TYPE_RAID0) अणु
		ioc_info(ioc, "WarpDrive : Direct IO is disabled for the drive with handle(0x%04x): type=%d, s_sz=%uK, blk_size=%u\n",
			 raid_device->handle, raid_device->volume_type,
			 (le32_to_cpu(vol_pg0->StripeSize) *
			  le16_to_cpu(vol_pg0->BlockSize)) / 1024,
			 le16_to_cpu(vol_pg0->BlockSize));
		जाओ out_error;
	पूर्ण

	stripe_sz = le32_to_cpu(vol_pg0->StripeSize);
	stripe_exp = find_first_bit(&stripe_sz, 32);
	अगर (stripe_exp == 32) अणु
		ioc_info(ioc, "WarpDrive : Direct IO is disabled for the drive with handle(0x%04x) invalid stripe sz %uK\n",
			 raid_device->handle,
			 (le32_to_cpu(vol_pg0->StripeSize) *
			  le16_to_cpu(vol_pg0->BlockSize)) / 1024);
		जाओ out_error;
	पूर्ण
	raid_device->stripe_exponent = stripe_exp;
	block_sz = le16_to_cpu(vol_pg0->BlockSize);
	block_exp = find_first_bit(&block_sz, 16);
	अगर (block_exp == 16) अणु
		ioc_info(ioc, "WarpDrive : Direct IO is disabled for the drive with handle(0x%04x) invalid block sz %u\n",
			 raid_device->handle, le16_to_cpu(vol_pg0->BlockSize));
		जाओ out_error;
	पूर्ण
	raid_device->block_exponent = block_exp;
	raid_device->direct_io_enabled = 1;

	ioc_info(ioc, "WarpDrive : Direct IO is Enabled for the drive with handle(0x%04x)\n",
		 raid_device->handle);
	/*
	 * WARPDRIVE: Though the following fields are not used क्रम direct IO,
	 * stored क्रम future purpose:
	 */
	raid_device->max_lba = le64_to_cpu(vol_pg0->MaxLBA);
	raid_device->stripe_sz = le32_to_cpu(vol_pg0->StripeSize);
	raid_device->block_sz = le16_to_cpu(vol_pg0->BlockSize);


	kमुक्त(vol_pg0);
	वापस;

out_error:
	raid_device->direct_io_enabled = 0;
	क्रम (count = 0; count < num_pds; count++)
		raid_device->pd_handle[count] = 0;
	kमुक्त(vol_pg0);
	वापस;
पूर्ण

/**
 * mpt3sas_setup_direct_io - setup MPI request क्रम WARPDRIVE Direct I/O
 * @ioc: per adapter object
 * @scmd: poपूर्णांकer to scsi command object
 * @raid_device: poपूर्णांकer to raid device data काष्ठाure
 * @mpi_request: poपूर्णांकer to the SCSI_IO reqest message frame
 */
व्योम
mpt3sas_setup_direct_io(काष्ठा MPT3SAS_ADAPTER *ioc, काष्ठा scsi_cmnd *scmd,
	काष्ठा _raid_device *raid_device, Mpi25SCSIIORequest_t *mpi_request)
अणु
	sector_t v_lba, p_lba, stripe_off, column, io_size;
	u32 stripe_sz, stripe_exp;
	u8 num_pds, cmd = scmd->cmnd[0];
	काष्ठा scsiio_tracker *st = scsi_cmd_priv(scmd);

	अगर (cmd != READ_10 && cmd != WRITE_10 &&
	    cmd != READ_16 && cmd != WRITE_16)
		वापस;

	अगर (cmd == READ_10 || cmd == WRITE_10)
		v_lba = get_unaligned_be32(&mpi_request->CDB.CDB32[2]);
	अन्यथा
		v_lba = get_unaligned_be64(&mpi_request->CDB.CDB32[2]);

	io_size = scsi_bufflen(scmd) >> raid_device->block_exponent;

	अगर (v_lba + io_size - 1 > raid_device->max_lba)
		वापस;

	stripe_sz = raid_device->stripe_sz;
	stripe_exp = raid_device->stripe_exponent;
	stripe_off = v_lba & (stripe_sz - 1);

	/* Return unless IO falls within a stripe */
	अगर (stripe_off + io_size > stripe_sz)
		वापस;

	num_pds = raid_device->num_pds;
	p_lba = v_lba >> stripe_exp;
	column = sector_भाग(p_lba, num_pds);
	p_lba = (p_lba << stripe_exp) + stripe_off;
	mpi_request->DevHandle = cpu_to_le16(raid_device->pd_handle[column]);

	अगर (cmd == READ_10 || cmd == WRITE_10)
		put_unaligned_be32(lower_32_bits(p_lba),
				   &mpi_request->CDB.CDB32[2]);
	अन्यथा
		put_unaligned_be64(p_lba, &mpi_request->CDB.CDB32[2]);

	st->direct_io = 1;
पूर्ण
