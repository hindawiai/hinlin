<शैली गुरु>
/*
 * PMC-Sierra SPCv/ve 8088/8089 SAS/SATA based host adapters driver
 *
 * Copyright (c) 2008-2009 PMC-Sierra, Inc.,
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions, and the following disclaimer,
 * without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 * substantially similar to the "NO WARRANTY" disclaimer below
 * ("Disclaimer") and any redistribution must be conditioned upon
 * including a substantially similar Disclaimer requirement क्रम further
 * binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 * of any contributors may be used to enकरोrse or promote products derived
 * from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 */
 #समावेश <linux/slab.h>
 #समावेश "pm8001_sas.h"
 #समावेश "pm80xx_hwi.h"
 #समावेश "pm8001_chips.h"
 #समावेश "pm8001_ctl.h"

#घोषणा SMP_सूचीECT 1
#घोषणा SMP_INसूचीECT 2


पूर्णांक pm80xx_bar4_shअगरt(काष्ठा pm8001_hba_info *pm8001_ha, u32 shअगरt_value)
अणु
	u32 reg_val;
	अचिन्हित दीर्घ start;
	pm8001_cw32(pm8001_ha, 0, MEMBASE_II_SHIFT_REGISTER, shअगरt_value);
	/* confirm the setting is written */
	start = jअगरfies + HZ; /* 1 sec */
	करो अणु
		reg_val = pm8001_cr32(pm8001_ha, 0, MEMBASE_II_SHIFT_REGISTER);
	पूर्ण जबतक ((reg_val != shअगरt_value) && समय_beक्रमe(jअगरfies, start));
	अगर (reg_val != shअगरt_value) अणु
		pm8001_dbg(pm8001_ha, FAIL, "TIMEOUT:MEMBASE_II_SHIFT_REGISTER = 0x%x\n",
			   reg_val);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम pm80xx_pci_mem_copy(काष्ठा pm8001_hba_info  *pm8001_ha, u32 soffset,
				स्थिर व्योम *destination,
				u32 dw_count, u32 bus_base_number)
अणु
	u32 index, value, offset;
	u32 *destination1;
	destination1 = (u32 *)destination;

	क्रम (index = 0; index < dw_count; index += 4, destination1++) अणु
		offset = (soffset + index);
		अगर (offset < (64 * 1024)) अणु
			value = pm8001_cr32(pm8001_ha, bus_base_number, offset);
			*destination1 =  cpu_to_le32(value);
		पूर्ण
	पूर्ण
	वापस;
पूर्ण

sमाप_प्रकार pm80xx_get_fatal_dump(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	व्योम __iomem *fatal_table_address = pm8001_ha->fatal_tbl_addr;
	u32 accum_len, reg_val, index, *temp;
	u32 status = 1;
	अचिन्हित दीर्घ start;
	u8 *direct_data;
	अक्षर *fatal_error_data = buf;
	u32 length_to_पढ़ो;
	u32 offset;

	pm8001_ha->क्रमensic_info.data_buf.direct_data = buf;
	अगर (pm8001_ha->chip_id == chip_8001) अणु
		pm8001_ha->क्रमensic_info.data_buf.direct_data +=
			प्र_लिखो(pm8001_ha->क्रमensic_info.data_buf.direct_data,
			"Not supported for SPC controller");
		वापस (अक्षर *)pm8001_ha->क्रमensic_info.data_buf.direct_data -
			(अक्षर *)buf;
	पूर्ण
	/* initialize variables क्रम very first call from host application */
	अगर (pm8001_ha->क्रमensic_info.data_buf.direct_offset == 0) अणु
		pm8001_dbg(pm8001_ha, IO,
			   "forensic_info TYPE_NON_FATAL..............\n");
		direct_data = (u8 *)fatal_error_data;
		pm8001_ha->क्रमensic_info.data_type = TYPE_NON_FATAL;
		pm8001_ha->क्रमensic_info.data_buf.direct_len = SYSFS_OFFSET;
		pm8001_ha->क्रमensic_info.data_buf.direct_offset = 0;
		pm8001_ha->क्रमensic_info.data_buf.पढ़ो_len = 0;
		pm8001_ha->क्रमensic_preserved_accumulated_transfer = 0;

		/* Write signature to fatal dump table */
		pm8001_mw32(fatal_table_address,
				MPI_FATAL_EDUMP_TABLE_SIGNATURE, 0x1234abcd);

		pm8001_ha->क्रमensic_info.data_buf.direct_data = direct_data;
		pm8001_dbg(pm8001_ha, IO, "ossaHwCB: status1 %d\n", status);
		pm8001_dbg(pm8001_ha, IO, "ossaHwCB: read_len 0x%x\n",
			   pm8001_ha->क्रमensic_info.data_buf.पढ़ो_len);
		pm8001_dbg(pm8001_ha, IO, "ossaHwCB: direct_len 0x%x\n",
			   pm8001_ha->क्रमensic_info.data_buf.direct_len);
		pm8001_dbg(pm8001_ha, IO, "ossaHwCB: direct_offset 0x%x\n",
			   pm8001_ha->क्रमensic_info.data_buf.direct_offset);
	पूर्ण
	अगर (pm8001_ha->क्रमensic_info.data_buf.direct_offset == 0) अणु
		/* start to get data */
		/* Program the MEMBASE II Shअगरting Register with 0x00.*/
		pm8001_cw32(pm8001_ha, 0, MEMBASE_II_SHIFT_REGISTER,
				pm8001_ha->fatal_क्रमensic_shअगरt_offset);
		pm8001_ha->क्रमensic_last_offset = 0;
		pm8001_ha->क्रमensic_fatal_step = 0;
		pm8001_ha->fatal_bar_loc = 0;
	पूर्ण

	/* Read until accum_len is retrived */
	accum_len = pm8001_mr32(fatal_table_address,
				MPI_FATAL_EDUMP_TABLE_ACCUM_LEN);
	/* Determine length of data between previously stored transfer length
	 * and current accumulated transfer length
	 */
	length_to_पढ़ो =
		accum_len - pm8001_ha->क्रमensic_preserved_accumulated_transfer;
	pm8001_dbg(pm8001_ha, IO, "get_fatal_spcv: accum_len 0x%x\n",
		   accum_len);
	pm8001_dbg(pm8001_ha, IO, "get_fatal_spcv: length_to_read 0x%x\n",
		   length_to_पढ़ो);
	pm8001_dbg(pm8001_ha, IO, "get_fatal_spcv: last_offset 0x%x\n",
		   pm8001_ha->क्रमensic_last_offset);
	pm8001_dbg(pm8001_ha, IO, "get_fatal_spcv: read_len 0x%x\n",
		   pm8001_ha->क्रमensic_info.data_buf.पढ़ो_len);
	pm8001_dbg(pm8001_ha, IO, "get_fatal_spcv:: direct_len 0x%x\n",
		   pm8001_ha->क्रमensic_info.data_buf.direct_len);
	pm8001_dbg(pm8001_ha, IO, "get_fatal_spcv:: direct_offset 0x%x\n",
		   pm8001_ha->क्रमensic_info.data_buf.direct_offset);

	/* If accumulated length failed to पढ़ो correctly fail the attempt.*/
	अगर (accum_len == 0xFFFFFFFF) अणु
		pm8001_dbg(pm8001_ha, IO,
			   "Possible PCI issue 0x%x not expected\n",
			   accum_len);
		वापस status;
	पूर्ण
	/* If accumulated length is zero fail the attempt */
	अगर (accum_len == 0) अणु
		pm8001_ha->क्रमensic_info.data_buf.direct_data +=
			प्र_लिखो(pm8001_ha->क्रमensic_info.data_buf.direct_data,
			"%08x ", 0xFFFFFFFF);
		वापस (अक्षर *)pm8001_ha->क्रमensic_info.data_buf.direct_data -
			(अक्षर *)buf;
	पूर्ण
	/* Accumulated length is good so start capturing the first data */
	temp = (u32 *)pm8001_ha->memoryMap.region[FORENSIC_MEM].virt_ptr;
	अगर (pm8001_ha->क्रमensic_fatal_step == 0) अणु
moreData:
		/* If data to पढ़ो is less than SYSFS_OFFSET then reduce the
		 * length of dataLen
		 */
		अगर (pm8001_ha->क्रमensic_last_offset + SYSFS_OFFSET
				> length_to_पढ़ो) अणु
			pm8001_ha->क्रमensic_info.data_buf.direct_len =
				length_to_पढ़ो -
				pm8001_ha->क्रमensic_last_offset;
		पूर्ण अन्यथा अणु
			pm8001_ha->क्रमensic_info.data_buf.direct_len =
				SYSFS_OFFSET;
		पूर्ण
		अगर (pm8001_ha->क्रमensic_info.data_buf.direct_data) अणु
			/* Data is in bar, copy to host memory */
			pm80xx_pci_mem_copy(pm8001_ha,
			pm8001_ha->fatal_bar_loc,
			pm8001_ha->memoryMap.region[FORENSIC_MEM].virt_ptr,
			pm8001_ha->क्रमensic_info.data_buf.direct_len, 1);
		पूर्ण
		pm8001_ha->fatal_bar_loc +=
			pm8001_ha->क्रमensic_info.data_buf.direct_len;
		pm8001_ha->क्रमensic_info.data_buf.direct_offset +=
			pm8001_ha->क्रमensic_info.data_buf.direct_len;
		pm8001_ha->क्रमensic_last_offset	+=
			pm8001_ha->क्रमensic_info.data_buf.direct_len;
		pm8001_ha->क्रमensic_info.data_buf.पढ़ो_len =
			pm8001_ha->क्रमensic_info.data_buf.direct_len;

		अगर (pm8001_ha->क्रमensic_last_offset  >= length_to_पढ़ो) अणु
			pm8001_ha->क्रमensic_info.data_buf.direct_data +=
			प्र_लिखो(pm8001_ha->क्रमensic_info.data_buf.direct_data,
				"%08x ", 3);
			क्रम (index = 0; index <
				(pm8001_ha->क्रमensic_info.data_buf.direct_len
				 / 4); index++) अणु
				pm8001_ha->क्रमensic_info.data_buf.direct_data +=
				प्र_लिखो(
				pm8001_ha->क्रमensic_info.data_buf.direct_data,
				"%08x ", *(temp + index));
			पूर्ण

			pm8001_ha->fatal_bar_loc = 0;
			pm8001_ha->क्रमensic_fatal_step = 1;
			pm8001_ha->fatal_क्रमensic_shअगरt_offset = 0;
			pm8001_ha->क्रमensic_last_offset	= 0;
			status = 0;
			offset = (पूर्णांक)
			((अक्षर *)pm8001_ha->क्रमensic_info.data_buf.direct_data
			- (अक्षर *)buf);
			pm8001_dbg(pm8001_ha, IO,
				   "get_fatal_spcv:return1 0x%x\n", offset);
			वापस (अक्षर *)pm8001_ha->
				क्रमensic_info.data_buf.direct_data -
				(अक्षर *)buf;
		पूर्ण
		अगर (pm8001_ha->fatal_bar_loc < (64 * 1024)) अणु
			pm8001_ha->क्रमensic_info.data_buf.direct_data +=
				प्र_लिखो(pm8001_ha->
					क्रमensic_info.data_buf.direct_data,
					"%08x ", 2);
			क्रम (index = 0; index <
				(pm8001_ha->क्रमensic_info.data_buf.direct_len
				 / 4); index++) अणु
				pm8001_ha->क्रमensic_info.data_buf.direct_data
					+= प्र_लिखो(pm8001_ha->
					क्रमensic_info.data_buf.direct_data,
					"%08x ", *(temp + index));
			पूर्ण
			status = 0;
			offset = (पूर्णांक)
			((अक्षर *)pm8001_ha->क्रमensic_info.data_buf.direct_data
			- (अक्षर *)buf);
			pm8001_dbg(pm8001_ha, IO,
				   "get_fatal_spcv:return2 0x%x\n", offset);
			वापस (अक्षर *)pm8001_ha->
				क्रमensic_info.data_buf.direct_data -
				(अक्षर *)buf;
		पूर्ण

		/* Increment the MEMBASE II Shअगरting Register value by 0x100.*/
		pm8001_ha->क्रमensic_info.data_buf.direct_data +=
			प्र_लिखो(pm8001_ha->क्रमensic_info.data_buf.direct_data,
				"%08x ", 2);
		क्रम (index = 0; index <
			(pm8001_ha->क्रमensic_info.data_buf.direct_len
			 / 4) ; index++) अणु
			pm8001_ha->क्रमensic_info.data_buf.direct_data +=
				प्र_लिखो(pm8001_ha->
				क्रमensic_info.data_buf.direct_data,
				"%08x ", *(temp + index));
		पूर्ण
		pm8001_ha->fatal_क्रमensic_shअगरt_offset += 0x100;
		pm8001_cw32(pm8001_ha, 0, MEMBASE_II_SHIFT_REGISTER,
			pm8001_ha->fatal_क्रमensic_shअगरt_offset);
		pm8001_ha->fatal_bar_loc = 0;
		status = 0;
		offset = (पूर्णांक)
			((अक्षर *)pm8001_ha->क्रमensic_info.data_buf.direct_data
			- (अक्षर *)buf);
		pm8001_dbg(pm8001_ha, IO, "get_fatal_spcv: return3 0x%x\n",
			   offset);
		वापस (अक्षर *)pm8001_ha->क्रमensic_info.data_buf.direct_data -
			(अक्षर *)buf;
	पूर्ण
	अगर (pm8001_ha->क्रमensic_fatal_step == 1) अणु
		/* store previous accumulated length beक्रमe triggering next
		 * accumulated length update
		 */
		pm8001_ha->क्रमensic_preserved_accumulated_transfer =
			pm8001_mr32(fatal_table_address,
			MPI_FATAL_EDUMP_TABLE_ACCUM_LEN);

		/* जारी capturing the fatal log until Dump status is 0x3 */
		अगर (pm8001_mr32(fatal_table_address,
			MPI_FATAL_EDUMP_TABLE_STATUS) <
			MPI_FATAL_EDUMP_TABLE_STAT_NF_SUCCESS_DONE) अणु

			/* reset fddstat bit by writing to zero*/
			pm8001_mw32(fatal_table_address,
					MPI_FATAL_EDUMP_TABLE_STATUS, 0x0);

			/* set dump control value to '1' so that new data will
			 * be transferred to shared memory
			 */
			pm8001_mw32(fatal_table_address,
				MPI_FATAL_EDUMP_TABLE_HANDSHAKE,
				MPI_FATAL_EDUMP_HANDSHAKE_RDY);

			/*Poll FDDHSHK  until clear */
			start = jअगरfies + (2 * HZ); /* 2 sec */

			करो अणु
				reg_val = pm8001_mr32(fatal_table_address,
					MPI_FATAL_EDUMP_TABLE_HANDSHAKE);
			पूर्ण जबतक ((reg_val) && समय_beक्रमe(jअगरfies, start));

			अगर (reg_val != 0) अणु
				pm8001_dbg(pm8001_ha, FAIL,
					   "TIMEOUT:MPI_FATAL_EDUMP_TABLE_HDSHAKE 0x%x\n",
					   reg_val);
			       /* Fail the dump अगर a समयout occurs */
				pm8001_ha->क्रमensic_info.data_buf.direct_data +=
				प्र_लिखो(
				pm8001_ha->क्रमensic_info.data_buf.direct_data,
				"%08x ", 0xFFFFFFFF);
				वापस((अक्षर *)
				pm8001_ha->क्रमensic_info.data_buf.direct_data
				- (अक्षर *)buf);
			पूर्ण
			/* Poll status रेजिस्टर until set to 2 or
			 * 3 क्रम up to 2 seconds
			 */
			start = jअगरfies + (2 * HZ); /* 2 sec */

			करो अणु
				reg_val = pm8001_mr32(fatal_table_address,
					MPI_FATAL_EDUMP_TABLE_STATUS);
			पूर्ण जबतक (((reg_val != 2) && (reg_val != 3)) &&
					समय_beक्रमe(jअगरfies, start));

			अगर (reg_val < 2) अणु
				pm8001_dbg(pm8001_ha, FAIL,
					   "TIMEOUT:MPI_FATAL_EDUMP_TABLE_STATUS = 0x%x\n",
					   reg_val);
				/* Fail the dump अगर a समयout occurs */
				pm8001_ha->क्रमensic_info.data_buf.direct_data +=
				प्र_लिखो(
				pm8001_ha->क्रमensic_info.data_buf.direct_data,
				"%08x ", 0xFFFFFFFF);
				वापस((अक्षर *)pm8001_ha->क्रमensic_info.data_buf.direct_data -
						(अक्षर *)buf);
			पूर्ण
	/* reset fatal_क्रमensic_shअगरt_offset back to zero and reset MEMBASE 2 रेजिस्टर to zero */
			pm8001_ha->fatal_क्रमensic_shअगरt_offset = 0; /* location in 64k region */
			pm8001_cw32(pm8001_ha, 0,
					MEMBASE_II_SHIFT_REGISTER,
					pm8001_ha->fatal_क्रमensic_shअगरt_offset);
		पूर्ण
		/* Read the next block of the debug data.*/
		length_to_पढ़ो = pm8001_mr32(fatal_table_address,
		MPI_FATAL_EDUMP_TABLE_ACCUM_LEN) -
		pm8001_ha->क्रमensic_preserved_accumulated_transfer;
		अगर (length_to_पढ़ो != 0x0) अणु
			pm8001_ha->क्रमensic_fatal_step = 0;
			जाओ moreData;
		पूर्ण अन्यथा अणु
			pm8001_ha->क्रमensic_info.data_buf.direct_data +=
			प्र_लिखो(pm8001_ha->क्रमensic_info.data_buf.direct_data,
				"%08x ", 4);
			pm8001_ha->क्रमensic_info.data_buf.पढ़ो_len = 0xFFFFFFFF;
			pm8001_ha->क्रमensic_info.data_buf.direct_len =  0;
			pm8001_ha->क्रमensic_info.data_buf.direct_offset = 0;
			pm8001_ha->क्रमensic_info.data_buf.पढ़ो_len = 0;
		पूर्ण
	पूर्ण
	offset = (पूर्णांक)((अक्षर *)pm8001_ha->क्रमensic_info.data_buf.direct_data
			- (अक्षर *)buf);
	pm8001_dbg(pm8001_ha, IO, "get_fatal_spcv: return4 0x%x\n", offset);
	वापस ((अक्षर *)pm8001_ha->क्रमensic_info.data_buf.direct_data -
		(अक्षर *)buf);
पूर्ण

/* pm80xx_get_non_fatal_dump - dump the nonfatal data from the dma
 * location by the firmware.
 */
sमाप_प्रकार pm80xx_get_non_fatal_dump(काष्ठा device *cdev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(cdev);
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	व्योम __iomem *nonfatal_table_address = pm8001_ha->fatal_tbl_addr;
	u32 accum_len = 0;
	u32 total_len = 0;
	u32 reg_val = 0;
	u32 *temp = शून्य;
	u32 index = 0;
	u32 output_length;
	अचिन्हित दीर्घ start = 0;
	अक्षर *buf_copy = buf;

	temp = (u32 *)pm8001_ha->memoryMap.region[FORENSIC_MEM].virt_ptr;
	अगर (++pm8001_ha->non_fatal_count == 1) अणु
		अगर (pm8001_ha->chip_id == chip_8001) अणु
			snम_लिखो(pm8001_ha->क्रमensic_info.data_buf.direct_data,
				PAGE_SIZE, "Not supported for SPC controller");
			वापस 0;
		पूर्ण
		pm8001_dbg(pm8001_ha, IO, "forensic_info TYPE_NON_FATAL...\n");
		/*
		 * Step 1: Write the host buffer parameters in the MPI Fatal and
		 * Non-Fatal Error Dump Capture Table.This is the buffer
		 * where debug data will be DMAed to.
		 */
		pm8001_mw32(nonfatal_table_address,
		MPI_FATAL_EDUMP_TABLE_LO_OFFSET,
		pm8001_ha->memoryMap.region[FORENSIC_MEM].phys_addr_lo);

		pm8001_mw32(nonfatal_table_address,
		MPI_FATAL_EDUMP_TABLE_HI_OFFSET,
		pm8001_ha->memoryMap.region[FORENSIC_MEM].phys_addr_hi);

		pm8001_mw32(nonfatal_table_address,
		MPI_FATAL_EDUMP_TABLE_LENGTH, SYSFS_OFFSET);

		/* Optionally, set the DUMPCTRL bit to 1 अगर the host
		 * keeps sending active I/Os जबतक capturing the non-fatal
		 * debug data. Otherwise, leave this bit set to zero
		 */
		pm8001_mw32(nonfatal_table_address,
		MPI_FATAL_EDUMP_TABLE_HANDSHAKE, MPI_FATAL_EDUMP_HANDSHAKE_RDY);

		/*
		 * Step 2: Clear Accumulative Length of Debug Data Transferred
		 * [ACCDDLEN] field in the MPI Fatal and Non-Fatal Error Dump
		 * Capture Table to zero.
		 */
		pm8001_mw32(nonfatal_table_address,
				MPI_FATAL_EDUMP_TABLE_ACCUM_LEN, 0);

		/* initiallize previous accumulated length to 0 */
		pm8001_ha->क्रमensic_preserved_accumulated_transfer = 0;
		pm8001_ha->non_fatal_पढ़ो_length = 0;
	पूर्ण

	total_len = pm8001_mr32(nonfatal_table_address,
			MPI_FATAL_EDUMP_TABLE_TOTAL_LEN);
	/*
	 * Step 3:Clear Fatal/Non-Fatal Debug Data Transfer Status [FDDTSTAT]
	 * field and then request that the SPCv controller transfer the debug
	 * data by setting bit 7 of the Inbound Doorbell Set Register.
	 */
	pm8001_mw32(nonfatal_table_address, MPI_FATAL_EDUMP_TABLE_STATUS, 0);
	pm8001_cw32(pm8001_ha, 0, MSGU_IBDB_SET,
			SPCv_MSGU_CFG_TABLE_NONFATAL_DUMP);

	/*
	 * Step 4.1: Read back the Inbound Doorbell Set Register (by polling क्रम
	 * 2 seconds) until रेजिस्टर bit 7 is cleared.
	 * This step only indicates the request is accepted by the controller.
	 */
	start = jअगरfies + (2 * HZ); /* 2 sec */
	करो अणु
		reg_val = pm8001_cr32(pm8001_ha, 0, MSGU_IBDB_SET) &
			SPCv_MSGU_CFG_TABLE_NONFATAL_DUMP;
	पूर्ण जबतक ((reg_val != 0) && समय_beक्रमe(jअगरfies, start));

	/* Step 4.2: To check the completion of the transfer, poll the Fatal/Non
	 * Fatal Debug Data Transfer Status [FDDTSTAT] field क्रम 2 seconds in
	 * the MPI Fatal and Non-Fatal Error Dump Capture Table.
	 */
	start = jअगरfies + (2 * HZ); /* 2 sec */
	करो अणु
		reg_val = pm8001_mr32(nonfatal_table_address,
				MPI_FATAL_EDUMP_TABLE_STATUS);
	पूर्ण जबतक ((!reg_val) && समय_beक्रमe(jअगरfies, start));

	अगर ((reg_val == 0x00) ||
		(reg_val == MPI_FATAL_EDUMP_TABLE_STAT_DMA_FAILED) ||
		(reg_val > MPI_FATAL_EDUMP_TABLE_STAT_NF_SUCCESS_DONE)) अणु
		pm8001_ha->non_fatal_पढ़ो_length = 0;
		buf_copy += snम_लिखो(buf_copy, PAGE_SIZE, "%08x ", 0xFFFFFFFF);
		pm8001_ha->non_fatal_count = 0;
		वापस (buf_copy - buf);
	पूर्ण अन्यथा अगर (reg_val ==
			MPI_FATAL_EDUMP_TABLE_STAT_NF_SUCCESS_MORE_DATA) अणु
		buf_copy += snम_लिखो(buf_copy, PAGE_SIZE, "%08x ", 2);
	पूर्ण अन्यथा अगर ((reg_val == MPI_FATAL_EDUMP_TABLE_STAT_NF_SUCCESS_DONE) ||
		(pm8001_ha->non_fatal_पढ़ो_length >= total_len)) अणु
		pm8001_ha->non_fatal_पढ़ो_length = 0;
		buf_copy += snम_लिखो(buf_copy, PAGE_SIZE, "%08x ", 4);
		pm8001_ha->non_fatal_count = 0;
	पूर्ण
	accum_len = pm8001_mr32(nonfatal_table_address,
			MPI_FATAL_EDUMP_TABLE_ACCUM_LEN);
	output_length = accum_len -
		pm8001_ha->क्रमensic_preserved_accumulated_transfer;

	क्रम (index = 0; index < output_length/4; index++)
		buf_copy += snम_लिखो(buf_copy, PAGE_SIZE,
				"%08x ", *(temp+index));

	pm8001_ha->non_fatal_पढ़ो_length += output_length;

	/* store current accumulated length to use in next iteration as
	 * the previous accumulated length
	 */
	pm8001_ha->क्रमensic_preserved_accumulated_transfer = accum_len;
	वापस (buf_copy - buf);
पूर्ण

/**
 * पढ़ो_मुख्य_config_table - पढ़ो the configure table and save it.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल व्योम पढ़ो_मुख्य_config_table(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	व्योम __iomem *address = pm8001_ha->मुख्य_cfg_tbl_addr;

	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.signature	=
		pm8001_mr32(address, MAIN_SIGNATURE_OFFSET);
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.पूर्णांकerface_rev =
		pm8001_mr32(address, MAIN_INTERFACE_REVISION);
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.firmware_rev	=
		pm8001_mr32(address, MAIN_FW_REVISION);
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.max_out_io	=
		pm8001_mr32(address, MAIN_MAX_OUTSTANDING_IO_OFFSET);
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.max_sgl	=
		pm8001_mr32(address, MAIN_MAX_SGL_OFFSET);
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.ctrl_cap_flag =
		pm8001_mr32(address, MAIN_CNTRL_CAP_OFFSET);
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.gst_offset	=
		pm8001_mr32(address, MAIN_GST_OFFSET);
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.inbound_queue_offset =
		pm8001_mr32(address, MAIN_IBQ_OFFSET);
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.outbound_queue_offset =
		pm8001_mr32(address, MAIN_OBQ_OFFSET);

	/* पढ़ो Error Dump Offset and Length */
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.fatal_err_dump_offset0 =
		pm8001_mr32(address, MAIN_FATAL_ERROR_RDUMP0_OFFSET);
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.fatal_err_dump_length0 =
		pm8001_mr32(address, MAIN_FATAL_ERROR_RDUMP0_LENGTH);
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.fatal_err_dump_offset1 =
		pm8001_mr32(address, MAIN_FATAL_ERROR_RDUMP1_OFFSET);
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.fatal_err_dump_length1 =
		pm8001_mr32(address, MAIN_FATAL_ERROR_RDUMP1_LENGTH);

	/* पढ़ो GPIO LED settings from the configuration table */
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.gpio_led_mapping =
		pm8001_mr32(address, MAIN_GPIO_LED_FLAGS_OFFSET);

	/* पढ़ो analog Setting offset from the configuration table */
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.analog_setup_table_offset =
		pm8001_mr32(address, MAIN_ANALOG_SETUP_OFFSET);

	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.पूर्णांक_vec_table_offset =
		pm8001_mr32(address, MAIN_INT_VECTOR_TABLE_OFFSET);
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.phy_attr_table_offset =
		pm8001_mr32(address, MAIN_SAS_PHY_ATTR_TABLE_OFFSET);
	/* पढ़ो port recover and reset समयout */
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.port_recovery_समयr =
		pm8001_mr32(address, MAIN_PORT_RECOVERY_TIMER);
	/* पढ़ो ILA and inactive firmware version */
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.ila_version =
		pm8001_mr32(address, MAIN_MPI_ILA_RELEASE_TYPE);
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.inc_fw_version =
		pm8001_mr32(address, MAIN_MPI_INACTIVE_FW_VERSION);

	pm8001_dbg(pm8001_ha, DEV,
		   "Main cfg table: sign:%x interface rev:%x fw_rev:%x\n",
		   pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.signature,
		   pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.पूर्णांकerface_rev,
		   pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.firmware_rev);

	pm8001_dbg(pm8001_ha, DEV,
		   "table offset: gst:%x iq:%x oq:%x int vec:%x phy attr:%x\n",
		   pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.gst_offset,
		   pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.inbound_queue_offset,
		   pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.outbound_queue_offset,
		   pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.पूर्णांक_vec_table_offset,
		   pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.phy_attr_table_offset);

	pm8001_dbg(pm8001_ha, DEV,
		   "Main cfg table; ila rev:%x Inactive fw rev:%x\n",
		   pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.ila_version,
		   pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.inc_fw_version);
पूर्ण

/**
 * पढ़ो_general_status_table - पढ़ो the general status table and save it.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल व्योम पढ़ो_general_status_table(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	व्योम __iomem *address = pm8001_ha->general_stat_tbl_addr;
	pm8001_ha->gs_tbl.pm80xx_tbl.gst_len_mpistate	=
			pm8001_mr32(address, GST_GSTLEN_MPIS_OFFSET);
	pm8001_ha->gs_tbl.pm80xx_tbl.iq_मुक्तze_state0	=
			pm8001_mr32(address, GST_IQ_FREEZE_STATE0_OFFSET);
	pm8001_ha->gs_tbl.pm80xx_tbl.iq_मुक्तze_state1	=
			pm8001_mr32(address, GST_IQ_FREEZE_STATE1_OFFSET);
	pm8001_ha->gs_tbl.pm80xx_tbl.msgu_tcnt		=
			pm8001_mr32(address, GST_MSGUTCNT_OFFSET);
	pm8001_ha->gs_tbl.pm80xx_tbl.iop_tcnt		=
			pm8001_mr32(address, GST_IOPTCNT_OFFSET);
	pm8001_ha->gs_tbl.pm80xx_tbl.gpio_input_val	=
			pm8001_mr32(address, GST_GPIO_INPUT_VAL);
	pm8001_ha->gs_tbl.pm80xx_tbl.recover_err_info[0] =
			pm8001_mr32(address, GST_RERRINFO_OFFSET0);
	pm8001_ha->gs_tbl.pm80xx_tbl.recover_err_info[1] =
			pm8001_mr32(address, GST_RERRINFO_OFFSET1);
	pm8001_ha->gs_tbl.pm80xx_tbl.recover_err_info[2] =
			pm8001_mr32(address, GST_RERRINFO_OFFSET2);
	pm8001_ha->gs_tbl.pm80xx_tbl.recover_err_info[3] =
			pm8001_mr32(address, GST_RERRINFO_OFFSET3);
	pm8001_ha->gs_tbl.pm80xx_tbl.recover_err_info[4] =
			pm8001_mr32(address, GST_RERRINFO_OFFSET4);
	pm8001_ha->gs_tbl.pm80xx_tbl.recover_err_info[5] =
			pm8001_mr32(address, GST_RERRINFO_OFFSET5);
	pm8001_ha->gs_tbl.pm80xx_tbl.recover_err_info[6] =
			pm8001_mr32(address, GST_RERRINFO_OFFSET6);
	pm8001_ha->gs_tbl.pm80xx_tbl.recover_err_info[7] =
			 pm8001_mr32(address, GST_RERRINFO_OFFSET7);
पूर्ण
/**
 * पढ़ो_phy_attr_table - पढ़ो the phy attribute table and save it.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल व्योम पढ़ो_phy_attr_table(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	व्योम __iomem *address = pm8001_ha->pspa_q_tbl_addr;
	pm8001_ha->phy_attr_table.phystart1_16[0] =
			pm8001_mr32(address, PSPA_PHYSTATE0_OFFSET);
	pm8001_ha->phy_attr_table.phystart1_16[1] =
			pm8001_mr32(address, PSPA_PHYSTATE1_OFFSET);
	pm8001_ha->phy_attr_table.phystart1_16[2] =
			pm8001_mr32(address, PSPA_PHYSTATE2_OFFSET);
	pm8001_ha->phy_attr_table.phystart1_16[3] =
			pm8001_mr32(address, PSPA_PHYSTATE3_OFFSET);
	pm8001_ha->phy_attr_table.phystart1_16[4] =
			pm8001_mr32(address, PSPA_PHYSTATE4_OFFSET);
	pm8001_ha->phy_attr_table.phystart1_16[5] =
			pm8001_mr32(address, PSPA_PHYSTATE5_OFFSET);
	pm8001_ha->phy_attr_table.phystart1_16[6] =
			pm8001_mr32(address, PSPA_PHYSTATE6_OFFSET);
	pm8001_ha->phy_attr_table.phystart1_16[7] =
			pm8001_mr32(address, PSPA_PHYSTATE7_OFFSET);
	pm8001_ha->phy_attr_table.phystart1_16[8] =
			pm8001_mr32(address, PSPA_PHYSTATE8_OFFSET);
	pm8001_ha->phy_attr_table.phystart1_16[9] =
			pm8001_mr32(address, PSPA_PHYSTATE9_OFFSET);
	pm8001_ha->phy_attr_table.phystart1_16[10] =
			pm8001_mr32(address, PSPA_PHYSTATE10_OFFSET);
	pm8001_ha->phy_attr_table.phystart1_16[11] =
			pm8001_mr32(address, PSPA_PHYSTATE11_OFFSET);
	pm8001_ha->phy_attr_table.phystart1_16[12] =
			pm8001_mr32(address, PSPA_PHYSTATE12_OFFSET);
	pm8001_ha->phy_attr_table.phystart1_16[13] =
			pm8001_mr32(address, PSPA_PHYSTATE13_OFFSET);
	pm8001_ha->phy_attr_table.phystart1_16[14] =
			pm8001_mr32(address, PSPA_PHYSTATE14_OFFSET);
	pm8001_ha->phy_attr_table.phystart1_16[15] =
			pm8001_mr32(address, PSPA_PHYSTATE15_OFFSET);

	pm8001_ha->phy_attr_table.outbound_hw_event_pid1_16[0] =
			pm8001_mr32(address, PSPA_OB_HW_EVENT_PID0_OFFSET);
	pm8001_ha->phy_attr_table.outbound_hw_event_pid1_16[1] =
			pm8001_mr32(address, PSPA_OB_HW_EVENT_PID1_OFFSET);
	pm8001_ha->phy_attr_table.outbound_hw_event_pid1_16[2] =
			pm8001_mr32(address, PSPA_OB_HW_EVENT_PID2_OFFSET);
	pm8001_ha->phy_attr_table.outbound_hw_event_pid1_16[3] =
			pm8001_mr32(address, PSPA_OB_HW_EVENT_PID3_OFFSET);
	pm8001_ha->phy_attr_table.outbound_hw_event_pid1_16[4] =
			pm8001_mr32(address, PSPA_OB_HW_EVENT_PID4_OFFSET);
	pm8001_ha->phy_attr_table.outbound_hw_event_pid1_16[5] =
			pm8001_mr32(address, PSPA_OB_HW_EVENT_PID5_OFFSET);
	pm8001_ha->phy_attr_table.outbound_hw_event_pid1_16[6] =
			pm8001_mr32(address, PSPA_OB_HW_EVENT_PID6_OFFSET);
	pm8001_ha->phy_attr_table.outbound_hw_event_pid1_16[7] =
			pm8001_mr32(address, PSPA_OB_HW_EVENT_PID7_OFFSET);
	pm8001_ha->phy_attr_table.outbound_hw_event_pid1_16[8] =
			pm8001_mr32(address, PSPA_OB_HW_EVENT_PID8_OFFSET);
	pm8001_ha->phy_attr_table.outbound_hw_event_pid1_16[9] =
			pm8001_mr32(address, PSPA_OB_HW_EVENT_PID9_OFFSET);
	pm8001_ha->phy_attr_table.outbound_hw_event_pid1_16[10] =
			pm8001_mr32(address, PSPA_OB_HW_EVENT_PID10_OFFSET);
	pm8001_ha->phy_attr_table.outbound_hw_event_pid1_16[11] =
			pm8001_mr32(address, PSPA_OB_HW_EVENT_PID11_OFFSET);
	pm8001_ha->phy_attr_table.outbound_hw_event_pid1_16[12] =
			pm8001_mr32(address, PSPA_OB_HW_EVENT_PID12_OFFSET);
	pm8001_ha->phy_attr_table.outbound_hw_event_pid1_16[13] =
			pm8001_mr32(address, PSPA_OB_HW_EVENT_PID13_OFFSET);
	pm8001_ha->phy_attr_table.outbound_hw_event_pid1_16[14] =
			pm8001_mr32(address, PSPA_OB_HW_EVENT_PID14_OFFSET);
	pm8001_ha->phy_attr_table.outbound_hw_event_pid1_16[15] =
			pm8001_mr32(address, PSPA_OB_HW_EVENT_PID15_OFFSET);

पूर्ण

/**
 * पढ़ो_inbnd_queue_table - पढ़ो the inbound queue table and save it.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल व्योम पढ़ो_inbnd_queue_table(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	पूर्णांक i;
	व्योम __iomem *address = pm8001_ha->inbnd_q_tbl_addr;
	क्रम (i = 0; i < PM8001_MAX_INB_NUM; i++) अणु
		u32 offset = i * 0x20;
		pm8001_ha->inbnd_q_tbl[i].pi_pci_bar =
			get_pci_bar_index(pm8001_mr32(address,
				(offset + IB_PIPCI_BAR)));
		pm8001_ha->inbnd_q_tbl[i].pi_offset =
			pm8001_mr32(address, (offset + IB_PIPCI_BAR_OFFSET));
	पूर्ण
पूर्ण

/**
 * पढ़ो_outbnd_queue_table - पढ़ो the outbound queue table and save it.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल व्योम पढ़ो_outbnd_queue_table(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	पूर्णांक i;
	व्योम __iomem *address = pm8001_ha->outbnd_q_tbl_addr;
	क्रम (i = 0; i < PM8001_MAX_OUTB_NUM; i++) अणु
		u32 offset = i * 0x24;
		pm8001_ha->outbnd_q_tbl[i].ci_pci_bar =
			get_pci_bar_index(pm8001_mr32(address,
				(offset + OB_CIPCI_BAR)));
		pm8001_ha->outbnd_q_tbl[i].ci_offset =
			pm8001_mr32(address, (offset + OB_CIPCI_BAR_OFFSET));
	पूर्ण
पूर्ण

/**
 * init_शेष_table_values - init the शेष table.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल व्योम init_शेष_table_values(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	पूर्णांक i;
	u32 offsetib, offsetob;
	व्योम __iomem *addressib = pm8001_ha->inbnd_q_tbl_addr;
	व्योम __iomem *addressob = pm8001_ha->outbnd_q_tbl_addr;
	u32 ib_offset = pm8001_ha->ib_offset;
	u32 ob_offset = pm8001_ha->ob_offset;
	u32 ci_offset = pm8001_ha->ci_offset;
	u32 pi_offset = pm8001_ha->pi_offset;

	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.upper_event_log_addr		=
		pm8001_ha->memoryMap.region[AAP1].phys_addr_hi;
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.lower_event_log_addr		=
		pm8001_ha->memoryMap.region[AAP1].phys_addr_lo;
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.event_log_size		=
							PM8001_EVENT_LOG_SIZE;
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.event_log_severity		= 0x01;
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.upper_pcs_event_log_addr	=
		pm8001_ha->memoryMap.region[IOP].phys_addr_hi;
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.lower_pcs_event_log_addr	=
		pm8001_ha->memoryMap.region[IOP].phys_addr_lo;
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.pcs_event_log_size		=
							PM8001_EVENT_LOG_SIZE;
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.pcs_event_log_severity	= 0x01;
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.fatal_err_पूर्णांकerrupt		= 0x01;

	/* Disable end to end CRC checking */
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.crc_core_dump = (0x1 << 16);

	क्रम (i = 0; i < pm8001_ha->max_q_num; i++) अणु
		pm8001_ha->inbnd_q_tbl[i].element_pri_size_cnt	=
			PM8001_MPI_QUEUE | (pm8001_ha->iomb_size << 16) | (0x00<<30);
		pm8001_ha->inbnd_q_tbl[i].upper_base_addr	=
			pm8001_ha->memoryMap.region[ib_offset + i].phys_addr_hi;
		pm8001_ha->inbnd_q_tbl[i].lower_base_addr	=
		pm8001_ha->memoryMap.region[ib_offset + i].phys_addr_lo;
		pm8001_ha->inbnd_q_tbl[i].base_virt		=
		  (u8 *)pm8001_ha->memoryMap.region[ib_offset + i].virt_ptr;
		pm8001_ha->inbnd_q_tbl[i].total_length		=
			pm8001_ha->memoryMap.region[ib_offset + i].total_len;
		pm8001_ha->inbnd_q_tbl[i].ci_upper_base_addr	=
			pm8001_ha->memoryMap.region[ci_offset + i].phys_addr_hi;
		pm8001_ha->inbnd_q_tbl[i].ci_lower_base_addr	=
			pm8001_ha->memoryMap.region[ci_offset + i].phys_addr_lo;
		pm8001_ha->inbnd_q_tbl[i].ci_virt		=
			pm8001_ha->memoryMap.region[ci_offset + i].virt_ptr;
		pm8001_ग_लिखो_32(pm8001_ha->inbnd_q_tbl[i].ci_virt, 0, 0);
		offsetib = i * 0x20;
		pm8001_ha->inbnd_q_tbl[i].pi_pci_bar		=
			get_pci_bar_index(pm8001_mr32(addressib,
				(offsetib + 0x14)));
		pm8001_ha->inbnd_q_tbl[i].pi_offset		=
			pm8001_mr32(addressib, (offsetib + 0x18));
		pm8001_ha->inbnd_q_tbl[i].producer_idx		= 0;
		pm8001_ha->inbnd_q_tbl[i].consumer_index	= 0;

		pm8001_dbg(pm8001_ha, DEV,
			   "IQ %d pi_bar 0x%x pi_offset 0x%x\n", i,
			   pm8001_ha->inbnd_q_tbl[i].pi_pci_bar,
			   pm8001_ha->inbnd_q_tbl[i].pi_offset);
	पूर्ण
	क्रम (i = 0; i < pm8001_ha->max_q_num; i++) अणु
		pm8001_ha->outbnd_q_tbl[i].element_size_cnt	=
			PM8001_MPI_QUEUE | (pm8001_ha->iomb_size << 16) | (0x01<<30);
		pm8001_ha->outbnd_q_tbl[i].upper_base_addr	=
			pm8001_ha->memoryMap.region[ob_offset + i].phys_addr_hi;
		pm8001_ha->outbnd_q_tbl[i].lower_base_addr	=
			pm8001_ha->memoryMap.region[ob_offset + i].phys_addr_lo;
		pm8001_ha->outbnd_q_tbl[i].base_virt		=
		  (u8 *)pm8001_ha->memoryMap.region[ob_offset + i].virt_ptr;
		pm8001_ha->outbnd_q_tbl[i].total_length		=
			pm8001_ha->memoryMap.region[ob_offset + i].total_len;
		pm8001_ha->outbnd_q_tbl[i].pi_upper_base_addr	=
			pm8001_ha->memoryMap.region[pi_offset + i].phys_addr_hi;
		pm8001_ha->outbnd_q_tbl[i].pi_lower_base_addr	=
			pm8001_ha->memoryMap.region[pi_offset + i].phys_addr_lo;
		/* पूर्णांकerrupt vector based on oq */
		pm8001_ha->outbnd_q_tbl[i].पूर्णांकerrup_vec_cnt_delay = (i << 24);
		pm8001_ha->outbnd_q_tbl[i].pi_virt		=
			pm8001_ha->memoryMap.region[pi_offset + i].virt_ptr;
		pm8001_ग_लिखो_32(pm8001_ha->outbnd_q_tbl[i].pi_virt, 0, 0);
		offsetob = i * 0x24;
		pm8001_ha->outbnd_q_tbl[i].ci_pci_bar		=
			get_pci_bar_index(pm8001_mr32(addressob,
			offsetob + 0x14));
		pm8001_ha->outbnd_q_tbl[i].ci_offset		=
			pm8001_mr32(addressob, (offsetob + 0x18));
		pm8001_ha->outbnd_q_tbl[i].consumer_idx		= 0;
		pm8001_ha->outbnd_q_tbl[i].producer_index	= 0;

		pm8001_dbg(pm8001_ha, DEV,
			   "OQ %d ci_bar 0x%x ci_offset 0x%x\n", i,
			   pm8001_ha->outbnd_q_tbl[i].ci_pci_bar,
			   pm8001_ha->outbnd_q_tbl[i].ci_offset);
	पूर्ण
पूर्ण

/**
 * update_मुख्य_config_table - update the मुख्य शेष table to the HBA.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल व्योम update_मुख्य_config_table(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	व्योम __iomem *address = pm8001_ha->मुख्य_cfg_tbl_addr;
	pm8001_mw32(address, MAIN_IQNPPD_HPPD_OFFSET,
		pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.inbound_q_nppd_hppd);
	pm8001_mw32(address, MAIN_EVENT_LOG_ADDR_HI,
		pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.upper_event_log_addr);
	pm8001_mw32(address, MAIN_EVENT_LOG_ADDR_LO,
		pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.lower_event_log_addr);
	pm8001_mw32(address, MAIN_EVENT_LOG_BUFF_SIZE,
		pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.event_log_size);
	pm8001_mw32(address, MAIN_EVENT_LOG_OPTION,
		pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.event_log_severity);
	pm8001_mw32(address, MAIN_PCS_EVENT_LOG_ADDR_HI,
		pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.upper_pcs_event_log_addr);
	pm8001_mw32(address, MAIN_PCS_EVENT_LOG_ADDR_LO,
		pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.lower_pcs_event_log_addr);
	pm8001_mw32(address, MAIN_PCS_EVENT_LOG_BUFF_SIZE,
		pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.pcs_event_log_size);
	pm8001_mw32(address, MAIN_PCS_EVENT_LOG_OPTION,
		pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.pcs_event_log_severity);
	/* Update Fatal error पूर्णांकerrupt vector */
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.fatal_err_पूर्णांकerrupt |=
					((pm8001_ha->max_q_num - 1) << 8);
	pm8001_mw32(address, MAIN_FATAL_ERROR_INTERRUPT,
		pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.fatal_err_पूर्णांकerrupt);
	pm8001_dbg(pm8001_ha, DEV,
		   "Updated Fatal error interrupt vector 0x%x\n",
		   pm8001_mr32(address, MAIN_FATAL_ERROR_INTERRUPT));

	pm8001_mw32(address, MAIN_EVENT_CRC_CHECK,
		pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.crc_core_dump);

	/* SPCv specअगरic */
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.gpio_led_mapping &= 0xCFFFFFFF;
	/* Set GPIOLED to 0x2 क्रम LED indicator */
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.gpio_led_mapping |= 0x20000000;
	pm8001_mw32(address, MAIN_GPIO_LED_FLAGS_OFFSET,
		pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.gpio_led_mapping);
	pm8001_dbg(pm8001_ha, DEV,
		   "Programming DW 0x21 in main cfg table with 0x%x\n",
		   pm8001_mr32(address, MAIN_GPIO_LED_FLAGS_OFFSET));

	pm8001_mw32(address, MAIN_PORT_RECOVERY_TIMER,
		pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.port_recovery_समयr);
	pm8001_mw32(address, MAIN_INT_REASSERTION_DELAY,
		pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.पूर्णांकerrupt_reनिश्चितion_delay);

	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.port_recovery_समयr &= 0xffff0000;
	pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.port_recovery_समयr |=
							PORT_RECOVERY_TIMEOUT;
	अगर (pm8001_ha->chip_id == chip_8006) अणु
		pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.port_recovery_समयr &=
					0x0000ffff;
		pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.port_recovery_समयr |=
					CHIP_8006_PORT_RECOVERY_TIMEOUT;
	पूर्ण
	pm8001_mw32(address, MAIN_PORT_RECOVERY_TIMER,
			pm8001_ha->मुख्य_cfg_tbl.pm80xx_tbl.port_recovery_समयr);
पूर्ण

/**
 * update_inbnd_queue_table - update the inbound queue table to the HBA.
 * @pm8001_ha: our hba card inक्रमmation
 * @number: entry in the queue
 */
अटल व्योम update_inbnd_queue_table(काष्ठा pm8001_hba_info *pm8001_ha,
					 पूर्णांक number)
अणु
	व्योम __iomem *address = pm8001_ha->inbnd_q_tbl_addr;
	u16 offset = number * 0x20;
	pm8001_mw32(address, offset + IB_PROPERITY_OFFSET,
		pm8001_ha->inbnd_q_tbl[number].element_pri_size_cnt);
	pm8001_mw32(address, offset + IB_BASE_ADDR_HI_OFFSET,
		pm8001_ha->inbnd_q_tbl[number].upper_base_addr);
	pm8001_mw32(address, offset + IB_BASE_ADDR_LO_OFFSET,
		pm8001_ha->inbnd_q_tbl[number].lower_base_addr);
	pm8001_mw32(address, offset + IB_CI_BASE_ADDR_HI_OFFSET,
		pm8001_ha->inbnd_q_tbl[number].ci_upper_base_addr);
	pm8001_mw32(address, offset + IB_CI_BASE_ADDR_LO_OFFSET,
		pm8001_ha->inbnd_q_tbl[number].ci_lower_base_addr);

	pm8001_dbg(pm8001_ha, DEV,
		   "IQ %d: Element pri size 0x%x\n",
		   number,
		   pm8001_ha->inbnd_q_tbl[number].element_pri_size_cnt);

	pm8001_dbg(pm8001_ha, DEV,
		   "IQ upr base addr 0x%x IQ lwr base addr 0x%x\n",
		   pm8001_ha->inbnd_q_tbl[number].upper_base_addr,
		   pm8001_ha->inbnd_q_tbl[number].lower_base_addr);

	pm8001_dbg(pm8001_ha, DEV,
		   "CI upper base addr 0x%x CI lower base addr 0x%x\n",
		   pm8001_ha->inbnd_q_tbl[number].ci_upper_base_addr,
		   pm8001_ha->inbnd_q_tbl[number].ci_lower_base_addr);
पूर्ण

/**
 * update_outbnd_queue_table - update the outbound queue table to the HBA.
 * @pm8001_ha: our hba card inक्रमmation
 * @number: entry in the queue
 */
अटल व्योम update_outbnd_queue_table(काष्ठा pm8001_hba_info *pm8001_ha,
						 पूर्णांक number)
अणु
	व्योम __iomem *address = pm8001_ha->outbnd_q_tbl_addr;
	u16 offset = number * 0x24;
	pm8001_mw32(address, offset + OB_PROPERITY_OFFSET,
		pm8001_ha->outbnd_q_tbl[number].element_size_cnt);
	pm8001_mw32(address, offset + OB_BASE_ADDR_HI_OFFSET,
		pm8001_ha->outbnd_q_tbl[number].upper_base_addr);
	pm8001_mw32(address, offset + OB_BASE_ADDR_LO_OFFSET,
		pm8001_ha->outbnd_q_tbl[number].lower_base_addr);
	pm8001_mw32(address, offset + OB_PI_BASE_ADDR_HI_OFFSET,
		pm8001_ha->outbnd_q_tbl[number].pi_upper_base_addr);
	pm8001_mw32(address, offset + OB_PI_BASE_ADDR_LO_OFFSET,
		pm8001_ha->outbnd_q_tbl[number].pi_lower_base_addr);
	pm8001_mw32(address, offset + OB_INTERRUPT_COALES_OFFSET,
		pm8001_ha->outbnd_q_tbl[number].पूर्णांकerrup_vec_cnt_delay);

	pm8001_dbg(pm8001_ha, DEV,
		   "OQ %d: Element pri size 0x%x\n",
		   number,
		   pm8001_ha->outbnd_q_tbl[number].element_size_cnt);

	pm8001_dbg(pm8001_ha, DEV,
		   "OQ upr base addr 0x%x OQ lwr base addr 0x%x\n",
		   pm8001_ha->outbnd_q_tbl[number].upper_base_addr,
		   pm8001_ha->outbnd_q_tbl[number].lower_base_addr);

	pm8001_dbg(pm8001_ha, DEV,
		   "PI upper base addr 0x%x PI lower base addr 0x%x\n",
		   pm8001_ha->outbnd_q_tbl[number].pi_upper_base_addr,
		   pm8001_ha->outbnd_q_tbl[number].pi_lower_base_addr);
पूर्ण

/**
 * mpi_init_check - check firmware initialization status.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल पूर्णांक mpi_init_check(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	u32 max_रुको_count;
	u32 value;
	u32 gst_len_mpistate;

	/* Write bit0=1 to Inbound DoorBell Register to tell the SPC FW the
	table is updated */
	pm8001_cw32(pm8001_ha, 0, MSGU_IBDB_SET, SPCv_MSGU_CFG_TABLE_UPDATE);
	/* रुको until Inbound DoorBell Clear Register toggled */
	अगर (IS_SPCV_12G(pm8001_ha->pdev)) अणु
		max_रुको_count = SPCV_DOORBELL_CLEAR_TIMEOUT;
	पूर्ण अन्यथा अणु
		max_रुको_count = SPC_DOORBELL_CLEAR_TIMEOUT;
	पूर्ण
	करो अणु
		msleep(FW_READY_INTERVAL);
		value = pm8001_cr32(pm8001_ha, 0, MSGU_IBDB_SET);
		value &= SPCv_MSGU_CFG_TABLE_UPDATE;
	पूर्ण जबतक ((value != 0) && (--max_रुको_count));

	अगर (!max_रुको_count) अणु
		/* additional check */
		pm8001_dbg(pm8001_ha, FAIL,
			   "Inb doorbell clear not toggled[value:%x]\n",
			   value);
		वापस -EBUSY;
	पूर्ण
	/* check the MPI-State क्रम initialization upto 100ms*/
	max_रुको_count = 5;/* 100 msec */
	करो अणु
		msleep(FW_READY_INTERVAL);
		gst_len_mpistate =
			pm8001_mr32(pm8001_ha->general_stat_tbl_addr,
					GST_GSTLEN_MPIS_OFFSET);
	पूर्ण जबतक ((GST_MPI_STATE_INIT !=
		(gst_len_mpistate & GST_MPI_STATE_MASK)) && (--max_रुको_count));
	अगर (!max_रुको_count)
		वापस -EBUSY;

	/* check MPI Initialization error */
	gst_len_mpistate = gst_len_mpistate >> 16;
	अगर (0x0000 != gst_len_mpistate)
		वापस -EBUSY;

	वापस 0;
पूर्ण

/**
 * check_fw_पढ़ोy - The LLDD check अगर the FW is पढ़ोy, अगर not, वापस error.
 * This function sleeps hence it must not be used in atomic context.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल पूर्णांक check_fw_पढ़ोy(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	u32 value;
	u32 max_रुको_count;
	u32 max_रुको_समय;
	u32 expected_mask;
	पूर्णांक ret = 0;

	/* reset / PCIe पढ़ोy */
	max_रुको_समय = max_रुको_count = 5;	/* 100 milli sec */
	करो अणु
		msleep(FW_READY_INTERVAL);
		value = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1);
	पूर्ण जबतक ((value == 0xFFFFFFFF) && (--max_रुको_count));

	/* check ila, RAAE and iops status */
	अगर ((pm8001_ha->chip_id != chip_8008) &&
			(pm8001_ha->chip_id != chip_8009)) अणु
		max_रुको_समय = max_रुको_count = 180;   /* 3600 milli sec */
		expected_mask = SCRATCH_PAD_ILA_READY |
			SCRATCH_PAD_RAAE_READY |
			SCRATCH_PAD_IOP0_READY |
			SCRATCH_PAD_IOP1_READY;
	पूर्ण अन्यथा अणु
		max_रुको_समय = max_रुको_count = 170;   /* 3400 milli sec */
		expected_mask = SCRATCH_PAD_ILA_READY |
			SCRATCH_PAD_RAAE_READY |
			SCRATCH_PAD_IOP0_READY;
	पूर्ण
	करो अणु
		msleep(FW_READY_INTERVAL);
		value = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1);
	पूर्ण जबतक (((value & expected_mask) !=
				 expected_mask) && (--max_रुको_count));
	अगर (!max_रुको_count) अणु
		pm8001_dbg(pm8001_ha, INIT,
		"At least one FW component failed to load within %d millisec: Scratchpad1: 0x%x\n",
			max_रुको_समय * FW_READY_INTERVAL, value);
		ret = -1;
	पूर्ण अन्यथा अणु
		pm8001_dbg(pm8001_ha, MSG,
			"All FW components ready by %d ms\n",
			(max_रुको_समय - max_रुको_count) * FW_READY_INTERVAL);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक init_pci_device_addresses(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	व्योम __iomem *base_addr;
	u32	value;
	u32	offset;
	u32	pcibar;
	u32	pcilogic;

	value = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_0);

	/**
	 * lower 26 bits of SCRATCHPAD0 रेजिस्टर describes offset within the
	 * PCIe BAR where the MPI configuration table is present
	 */
	offset = value & 0x03FFFFFF; /* scratch pad 0 TBL address */

	pm8001_dbg(pm8001_ha, DEV, "Scratchpad 0 Offset: 0x%x value 0x%x\n",
		   offset, value);
	/**
	 * Upper 6 bits describe the offset within PCI config space where BAR
	 * is located.
	 */
	pcilogic = (value & 0xFC000000) >> 26;
	pcibar = get_pci_bar_index(pcilogic);
	pm8001_dbg(pm8001_ha, INIT, "Scratchpad 0 PCI BAR: %d\n", pcibar);

	/**
	 * Make sure the offset falls inside the ioremapped PCI BAR
	 */
	अगर (offset > pm8001_ha->io_mem[pcibar].memsize) अणु
		pm8001_dbg(pm8001_ha, FAIL,
			"Main cfg tbl offset outside %u > %u\n",
				offset, pm8001_ha->io_mem[pcibar].memsize);
		वापस -EBUSY;
	पूर्ण
	pm8001_ha->मुख्य_cfg_tbl_addr = base_addr =
		pm8001_ha->io_mem[pcibar].memvirtaddr + offset;

	/**
	 * Validate मुख्य configuration table address: first DWord should पढ़ो
	 * "PMCS"
	 */
	value = pm8001_mr32(pm8001_ha->मुख्य_cfg_tbl_addr, 0);
	अगर (स_भेद(&value, "PMCS", 4) != 0) अणु
		pm8001_dbg(pm8001_ha, FAIL,
			"BAD main config signature 0x%x\n",
				value);
		वापस -EBUSY;
	पूर्ण
	pm8001_dbg(pm8001_ha, INIT,
			"VALID main config signature 0x%x\n", value);
	pm8001_ha->general_stat_tbl_addr =
		base_addr + (pm8001_cr32(pm8001_ha, pcibar, offset + 0x18) &
					0xFFFFFF);
	pm8001_ha->inbnd_q_tbl_addr =
		base_addr + (pm8001_cr32(pm8001_ha, pcibar, offset + 0x1C) &
					0xFFFFFF);
	pm8001_ha->outbnd_q_tbl_addr =
		base_addr + (pm8001_cr32(pm8001_ha, pcibar, offset + 0x20) &
					0xFFFFFF);
	pm8001_ha->ivt_tbl_addr =
		base_addr + (pm8001_cr32(pm8001_ha, pcibar, offset + 0x8C) &
					0xFFFFFF);
	pm8001_ha->pspa_q_tbl_addr =
		base_addr + (pm8001_cr32(pm8001_ha, pcibar, offset + 0x90) &
					0xFFFFFF);
	pm8001_ha->fatal_tbl_addr =
		base_addr + (pm8001_cr32(pm8001_ha, pcibar, offset + 0xA0) &
					0xFFFFFF);

	pm8001_dbg(pm8001_ha, INIT, "GST OFFSET 0x%x\n",
		   pm8001_cr32(pm8001_ha, pcibar, offset + 0x18));
	pm8001_dbg(pm8001_ha, INIT, "INBND OFFSET 0x%x\n",
		   pm8001_cr32(pm8001_ha, pcibar, offset + 0x1C));
	pm8001_dbg(pm8001_ha, INIT, "OBND OFFSET 0x%x\n",
		   pm8001_cr32(pm8001_ha, pcibar, offset + 0x20));
	pm8001_dbg(pm8001_ha, INIT, "IVT OFFSET 0x%x\n",
		   pm8001_cr32(pm8001_ha, pcibar, offset + 0x8C));
	pm8001_dbg(pm8001_ha, INIT, "PSPA OFFSET 0x%x\n",
		   pm8001_cr32(pm8001_ha, pcibar, offset + 0x90));
	pm8001_dbg(pm8001_ha, INIT, "addr - main cfg %p general status %p\n",
		   pm8001_ha->मुख्य_cfg_tbl_addr,
		   pm8001_ha->general_stat_tbl_addr);
	pm8001_dbg(pm8001_ha, INIT, "addr - inbnd %p obnd %p\n",
		   pm8001_ha->inbnd_q_tbl_addr,
		   pm8001_ha->outbnd_q_tbl_addr);
	pm8001_dbg(pm8001_ha, INIT, "addr - pspa %p ivt %p\n",
		   pm8001_ha->pspa_q_tbl_addr,
		   pm8001_ha->ivt_tbl_addr);
	वापस 0;
पूर्ण

/**
 * pm80xx_set_thermal_config - support the thermal configuration
 * @pm8001_ha: our hba card inक्रमmation.
 */
पूर्णांक
pm80xx_set_thermal_config(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	काष्ठा set_ctrl_cfg_req payload;
	काष्ठा inbound_queue_table *circularQ;
	पूर्णांक rc;
	u32 tag;
	u32 opc = OPC_INB_SET_CONTROLLER_CONFIG;
	u32 page_code;

	स_रखो(&payload, 0, माप(काष्ठा set_ctrl_cfg_req));
	rc = pm8001_tag_alloc(pm8001_ha, &tag);
	अगर (rc)
		वापस -1;

	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	payload.tag = cpu_to_le32(tag);

	अगर (IS_SPCV_12G(pm8001_ha->pdev))
		page_code = THERMAL_PAGE_CODE_7H;
	अन्यथा
		page_code = THERMAL_PAGE_CODE_8H;

	payload.cfg_pg[0] = (THERMAL_LOG_ENABLE << 9) |
				(THERMAL_ENABLE << 8) | page_code;
	payload.cfg_pg[1] = (LTEMPHIL << 24) | (RTEMPHIL << 8);

	pm8001_dbg(pm8001_ha, DEV,
		   "Setting up thermal config. cfg_pg 0 0x%x cfg_pg 1 0x%x\n",
		   payload.cfg_pg[0], payload.cfg_pg[1]);

	rc = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload,
			माप(payload), 0);
	अगर (rc)
		pm8001_tag_मुक्त(pm8001_ha, tag);
	वापस rc;

पूर्ण

/**
* pm80xx_set_sas_protocol_समयr_config - support the SAS Protocol
* Timer configuration page
* @pm8001_ha: our hba card inक्रमmation.
*/
अटल पूर्णांक
pm80xx_set_sas_protocol_समयr_config(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	काष्ठा set_ctrl_cfg_req payload;
	काष्ठा inbound_queue_table *circularQ;
	SASProtocolTimerConfig_t SASConfigPage;
	पूर्णांक rc;
	u32 tag;
	u32 opc = OPC_INB_SET_CONTROLLER_CONFIG;

	स_रखो(&payload, 0, माप(काष्ठा set_ctrl_cfg_req));
	स_रखो(&SASConfigPage, 0, माप(SASProtocolTimerConfig_t));

	rc = pm8001_tag_alloc(pm8001_ha, &tag);

	अगर (rc)
		वापस -1;

	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	payload.tag = cpu_to_le32(tag);

	SASConfigPage.pageCode        =  SAS_PROTOCOL_TIMER_CONFIG_PAGE;
	SASConfigPage.MST_MSI         =  3 << 15;
	SASConfigPage.STP_SSP_MCT_TMO =  (STP_MCT_TMO << 16) | SSP_MCT_TMO;
	SASConfigPage.STP_FRM_TMO     = (SAS_MAX_OPEN_TIME << 24) |
				(SMP_MAX_CONN_TIMER << 16) | STP_FRM_TIMER;
	SASConfigPage.STP_IDLE_TMO    =  STP_IDLE_TIME;

	अगर (SASConfigPage.STP_IDLE_TMO > 0x3FFFFFF)
		SASConfigPage.STP_IDLE_TMO = 0x3FFFFFF;


	SASConfigPage.OPNRJT_RTRY_INTVL =         (SAS_MFD << 16) |
						SAS_OPNRJT_RTRY_INTVL;
	SASConfigPage.Data_Cmd_OPNRJT_RTRY_TMO =  (SAS_DOPNRJT_RTRY_TMO << 16)
						| SAS_COPNRJT_RTRY_TMO;
	SASConfigPage.Data_Cmd_OPNRJT_RTRY_THR =  (SAS_DOPNRJT_RTRY_THR << 16)
						| SAS_COPNRJT_RTRY_THR;
	SASConfigPage.MAX_AIP =  SAS_MAX_AIP;

	pm8001_dbg(pm8001_ha, INIT, "SASConfigPage.pageCode 0x%08x\n",
		   SASConfigPage.pageCode);
	pm8001_dbg(pm8001_ha, INIT, "SASConfigPage.MST_MSI  0x%08x\n",
		   SASConfigPage.MST_MSI);
	pm8001_dbg(pm8001_ha, INIT, "SASConfigPage.STP_SSP_MCT_TMO  0x%08x\n",
		   SASConfigPage.STP_SSP_MCT_TMO);
	pm8001_dbg(pm8001_ha, INIT, "SASConfigPage.STP_FRM_TMO  0x%08x\n",
		   SASConfigPage.STP_FRM_TMO);
	pm8001_dbg(pm8001_ha, INIT, "SASConfigPage.STP_IDLE_TMO  0x%08x\n",
		   SASConfigPage.STP_IDLE_TMO);
	pm8001_dbg(pm8001_ha, INIT, "SASConfigPage.OPNRJT_RTRY_INTVL  0x%08x\n",
		   SASConfigPage.OPNRJT_RTRY_INTVL);
	pm8001_dbg(pm8001_ha, INIT, "SASConfigPage.Data_Cmd_OPNRJT_RTRY_TMO  0x%08x\n",
		   SASConfigPage.Data_Cmd_OPNRJT_RTRY_TMO);
	pm8001_dbg(pm8001_ha, INIT, "SASConfigPage.Data_Cmd_OPNRJT_RTRY_THR  0x%08x\n",
		   SASConfigPage.Data_Cmd_OPNRJT_RTRY_THR);
	pm8001_dbg(pm8001_ha, INIT, "SASConfigPage.MAX_AIP  0x%08x\n",
		   SASConfigPage.MAX_AIP);

	स_नकल(&payload.cfg_pg, &SASConfigPage,
			 माप(SASProtocolTimerConfig_t));

	rc = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload,
			माप(payload), 0);
	अगर (rc)
		pm8001_tag_मुक्त(pm8001_ha, tag);

	वापस rc;
पूर्ण

/**
 * pm80xx_get_encrypt_info - Check क्रम encryption
 * @pm8001_ha: our hba card inक्रमmation.
 */
अटल पूर्णांक
pm80xx_get_encrypt_info(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	u32 scratch3_value;
	पूर्णांक ret = -1;

	/* Read encryption status from SCRATCH PAD 3 */
	scratch3_value = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_3);

	अगर ((scratch3_value & SCRATCH_PAD3_ENC_MASK) ==
					SCRATCH_PAD3_ENC_READY) अणु
		अगर (scratch3_value & SCRATCH_PAD3_XTS_ENABLED)
			pm8001_ha->encrypt_info.cipher_mode = CIPHER_MODE_XTS;
		अगर ((scratch3_value & SCRATCH_PAD3_SM_MASK) ==
						SCRATCH_PAD3_SMF_ENABLED)
			pm8001_ha->encrypt_info.sec_mode = SEC_MODE_SMF;
		अगर ((scratch3_value & SCRATCH_PAD3_SM_MASK) ==
						SCRATCH_PAD3_SMA_ENABLED)
			pm8001_ha->encrypt_info.sec_mode = SEC_MODE_SMA;
		अगर ((scratch3_value & SCRATCH_PAD3_SM_MASK) ==
						SCRATCH_PAD3_SMB_ENABLED)
			pm8001_ha->encrypt_info.sec_mode = SEC_MODE_SMB;
		pm8001_ha->encrypt_info.status = 0;
		pm8001_dbg(pm8001_ha, INIT,
			   "Encryption: SCRATCH_PAD3_ENC_READY 0x%08X.Cipher mode 0x%x Sec mode 0x%x status 0x%x\n",
			   scratch3_value,
			   pm8001_ha->encrypt_info.cipher_mode,
			   pm8001_ha->encrypt_info.sec_mode,
			   pm8001_ha->encrypt_info.status);
		ret = 0;
	पूर्ण अन्यथा अगर ((scratch3_value & SCRATCH_PAD3_ENC_READY) ==
					SCRATCH_PAD3_ENC_DISABLED) अणु
		pm8001_dbg(pm8001_ha, INIT,
			   "Encryption: SCRATCH_PAD3_ENC_DISABLED 0x%08X\n",
			   scratch3_value);
		pm8001_ha->encrypt_info.status = 0xFFFFFFFF;
		pm8001_ha->encrypt_info.cipher_mode = 0;
		pm8001_ha->encrypt_info.sec_mode = 0;
		ret = 0;
	पूर्ण अन्यथा अगर ((scratch3_value & SCRATCH_PAD3_ENC_MASK) ==
				SCRATCH_PAD3_ENC_DIS_ERR) अणु
		pm8001_ha->encrypt_info.status =
			(scratch3_value & SCRATCH_PAD3_ERR_CODE) >> 16;
		अगर (scratch3_value & SCRATCH_PAD3_XTS_ENABLED)
			pm8001_ha->encrypt_info.cipher_mode = CIPHER_MODE_XTS;
		अगर ((scratch3_value & SCRATCH_PAD3_SM_MASK) ==
					SCRATCH_PAD3_SMF_ENABLED)
			pm8001_ha->encrypt_info.sec_mode = SEC_MODE_SMF;
		अगर ((scratch3_value & SCRATCH_PAD3_SM_MASK) ==
					SCRATCH_PAD3_SMA_ENABLED)
			pm8001_ha->encrypt_info.sec_mode = SEC_MODE_SMA;
		अगर ((scratch3_value & SCRATCH_PAD3_SM_MASK) ==
					SCRATCH_PAD3_SMB_ENABLED)
			pm8001_ha->encrypt_info.sec_mode = SEC_MODE_SMB;
		pm8001_dbg(pm8001_ha, INIT,
			   "Encryption: SCRATCH_PAD3_DIS_ERR 0x%08X.Cipher mode 0x%x sec mode 0x%x status 0x%x\n",
			   scratch3_value,
			   pm8001_ha->encrypt_info.cipher_mode,
			   pm8001_ha->encrypt_info.sec_mode,
			   pm8001_ha->encrypt_info.status);
	पूर्ण अन्यथा अगर ((scratch3_value & SCRATCH_PAD3_ENC_MASK) ==
				 SCRATCH_PAD3_ENC_ENA_ERR) अणु

		pm8001_ha->encrypt_info.status =
			(scratch3_value & SCRATCH_PAD3_ERR_CODE) >> 16;
		अगर (scratch3_value & SCRATCH_PAD3_XTS_ENABLED)
			pm8001_ha->encrypt_info.cipher_mode = CIPHER_MODE_XTS;
		अगर ((scratch3_value & SCRATCH_PAD3_SM_MASK) ==
					SCRATCH_PAD3_SMF_ENABLED)
			pm8001_ha->encrypt_info.sec_mode = SEC_MODE_SMF;
		अगर ((scratch3_value & SCRATCH_PAD3_SM_MASK) ==
					SCRATCH_PAD3_SMA_ENABLED)
			pm8001_ha->encrypt_info.sec_mode = SEC_MODE_SMA;
		अगर ((scratch3_value & SCRATCH_PAD3_SM_MASK) ==
					SCRATCH_PAD3_SMB_ENABLED)
			pm8001_ha->encrypt_info.sec_mode = SEC_MODE_SMB;

		pm8001_dbg(pm8001_ha, INIT,
			   "Encryption: SCRATCH_PAD3_ENA_ERR 0x%08X.Cipher mode 0x%x sec mode 0x%x status 0x%x\n",
			   scratch3_value,
			   pm8001_ha->encrypt_info.cipher_mode,
			   pm8001_ha->encrypt_info.sec_mode,
			   pm8001_ha->encrypt_info.status);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * pm80xx_encrypt_update - update flash with encryption inक्रमmtion
 * @pm8001_ha: our hba card inक्रमmation.
 */
अटल पूर्णांक pm80xx_encrypt_update(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	काष्ठा kek_mgmt_req payload;
	काष्ठा inbound_queue_table *circularQ;
	पूर्णांक rc;
	u32 tag;
	u32 opc = OPC_INB_KEK_MANAGEMENT;

	स_रखो(&payload, 0, माप(काष्ठा kek_mgmt_req));
	rc = pm8001_tag_alloc(pm8001_ha, &tag);
	अगर (rc)
		वापस -1;

	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	payload.tag = cpu_to_le32(tag);
	/* Currently only one key is used. New KEK index is 1.
	 * Current KEK index is 1. Store KEK to NVRAM is 1.
	 */
	payload.new_curidx_ksop = ((1 << 24) | (1 << 16) | (1 << 8) |
					KEK_MGMT_SUBOP_KEYCARDUPDATE);

	pm8001_dbg(pm8001_ha, DEV,
		   "Saving Encryption info to flash. payload 0x%x\n",
		   payload.new_curidx_ksop);

	rc = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload,
			माप(payload), 0);
	अगर (rc)
		pm8001_tag_मुक्त(pm8001_ha, tag);

	वापस rc;
पूर्ण

/**
 * pm80xx_chip_init - the मुख्य init function that initialize whole PM8001 chip.
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल पूर्णांक pm80xx_chip_init(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	पूर्णांक ret;
	u8 i = 0;

	/* check the firmware status */
	अगर (-1 == check_fw_पढ़ोy(pm8001_ha)) अणु
		pm8001_dbg(pm8001_ha, FAIL, "Firmware is not ready!\n");
		वापस -EBUSY;
	पूर्ण

	/* Initialize the controller fatal error flag */
	pm8001_ha->controller_fatal_error = false;

	/* Initialize pci space address eg: mpi offset */
	ret = init_pci_device_addresses(pm8001_ha);
	अगर (ret) अणु
		pm8001_dbg(pm8001_ha, FAIL,
			"Failed to init pci addresses");
		वापस ret;
	पूर्ण
	init_शेष_table_values(pm8001_ha);
	पढ़ो_मुख्य_config_table(pm8001_ha);
	पढ़ो_general_status_table(pm8001_ha);
	पढ़ो_inbnd_queue_table(pm8001_ha);
	पढ़ो_outbnd_queue_table(pm8001_ha);
	पढ़ो_phy_attr_table(pm8001_ha);

	/* update मुख्य config table ,inbound table and outbound table */
	update_मुख्य_config_table(pm8001_ha);
	क्रम (i = 0; i < pm8001_ha->max_q_num; i++) अणु
		update_inbnd_queue_table(pm8001_ha, i);
		update_outbnd_queue_table(pm8001_ha, i);
	पूर्ण
	/* notअगरy firmware update finished and check initialization status */
	अगर (0 == mpi_init_check(pm8001_ha)) अणु
		pm8001_dbg(pm8001_ha, INIT, "MPI initialize successful!\n");
	पूर्ण अन्यथा
		वापस -EBUSY;

	/* send SAS protocol समयr configuration page to FW */
	ret = pm80xx_set_sas_protocol_समयr_config(pm8001_ha);

	/* Check क्रम encryption */
	अगर (pm8001_ha->chip->encrypt) अणु
		pm8001_dbg(pm8001_ha, INIT, "Checking for encryption\n");
		ret = pm80xx_get_encrypt_info(pm8001_ha);
		अगर (ret == -1) अणु
			pm8001_dbg(pm8001_ha, INIT, "Encryption error !!\n");
			अगर (pm8001_ha->encrypt_info.status == 0x81) अणु
				pm8001_dbg(pm8001_ha, INIT,
					   "Encryption enabled with error.Saving encryption key to flash\n");
				pm80xx_encrypt_update(pm8001_ha);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mpi_uninit_check(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	u32 max_रुको_count;
	u32 value;
	u32 gst_len_mpistate;
	पूर्णांक ret;

	ret = init_pci_device_addresses(pm8001_ha);
	अगर (ret) अणु
		pm8001_dbg(pm8001_ha, FAIL,
			"Failed to init pci addresses");
		वापस ret;
	पूर्ण

	/* Write bit1=1 to Inbound DoorBell Register to tell the SPC FW the
	table is stop */
	pm8001_cw32(pm8001_ha, 0, MSGU_IBDB_SET, SPCv_MSGU_CFG_TABLE_RESET);

	/* रुको until Inbound DoorBell Clear Register toggled */
	अगर (IS_SPCV_12G(pm8001_ha->pdev)) अणु
		max_रुको_count = SPCV_DOORBELL_CLEAR_TIMEOUT;
	पूर्ण अन्यथा अणु
		max_रुको_count = SPC_DOORBELL_CLEAR_TIMEOUT;
	पूर्ण
	करो अणु
		msleep(FW_READY_INTERVAL);
		value = pm8001_cr32(pm8001_ha, 0, MSGU_IBDB_SET);
		value &= SPCv_MSGU_CFG_TABLE_RESET;
	पूर्ण जबतक ((value != 0) && (--max_रुको_count));

	अगर (!max_रुको_count) अणु
		pm8001_dbg(pm8001_ha, FAIL, "TIMEOUT:IBDB value/=%x\n", value);
		वापस -1;
	पूर्ण

	/* check the MPI-State क्रम termination in progress */
	/* रुको until Inbound DoorBell Clear Register toggled */
	max_रुको_count = 100; /* 2 sec क्रम spcv/ve */
	करो अणु
		msleep(FW_READY_INTERVAL);
		gst_len_mpistate =
			pm8001_mr32(pm8001_ha->general_stat_tbl_addr,
			GST_GSTLEN_MPIS_OFFSET);
		अगर (GST_MPI_STATE_UNINIT ==
			(gst_len_mpistate & GST_MPI_STATE_MASK))
			अवरोध;
	पूर्ण जबतक (--max_रुको_count);
	अगर (!max_रुको_count) अणु
		pm8001_dbg(pm8001_ha, FAIL, " TIME OUT MPI State = 0x%x\n",
			   gst_len_mpistate & GST_MPI_STATE_MASK);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pm80xx_fatal_errors - वापसs non zero *ONLY* when fatal errors
 * @pm8001_ha: our hba card inक्रमmation
 *
 * Fatal errors are recoverable only after a host reboot.
 */
पूर्णांक
pm80xx_fatal_errors(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	पूर्णांक ret = 0;
	u32 scratch_pad_rsvd0 = pm8001_cr32(pm8001_ha, 0,
					MSGU_HOST_SCRATCH_PAD_6);
	u32 scratch_pad_rsvd1 = pm8001_cr32(pm8001_ha, 0,
					MSGU_HOST_SCRATCH_PAD_7);
	u32 scratch_pad1 = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1);
	u32 scratch_pad2 = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_2);
	u32 scratch_pad3 = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_3);

	अगर (pm8001_ha->chip_id != chip_8006 &&
			pm8001_ha->chip_id != chip_8074 &&
			pm8001_ha->chip_id != chip_8076) अणु
		वापस 0;
	पूर्ण

	अगर (MSGU_SCRATCHPAD1_STATE_FATAL_ERROR(scratch_pad1)) अणु
		pm8001_dbg(pm8001_ha, FAIL,
			"Fatal error SCRATCHPAD1 = 0x%x SCRATCHPAD2 = 0x%x SCRATCHPAD3 = 0x%x SCRATCHPAD_RSVD0 = 0x%x SCRATCHPAD_RSVD1 = 0x%x\n",
				scratch_pad1, scratch_pad2, scratch_pad3,
				scratch_pad_rsvd0, scratch_pad_rsvd1);
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * pm80xx_chip_soft_rst - soft reset the PM8001 chip, so that the clear all
 * the FW रेजिस्टर status to the originated status.
 * @pm8001_ha: our hba card inक्रमmation
 */

अटल पूर्णांक
pm80xx_chip_soft_rst(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	u32 regval;
	u32 bootloader_state;
	u32 ibutton0, ibutton1;

	/* Process MPI table uninitialization only अगर FW is पढ़ोy */
	अगर (!pm8001_ha->controller_fatal_error) अणु
		/* Check अगर MPI is in पढ़ोy state to reset */
		अगर (mpi_uninit_check(pm8001_ha) != 0) अणु
			u32 r0 = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_0);
			u32 r1 = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1);
			u32 r2 = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_2);
			u32 r3 = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_3);
			pm8001_dbg(pm8001_ha, FAIL,
				   "MPI state is not ready scratch: %x:%x:%x:%x\n",
				   r0, r1, r2, r3);
			/* अगर things aren't पढ़ोy but the bootloader is ok then
			 * try the reset anyway.
			 */
			अगर (r1 & SCRATCH_PAD1_BOOTSTATE_MASK)
				वापस -1;
		पूर्ण
	पूर्ण
	/* checked क्रम reset रेजिस्टर normal state; 0x0 */
	regval = pm8001_cr32(pm8001_ha, 0, SPC_REG_SOFT_RESET);
	pm8001_dbg(pm8001_ha, INIT, "reset register before write : 0x%x\n",
		   regval);

	pm8001_cw32(pm8001_ha, 0, SPC_REG_SOFT_RESET, SPCv_NORMAL_RESET_VALUE);
	msleep(500);

	regval = pm8001_cr32(pm8001_ha, 0, SPC_REG_SOFT_RESET);
	pm8001_dbg(pm8001_ha, INIT, "reset register after write 0x%x\n",
		   regval);

	अगर ((regval & SPCv_SOFT_RESET_READ_MASK) ==
			SPCv_SOFT_RESET_NORMAL_RESET_OCCURED) अणु
		pm8001_dbg(pm8001_ha, MSG,
			   " soft reset successful [regval: 0x%x]\n",
			   regval);
	पूर्ण अन्यथा अणु
		pm8001_dbg(pm8001_ha, MSG,
			   " soft reset failed [regval: 0x%x]\n",
			   regval);

		/* check bootloader is successfully executed or in HDA mode */
		bootloader_state =
			pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1) &
			SCRATCH_PAD1_BOOTSTATE_MASK;

		अगर (bootloader_state == SCRATCH_PAD1_BOOTSTATE_HDA_SEEPROM) अणु
			pm8001_dbg(pm8001_ha, MSG,
				   "Bootloader state - HDA mode SEEPROM\n");
		पूर्ण अन्यथा अगर (bootloader_state ==
				SCRATCH_PAD1_BOOTSTATE_HDA_BOOTSTRAP) अणु
			pm8001_dbg(pm8001_ha, MSG,
				   "Bootloader state - HDA mode Bootstrap Pin\n");
		पूर्ण अन्यथा अगर (bootloader_state ==
				SCRATCH_PAD1_BOOTSTATE_HDA_SOFTRESET) अणु
			pm8001_dbg(pm8001_ha, MSG,
				   "Bootloader state - HDA mode soft reset\n");
		पूर्ण अन्यथा अगर (bootloader_state ==
					SCRATCH_PAD1_BOOTSTATE_CRIT_ERROR) अणु
			pm8001_dbg(pm8001_ha, MSG,
				   "Bootloader state-HDA mode critical error\n");
		पूर्ण
		वापस -EBUSY;
	पूर्ण

	/* check the firmware status after reset */
	अगर (-1 == check_fw_पढ़ोy(pm8001_ha)) अणु
		pm8001_dbg(pm8001_ha, FAIL, "Firmware is not ready!\n");
		/* check iButton feature support क्रम motherboard controller */
		अगर (pm8001_ha->pdev->subप्रणाली_venकरोr !=
			PCI_VENDOR_ID_ADAPTEC2 &&
			pm8001_ha->pdev->subप्रणाली_venकरोr !=
			PCI_VENDOR_ID_ATTO &&
			pm8001_ha->pdev->subप्रणाली_venकरोr != 0) अणु
			ibutton0 = pm8001_cr32(pm8001_ha, 0,
					MSGU_HOST_SCRATCH_PAD_6);
			ibutton1 = pm8001_cr32(pm8001_ha, 0,
					MSGU_HOST_SCRATCH_PAD_7);
			अगर (!ibutton0 && !ibutton1) अणु
				pm8001_dbg(pm8001_ha, FAIL,
					   "iButton Feature is not Available!!!\n");
				वापस -EBUSY;
			पूर्ण
			अगर (ibutton0 == 0xdeadbeef && ibutton1 == 0xdeadbeef) अणु
				pm8001_dbg(pm8001_ha, FAIL,
					   "CRC Check for iButton Feature Failed!!!\n");
				वापस -EBUSY;
			पूर्ण
		पूर्ण
	पूर्ण
	pm8001_dbg(pm8001_ha, INIT, "SPCv soft reset Complete\n");
	वापस 0;
पूर्ण

अटल व्योम pm80xx_hw_chip_rst(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	u32 i;

	pm8001_dbg(pm8001_ha, INIT, "chip reset start\n");

	/* करो SPCv chip reset. */
	pm8001_cw32(pm8001_ha, 0, SPC_REG_SOFT_RESET, 0x11);
	pm8001_dbg(pm8001_ha, INIT, "SPC soft reset Complete\n");

	/* Check this ..whether delay is required or no */
	/* delay 10 usec */
	udelay(10);

	/* रुको क्रम 20 msec until the firmware माला_लो reloaded */
	i = 20;
	करो अणु
		mdelay(1);
	पूर्ण जबतक ((--i) != 0);

	pm8001_dbg(pm8001_ha, INIT, "chip reset finished\n");
पूर्ण

/**
 * pm80xx_chip_पूर्णांकx_पूर्णांकerrupt_enable - enable PM8001 chip पूर्णांकerrupt
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल व्योम
pm80xx_chip_पूर्णांकx_पूर्णांकerrupt_enable(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	pm8001_cw32(pm8001_ha, 0, MSGU_ODMR, ODMR_CLEAR_ALL);
	pm8001_cw32(pm8001_ha, 0, MSGU_ODCR, ODCR_CLEAR_ALL);
पूर्ण

/**
 * pm80xx_chip_पूर्णांकx_पूर्णांकerrupt_disable - disable PM8001 chip पूर्णांकerrupt
 * @pm8001_ha: our hba card inक्रमmation
 */
अटल व्योम
pm80xx_chip_पूर्णांकx_पूर्णांकerrupt_disable(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	pm8001_cw32(pm8001_ha, 0, MSGU_ODMR_CLR, ODMR_MASK_ALL);
पूर्ण

/**
 * pm80xx_chip_पूर्णांकerrupt_enable - enable PM8001 chip पूर्णांकerrupt
 * @pm8001_ha: our hba card inक्रमmation
 * @vec: पूर्णांकerrupt number to enable
 */
अटल व्योम
pm80xx_chip_पूर्णांकerrupt_enable(काष्ठा pm8001_hba_info *pm8001_ha, u8 vec)
अणु
#अगर_घोषित PM8001_USE_MSIX
	u32 mask;
	mask = (u32)(1 << vec);

	pm8001_cw32(pm8001_ha, 0, MSGU_ODMR_CLR, (u32)(mask & 0xFFFFFFFF));
	वापस;
#पूर्ण_अगर
	pm80xx_chip_पूर्णांकx_पूर्णांकerrupt_enable(pm8001_ha);

पूर्ण

/**
 * pm80xx_chip_पूर्णांकerrupt_disable - disable PM8001 chip पूर्णांकerrupt
 * @pm8001_ha: our hba card inक्रमmation
 * @vec: पूर्णांकerrupt number to disable
 */
अटल व्योम
pm80xx_chip_पूर्णांकerrupt_disable(काष्ठा pm8001_hba_info *pm8001_ha, u8 vec)
अणु
#अगर_घोषित PM8001_USE_MSIX
	u32 mask;
	अगर (vec == 0xFF)
		mask = 0xFFFFFFFF;
	अन्यथा
		mask = (u32)(1 << vec);
	pm8001_cw32(pm8001_ha, 0, MSGU_ODMR, (u32)(mask & 0xFFFFFFFF));
	वापस;
#पूर्ण_अगर
	pm80xx_chip_पूर्णांकx_पूर्णांकerrupt_disable(pm8001_ha);
पूर्ण

अटल व्योम pm80xx_send_पात_all(काष्ठा pm8001_hba_info *pm8001_ha,
		काष्ठा pm8001_device *pm8001_ha_dev)
अणु
	पूर्णांक res;
	u32 ccb_tag;
	काष्ठा pm8001_ccb_info *ccb;
	काष्ठा sas_task *task = शून्य;
	काष्ठा task_पात_req task_पात;
	काष्ठा inbound_queue_table *circularQ;
	u32 opc = OPC_INB_SATA_ABORT;
	पूर्णांक ret;

	अगर (!pm8001_ha_dev) अणु
		pm8001_dbg(pm8001_ha, FAIL, "dev is null\n");
		वापस;
	पूर्ण

	task = sas_alloc_slow_task(GFP_ATOMIC);

	अगर (!task) अणु
		pm8001_dbg(pm8001_ha, FAIL, "cannot allocate task\n");
		वापस;
	पूर्ण

	task->task_करोne = pm8001_task_करोne;

	res = pm8001_tag_alloc(pm8001_ha, &ccb_tag);
	अगर (res) अणु
		sas_मुक्त_task(task);
		वापस;
	पूर्ण

	ccb = &pm8001_ha->ccb_info[ccb_tag];
	ccb->device = pm8001_ha_dev;
	ccb->ccb_tag = ccb_tag;
	ccb->task = task;

	circularQ = &pm8001_ha->inbnd_q_tbl[0];

	स_रखो(&task_पात, 0, माप(task_पात));
	task_पात.पात_all = cpu_to_le32(1);
	task_पात.device_id = cpu_to_le32(pm8001_ha_dev->device_id);
	task_पात.tag = cpu_to_le32(ccb_tag);

	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &task_पात,
			माप(task_पात), 0);
	pm8001_dbg(pm8001_ha, FAIL, "Executing abort task end\n");
	अगर (ret) अणु
		sas_मुक्त_task(task);
		pm8001_tag_मुक्त(pm8001_ha, ccb_tag);
	पूर्ण
पूर्ण

अटल व्योम pm80xx_send_पढ़ो_log(काष्ठा pm8001_hba_info *pm8001_ha,
		काष्ठा pm8001_device *pm8001_ha_dev)
अणु
	काष्ठा sata_start_req sata_cmd;
	पूर्णांक res;
	u32 ccb_tag;
	काष्ठा pm8001_ccb_info *ccb;
	काष्ठा sas_task *task = शून्य;
	काष्ठा host_to_dev_fis fis;
	काष्ठा करोमुख्य_device *dev;
	काष्ठा inbound_queue_table *circularQ;
	u32 opc = OPC_INB_SATA_HOST_OPSTART;

	task = sas_alloc_slow_task(GFP_ATOMIC);

	अगर (!task) अणु
		pm8001_dbg(pm8001_ha, FAIL, "cannot allocate task !!!\n");
		वापस;
	पूर्ण
	task->task_करोne = pm8001_task_करोne;

	res = pm8001_tag_alloc(pm8001_ha, &ccb_tag);
	अगर (res) अणु
		sas_मुक्त_task(task);
		pm8001_dbg(pm8001_ha, FAIL, "cannot allocate tag !!!\n");
		वापस;
	पूर्ण

	/* allocate करोमुख्य device by ourselves as libsas
	 * is not going to provide any
	*/
	dev = kzalloc(माप(काष्ठा करोमुख्य_device), GFP_ATOMIC);
	अगर (!dev) अणु
		sas_मुक्त_task(task);
		pm8001_tag_मुक्त(pm8001_ha, ccb_tag);
		pm8001_dbg(pm8001_ha, FAIL,
			   "Domain device cannot be allocated\n");
		वापस;
	पूर्ण

	task->dev = dev;
	task->dev->lldd_dev = pm8001_ha_dev;

	ccb = &pm8001_ha->ccb_info[ccb_tag];
	ccb->device = pm8001_ha_dev;
	ccb->ccb_tag = ccb_tag;
	ccb->task = task;
	ccb->n_elem = 0;
	pm8001_ha_dev->id |= NCQ_READ_LOG_FLAG;
	pm8001_ha_dev->id |= NCQ_2ND_RLE_FLAG;

	स_रखो(&sata_cmd, 0, माप(sata_cmd));
	circularQ = &pm8001_ha->inbnd_q_tbl[0];

	/* स्थिरruct पढ़ो log FIS */
	स_रखो(&fis, 0, माप(काष्ठा host_to_dev_fis));
	fis.fis_type = 0x27;
	fis.flags = 0x80;
	fis.command = ATA_CMD_READ_LOG_EXT;
	fis.lbal = 0x10;
	fis.sector_count = 0x1;

	sata_cmd.tag = cpu_to_le32(ccb_tag);
	sata_cmd.device_id = cpu_to_le32(pm8001_ha_dev->device_id);
	sata_cmd.ncqtag_atap_dir_m_dad |= ((0x1 << 7) | (0x5 << 9));
	स_नकल(&sata_cmd.sata_fis, &fis, माप(काष्ठा host_to_dev_fis));

	res = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &sata_cmd,
			माप(sata_cmd), 0);
	pm8001_dbg(pm8001_ha, FAIL, "Executing read log end\n");
	अगर (res) अणु
		sas_मुक्त_task(task);
		pm8001_tag_मुक्त(pm8001_ha, ccb_tag);
		kमुक्त(dev);
	पूर्ण
पूर्ण

/**
 * mpi_ssp_completion- process the event that FW response to the SSP request.
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: the message contents of this outbound message.
 *
 * When FW has completed a ssp request क्रम example a IO request, after it has
 * filled the SG data with the data, it will trigger this event represent
 * that he has finished the job,please check the coresponding buffer.
 * So we will tell the caller who maybe रुकोing the result to tell upper layer
 * that the task has been finished.
 */
अटल व्योम
mpi_ssp_completion(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा sas_task *t;
	काष्ठा pm8001_ccb_info *ccb;
	अचिन्हित दीर्घ flags;
	u32 status;
	u32 param;
	u32 tag;
	काष्ठा ssp_completion_resp *psspPayload;
	काष्ठा task_status_काष्ठा *ts;
	काष्ठा ssp_response_iu *iu;
	काष्ठा pm8001_device *pm8001_dev;
	psspPayload = (काष्ठा ssp_completion_resp *)(piomb + 4);
	status = le32_to_cpu(psspPayload->status);
	tag = le32_to_cpu(psspPayload->tag);
	ccb = &pm8001_ha->ccb_info[tag];
	अगर ((status == IO_ABORTED) && ccb->खोलो_retry) अणु
		/* Being completed by another */
		ccb->खोलो_retry = 0;
		वापस;
	पूर्ण
	pm8001_dev = ccb->device;
	param = le32_to_cpu(psspPayload->param);
	t = ccb->task;

	अगर (status && status != IO_UNDERFLOW)
		pm8001_dbg(pm8001_ha, FAIL, "sas IO status 0x%x\n", status);
	अगर (unlikely(!t || !t->lldd_task || !t->dev))
		वापस;
	ts = &t->task_status;

	pm8001_dbg(pm8001_ha, DEV,
		   "tag::0x%x, status::0x%x task::0x%p\n", tag, status, t);

	/* Prपूर्णांक sas address of IO failed device */
	अगर ((status != IO_SUCCESS) && (status != IO_OVERFLOW) &&
		(status != IO_UNDERFLOW))
		pm8001_dbg(pm8001_ha, FAIL, "SAS Address of IO Failure Drive:%016llx\n",
			   SAS_ADDR(t->dev->sas_addr));

	चयन (status) अणु
	हाल IO_SUCCESS:
		pm8001_dbg(pm8001_ha, IO, "IO_SUCCESS ,param = 0x%x\n",
			   param);
		अगर (param == 0) अणु
			ts->resp = SAS_TASK_COMPLETE;
			ts->stat = SAM_STAT_GOOD;
		पूर्ण अन्यथा अणु
			ts->resp = SAS_TASK_COMPLETE;
			ts->stat = SAS_PROTO_RESPONSE;
			ts->residual = param;
			iu = &psspPayload->ssp_resp_iu;
			sas_ssp_task_response(pm8001_ha->dev, t, iu);
		पूर्ण
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_ABORTED:
		pm8001_dbg(pm8001_ha, IO, "IO_ABORTED IOMB Tag\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_ABORTED_TASK;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_UNDERFLOW:
		/* SSP Completion with error */
		pm8001_dbg(pm8001_ha, IO, "IO_UNDERFLOW ,param = 0x%x\n",
			   param);
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_UNDERRUN;
		ts->residual = param;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_NO_DEVICE:
		pm8001_dbg(pm8001_ha, IO, "IO_NO_DEVICE\n");
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_PHY_DOWN;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_BREAK:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_BREAK\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		/* Force the midlayer to retry */
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_PHY_NOT_READY:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_PHY_NOT_READY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_INVALID_SSP_RSP_FRAME:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_XFER_ERROR_INVALID_SSP_RSP_FRAME\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_EPROTO;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_ZONE_VIOLATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_ZONE_VIOLATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_BREAK:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_BREAK\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS:
	हाल IO_XFER_OPEN_RETRY_BACKOFF_THRESHOLD_REACHED:
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_OPEN_TMO:
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_NO_DEST:
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_OPEN_COLLIDE:
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_PATHWAY_BLOCKED:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
		अगर (!t->uldd_task)
			pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_BAD_DESTINATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_BAD_DESTINATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_BAD_DEST;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_CONN_RATE;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_WRONG_DESTINATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_WRONG_DESTINATION\n");
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_WRONG_DEST;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_NAK_RECEIVED:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_NAK_RECEIVED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_ACK_NAK_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_ACK_NAK_TIMEOUT\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_NAK_R_ERR;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_DMA:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_DMA\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_OPEN_RETRY_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_OPEN_RETRY_TIMEOUT\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_OFFSET_MISMATCH:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_OFFSET_MISMATCH\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_PORT_IN_RESET:
		pm8001_dbg(pm8001_ha, IO, "IO_PORT_IN_RESET\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_DS_NON_OPERATIONAL:
		pm8001_dbg(pm8001_ha, IO, "IO_DS_NON_OPERATIONAL\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		अगर (!t->uldd_task)
			pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_DS_NON_OPERATIONAL);
		अवरोध;
	हाल IO_DS_IN_RECOVERY:
		pm8001_dbg(pm8001_ha, IO, "IO_DS_IN_RECOVERY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_TM_TAG_NOT_FOUND:
		pm8001_dbg(pm8001_ha, IO, "IO_TM_TAG_NOT_FOUND\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_SSP_EXT_IU_ZERO_LEN_ERROR:
		pm8001_dbg(pm8001_ha, IO, "IO_SSP_EXT_IU_ZERO_LEN_ERROR\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_HW_RESOURCE_BUSY:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_HW_RESOURCE_BUSY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	शेष:
		pm8001_dbg(pm8001_ha, DEVIO, "Unknown status 0x%x\n", status);
		/* not allowed हाल. Thereक्रमe, वापस failed status */
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	पूर्ण
	pm8001_dbg(pm8001_ha, IO, "scsi_status = 0x%x\n ",
		   psspPayload->ssp_resp_iu.status);
	spin_lock_irqsave(&t->task_state_lock, flags);
	t->task_state_flags &= ~SAS_TASK_STATE_PENDING;
	t->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
	t->task_state_flags |= SAS_TASK_STATE_DONE;
	अगर (unlikely((t->task_state_flags & SAS_TASK_STATE_ABORTED))) अणु
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_dbg(pm8001_ha, FAIL,
			   "task 0x%p done with io_status 0x%x resp 0x%x stat 0x%x but aborted by upper layer!\n",
			   t, status, ts->resp, ts->stat);
		अगर (t->slow_task)
			complete(&t->slow_task->completion);
		pm8001_ccb_task_मुक्त(pm8001_ha, t, ccb, tag);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_ccb_task_मुक्त(pm8001_ha, t, ccb, tag);
		mb();/* in order to क्रमce CPU ordering */
		t->task_करोne(t);
	पूर्ण
पूर्ण

/*See the comments क्रम mpi_ssp_completion */
अटल व्योम mpi_ssp_event(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा sas_task *t;
	अचिन्हित दीर्घ flags;
	काष्ठा task_status_काष्ठा *ts;
	काष्ठा pm8001_ccb_info *ccb;
	काष्ठा pm8001_device *pm8001_dev;
	काष्ठा ssp_event_resp *psspPayload =
		(काष्ठा ssp_event_resp *)(piomb + 4);
	u32 event = le32_to_cpu(psspPayload->event);
	u32 tag = le32_to_cpu(psspPayload->tag);
	u32 port_id = le32_to_cpu(psspPayload->port_id);

	ccb = &pm8001_ha->ccb_info[tag];
	t = ccb->task;
	pm8001_dev = ccb->device;
	अगर (event)
		pm8001_dbg(pm8001_ha, FAIL, "sas IO status 0x%x\n", event);
	अगर (unlikely(!t || !t->lldd_task || !t->dev))
		वापस;
	ts = &t->task_status;
	pm8001_dbg(pm8001_ha, IOERR, "port_id:0x%x, tag:0x%x, event:0x%x\n",
		   port_id, tag, event);
	चयन (event) अणु
	हाल IO_OVERFLOW:
		pm8001_dbg(pm8001_ha, IO, "IO_UNDERFLOW\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		ts->residual = 0;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_BREAK:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_BREAK\n");
		pm8001_handle_event(pm8001_ha, t, IO_XFER_ERROR_BREAK);
		वापस;
	हाल IO_XFER_ERROR_PHY_NOT_READY:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_PHY_NOT_READY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_EPROTO;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_ZONE_VIOLATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_ZONE_VIOLATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_BREAK:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_BREAK\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS:
	हाल IO_XFER_OPEN_RETRY_BACKOFF_THRESHOLD_REACHED:
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_OPEN_TMO:
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_NO_DEST:
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_OPEN_COLLIDE:
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_PATHWAY_BLOCKED:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
		अगर (!t->uldd_task)
			pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_BAD_DESTINATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_BAD_DESTINATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_BAD_DEST;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_CONN_RATE;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_WRONG_DESTINATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_WRONG_DESTINATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_WRONG_DEST;
		अवरोध;
	हाल IO_XFER_ERROR_NAK_RECEIVED:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_NAK_RECEIVED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	हाल IO_XFER_ERROR_ACK_NAK_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_ACK_NAK_TIMEOUT\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_NAK_R_ERR;
		अवरोध;
	हाल IO_XFER_OPEN_RETRY_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_OPEN_RETRY_TIMEOUT\n");
		pm8001_handle_event(pm8001_ha, t, IO_XFER_OPEN_RETRY_TIMEOUT);
		वापस;
	हाल IO_XFER_ERROR_UNEXPECTED_PHASE:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_UNEXPECTED_PHASE\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		अवरोध;
	हाल IO_XFER_ERROR_XFER_RDY_OVERRUN:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_XFER_RDY_OVERRUN\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		अवरोध;
	हाल IO_XFER_ERROR_XFER_RDY_NOT_EXPECTED:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_XFER_ERROR_XFER_RDY_NOT_EXPECTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		अवरोध;
	हाल IO_XFER_ERROR_CMD_ISSUE_ACK_NAK_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_XFER_ERROR_CMD_ISSUE_ACK_NAK_TIMEOUT\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		अवरोध;
	हाल IO_XFER_ERROR_OFFSET_MISMATCH:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_OFFSET_MISMATCH\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		अवरोध;
	हाल IO_XFER_ERROR_XFER_ZERO_DATA_LEN:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_XFER_ERROR_XFER_ZERO_DATA_LEN\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		अवरोध;
	हाल IO_XFER_ERROR_INTERNAL_CRC_ERROR:
		pm8001_dbg(pm8001_ha, IOERR,
			   "IO_XFR_ERROR_INTERNAL_CRC_ERROR\n");
		/* TBC: used शेष set values */
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		अवरोध;
	हाल IO_XFER_CMD_FRAME_ISSUED:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_CMD_FRAME_ISSUED\n");
		वापस;
	शेष:
		pm8001_dbg(pm8001_ha, DEVIO, "Unknown status 0x%x\n", event);
		/* not allowed हाल. Thereक्रमe, वापस failed status */
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		अवरोध;
	पूर्ण
	spin_lock_irqsave(&t->task_state_lock, flags);
	t->task_state_flags &= ~SAS_TASK_STATE_PENDING;
	t->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
	t->task_state_flags |= SAS_TASK_STATE_DONE;
	अगर (unlikely((t->task_state_flags & SAS_TASK_STATE_ABORTED))) अणु
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_dbg(pm8001_ha, FAIL,
			   "task 0x%p done with event 0x%x resp 0x%x stat 0x%x but aborted by upper layer!\n",
			   t, event, ts->resp, ts->stat);
		pm8001_ccb_task_मुक्त(pm8001_ha, t, ccb, tag);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_ccb_task_मुक्त(pm8001_ha, t, ccb, tag);
		mb();/* in order to क्रमce CPU ordering */
		t->task_करोne(t);
	पूर्ण
पूर्ण

/*See the comments क्रम mpi_ssp_completion */
अटल व्योम
mpi_sata_completion(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा sas_task *t;
	काष्ठा pm8001_ccb_info *ccb;
	u32 param;
	u32 status;
	u32 tag;
	पूर्णांक i, j;
	u8 sata_addr_low[4];
	u32 temp_sata_addr_low, temp_sata_addr_hi;
	u8 sata_addr_hi[4];
	काष्ठा sata_completion_resp *psataPayload;
	काष्ठा task_status_काष्ठा *ts;
	काष्ठा ata_task_resp *resp ;
	u32 *sata_resp;
	काष्ठा pm8001_device *pm8001_dev;
	अचिन्हित दीर्घ flags;

	psataPayload = (काष्ठा sata_completion_resp *)(piomb + 4);
	status = le32_to_cpu(psataPayload->status);
	tag = le32_to_cpu(psataPayload->tag);

	अगर (!tag) अणु
		pm8001_dbg(pm8001_ha, FAIL, "tag null\n");
		वापस;
	पूर्ण
	ccb = &pm8001_ha->ccb_info[tag];
	param = le32_to_cpu(psataPayload->param);
	अगर (ccb) अणु
		t = ccb->task;
		pm8001_dev = ccb->device;
	पूर्ण अन्यथा अणु
		pm8001_dbg(pm8001_ha, FAIL, "ccb null\n");
		वापस;
	पूर्ण

	अगर (t) अणु
		अगर (t->dev && (t->dev->lldd_dev))
			pm8001_dev = t->dev->lldd_dev;
	पूर्ण अन्यथा अणु
		pm8001_dbg(pm8001_ha, FAIL, "task null\n");
		वापस;
	पूर्ण

	अगर ((pm8001_dev && !(pm8001_dev->id & NCQ_READ_LOG_FLAG))
		&& unlikely(!t || !t->lldd_task || !t->dev)) अणु
		pm8001_dbg(pm8001_ha, FAIL, "task or dev null\n");
		वापस;
	पूर्ण

	ts = &t->task_status;
	अगर (!ts) अणु
		pm8001_dbg(pm8001_ha, FAIL, "ts null\n");
		वापस;
	पूर्ण

	अगर (status != IO_SUCCESS) अणु
		pm8001_dbg(pm8001_ha, FAIL,
			"IO failed device_id %u status 0x%x tag %d\n",
			pm8001_dev->device_id, status, tag);
	पूर्ण

	/* Prपूर्णांक sas address of IO failed device */
	अगर ((status != IO_SUCCESS) && (status != IO_OVERFLOW) &&
		(status != IO_UNDERFLOW)) अणु
		अगर (!((t->dev->parent) &&
			(dev_is_expander(t->dev->parent->dev_type)))) अणु
			क्रम (i = 0, j = 4; i <= 3 && j <= 7; i++, j++)
				sata_addr_low[i] = pm8001_ha->sas_addr[j];
			क्रम (i = 0, j = 0; i <= 3 && j <= 3; i++, j++)
				sata_addr_hi[i] = pm8001_ha->sas_addr[j];
			स_नकल(&temp_sata_addr_low, sata_addr_low,
				माप(sata_addr_low));
			स_नकल(&temp_sata_addr_hi, sata_addr_hi,
				माप(sata_addr_hi));
			temp_sata_addr_hi = (((temp_sata_addr_hi >> 24) & 0xff)
						|((temp_sata_addr_hi << 8) &
						0xff0000) |
						((temp_sata_addr_hi >> 8)
						& 0xff00) |
						((temp_sata_addr_hi << 24) &
						0xff000000));
			temp_sata_addr_low = ((((temp_sata_addr_low >> 24)
						& 0xff) |
						((temp_sata_addr_low << 8)
						& 0xff0000) |
						((temp_sata_addr_low >> 8)
						& 0xff00) |
						((temp_sata_addr_low << 24)
						& 0xff000000)) +
						pm8001_dev->attached_phy +
						0x10);
			pm8001_dbg(pm8001_ha, FAIL,
				   "SAS Address of IO Failure Drive:%08x%08x\n",
				   temp_sata_addr_hi,
				   temp_sata_addr_low);

		पूर्ण अन्यथा अणु
			pm8001_dbg(pm8001_ha, FAIL,
				   "SAS Address of IO Failure Drive:%016llx\n",
				   SAS_ADDR(t->dev->sas_addr));
		पूर्ण
	पूर्ण
	चयन (status) अणु
	हाल IO_SUCCESS:
		pm8001_dbg(pm8001_ha, IO, "IO_SUCCESS\n");
		अगर (param == 0) अणु
			ts->resp = SAS_TASK_COMPLETE;
			ts->stat = SAM_STAT_GOOD;
			/* check अगर response is क्रम SEND READ LOG */
			अगर (pm8001_dev &&
				(pm8001_dev->id & NCQ_READ_LOG_FLAG)) अणु
				/* set new bit क्रम पात_all */
				pm8001_dev->id |= NCQ_ABORT_ALL_FLAG;
				/* clear bit क्रम पढ़ो log */
				pm8001_dev->id = pm8001_dev->id & 0x7FFFFFFF;
				pm80xx_send_पात_all(pm8001_ha, pm8001_dev);
				/* Free the tag */
				pm8001_tag_मुक्त(pm8001_ha, tag);
				sas_मुक्त_task(t);
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			u8 len;
			ts->resp = SAS_TASK_COMPLETE;
			ts->stat = SAS_PROTO_RESPONSE;
			ts->residual = param;
			pm8001_dbg(pm8001_ha, IO,
				   "SAS_PROTO_RESPONSE len = %d\n",
				   param);
			sata_resp = &psataPayload->sata_resp[0];
			resp = (काष्ठा ata_task_resp *)ts->buf;
			अगर (t->ata_task.dma_xfer == 0 &&
			    t->data_dir == DMA_FROM_DEVICE) अणु
				len = माप(काष्ठा pio_setup_fis);
				pm8001_dbg(pm8001_ha, IO,
					   "PIO read len = %d\n", len);
			पूर्ण अन्यथा अगर (t->ata_task.use_ncq) अणु
				len = माप(काष्ठा set_dev_bits_fis);
				pm8001_dbg(pm8001_ha, IO, "FPDMA len = %d\n",
					   len);
			पूर्ण अन्यथा अणु
				len = माप(काष्ठा dev_to_host_fis);
				pm8001_dbg(pm8001_ha, IO, "other len = %d\n",
					   len);
			पूर्ण
			अगर (SAS_STATUS_BUF_SIZE >= माप(*resp)) अणु
				resp->frame_len = len;
				स_नकल(&resp->ending_fis[0], sata_resp, len);
				ts->buf_valid_size = माप(*resp);
			पूर्ण अन्यथा
				pm8001_dbg(pm8001_ha, IO,
					   "response too large\n");
		पूर्ण
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_ABORTED:
		pm8001_dbg(pm8001_ha, IO, "IO_ABORTED IOMB Tag\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_ABORTED_TASK;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
		/* following हालs are to करो हालs */
	हाल IO_UNDERFLOW:
		/* SATA Completion with error */
		pm8001_dbg(pm8001_ha, IO, "IO_UNDERFLOW param = %d\n", param);
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_UNDERRUN;
		ts->residual = param;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_NO_DEVICE:
		pm8001_dbg(pm8001_ha, IO, "IO_NO_DEVICE\n");
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_PHY_DOWN;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_BREAK:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_BREAK\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_INTERRUPTED;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_PHY_NOT_READY:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_PHY_NOT_READY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_EPROTO;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_ZONE_VIOLATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_ZONE_VIOLATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_BREAK:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_BREAK\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_CONT0;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS:
	हाल IO_XFER_OPEN_RETRY_BACKOFF_THRESHOLD_REACHED:
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_OPEN_TMO:
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_NO_DEST:
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_OPEN_COLLIDE:
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_PATHWAY_BLOCKED:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अगर (!t->uldd_task) अणु
			pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS);
			ts->resp = SAS_TASK_UNDELIVERED;
			ts->stat = SAS_QUEUE_FULL;
			pm8001_ccb_task_मुक्त_करोne(pm8001_ha, t, ccb, tag);
			वापस;
		पूर्ण
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_BAD_DESTINATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_BAD_DESTINATION\n");
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_BAD_DEST;
		अगर (!t->uldd_task) अणु
			pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS);
			ts->resp = SAS_TASK_UNDELIVERED;
			ts->stat = SAS_QUEUE_FULL;
			pm8001_ccb_task_मुक्त_करोne(pm8001_ha, t, ccb, tag);
			वापस;
		पूर्ण
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_CONN_RATE;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_STP_RESOURCES_BUSY:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_STP_RESOURCES_BUSY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अगर (!t->uldd_task) अणु
			pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_OPEN_CNX_ERROR_STP_RESOURCES_BUSY);
			ts->resp = SAS_TASK_UNDELIVERED;
			ts->stat = SAS_QUEUE_FULL;
			pm8001_ccb_task_मुक्त_करोne(pm8001_ha, t, ccb, tag);
			वापस;
		पूर्ण
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_WRONG_DESTINATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_WRONG_DESTINATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_WRONG_DEST;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_NAK_RECEIVED:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_NAK_RECEIVED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_NAK_R_ERR;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_ACK_NAK_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_ACK_NAK_TIMEOUT\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_NAK_R_ERR;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_DMA:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_DMA\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_ABORTED_TASK;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_SATA_LINK_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_SATA_LINK_TIMEOUT\n");
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_REJECTED_NCQ_MODE:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_REJECTED_NCQ_MODE\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_UNDERRUN;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_OPEN_RETRY_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_OPEN_RETRY_TIMEOUT\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_PORT_IN_RESET:
		pm8001_dbg(pm8001_ha, IO, "IO_PORT_IN_RESET\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_DS_NON_OPERATIONAL:
		pm8001_dbg(pm8001_ha, IO, "IO_DS_NON_OPERATIONAL\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अगर (!t->uldd_task) अणु
			pm8001_handle_event(pm8001_ha, pm8001_dev,
					IO_DS_NON_OPERATIONAL);
			ts->resp = SAS_TASK_UNDELIVERED;
			ts->stat = SAS_QUEUE_FULL;
			pm8001_ccb_task_मुक्त_करोne(pm8001_ha, t, ccb, tag);
			वापस;
		पूर्ण
		अवरोध;
	हाल IO_DS_IN_RECOVERY:
		pm8001_dbg(pm8001_ha, IO, "IO_DS_IN_RECOVERY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_DS_IN_ERROR:
		pm8001_dbg(pm8001_ha, IO, "IO_DS_IN_ERROR\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अगर (!t->uldd_task) अणु
			pm8001_handle_event(pm8001_ha, pm8001_dev,
					IO_DS_IN_ERROR);
			ts->resp = SAS_TASK_UNDELIVERED;
			ts->stat = SAS_QUEUE_FULL;
			pm8001_ccb_task_मुक्त_करोne(pm8001_ha, t, ccb, tag);
			वापस;
		पूर्ण
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_HW_RESOURCE_BUSY:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_HW_RESOURCE_BUSY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	शेष:
		pm8001_dbg(pm8001_ha, DEVIO,
				"Unknown status device_id %u status 0x%x tag %d\n",
			pm8001_dev->device_id, status, tag);
		/* not allowed हाल. Thereक्रमe, वापस failed status */
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	पूर्ण
	spin_lock_irqsave(&t->task_state_lock, flags);
	t->task_state_flags &= ~SAS_TASK_STATE_PENDING;
	t->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
	t->task_state_flags |= SAS_TASK_STATE_DONE;
	अगर (unlikely((t->task_state_flags & SAS_TASK_STATE_ABORTED))) अणु
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_dbg(pm8001_ha, FAIL,
			   "task 0x%p done with io_status 0x%x resp 0x%x stat 0x%x but aborted by upper layer!\n",
			   t, status, ts->resp, ts->stat);
		अगर (t->slow_task)
			complete(&t->slow_task->completion);
		pm8001_ccb_task_मुक्त(pm8001_ha, t, ccb, tag);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_ccb_task_मुक्त_करोne(pm8001_ha, t, ccb, tag);
	पूर्ण
पूर्ण

/*See the comments क्रम mpi_ssp_completion */
अटल व्योम mpi_sata_event(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा sas_task *t;
	काष्ठा task_status_काष्ठा *ts;
	काष्ठा pm8001_ccb_info *ccb;
	काष्ठा pm8001_device *pm8001_dev;
	काष्ठा sata_event_resp *psataPayload =
		(काष्ठा sata_event_resp *)(piomb + 4);
	u32 event = le32_to_cpu(psataPayload->event);
	u32 tag = le32_to_cpu(psataPayload->tag);
	u32 port_id = le32_to_cpu(psataPayload->port_id);
	u32 dev_id = le32_to_cpu(psataPayload->device_id);
	अचिन्हित दीर्घ flags;

	ccb = &pm8001_ha->ccb_info[tag];

	अगर (ccb) अणु
		t = ccb->task;
		pm8001_dev = ccb->device;
	पूर्ण अन्यथा अणु
		pm8001_dbg(pm8001_ha, FAIL, "No CCB !!!. returning\n");
		वापस;
	पूर्ण
	अगर (event)
		pm8001_dbg(pm8001_ha, FAIL, "SATA EVENT 0x%x\n", event);

	/* Check अगर this is NCQ error */
	अगर (event == IO_XFER_ERROR_ABORTED_NCQ_MODE) अणु
		/* find device using device id */
		pm8001_dev = pm8001_find_dev(pm8001_ha, dev_id);
		/* send पढ़ो log extension */
		अगर (pm8001_dev)
			pm80xx_send_पढ़ो_log(pm8001_ha, pm8001_dev);
		वापस;
	पूर्ण

	अगर (unlikely(!t || !t->lldd_task || !t->dev)) अणु
		pm8001_dbg(pm8001_ha, FAIL, "task or dev null\n");
		वापस;
	पूर्ण

	ts = &t->task_status;
	pm8001_dbg(pm8001_ha, IOERR, "port_id:0x%x, tag:0x%x, event:0x%x\n",
		   port_id, tag, event);
	चयन (event) अणु
	हाल IO_OVERFLOW:
		pm8001_dbg(pm8001_ha, IO, "IO_UNDERFLOW\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		ts->residual = 0;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_XFER_ERROR_BREAK:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_BREAK\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_INTERRUPTED;
		अवरोध;
	हाल IO_XFER_ERROR_PHY_NOT_READY:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_PHY_NOT_READY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_EPROTO;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_ZONE_VIOLATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_ZONE_VIOLATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_BREAK:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_BREAK\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_CONT0;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS:
	हाल IO_XFER_OPEN_RETRY_BACKOFF_THRESHOLD_REACHED:
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_OPEN_TMO:
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_NO_DEST:
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_OPEN_COLLIDE:
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_PATHWAY_BLOCKED:
		pm8001_dbg(pm8001_ha, FAIL,
			   "IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS\n");
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अगर (!t->uldd_task) अणु
			pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS);
			ts->resp = SAS_TASK_COMPLETE;
			ts->stat = SAS_QUEUE_FULL;
			pm8001_ccb_task_मुक्त_करोne(pm8001_ha, t, ccb, tag);
			वापस;
		पूर्ण
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_BAD_DESTINATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_BAD_DESTINATION\n");
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_BAD_DEST;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_CONN_RATE;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_WRONG_DESTINATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_WRONG_DESTINATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_WRONG_DEST;
		अवरोध;
	हाल IO_XFER_ERROR_NAK_RECEIVED:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_NAK_RECEIVED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_NAK_R_ERR;
		अवरोध;
	हाल IO_XFER_ERROR_PEER_ABORTED:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_PEER_ABORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_NAK_R_ERR;
		अवरोध;
	हाल IO_XFER_ERROR_REJECTED_NCQ_MODE:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_REJECTED_NCQ_MODE\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_UNDERRUN;
		अवरोध;
	हाल IO_XFER_OPEN_RETRY_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_OPEN_RETRY_TIMEOUT\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		अवरोध;
	हाल IO_XFER_ERROR_UNEXPECTED_PHASE:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_UNEXPECTED_PHASE\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		अवरोध;
	हाल IO_XFER_ERROR_XFER_RDY_OVERRUN:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_XFER_RDY_OVERRUN\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		अवरोध;
	हाल IO_XFER_ERROR_XFER_RDY_NOT_EXPECTED:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_XFER_ERROR_XFER_RDY_NOT_EXPECTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		अवरोध;
	हाल IO_XFER_ERROR_OFFSET_MISMATCH:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_OFFSET_MISMATCH\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		अवरोध;
	हाल IO_XFER_ERROR_XFER_ZERO_DATA_LEN:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_XFER_ERROR_XFER_ZERO_DATA_LEN\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		अवरोध;
	हाल IO_XFER_CMD_FRAME_ISSUED:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_CMD_FRAME_ISSUED\n");
		अवरोध;
	हाल IO_XFER_PIO_SETUP_ERROR:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_PIO_SETUP_ERROR\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		अवरोध;
	हाल IO_XFER_ERROR_INTERNAL_CRC_ERROR:
		pm8001_dbg(pm8001_ha, FAIL,
			   "IO_XFR_ERROR_INTERNAL_CRC_ERROR\n");
		/* TBC: used शेष set values */
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		अवरोध;
	हाल IO_XFER_DMA_ACTIVATE_TIMEOUT:
		pm8001_dbg(pm8001_ha, FAIL, "IO_XFR_DMA_ACTIVATE_TIMEOUT\n");
		/* TBC: used शेष set values */
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		अवरोध;
	शेष:
		pm8001_dbg(pm8001_ha, IO, "Unknown status 0x%x\n", event);
		/* not allowed हाल. Thereक्रमe, वापस failed status */
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		अवरोध;
	पूर्ण
	spin_lock_irqsave(&t->task_state_lock, flags);
	t->task_state_flags &= ~SAS_TASK_STATE_PENDING;
	t->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
	t->task_state_flags |= SAS_TASK_STATE_DONE;
	अगर (unlikely((t->task_state_flags & SAS_TASK_STATE_ABORTED))) अणु
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_dbg(pm8001_ha, FAIL,
			   "task 0x%p done with io_status 0x%x resp 0x%x stat 0x%x but aborted by upper layer!\n",
			   t, event, ts->resp, ts->stat);
		pm8001_ccb_task_मुक्त(pm8001_ha, t, ccb, tag);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_ccb_task_मुक्त_करोne(pm8001_ha, t, ccb, tag);
	पूर्ण
पूर्ण

/*See the comments क्रम mpi_ssp_completion */
अटल व्योम
mpi_smp_completion(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	u32 param, i;
	काष्ठा sas_task *t;
	काष्ठा pm8001_ccb_info *ccb;
	अचिन्हित दीर्घ flags;
	u32 status;
	u32 tag;
	काष्ठा smp_completion_resp *psmpPayload;
	काष्ठा task_status_काष्ठा *ts;
	काष्ठा pm8001_device *pm8001_dev;
	अक्षर *pdma_respaddr = शून्य;

	psmpPayload = (काष्ठा smp_completion_resp *)(piomb + 4);
	status = le32_to_cpu(psmpPayload->status);
	tag = le32_to_cpu(psmpPayload->tag);

	ccb = &pm8001_ha->ccb_info[tag];
	param = le32_to_cpu(psmpPayload->param);
	t = ccb->task;
	ts = &t->task_status;
	pm8001_dev = ccb->device;
	अगर (status)
		pm8001_dbg(pm8001_ha, FAIL, "smp IO status 0x%x\n", status);
	अगर (unlikely(!t || !t->lldd_task || !t->dev))
		वापस;

	pm8001_dbg(pm8001_ha, DEV, "tag::0x%x status::0x%x\n", tag, status);

	चयन (status) अणु

	हाल IO_SUCCESS:
		pm8001_dbg(pm8001_ha, IO, "IO_SUCCESS\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAM_STAT_GOOD;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अगर (pm8001_ha->smp_exp_mode == SMP_सूचीECT) अणु
			pm8001_dbg(pm8001_ha, IO,
				   "DIRECT RESPONSE Length:%d\n",
				   param);
			pdma_respaddr = (अक्षर *)(phys_to_virt(cpu_to_le64
						((u64)sg_dma_address
						(&t->smp_task.smp_resp))));
			क्रम (i = 0; i < param; i++) अणु
				*(pdma_respaddr+i) = psmpPayload->_r_a[i];
				pm8001_dbg(pm8001_ha, IO,
					   "SMP Byte%d DMA data 0x%x psmp 0x%x\n",
					   i, *(pdma_respaddr + i),
					   psmpPayload->_r_a[i]);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल IO_ABORTED:
		pm8001_dbg(pm8001_ha, IO, "IO_ABORTED IOMB\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_ABORTED_TASK;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_OVERFLOW:
		pm8001_dbg(pm8001_ha, IO, "IO_UNDERFLOW\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		ts->residual = 0;
		अगर (pm8001_dev)
			atomic_dec(&pm8001_dev->running_req);
		अवरोध;
	हाल IO_NO_DEVICE:
		pm8001_dbg(pm8001_ha, IO, "IO_NO_DEVICE\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_PHY_DOWN;
		अवरोध;
	हाल IO_ERROR_HW_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO, "IO_ERROR_HW_TIMEOUT\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAM_STAT_BUSY;
		अवरोध;
	हाल IO_XFER_ERROR_BREAK:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_BREAK\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAM_STAT_BUSY;
		अवरोध;
	हाल IO_XFER_ERROR_PHY_NOT_READY:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_PHY_NOT_READY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAM_STAT_BUSY;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_ZONE_VIOLATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_ZONE_VIOLATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_BREAK:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_BREAK\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_CONT0;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS:
	हाल IO_XFER_OPEN_RETRY_BACKOFF_THRESHOLD_REACHED:
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_OPEN_TMO:
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_NO_DEST:
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_OPEN_COLLIDE:
	हाल IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_PATHWAY_BLOCKED:
		pm8001_dbg(pm8001_ha, IO, "IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
		pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS);
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_BAD_DESTINATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_BAD_DESTINATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_BAD_DEST;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_CONN_RATE;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_WRONG_DESTINATION:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_WRONG_DESTINATION\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_WRONG_DEST;
		अवरोध;
	हाल IO_XFER_ERROR_RX_FRAME:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_ERROR_RX_FRAME\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अवरोध;
	हाल IO_XFER_OPEN_RETRY_TIMEOUT:
		pm8001_dbg(pm8001_ha, IO, "IO_XFER_OPEN_RETRY_TIMEOUT\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	हाल IO_ERROR_INTERNAL_SMP_RESOURCE:
		pm8001_dbg(pm8001_ha, IO, "IO_ERROR_INTERNAL_SMP_RESOURCE\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_QUEUE_FULL;
		अवरोध;
	हाल IO_PORT_IN_RESET:
		pm8001_dbg(pm8001_ha, IO, "IO_PORT_IN_RESET\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	हाल IO_DS_NON_OPERATIONAL:
		pm8001_dbg(pm8001_ha, IO, "IO_DS_NON_OPERATIONAL\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अवरोध;
	हाल IO_DS_IN_RECOVERY:
		pm8001_dbg(pm8001_ha, IO, "IO_DS_IN_RECOVERY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	हाल IO_OPEN_CNX_ERROR_HW_RESOURCE_BUSY:
		pm8001_dbg(pm8001_ha, IO,
			   "IO_OPEN_CNX_ERROR_HW_RESOURCE_BUSY\n");
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		अवरोध;
	शेष:
		pm8001_dbg(pm8001_ha, DEVIO, "Unknown status 0x%x\n", status);
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		/* not allowed हाल. Thereक्रमe, वापस failed status */
		अवरोध;
	पूर्ण
	spin_lock_irqsave(&t->task_state_lock, flags);
	t->task_state_flags &= ~SAS_TASK_STATE_PENDING;
	t->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
	t->task_state_flags |= SAS_TASK_STATE_DONE;
	अगर (unlikely((t->task_state_flags & SAS_TASK_STATE_ABORTED))) अणु
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_dbg(pm8001_ha, FAIL,
			   "task 0x%p done with io_status 0x%x resp 0x%xstat 0x%x but aborted by upper layer!\n",
			   t, status, ts->resp, ts->stat);
		pm8001_ccb_task_मुक्त(pm8001_ha, t, ccb, tag);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_ccb_task_मुक्त(pm8001_ha, t, ccb, tag);
		mb();/* in order to क्रमce CPU ordering */
		t->task_करोne(t);
	पूर्ण
पूर्ण

/**
 * pm80xx_hw_event_ack_req- For PM8001,some events need to acknowage to FW.
 * @pm8001_ha: our hba card inक्रमmation
 * @Qnum: the outbound queue message number.
 * @SEA: source of event to ack
 * @port_id: port id.
 * @phyId: phy id.
 * @param0: parameter 0.
 * @param1: parameter 1.
 */
अटल व्योम pm80xx_hw_event_ack_req(काष्ठा pm8001_hba_info *pm8001_ha,
	u32 Qnum, u32 SEA, u32 port_id, u32 phyId, u32 param0, u32 param1)
अणु
	काष्ठा hw_event_ack_req	 payload;
	u32 opc = OPC_INB_SAS_HW_EVENT_ACK;

	काष्ठा inbound_queue_table *circularQ;

	स_रखो((u8 *)&payload, 0, माप(payload));
	circularQ = &pm8001_ha->inbnd_q_tbl[Qnum];
	payload.tag = cpu_to_le32(1);
	payload.phyid_sea_portid = cpu_to_le32(((SEA & 0xFFFF) << 8) |
		((phyId & 0xFF) << 24) | (port_id & 0xFF));
	payload.param0 = cpu_to_le32(param0);
	payload.param1 = cpu_to_le32(param1);
	pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload,
			माप(payload), 0);
पूर्ण

अटल पूर्णांक pm80xx_chip_phy_ctl_req(काष्ठा pm8001_hba_info *pm8001_ha,
	u32 phyId, u32 phy_op);

अटल व्योम hw_event_port_recover(काष्ठा pm8001_hba_info *pm8001_ha,
					व्योम *piomb)
अणु
	काष्ठा hw_event_resp *pPayload = (काष्ठा hw_event_resp *)(piomb + 4);
	u32 phyid_npip_portstate = le32_to_cpu(pPayload->phyid_npip_portstate);
	u8 phy_id = (u8)((phyid_npip_portstate & 0xFF0000) >> 16);
	u32 lr_status_evt_portid =
		le32_to_cpu(pPayload->lr_status_evt_portid);
	u8 deviceType = pPayload->sas_identअगरy.dev_type;
	u8 link_rate = (u8)((lr_status_evt_portid & 0xF0000000) >> 28);
	काष्ठा pm8001_phy *phy = &pm8001_ha->phy[phy_id];
	u8 port_id = (u8)(lr_status_evt_portid & 0x000000FF);
	काष्ठा pm8001_port *port = &pm8001_ha->port[port_id];

	अगर (deviceType == SAS_END_DEVICE) अणु
		pm80xx_chip_phy_ctl_req(pm8001_ha, phy_id,
					PHY_NOTIFY_ENABLE_SPINUP);
	पूर्ण

	port->wide_port_phymap |= (1U << phy_id);
	pm8001_get_lrate_mode(phy, link_rate);
	phy->sas_phy.oob_mode = SAS_OOB_MODE;
	phy->phy_state = PHY_STATE_LINK_UP_SPCV;
	phy->phy_attached = 1;
पूर्ण

/**
 * hw_event_sas_phy_up -FW tells me a SAS phy up event.
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
अटल व्योम
hw_event_sas_phy_up(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा hw_event_resp *pPayload =
		(काष्ठा hw_event_resp *)(piomb + 4);
	u32 lr_status_evt_portid =
		le32_to_cpu(pPayload->lr_status_evt_portid);
	u32 phyid_npip_portstate = le32_to_cpu(pPayload->phyid_npip_portstate);

	u8 link_rate =
		(u8)((lr_status_evt_portid & 0xF0000000) >> 28);
	u8 port_id = (u8)(lr_status_evt_portid & 0x000000FF);
	u8 phy_id =
		(u8)((phyid_npip_portstate & 0xFF0000) >> 16);
	u8 portstate = (u8)(phyid_npip_portstate & 0x0000000F);

	काष्ठा pm8001_port *port = &pm8001_ha->port[port_id];
	काष्ठा pm8001_phy *phy = &pm8001_ha->phy[phy_id];
	अचिन्हित दीर्घ flags;
	u8 deviceType = pPayload->sas_identअगरy.dev_type;
	port->port_state = portstate;
	port->wide_port_phymap |= (1U << phy_id);
	phy->phy_state = PHY_STATE_LINK_UP_SPCV;
	pm8001_dbg(pm8001_ha, MSG,
		   "portid:%d; phyid:%d; linkrate:%d; portstate:%x; devicetype:%x\n",
		   port_id, phy_id, link_rate, portstate, deviceType);

	चयन (deviceType) अणु
	हाल SAS_PHY_UNUSED:
		pm8001_dbg(pm8001_ha, MSG, "device type no device.\n");
		अवरोध;
	हाल SAS_END_DEVICE:
		pm8001_dbg(pm8001_ha, MSG, "end device.\n");
		pm80xx_chip_phy_ctl_req(pm8001_ha, phy_id,
			PHY_NOTIFY_ENABLE_SPINUP);
		port->port_attached = 1;
		pm8001_get_lrate_mode(phy, link_rate);
		अवरोध;
	हाल SAS_EDGE_EXPANDER_DEVICE:
		pm8001_dbg(pm8001_ha, MSG, "expander device.\n");
		port->port_attached = 1;
		pm8001_get_lrate_mode(phy, link_rate);
		अवरोध;
	हाल SAS_FANOUT_EXPANDER_DEVICE:
		pm8001_dbg(pm8001_ha, MSG, "fanout expander device.\n");
		port->port_attached = 1;
		pm8001_get_lrate_mode(phy, link_rate);
		अवरोध;
	शेष:
		pm8001_dbg(pm8001_ha, DEVIO, "unknown device type(%x)\n",
			   deviceType);
		अवरोध;
	पूर्ण
	phy->phy_type |= PORT_TYPE_SAS;
	phy->identअगरy.device_type = deviceType;
	phy->phy_attached = 1;
	अगर (phy->identअगरy.device_type == SAS_END_DEVICE)
		phy->identअगरy.target_port_protocols = SAS_PROTOCOL_SSP;
	अन्यथा अगर (phy->identअगरy.device_type != SAS_PHY_UNUSED)
		phy->identअगरy.target_port_protocols = SAS_PROTOCOL_SMP;
	phy->sas_phy.oob_mode = SAS_OOB_MODE;
	sas_notअगरy_phy_event(&phy->sas_phy, PHYE_OOB_DONE, GFP_ATOMIC);
	spin_lock_irqsave(&phy->sas_phy.frame_rcvd_lock, flags);
	स_नकल(phy->frame_rcvd, &pPayload->sas_identअगरy,
		माप(काष्ठा sas_identअगरy_frame)-4);
	phy->frame_rcvd_size = माप(काष्ठा sas_identअगरy_frame) - 4;
	pm8001_get_attached_sas_addr(phy, phy->sas_phy.attached_sas_addr);
	spin_unlock_irqrestore(&phy->sas_phy.frame_rcvd_lock, flags);
	अगर (pm8001_ha->flags == PM8001F_RUN_TIME)
		mdelay(200); /* delay a moment to रुको क्रम disk to spin up */
	pm8001_bytes_dmaed(pm8001_ha, phy_id);
पूर्ण

/**
 * hw_event_sata_phy_up -FW tells me a SATA phy up event.
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
अटल व्योम
hw_event_sata_phy_up(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा hw_event_resp *pPayload =
		(काष्ठा hw_event_resp *)(piomb + 4);
	u32 phyid_npip_portstate = le32_to_cpu(pPayload->phyid_npip_portstate);
	u32 lr_status_evt_portid =
		le32_to_cpu(pPayload->lr_status_evt_portid);
	u8 link_rate =
		(u8)((lr_status_evt_portid & 0xF0000000) >> 28);
	u8 port_id = (u8)(lr_status_evt_portid & 0x000000FF);
	u8 phy_id =
		(u8)((phyid_npip_portstate & 0xFF0000) >> 16);

	u8 portstate = (u8)(phyid_npip_portstate & 0x0000000F);

	काष्ठा pm8001_port *port = &pm8001_ha->port[port_id];
	काष्ठा pm8001_phy *phy = &pm8001_ha->phy[phy_id];
	अचिन्हित दीर्घ flags;
	pm8001_dbg(pm8001_ha, DEVIO,
		   "port id %d, phy id %d link_rate %d portstate 0x%x\n",
		   port_id, phy_id, link_rate, portstate);

	port->port_state = portstate;
	phy->phy_state = PHY_STATE_LINK_UP_SPCV;
	port->port_attached = 1;
	pm8001_get_lrate_mode(phy, link_rate);
	phy->phy_type |= PORT_TYPE_SATA;
	phy->phy_attached = 1;
	phy->sas_phy.oob_mode = SATA_OOB_MODE;
	sas_notअगरy_phy_event(&phy->sas_phy, PHYE_OOB_DONE, GFP_ATOMIC);
	spin_lock_irqsave(&phy->sas_phy.frame_rcvd_lock, flags);
	स_नकल(phy->frame_rcvd, ((u8 *)&pPayload->sata_fis - 4),
		माप(काष्ठा dev_to_host_fis));
	phy->frame_rcvd_size = माप(काष्ठा dev_to_host_fis);
	phy->identअगरy.target_port_protocols = SAS_PROTOCOL_SATA;
	phy->identअगरy.device_type = SAS_SATA_DEV;
	pm8001_get_attached_sas_addr(phy, phy->sas_phy.attached_sas_addr);
	spin_unlock_irqrestore(&phy->sas_phy.frame_rcvd_lock, flags);
	pm8001_bytes_dmaed(pm8001_ha, phy_id);
पूर्ण

/**
 * hw_event_phy_करोwn -we should notअगरy the libsas the phy is करोwn.
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
अटल व्योम
hw_event_phy_करोwn(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा hw_event_resp *pPayload =
		(काष्ठा hw_event_resp *)(piomb + 4);

	u32 lr_status_evt_portid =
		le32_to_cpu(pPayload->lr_status_evt_portid);
	u8 port_id = (u8)(lr_status_evt_portid & 0x000000FF);
	u32 phyid_npip_portstate = le32_to_cpu(pPayload->phyid_npip_portstate);
	u8 phy_id =
		(u8)((phyid_npip_portstate & 0xFF0000) >> 16);
	u8 portstate = (u8)(phyid_npip_portstate & 0x0000000F);

	काष्ठा pm8001_port *port = &pm8001_ha->port[port_id];
	काष्ठा pm8001_phy *phy = &pm8001_ha->phy[phy_id];
	u32 port_sata = (phy->phy_type & PORT_TYPE_SATA);
	port->port_state = portstate;
	phy->identअगरy.device_type = 0;
	phy->phy_attached = 0;
	चयन (portstate) अणु
	हाल PORT_VALID:
		अवरोध;
	हाल PORT_INVALID:
		pm8001_dbg(pm8001_ha, MSG, " PortInvalid portID %d\n",
			   port_id);
		pm8001_dbg(pm8001_ha, MSG,
			   " Last phy Down and port invalid\n");
		अगर (port_sata) अणु
			phy->phy_type = 0;
			port->port_attached = 0;
			pm80xx_hw_event_ack_req(pm8001_ha, 0, HW_EVENT_PHY_DOWN,
					port_id, phy_id, 0, 0);
		पूर्ण
		sas_phy_disconnected(&phy->sas_phy);
		अवरोध;
	हाल PORT_IN_RESET:
		pm8001_dbg(pm8001_ha, MSG, " Port In Reset portID %d\n",
			   port_id);
		अवरोध;
	हाल PORT_NOT_ESTABLISHED:
		pm8001_dbg(pm8001_ha, MSG,
			   " Phy Down and PORT_NOT_ESTABLISHED\n");
		port->port_attached = 0;
		अवरोध;
	हाल PORT_LOSTCOMM:
		pm8001_dbg(pm8001_ha, MSG, " Phy Down and PORT_LOSTCOMM\n");
		pm8001_dbg(pm8001_ha, MSG,
			   " Last phy Down and port invalid\n");
		अगर (port_sata) अणु
			port->port_attached = 0;
			phy->phy_type = 0;
			pm80xx_hw_event_ack_req(pm8001_ha, 0, HW_EVENT_PHY_DOWN,
					port_id, phy_id, 0, 0);
		पूर्ण
		sas_phy_disconnected(&phy->sas_phy);
		अवरोध;
	शेष:
		port->port_attached = 0;
		pm8001_dbg(pm8001_ha, DEVIO,
			   " Phy Down and(default) = 0x%x\n",
			   portstate);
		अवरोध;

	पूर्ण
	अगर (port_sata && (portstate != PORT_IN_RESET))
		sas_notअगरy_phy_event(&phy->sas_phy, PHYE_LOSS_OF_SIGNAL,
				GFP_ATOMIC);
पूर्ण

अटल पूर्णांक mpi_phy_start_resp(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा phy_start_resp *pPayload =
		(काष्ठा phy_start_resp *)(piomb + 4);
	u32 status =
		le32_to_cpu(pPayload->status);
	u32 phy_id =
		le32_to_cpu(pPayload->phyid);
	काष्ठा pm8001_phy *phy = &pm8001_ha->phy[phy_id];

	pm8001_dbg(pm8001_ha, INIT,
		   "phy start resp status:0x%x, phyid:0x%x\n",
		   status, phy_id);
	अगर (status == 0)
		phy->phy_state = PHY_LINK_DOWN;

	अगर (pm8001_ha->flags == PM8001F_RUN_TIME &&
			phy->enable_completion != शून्य) अणु
		complete(phy->enable_completion);
		phy->enable_completion = शून्य;
	पूर्ण
	वापस 0;

पूर्ण

/**
 * mpi_thermal_hw_event -The hw event has come.
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
अटल पूर्णांक mpi_thermal_hw_event(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा thermal_hw_event *pPayload =
		(काष्ठा thermal_hw_event *)(piomb + 4);

	u32 thermal_event = le32_to_cpu(pPayload->thermal_event);
	u32 rht_lht = le32_to_cpu(pPayload->rht_lht);

	अगर (thermal_event & 0x40) अणु
		pm8001_dbg(pm8001_ha, IO,
			   "Thermal Event: Local high temperature violated!\n");
		pm8001_dbg(pm8001_ha, IO,
			   "Thermal Event: Measured local high temperature %d\n",
			   ((rht_lht & 0xFF00) >> 8));
	पूर्ण
	अगर (thermal_event & 0x10) अणु
		pm8001_dbg(pm8001_ha, IO,
			   "Thermal Event: Remote high temperature violated!\n");
		pm8001_dbg(pm8001_ha, IO,
			   "Thermal Event: Measured remote high temperature %d\n",
			   ((rht_lht & 0xFF000000) >> 24));
	पूर्ण
	वापस 0;
पूर्ण

/**
 * mpi_hw_event -The hw event has come.
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
अटल पूर्णांक mpi_hw_event(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	अचिन्हित दीर्घ flags, i;
	काष्ठा hw_event_resp *pPayload =
		(काष्ठा hw_event_resp *)(piomb + 4);
	u32 lr_status_evt_portid =
		le32_to_cpu(pPayload->lr_status_evt_portid);
	u32 phyid_npip_portstate = le32_to_cpu(pPayload->phyid_npip_portstate);
	u8 port_id = (u8)(lr_status_evt_portid & 0x000000FF);
	u8 phy_id =
		(u8)((phyid_npip_portstate & 0xFF0000) >> 16);
	u16 eventType =
		(u16)((lr_status_evt_portid & 0x00FFFF00) >> 8);
	u8 status =
		(u8)((lr_status_evt_portid & 0x0F000000) >> 24);
	काष्ठा sas_ha_काष्ठा *sas_ha = pm8001_ha->sas;
	काष्ठा pm8001_phy *phy = &pm8001_ha->phy[phy_id];
	काष्ठा pm8001_port *port = &pm8001_ha->port[port_id];
	काष्ठा asd_sas_phy *sas_phy = sas_ha->sas_phy[phy_id];
	pm8001_dbg(pm8001_ha, DEV,
		   "portid:%d phyid:%d event:0x%x status:0x%x\n",
		   port_id, phy_id, eventType, status);

	चयन (eventType) अणु

	हाल HW_EVENT_SAS_PHY_UP:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_PHY_START_STATUS\n");
		hw_event_sas_phy_up(pm8001_ha, piomb);
		अवरोध;
	हाल HW_EVENT_SATA_PHY_UP:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_SATA_PHY_UP\n");
		hw_event_sata_phy_up(pm8001_ha, piomb);
		अवरोध;
	हाल HW_EVENT_SATA_SPINUP_HOLD:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_SATA_SPINUP_HOLD\n");
		sas_notअगरy_phy_event(&phy->sas_phy, PHYE_SPINUP_HOLD,
			GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_PHY_DOWN:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_PHY_DOWN\n");
		hw_event_phy_करोwn(pm8001_ha, piomb);
		अगर (pm8001_ha->reset_in_progress) अणु
			pm8001_dbg(pm8001_ha, MSG, "Reset in progress\n");
			वापस 0;
		पूर्ण
		phy->phy_attached = 0;
		phy->phy_state = PHY_LINK_DISABLE;
		अवरोध;
	हाल HW_EVENT_PORT_INVALID:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_PORT_INVALID\n");
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_notअगरy_port_event(sas_phy, PORTE_LINK_RESET_ERR,
			GFP_ATOMIC);
		अवरोध;
	/* the broadcast change primitive received, tell the LIBSAS this event
	to revalidate the sas करोमुख्य*/
	हाल HW_EVENT_BROADCAST_CHANGE:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_BROADCAST_CHANGE\n");
		pm80xx_hw_event_ack_req(pm8001_ha, 0, HW_EVENT_BROADCAST_CHANGE,
			port_id, phy_id, 1, 0);
		spin_lock_irqsave(&sas_phy->sas_prim_lock, flags);
		sas_phy->sas_prim = HW_EVENT_BROADCAST_CHANGE;
		spin_unlock_irqrestore(&sas_phy->sas_prim_lock, flags);
		sas_notअगरy_port_event(sas_phy, PORTE_BROADCAST_RCVD,
			GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_PHY_ERROR:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_PHY_ERROR\n");
		sas_phy_disconnected(&phy->sas_phy);
		phy->phy_attached = 0;
		sas_notअगरy_phy_event(&phy->sas_phy, PHYE_OOB_ERROR, GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_BROADCAST_EXP:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_BROADCAST_EXP\n");
		spin_lock_irqsave(&sas_phy->sas_prim_lock, flags);
		sas_phy->sas_prim = HW_EVENT_BROADCAST_EXP;
		spin_unlock_irqrestore(&sas_phy->sas_prim_lock, flags);
		sas_notअगरy_port_event(sas_phy, PORTE_BROADCAST_RCVD,
			GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_LINK_ERR_INVALID_DWORD:
		pm8001_dbg(pm8001_ha, MSG,
			   "HW_EVENT_LINK_ERR_INVALID_DWORD\n");
		pm80xx_hw_event_ack_req(pm8001_ha, 0,
			HW_EVENT_LINK_ERR_INVALID_DWORD, port_id, phy_id, 0, 0);
		अवरोध;
	हाल HW_EVENT_LINK_ERR_DISPARITY_ERROR:
		pm8001_dbg(pm8001_ha, MSG,
			   "HW_EVENT_LINK_ERR_DISPARITY_ERROR\n");
		pm80xx_hw_event_ack_req(pm8001_ha, 0,
			HW_EVENT_LINK_ERR_DISPARITY_ERROR,
			port_id, phy_id, 0, 0);
		अवरोध;
	हाल HW_EVENT_LINK_ERR_CODE_VIOLATION:
		pm8001_dbg(pm8001_ha, MSG,
			   "HW_EVENT_LINK_ERR_CODE_VIOLATION\n");
		pm80xx_hw_event_ack_req(pm8001_ha, 0,
			HW_EVENT_LINK_ERR_CODE_VIOLATION,
			port_id, phy_id, 0, 0);
		अवरोध;
	हाल HW_EVENT_LINK_ERR_LOSS_OF_DWORD_SYNCH:
		pm8001_dbg(pm8001_ha, MSG,
			   "HW_EVENT_LINK_ERR_LOSS_OF_DWORD_SYNCH\n");
		pm80xx_hw_event_ack_req(pm8001_ha, 0,
			HW_EVENT_LINK_ERR_LOSS_OF_DWORD_SYNCH,
			port_id, phy_id, 0, 0);
		अवरोध;
	हाल HW_EVENT_MALFUNCTION:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_MALFUNCTION\n");
		अवरोध;
	हाल HW_EVENT_BROADCAST_SES:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_BROADCAST_SES\n");
		spin_lock_irqsave(&sas_phy->sas_prim_lock, flags);
		sas_phy->sas_prim = HW_EVENT_BROADCAST_SES;
		spin_unlock_irqrestore(&sas_phy->sas_prim_lock, flags);
		sas_notअगरy_port_event(sas_phy, PORTE_BROADCAST_RCVD,
			GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_INBOUND_CRC_ERROR:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_INBOUND_CRC_ERROR\n");
		pm80xx_hw_event_ack_req(pm8001_ha, 0,
			HW_EVENT_INBOUND_CRC_ERROR,
			port_id, phy_id, 0, 0);
		अवरोध;
	हाल HW_EVENT_HARD_RESET_RECEIVED:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_HARD_RESET_RECEIVED\n");
		sas_notअगरy_port_event(sas_phy, PORTE_HARD_RESET, GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_ID_FRAME_TIMEOUT:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_ID_FRAME_TIMEOUT\n");
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_notअगरy_port_event(sas_phy, PORTE_LINK_RESET_ERR,
			GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_LINK_ERR_PHY_RESET_FAILED:
		pm8001_dbg(pm8001_ha, MSG,
			   "HW_EVENT_LINK_ERR_PHY_RESET_FAILED\n");
		pm80xx_hw_event_ack_req(pm8001_ha, 0,
			HW_EVENT_LINK_ERR_PHY_RESET_FAILED,
			port_id, phy_id, 0, 0);
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_notअगरy_port_event(sas_phy, PORTE_LINK_RESET_ERR,
			GFP_ATOMIC);
		अवरोध;
	हाल HW_EVENT_PORT_RESET_TIMER_TMO:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_PORT_RESET_TIMER_TMO\n");
		pm80xx_hw_event_ack_req(pm8001_ha, 0, HW_EVENT_PHY_DOWN,
			port_id, phy_id, 0, 0);
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_notअगरy_port_event(sas_phy, PORTE_LINK_RESET_ERR,
			GFP_ATOMIC);
		अगर (pm8001_ha->phy[phy_id].reset_completion) अणु
			pm8001_ha->phy[phy_id].port_reset_status =
					PORT_RESET_TMO;
			complete(pm8001_ha->phy[phy_id].reset_completion);
			pm8001_ha->phy[phy_id].reset_completion = शून्य;
		पूर्ण
		अवरोध;
	हाल HW_EVENT_PORT_RECOVERY_TIMER_TMO:
		pm8001_dbg(pm8001_ha, MSG,
			   "HW_EVENT_PORT_RECOVERY_TIMER_TMO\n");
		pm80xx_hw_event_ack_req(pm8001_ha, 0,
			HW_EVENT_PORT_RECOVERY_TIMER_TMO,
			port_id, phy_id, 0, 0);
		क्रम (i = 0; i < pm8001_ha->chip->n_phy; i++) अणु
			अगर (port->wide_port_phymap & (1 << i)) अणु
				phy = &pm8001_ha->phy[i];
				sas_notअगरy_phy_event(&phy->sas_phy,
					PHYE_LOSS_OF_SIGNAL, GFP_ATOMIC);
				port->wide_port_phymap &= ~(1 << i);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल HW_EVENT_PORT_RECOVER:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_PORT_RECOVER\n");
		hw_event_port_recover(pm8001_ha, piomb);
		अवरोध;
	हाल HW_EVENT_PORT_RESET_COMPLETE:
		pm8001_dbg(pm8001_ha, MSG, "HW_EVENT_PORT_RESET_COMPLETE\n");
		अगर (pm8001_ha->phy[phy_id].reset_completion) अणु
			pm8001_ha->phy[phy_id].port_reset_status =
					PORT_RESET_SUCCESS;
			complete(pm8001_ha->phy[phy_id].reset_completion);
			pm8001_ha->phy[phy_id].reset_completion = शून्य;
		पूर्ण
		अवरोध;
	हाल EVENT_BROADCAST_ASYNCH_EVENT:
		pm8001_dbg(pm8001_ha, MSG, "EVENT_BROADCAST_ASYNCH_EVENT\n");
		अवरोध;
	शेष:
		pm8001_dbg(pm8001_ha, DEVIO, "Unknown event type 0x%x\n",
			   eventType);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * mpi_phy_stop_resp - SPCv specअगरic
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
अटल पूर्णांक mpi_phy_stop_resp(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	काष्ठा phy_stop_resp *pPayload =
		(काष्ठा phy_stop_resp *)(piomb + 4);
	u32 status =
		le32_to_cpu(pPayload->status);
	u32 phyid =
		le32_to_cpu(pPayload->phyid) & 0xFF;
	काष्ठा pm8001_phy *phy = &pm8001_ha->phy[phyid];
	pm8001_dbg(pm8001_ha, MSG, "phy:0x%x status:0x%x\n",
		   phyid, status);
	अगर (status == PHY_STOP_SUCCESS ||
		status == PHY_STOP_ERR_DEVICE_ATTACHED)
		phy->phy_state = PHY_LINK_DISABLE;
	वापस 0;
पूर्ण

/**
 * mpi_set_controller_config_resp - SPCv specअगरic
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
अटल पूर्णांक mpi_set_controller_config_resp(काष्ठा pm8001_hba_info *pm8001_ha,
			व्योम *piomb)
अणु
	काष्ठा set_ctrl_cfg_resp *pPayload =
			(काष्ठा set_ctrl_cfg_resp *)(piomb + 4);
	u32 status = le32_to_cpu(pPayload->status);
	u32 err_qlfr_pgcd = le32_to_cpu(pPayload->err_qlfr_pgcd);

	pm8001_dbg(pm8001_ha, MSG,
		   "SET CONTROLLER RESP: status 0x%x qlfr_pgcd 0x%x\n",
		   status, err_qlfr_pgcd);

	वापस 0;
पूर्ण

/**
 * mpi_get_controller_config_resp - SPCv specअगरic
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
अटल पूर्णांक mpi_get_controller_config_resp(काष्ठा pm8001_hba_info *pm8001_ha,
			व्योम *piomb)
अणु
	pm8001_dbg(pm8001_ha, MSG, " pm80xx_addition_functionality\n");

	वापस 0;
पूर्ण

/**
 * mpi_get_phy_profile_resp - SPCv specअगरic
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
अटल पूर्णांक mpi_get_phy_profile_resp(काष्ठा pm8001_hba_info *pm8001_ha,
			व्योम *piomb)
अणु
	pm8001_dbg(pm8001_ha, MSG, " pm80xx_addition_functionality\n");

	वापस 0;
पूर्ण

/**
 * mpi_flash_op_ext_resp - SPCv specअगरic
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
अटल पूर्णांक mpi_flash_op_ext_resp(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	pm8001_dbg(pm8001_ha, MSG, " pm80xx_addition_functionality\n");

	वापस 0;
पूर्ण

/**
 * mpi_set_phy_profile_resp - SPCv specअगरic
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
अटल पूर्णांक mpi_set_phy_profile_resp(काष्ठा pm8001_hba_info *pm8001_ha,
			व्योम *piomb)
अणु
	u32 tag;
	u8 page_code;
	पूर्णांक rc = 0;
	काष्ठा set_phy_profile_resp *pPayload =
		(काष्ठा set_phy_profile_resp *)(piomb + 4);
	u32 ppc_phyid = le32_to_cpu(pPayload->ppc_phyid);
	u32 status = le32_to_cpu(pPayload->status);

	tag = le32_to_cpu(pPayload->tag);
	page_code = (u8)((ppc_phyid & 0xFF00) >> 8);
	अगर (status) अणु
		/* status is FAILED */
		pm8001_dbg(pm8001_ha, FAIL,
			   "PhyProfile command failed  with status 0x%08X\n",
			   status);
		rc = -1;
	पूर्ण अन्यथा अणु
		अगर (page_code != SAS_PHY_ANALOG_SETTINGS_PAGE) अणु
			pm8001_dbg(pm8001_ha, FAIL, "Invalid page code 0x%X\n",
				   page_code);
			rc = -1;
		पूर्ण
	पूर्ण
	pm8001_tag_मुक्त(pm8001_ha, tag);
	वापस rc;
पूर्ण

/**
 * mpi_kek_management_resp - SPCv specअगरic
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
अटल पूर्णांक mpi_kek_management_resp(काष्ठा pm8001_hba_info *pm8001_ha,
			व्योम *piomb)
अणु
	काष्ठा kek_mgmt_resp *pPayload = (काष्ठा kek_mgmt_resp *)(piomb + 4);

	u32 status = le32_to_cpu(pPayload->status);
	u32 kidx_new_curr_ksop = le32_to_cpu(pPayload->kidx_new_curr_ksop);
	u32 err_qlfr = le32_to_cpu(pPayload->err_qlfr);

	pm8001_dbg(pm8001_ha, MSG,
		   "KEK MGMT RESP. Status 0x%x idx_ksop 0x%x err_qlfr 0x%x\n",
		   status, kidx_new_curr_ksop, err_qlfr);

	वापस 0;
पूर्ण

/**
 * mpi_dek_management_resp - SPCv specअगरic
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
अटल पूर्णांक mpi_dek_management_resp(काष्ठा pm8001_hba_info *pm8001_ha,
			व्योम *piomb)
अणु
	pm8001_dbg(pm8001_ha, MSG, " pm80xx_addition_functionality\n");

	वापस 0;
पूर्ण

/**
 * ssp_coalesced_comp_resp - SPCv specअगरic
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
अटल पूर्णांक ssp_coalesced_comp_resp(काष्ठा pm8001_hba_info *pm8001_ha,
			व्योम *piomb)
अणु
	pm8001_dbg(pm8001_ha, MSG, " pm80xx_addition_functionality\n");

	वापस 0;
पूर्ण

/**
 * process_one_iomb - process one outbound Queue memory block
 * @pm8001_ha: our hba card inक्रमmation
 * @piomb: IO message buffer
 */
अटल व्योम process_one_iomb(काष्ठा pm8001_hba_info *pm8001_ha, व्योम *piomb)
अणु
	__le32 pHeader = *(__le32 *)piomb;
	u32 opc = (u32)((le32_to_cpu(pHeader)) & 0xFFF);

	चयन (opc) अणु
	हाल OPC_OUB_ECHO:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_ECHO\n");
		अवरोध;
	हाल OPC_OUB_HW_EVENT:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_HW_EVENT\n");
		mpi_hw_event(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_THERM_HW_EVENT:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_THERMAL_EVENT\n");
		mpi_thermal_hw_event(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_SSP_COMP:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SSP_COMP\n");
		mpi_ssp_completion(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_SMP_COMP:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SMP_COMP\n");
		mpi_smp_completion(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_LOCAL_PHY_CNTRL:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_LOCAL_PHY_CNTRL\n");
		pm8001_mpi_local_phy_ctl(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_DEV_REGIST:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_DEV_REGIST\n");
		pm8001_mpi_reg_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_DEREG_DEV:
		pm8001_dbg(pm8001_ha, MSG, "unregister the device\n");
		pm8001_mpi_dereg_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_GET_DEV_HANDLE:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_GET_DEV_HANDLE\n");
		अवरोध;
	हाल OPC_OUB_SATA_COMP:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SATA_COMP\n");
		mpi_sata_completion(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_SATA_EVENT:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SATA_EVENT\n");
		mpi_sata_event(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_SSP_EVENT:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SSP_EVENT\n");
		mpi_ssp_event(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_DEV_HANDLE_ARRIV:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_DEV_HANDLE_ARRIV\n");
		/*This is क्रम target*/
		अवरोध;
	हाल OPC_OUB_SSP_RECV_EVENT:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SSP_RECV_EVENT\n");
		/*This is क्रम target*/
		अवरोध;
	हाल OPC_OUB_FW_FLASH_UPDATE:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_FW_FLASH_UPDATE\n");
		pm8001_mpi_fw_flash_update_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_GPIO_RESPONSE:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_GPIO_RESPONSE\n");
		अवरोध;
	हाल OPC_OUB_GPIO_EVENT:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_GPIO_EVENT\n");
		अवरोध;
	हाल OPC_OUB_GENERAL_EVENT:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_GENERAL_EVENT\n");
		pm8001_mpi_general_event(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_SSP_ABORT_RSP:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SSP_ABORT_RSP\n");
		pm8001_mpi_task_पात_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_SATA_ABORT_RSP:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SATA_ABORT_RSP\n");
		pm8001_mpi_task_पात_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_SAS_DIAG_MODE_START_END:
		pm8001_dbg(pm8001_ha, MSG,
			   "OPC_OUB_SAS_DIAG_MODE_START_END\n");
		अवरोध;
	हाल OPC_OUB_SAS_DIAG_EXECUTE:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SAS_DIAG_EXECUTE\n");
		अवरोध;
	हाल OPC_OUB_GET_TIME_STAMP:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_GET_TIME_STAMP\n");
		अवरोध;
	हाल OPC_OUB_SAS_HW_EVENT_ACK:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SAS_HW_EVENT_ACK\n");
		अवरोध;
	हाल OPC_OUB_PORT_CONTROL:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_PORT_CONTROL\n");
		अवरोध;
	हाल OPC_OUB_SMP_ABORT_RSP:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SMP_ABORT_RSP\n");
		pm8001_mpi_task_पात_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_GET_NVMD_DATA:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_GET_NVMD_DATA\n");
		pm8001_mpi_get_nvmd_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_SET_NVMD_DATA:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SET_NVMD_DATA\n");
		pm8001_mpi_set_nvmd_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_DEVICE_HANDLE_REMOVAL:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_DEVICE_HANDLE_REMOVAL\n");
		अवरोध;
	हाल OPC_OUB_SET_DEVICE_STATE:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SET_DEVICE_STATE\n");
		pm8001_mpi_set_dev_state_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_GET_DEVICE_STATE:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_GET_DEVICE_STATE\n");
		अवरोध;
	हाल OPC_OUB_SET_DEV_INFO:
		pm8001_dbg(pm8001_ha, MSG, "OPC_OUB_SET_DEV_INFO\n");
		अवरोध;
	/* spcv specअगरc commands */
	हाल OPC_OUB_PHY_START_RESP:
		pm8001_dbg(pm8001_ha, MSG,
			   "OPC_OUB_PHY_START_RESP opcode:%x\n", opc);
		mpi_phy_start_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_PHY_STOP_RESP:
		pm8001_dbg(pm8001_ha, MSG,
			   "OPC_OUB_PHY_STOP_RESP opcode:%x\n", opc);
		mpi_phy_stop_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_SET_CONTROLLER_CONFIG:
		pm8001_dbg(pm8001_ha, MSG,
			   "OPC_OUB_SET_CONTROLLER_CONFIG opcode:%x\n", opc);
		mpi_set_controller_config_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_GET_CONTROLLER_CONFIG:
		pm8001_dbg(pm8001_ha, MSG,
			   "OPC_OUB_GET_CONTROLLER_CONFIG opcode:%x\n", opc);
		mpi_get_controller_config_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_GET_PHY_PROखाता:
		pm8001_dbg(pm8001_ha, MSG,
			   "OPC_OUB_GET_PHY_PROFILE opcode:%x\n", opc);
		mpi_get_phy_profile_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_FLASH_OP_EXT:
		pm8001_dbg(pm8001_ha, MSG,
			   "OPC_OUB_FLASH_OP_EXT opcode:%x\n", opc);
		mpi_flash_op_ext_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_SET_PHY_PROखाता:
		pm8001_dbg(pm8001_ha, MSG,
			   "OPC_OUB_SET_PHY_PROFILE opcode:%x\n", opc);
		mpi_set_phy_profile_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_KEK_MANAGEMENT_RESP:
		pm8001_dbg(pm8001_ha, MSG,
			   "OPC_OUB_KEK_MANAGEMENT_RESP opcode:%x\n", opc);
		mpi_kek_management_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_DEK_MANAGEMENT_RESP:
		pm8001_dbg(pm8001_ha, MSG,
			   "OPC_OUB_DEK_MANAGEMENT_RESP opcode:%x\n", opc);
		mpi_dek_management_resp(pm8001_ha, piomb);
		अवरोध;
	हाल OPC_OUB_SSP_COALESCED_COMP_RESP:
		pm8001_dbg(pm8001_ha, MSG,
			   "OPC_OUB_SSP_COALESCED_COMP_RESP opcode:%x\n", opc);
		ssp_coalesced_comp_resp(pm8001_ha, piomb);
		अवरोध;
	शेष:
		pm8001_dbg(pm8001_ha, DEVIO,
			   "Unknown outbound Queue IOMB OPC = 0x%x\n", opc);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_scratchpad_रेजिस्टरs(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
	pm8001_dbg(pm8001_ha, FAIL, "MSGU_SCRATCH_PAD_0: 0x%x\n",
		   pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_0));
	pm8001_dbg(pm8001_ha, FAIL, "MSGU_SCRATCH_PAD_1:0x%x\n",
		   pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1));
	pm8001_dbg(pm8001_ha, FAIL, "MSGU_SCRATCH_PAD_2: 0x%x\n",
		   pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_2));
	pm8001_dbg(pm8001_ha, FAIL, "MSGU_SCRATCH_PAD_3: 0x%x\n",
		   pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_3));
	pm8001_dbg(pm8001_ha, FAIL, "MSGU_HOST_SCRATCH_PAD_0: 0x%x\n",
		   pm8001_cr32(pm8001_ha, 0, MSGU_HOST_SCRATCH_PAD_0));
	pm8001_dbg(pm8001_ha, FAIL, "MSGU_HOST_SCRATCH_PAD_1: 0x%x\n",
		   pm8001_cr32(pm8001_ha, 0, MSGU_HOST_SCRATCH_PAD_1));
	pm8001_dbg(pm8001_ha, FAIL, "MSGU_HOST_SCRATCH_PAD_2: 0x%x\n",
		   pm8001_cr32(pm8001_ha, 0, MSGU_HOST_SCRATCH_PAD_2));
	pm8001_dbg(pm8001_ha, FAIL, "MSGU_HOST_SCRATCH_PAD_3: 0x%x\n",
		   pm8001_cr32(pm8001_ha, 0, MSGU_HOST_SCRATCH_PAD_3));
	pm8001_dbg(pm8001_ha, FAIL, "MSGU_HOST_SCRATCH_PAD_4: 0x%x\n",
		   pm8001_cr32(pm8001_ha, 0, MSGU_HOST_SCRATCH_PAD_4));
	pm8001_dbg(pm8001_ha, FAIL, "MSGU_HOST_SCRATCH_PAD_5: 0x%x\n",
		   pm8001_cr32(pm8001_ha, 0, MSGU_HOST_SCRATCH_PAD_5));
	pm8001_dbg(pm8001_ha, FAIL, "MSGU_RSVD_SCRATCH_PAD_0: 0x%x\n",
		   pm8001_cr32(pm8001_ha, 0, MSGU_HOST_SCRATCH_PAD_6));
	pm8001_dbg(pm8001_ha, FAIL, "MSGU_RSVD_SCRATCH_PAD_1: 0x%x\n",
		   pm8001_cr32(pm8001_ha, 0, MSGU_HOST_SCRATCH_PAD_7));
पूर्ण

अटल पूर्णांक process_oq(काष्ठा pm8001_hba_info *pm8001_ha, u8 vec)
अणु
	काष्ठा outbound_queue_table *circularQ;
	व्योम *pMsg1 = शून्य;
	u8 bc;
	u32 ret = MPI_IO_STATUS_FAIL;
	अचिन्हित दीर्घ flags;
	u32 regval;

	अगर (vec == (pm8001_ha->max_q_num - 1)) अणु
		regval = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1);
		अगर ((regval & SCRATCH_PAD_MIPSALL_READY) !=
					SCRATCH_PAD_MIPSALL_READY) अणु
			pm8001_ha->controller_fatal_error = true;
			pm8001_dbg(pm8001_ha, FAIL,
				   "Firmware Fatal error! Regval:0x%x\n",
				   regval);
			pm8001_handle_event(pm8001_ha, शून्य, IO_FATAL_ERROR);
			prपूर्णांक_scratchpad_रेजिस्टरs(pm8001_ha);
			वापस ret;
		पूर्ण
	पूर्ण
	circularQ = &pm8001_ha->outbnd_q_tbl[vec];
	spin_lock_irqsave(&circularQ->oq_lock, flags);
	करो अणु
		/* spurious पूर्णांकerrupt during setup अगर kexec-ing and
		 * driver करोing a करोorbell access w/ the pre-kexec oq
		 * पूर्णांकerrupt setup.
		 */
		अगर (!circularQ->pi_virt)
			अवरोध;
		ret = pm8001_mpi_msg_consume(pm8001_ha, circularQ, &pMsg1, &bc);
		अगर (MPI_IO_STATUS_SUCCESS == ret) अणु
			/* process the outbound message */
			process_one_iomb(pm8001_ha, (व्योम *)(pMsg1 - 4));
			/* मुक्त the message from the outbound circular buffer */
			pm8001_mpi_msg_मुक्त_set(pm8001_ha, pMsg1,
							circularQ, bc);
		पूर्ण
		अगर (MPI_IO_STATUS_BUSY == ret) अणु
			/* Update the producer index from SPC */
			circularQ->producer_index =
				cpu_to_le32(pm8001_पढ़ो_32(circularQ->pi_virt));
			अगर (le32_to_cpu(circularQ->producer_index) ==
				circularQ->consumer_idx)
				/* OQ is empty */
				अवरोध;
		पूर्ण
	पूर्ण जबतक (1);
	spin_unlock_irqrestore(&circularQ->oq_lock, flags);
	वापस ret;
पूर्ण

/* DMA_... to our direction translation. */
अटल स्थिर u8 data_dir_flags[] = अणु
	[DMA_BIसूचीECTIONAL]	= DATA_सूची_BYRECIPIENT,	/* UNSPECIFIED */
	[DMA_TO_DEVICE]		= DATA_सूची_OUT,		/* OUTBOUND */
	[DMA_FROM_DEVICE]	= DATA_सूची_IN,		/* INBOUND */
	[DMA_NONE]		= DATA_सूची_NONE,	/* NO TRANSFER */
पूर्ण;

अटल व्योम build_smp_cmd(u32 deviceID, __le32 hTag,
			काष्ठा smp_req *psmp_cmd, पूर्णांक mode, पूर्णांक length)
अणु
	psmp_cmd->tag = hTag;
	psmp_cmd->device_id = cpu_to_le32(deviceID);
	अगर (mode == SMP_सूचीECT) अणु
		length = length - 4; /* subtract crc */
		psmp_cmd->len_ip_ir = cpu_to_le32(length << 16);
	पूर्ण अन्यथा अणु
		psmp_cmd->len_ip_ir = cpu_to_le32(1|(1 << 1));
	पूर्ण
पूर्ण

/**
 * pm80xx_chip_smp_req - send a SMP task to FW
 * @pm8001_ha: our hba card inक्रमmation.
 * @ccb: the ccb inक्रमmation this request used.
 */
अटल पूर्णांक pm80xx_chip_smp_req(काष्ठा pm8001_hba_info *pm8001_ha,
	काष्ठा pm8001_ccb_info *ccb)
अणु
	पूर्णांक elem, rc;
	काष्ठा sas_task *task = ccb->task;
	काष्ठा करोमुख्य_device *dev = task->dev;
	काष्ठा pm8001_device *pm8001_dev = dev->lldd_dev;
	काष्ठा scatterlist *sg_req, *sg_resp;
	u32 req_len, resp_len;
	काष्ठा smp_req smp_cmd;
	u32 opc;
	काष्ठा inbound_queue_table *circularQ;
	अक्षर *preq_dma_addr = शून्य;
	__le64 पंचांगp_addr;
	u32 i, length;

	स_रखो(&smp_cmd, 0, माप(smp_cmd));
	/*
	 * DMA-map SMP request, response buffers
	 */
	sg_req = &task->smp_task.smp_req;
	elem = dma_map_sg(pm8001_ha->dev, sg_req, 1, DMA_TO_DEVICE);
	अगर (!elem)
		वापस -ENOMEM;
	req_len = sg_dma_len(sg_req);

	sg_resp = &task->smp_task.smp_resp;
	elem = dma_map_sg(pm8001_ha->dev, sg_resp, 1, DMA_FROM_DEVICE);
	अगर (!elem) अणु
		rc = -ENOMEM;
		जाओ err_out;
	पूर्ण
	resp_len = sg_dma_len(sg_resp);
	/* must be in dwords */
	अगर ((req_len & 0x3) || (resp_len & 0x3)) अणु
		rc = -EINVAL;
		जाओ err_out_2;
	पूर्ण

	opc = OPC_INB_SMP_REQUEST;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	smp_cmd.tag = cpu_to_le32(ccb->ccb_tag);

	length = sg_req->length;
	pm8001_dbg(pm8001_ha, IO, "SMP Frame Length %d\n", sg_req->length);
	अगर (!(length - 8))
		pm8001_ha->smp_exp_mode = SMP_सूचीECT;
	अन्यथा
		pm8001_ha->smp_exp_mode = SMP_INसूचीECT;


	पंचांगp_addr = cpu_to_le64((u64)sg_dma_address(&task->smp_task.smp_req));
	preq_dma_addr = (अक्षर *)phys_to_virt(पंचांगp_addr);

	/* INसूचीECT MODE command settings. Use DMA */
	अगर (pm8001_ha->smp_exp_mode == SMP_INसूचीECT) अणु
		pm8001_dbg(pm8001_ha, IO, "SMP REQUEST INDIRECT MODE\n");
		/* क्रम SPCv indirect mode. Place the top 4 bytes of
		 * SMP Request header here. */
		क्रम (i = 0; i < 4; i++)
			smp_cmd.smp_req16[i] = *(preq_dma_addr + i);
		/* exclude top 4 bytes क्रम SMP req header */
		smp_cmd.दीर्घ_smp_req.दीर्घ_req_addr =
			cpu_to_le64((u64)sg_dma_address
				(&task->smp_task.smp_req) + 4);
		/* exclude 4 bytes क्रम SMP req header and CRC */
		smp_cmd.दीर्घ_smp_req.दीर्घ_req_size =
			cpu_to_le32((u32)sg_dma_len(&task->smp_task.smp_req)-8);
		smp_cmd.दीर्घ_smp_req.दीर्घ_resp_addr =
				cpu_to_le64((u64)sg_dma_address
					(&task->smp_task.smp_resp));
		smp_cmd.दीर्घ_smp_req.दीर्घ_resp_size =
				cpu_to_le32((u32)sg_dma_len
					(&task->smp_task.smp_resp)-4);
	पूर्ण अन्यथा अणु /* सूचीECT MODE */
		smp_cmd.दीर्घ_smp_req.दीर्घ_req_addr =
			cpu_to_le64((u64)sg_dma_address
					(&task->smp_task.smp_req));
		smp_cmd.दीर्घ_smp_req.दीर्घ_req_size =
			cpu_to_le32((u32)sg_dma_len(&task->smp_task.smp_req)-4);
		smp_cmd.दीर्घ_smp_req.दीर्घ_resp_addr =
			cpu_to_le64((u64)sg_dma_address
				(&task->smp_task.smp_resp));
		smp_cmd.दीर्घ_smp_req.दीर्घ_resp_size =
			cpu_to_le32
			((u32)sg_dma_len(&task->smp_task.smp_resp)-4);
	पूर्ण
	अगर (pm8001_ha->smp_exp_mode == SMP_सूचीECT) अणु
		pm8001_dbg(pm8001_ha, IO, "SMP REQUEST DIRECT MODE\n");
		क्रम (i = 0; i < length; i++)
			अगर (i < 16) अणु
				smp_cmd.smp_req16[i] = *(preq_dma_addr+i);
				pm8001_dbg(pm8001_ha, IO,
					   "Byte[%d]:%x (DMA data:%x)\n",
					   i, smp_cmd.smp_req16[i],
					   *(preq_dma_addr));
			पूर्ण अन्यथा अणु
				smp_cmd.smp_req[i] = *(preq_dma_addr+i);
				pm8001_dbg(pm8001_ha, IO,
					   "Byte[%d]:%x (DMA data:%x)\n",
					   i, smp_cmd.smp_req[i],
					   *(preq_dma_addr));
			पूर्ण
	पूर्ण

	build_smp_cmd(pm8001_dev->device_id, smp_cmd.tag,
				&smp_cmd, pm8001_ha->smp_exp_mode, length);
	rc = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &smp_cmd,
			माप(smp_cmd), 0);
	अगर (rc)
		जाओ err_out_2;
	वापस 0;

err_out_2:
	dma_unmap_sg(pm8001_ha->dev, &ccb->task->smp_task.smp_resp, 1,
			DMA_FROM_DEVICE);
err_out:
	dma_unmap_sg(pm8001_ha->dev, &ccb->task->smp_task.smp_req, 1,
			DMA_TO_DEVICE);
	वापस rc;
पूर्ण

अटल पूर्णांक check_enc_sas_cmd(काष्ठा sas_task *task)
अणु
	u8 cmd = task->ssp_task.cmd->cmnd[0];

	अगर (cmd == READ_10 || cmd == WRITE_10 || cmd == WRITE_VERIFY)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक check_enc_sat_cmd(काष्ठा sas_task *task)
अणु
	पूर्णांक ret = 0;
	चयन (task->ata_task.fis.command) अणु
	हाल ATA_CMD_FPDMA_READ:
	हाल ATA_CMD_READ_EXT:
	हाल ATA_CMD_READ:
	हाल ATA_CMD_FPDMA_WRITE:
	हाल ATA_CMD_WRITE_EXT:
	हाल ATA_CMD_WRITE:
	हाल ATA_CMD_PIO_READ:
	हाल ATA_CMD_PIO_READ_EXT:
	हाल ATA_CMD_PIO_WRITE:
	हाल ATA_CMD_PIO_WRITE_EXT:
		ret = 1;
		अवरोध;
	शेष:
		ret = 0;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * pm80xx_chip_ssp_io_req - send a SSP task to FW
 * @pm8001_ha: our hba card inक्रमmation.
 * @ccb: the ccb inक्रमmation this request used.
 */
अटल पूर्णांक pm80xx_chip_ssp_io_req(काष्ठा pm8001_hba_info *pm8001_ha,
	काष्ठा pm8001_ccb_info *ccb)
अणु
	काष्ठा sas_task *task = ccb->task;
	काष्ठा करोमुख्य_device *dev = task->dev;
	काष्ठा pm8001_device *pm8001_dev = dev->lldd_dev;
	काष्ठा ssp_ini_io_start_req ssp_cmd;
	u32 tag = ccb->ccb_tag;
	पूर्णांक ret;
	u64 phys_addr, start_addr, end_addr;
	u32 end_addr_high, end_addr_low;
	काष्ठा inbound_queue_table *circularQ;
	u32 q_index, cpu_id;
	u32 opc = OPC_INB_SSPINIIOSTART;
	स_रखो(&ssp_cmd, 0, माप(ssp_cmd));
	स_नकल(ssp_cmd.ssp_iu.lun, task->ssp_task.LUN, 8);
	/* data address करोमुख्य added क्रम spcv; set to 0 by host,
	 * used पूर्णांकernally by controller
	 * 0 क्रम SAS 1.1 and SAS 2.0 compatible TLR
	 */
	ssp_cmd.dad_dir_m_tlr =
		cpu_to_le32(data_dir_flags[task->data_dir] << 8 | 0x0);
	ssp_cmd.data_len = cpu_to_le32(task->total_xfer_len);
	ssp_cmd.device_id = cpu_to_le32(pm8001_dev->device_id);
	ssp_cmd.tag = cpu_to_le32(tag);
	अगर (task->ssp_task.enable_first_burst)
		ssp_cmd.ssp_iu.efb_prio_attr |= 0x80;
	ssp_cmd.ssp_iu.efb_prio_attr |= (task->ssp_task.task_prio << 3);
	ssp_cmd.ssp_iu.efb_prio_attr |= (task->ssp_task.task_attr & 7);
	स_नकल(ssp_cmd.ssp_iu.cdb, task->ssp_task.cmd->cmnd,
		       task->ssp_task.cmd->cmd_len);
	cpu_id = smp_processor_id();
	q_index = (u32) (cpu_id) % (pm8001_ha->max_q_num);
	circularQ = &pm8001_ha->inbnd_q_tbl[q_index];

	/* Check अगर encryption is set */
	अगर (pm8001_ha->chip->encrypt &&
		!(pm8001_ha->encrypt_info.status) && check_enc_sas_cmd(task)) अणु
		pm8001_dbg(pm8001_ha, IO,
			   "Encryption enabled.Sending Encrypt SAS command 0x%x\n",
			   task->ssp_task.cmd->cmnd[0]);
		opc = OPC_INB_SSP_INI_DIF_ENC_IO;
		/* enable encryption. 0 क्रम SAS 1.1 and SAS 2.0 compatible TLR*/
		ssp_cmd.dad_dir_m_tlr =	cpu_to_le32
			((data_dir_flags[task->data_dir] << 8) | 0x20 | 0x0);

		/* fill in PRD (scatter/gather) table, अगर any */
		अगर (task->num_scatter > 1) अणु
			pm8001_chip_make_sg(task->scatter,
						ccb->n_elem, ccb->buf_prd);
			phys_addr = ccb->ccb_dma_handle;
			ssp_cmd.enc_addr_low =
				cpu_to_le32(lower_32_bits(phys_addr));
			ssp_cmd.enc_addr_high =
				cpu_to_le32(upper_32_bits(phys_addr));
			ssp_cmd.enc_esgl = cpu_to_le32(1<<31);
		पूर्ण अन्यथा अगर (task->num_scatter == 1) अणु
			u64 dma_addr = sg_dma_address(task->scatter);
			ssp_cmd.enc_addr_low =
				cpu_to_le32(lower_32_bits(dma_addr));
			ssp_cmd.enc_addr_high =
				cpu_to_le32(upper_32_bits(dma_addr));
			ssp_cmd.enc_len = cpu_to_le32(task->total_xfer_len);
			ssp_cmd.enc_esgl = 0;
			/* Check 4G Boundary */
			start_addr = cpu_to_le64(dma_addr);
			end_addr = (start_addr + ssp_cmd.enc_len) - 1;
			end_addr_low = cpu_to_le32(lower_32_bits(end_addr));
			end_addr_high = cpu_to_le32(upper_32_bits(end_addr));
			अगर (end_addr_high != ssp_cmd.enc_addr_high) अणु
				pm8001_dbg(pm8001_ha, FAIL,
					   "The sg list address start_addr=0x%016llx data_len=0x%x end_addr_high=0x%08x end_addr_low=0x%08x has crossed 4G boundary\n",
					   start_addr, ssp_cmd.enc_len,
					   end_addr_high, end_addr_low);
				pm8001_chip_make_sg(task->scatter, 1,
					ccb->buf_prd);
				phys_addr = ccb->ccb_dma_handle;
				ssp_cmd.enc_addr_low =
					cpu_to_le32(lower_32_bits(phys_addr));
				ssp_cmd.enc_addr_high =
					cpu_to_le32(upper_32_bits(phys_addr));
				ssp_cmd.enc_esgl = cpu_to_le32(1<<31);
			पूर्ण
		पूर्ण अन्यथा अगर (task->num_scatter == 0) अणु
			ssp_cmd.enc_addr_low = 0;
			ssp_cmd.enc_addr_high = 0;
			ssp_cmd.enc_len = cpu_to_le32(task->total_xfer_len);
			ssp_cmd.enc_esgl = 0;
		पूर्ण
		/* XTS mode. All other fields are 0 */
		ssp_cmd.key_cmode = 0x6 << 4;
		/* set tweak values. Should be the start lba */
		ssp_cmd.twk_val0 = cpu_to_le32((task->ssp_task.cmd->cmnd[2] << 24) |
						(task->ssp_task.cmd->cmnd[3] << 16) |
						(task->ssp_task.cmd->cmnd[4] << 8) |
						(task->ssp_task.cmd->cmnd[5]));
	पूर्ण अन्यथा अणु
		pm8001_dbg(pm8001_ha, IO,
			   "Sending Normal SAS command 0x%x inb q %x\n",
			   task->ssp_task.cmd->cmnd[0], q_index);
		/* fill in PRD (scatter/gather) table, अगर any */
		अगर (task->num_scatter > 1) अणु
			pm8001_chip_make_sg(task->scatter, ccb->n_elem,
					ccb->buf_prd);
			phys_addr = ccb->ccb_dma_handle;
			ssp_cmd.addr_low =
				cpu_to_le32(lower_32_bits(phys_addr));
			ssp_cmd.addr_high =
				cpu_to_le32(upper_32_bits(phys_addr));
			ssp_cmd.esgl = cpu_to_le32(1<<31);
		पूर्ण अन्यथा अगर (task->num_scatter == 1) अणु
			u64 dma_addr = sg_dma_address(task->scatter);
			ssp_cmd.addr_low = cpu_to_le32(lower_32_bits(dma_addr));
			ssp_cmd.addr_high =
				cpu_to_le32(upper_32_bits(dma_addr));
			ssp_cmd.len = cpu_to_le32(task->total_xfer_len);
			ssp_cmd.esgl = 0;
			/* Check 4G Boundary */
			start_addr = cpu_to_le64(dma_addr);
			end_addr = (start_addr + ssp_cmd.len) - 1;
			end_addr_low = cpu_to_le32(lower_32_bits(end_addr));
			end_addr_high = cpu_to_le32(upper_32_bits(end_addr));
			अगर (end_addr_high != ssp_cmd.addr_high) अणु
				pm8001_dbg(pm8001_ha, FAIL,
					   "The sg list address start_addr=0x%016llx data_len=0x%x end_addr_high=0x%08x end_addr_low=0x%08x has crossed 4G boundary\n",
					   start_addr, ssp_cmd.len,
					   end_addr_high, end_addr_low);
				pm8001_chip_make_sg(task->scatter, 1,
					ccb->buf_prd);
				phys_addr = ccb->ccb_dma_handle;
				ssp_cmd.addr_low =
					cpu_to_le32(lower_32_bits(phys_addr));
				ssp_cmd.addr_high =
					cpu_to_le32(upper_32_bits(phys_addr));
				ssp_cmd.esgl = cpu_to_le32(1<<31);
			पूर्ण
		पूर्ण अन्यथा अगर (task->num_scatter == 0) अणु
			ssp_cmd.addr_low = 0;
			ssp_cmd.addr_high = 0;
			ssp_cmd.len = cpu_to_le32(task->total_xfer_len);
			ssp_cmd.esgl = 0;
		पूर्ण
	पूर्ण
	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc,
			&ssp_cmd, माप(ssp_cmd), q_index);
	वापस ret;
पूर्ण

अटल पूर्णांक pm80xx_chip_sata_req(काष्ठा pm8001_hba_info *pm8001_ha,
	काष्ठा pm8001_ccb_info *ccb)
अणु
	काष्ठा sas_task *task = ccb->task;
	काष्ठा करोमुख्य_device *dev = task->dev;
	काष्ठा pm8001_device *pm8001_ha_dev = dev->lldd_dev;
	u32 tag = ccb->ccb_tag;
	पूर्णांक ret;
	u32 q_index, cpu_id;
	काष्ठा sata_start_req sata_cmd;
	u32 hdr_tag, ncg_tag = 0;
	u64 phys_addr, start_addr, end_addr;
	u32 end_addr_high, end_addr_low;
	u32 ATAP = 0x0;
	u32 dir;
	काष्ठा inbound_queue_table *circularQ;
	अचिन्हित दीर्घ flags;
	u32 opc = OPC_INB_SATA_HOST_OPSTART;
	स_रखो(&sata_cmd, 0, माप(sata_cmd));
	cpu_id = smp_processor_id();
	q_index = (u32) (cpu_id) % (pm8001_ha->max_q_num);
	circularQ = &pm8001_ha->inbnd_q_tbl[q_index];

	अगर (task->data_dir == DMA_NONE) अणु
		ATAP = 0x04; /* no data*/
		pm8001_dbg(pm8001_ha, IO, "no data\n");
	पूर्ण अन्यथा अगर (likely(!task->ata_task.device_control_reg_update)) अणु
		अगर (task->ata_task.dma_xfer) अणु
			ATAP = 0x06; /* DMA */
			pm8001_dbg(pm8001_ha, IO, "DMA\n");
		पूर्ण अन्यथा अणु
			ATAP = 0x05; /* PIO*/
			pm8001_dbg(pm8001_ha, IO, "PIO\n");
		पूर्ण
		अगर (task->ata_task.use_ncq &&
		    dev->sata_dev.class != ATA_DEV_ATAPI) अणु
			ATAP = 0x07; /* FPDMA */
			pm8001_dbg(pm8001_ha, IO, "FPDMA\n");
		पूर्ण
	पूर्ण
	अगर (task->ata_task.use_ncq && pm8001_get_ncq_tag(task, &hdr_tag)) अणु
		task->ata_task.fis.sector_count |= (u8) (hdr_tag << 3);
		ncg_tag = hdr_tag;
	पूर्ण
	dir = data_dir_flags[task->data_dir] << 8;
	sata_cmd.tag = cpu_to_le32(tag);
	sata_cmd.device_id = cpu_to_le32(pm8001_ha_dev->device_id);
	sata_cmd.data_len = cpu_to_le32(task->total_xfer_len);

	sata_cmd.sata_fis = task->ata_task.fis;
	अगर (likely(!task->ata_task.device_control_reg_update))
		sata_cmd.sata_fis.flags |= 0x80;/* C=1: update ATA cmd reg */
	sata_cmd.sata_fis.flags &= 0xF0;/* PM_PORT field shall be 0 */

	/* Check अगर encryption is set */
	अगर (pm8001_ha->chip->encrypt &&
		!(pm8001_ha->encrypt_info.status) && check_enc_sat_cmd(task)) अणु
		pm8001_dbg(pm8001_ha, IO,
			   "Encryption enabled.Sending Encrypt SATA cmd 0x%x\n",
			   sata_cmd.sata_fis.command);
		opc = OPC_INB_SATA_DIF_ENC_IO;

		/* set encryption bit */
		sata_cmd.ncqtag_atap_dir_m_dad =
			cpu_to_le32(((ncg_tag & 0xff)<<16)|
				((ATAP & 0x3f) << 10) | 0x20 | dir);
							/* dad (bit 0-1) is 0 */
		/* fill in PRD (scatter/gather) table, अगर any */
		अगर (task->num_scatter > 1) अणु
			pm8001_chip_make_sg(task->scatter,
						ccb->n_elem, ccb->buf_prd);
			phys_addr = ccb->ccb_dma_handle;
			sata_cmd.enc_addr_low = lower_32_bits(phys_addr);
			sata_cmd.enc_addr_high = upper_32_bits(phys_addr);
			sata_cmd.enc_esgl = cpu_to_le32(1 << 31);
		पूर्ण अन्यथा अगर (task->num_scatter == 1) अणु
			u64 dma_addr = sg_dma_address(task->scatter);
			sata_cmd.enc_addr_low = lower_32_bits(dma_addr);
			sata_cmd.enc_addr_high = upper_32_bits(dma_addr);
			sata_cmd.enc_len = cpu_to_le32(task->total_xfer_len);
			sata_cmd.enc_esgl = 0;
			/* Check 4G Boundary */
			start_addr = cpu_to_le64(dma_addr);
			end_addr = (start_addr + sata_cmd.enc_len) - 1;
			end_addr_low = cpu_to_le32(lower_32_bits(end_addr));
			end_addr_high = cpu_to_le32(upper_32_bits(end_addr));
			अगर (end_addr_high != sata_cmd.enc_addr_high) अणु
				pm8001_dbg(pm8001_ha, FAIL,
					   "The sg list address start_addr=0x%016llx data_len=0x%x end_addr_high=0x%08x end_addr_low=0x%08x has crossed 4G boundary\n",
					   start_addr, sata_cmd.enc_len,
					   end_addr_high, end_addr_low);
				pm8001_chip_make_sg(task->scatter, 1,
					ccb->buf_prd);
				phys_addr = ccb->ccb_dma_handle;
				sata_cmd.enc_addr_low =
					lower_32_bits(phys_addr);
				sata_cmd.enc_addr_high =
					upper_32_bits(phys_addr);
				sata_cmd.enc_esgl =
					cpu_to_le32(1 << 31);
			पूर्ण
		पूर्ण अन्यथा अगर (task->num_scatter == 0) अणु
			sata_cmd.enc_addr_low = 0;
			sata_cmd.enc_addr_high = 0;
			sata_cmd.enc_len = cpu_to_le32(task->total_xfer_len);
			sata_cmd.enc_esgl = 0;
		पूर्ण
		/* XTS mode. All other fields are 0 */
		sata_cmd.key_index_mode = 0x6 << 4;
		/* set tweak values. Should be the start lba */
		sata_cmd.twk_val0 =
			cpu_to_le32((sata_cmd.sata_fis.lbal_exp << 24) |
					(sata_cmd.sata_fis.lbah << 16) |
					(sata_cmd.sata_fis.lbam << 8) |
					(sata_cmd.sata_fis.lbal));
		sata_cmd.twk_val1 =
			cpu_to_le32((sata_cmd.sata_fis.lbah_exp << 8) |
					 (sata_cmd.sata_fis.lbam_exp));
	पूर्ण अन्यथा अणु
		pm8001_dbg(pm8001_ha, IO,
			   "Sending Normal SATA command 0x%x inb %x\n",
			   sata_cmd.sata_fis.command, q_index);
		/* dad (bit 0-1) is 0 */
		sata_cmd.ncqtag_atap_dir_m_dad =
			cpu_to_le32(((ncg_tag & 0xff)<<16) |
					((ATAP & 0x3f) << 10) | dir);

		/* fill in PRD (scatter/gather) table, अगर any */
		अगर (task->num_scatter > 1) अणु
			pm8001_chip_make_sg(task->scatter,
					ccb->n_elem, ccb->buf_prd);
			phys_addr = ccb->ccb_dma_handle;
			sata_cmd.addr_low = lower_32_bits(phys_addr);
			sata_cmd.addr_high = upper_32_bits(phys_addr);
			sata_cmd.esgl = cpu_to_le32(1 << 31);
		पूर्ण अन्यथा अगर (task->num_scatter == 1) अणु
			u64 dma_addr = sg_dma_address(task->scatter);
			sata_cmd.addr_low = lower_32_bits(dma_addr);
			sata_cmd.addr_high = upper_32_bits(dma_addr);
			sata_cmd.len = cpu_to_le32(task->total_xfer_len);
			sata_cmd.esgl = 0;
			/* Check 4G Boundary */
			start_addr = cpu_to_le64(dma_addr);
			end_addr = (start_addr + sata_cmd.len) - 1;
			end_addr_low = cpu_to_le32(lower_32_bits(end_addr));
			end_addr_high = cpu_to_le32(upper_32_bits(end_addr));
			अगर (end_addr_high != sata_cmd.addr_high) अणु
				pm8001_dbg(pm8001_ha, FAIL,
					   "The sg list address start_addr=0x%016llx data_len=0x%xend_addr_high=0x%08x end_addr_low=0x%08x has crossed 4G boundary\n",
					   start_addr, sata_cmd.len,
					   end_addr_high, end_addr_low);
				pm8001_chip_make_sg(task->scatter, 1,
					ccb->buf_prd);
				phys_addr = ccb->ccb_dma_handle;
				sata_cmd.addr_low =
					lower_32_bits(phys_addr);
				sata_cmd.addr_high =
					upper_32_bits(phys_addr);
				sata_cmd.esgl = cpu_to_le32(1 << 31);
			पूर्ण
		पूर्ण अन्यथा अगर (task->num_scatter == 0) अणु
			sata_cmd.addr_low = 0;
			sata_cmd.addr_high = 0;
			sata_cmd.len = cpu_to_le32(task->total_xfer_len);
			sata_cmd.esgl = 0;
		पूर्ण
		/* scsi cdb */
		sata_cmd.atapi_scsi_cdb[0] =
			cpu_to_le32(((task->ata_task.atapi_packet[0]) |
			(task->ata_task.atapi_packet[1] << 8) |
			(task->ata_task.atapi_packet[2] << 16) |
			(task->ata_task.atapi_packet[3] << 24)));
		sata_cmd.atapi_scsi_cdb[1] =
			cpu_to_le32(((task->ata_task.atapi_packet[4]) |
			(task->ata_task.atapi_packet[5] << 8) |
			(task->ata_task.atapi_packet[6] << 16) |
			(task->ata_task.atapi_packet[7] << 24)));
		sata_cmd.atapi_scsi_cdb[2] =
			cpu_to_le32(((task->ata_task.atapi_packet[8]) |
			(task->ata_task.atapi_packet[9] << 8) |
			(task->ata_task.atapi_packet[10] << 16) |
			(task->ata_task.atapi_packet[11] << 24)));
		sata_cmd.atapi_scsi_cdb[3] =
			cpu_to_le32(((task->ata_task.atapi_packet[12]) |
			(task->ata_task.atapi_packet[13] << 8) |
			(task->ata_task.atapi_packet[14] << 16) |
			(task->ata_task.atapi_packet[15] << 24)));
	पूर्ण

	/* Check क्रम पढ़ो log क्रम failed drive and वापस */
	अगर (sata_cmd.sata_fis.command == 0x2f) अणु
		अगर (pm8001_ha_dev && ((pm8001_ha_dev->id & NCQ_READ_LOG_FLAG) ||
			(pm8001_ha_dev->id & NCQ_ABORT_ALL_FLAG) ||
			(pm8001_ha_dev->id & NCQ_2ND_RLE_FLAG))) अणु
			काष्ठा task_status_काष्ठा *ts;

			pm8001_ha_dev->id &= 0xDFFFFFFF;
			ts = &task->task_status;

			spin_lock_irqsave(&task->task_state_lock, flags);
			ts->resp = SAS_TASK_COMPLETE;
			ts->stat = SAM_STAT_GOOD;
			task->task_state_flags &= ~SAS_TASK_STATE_PENDING;
			task->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
			task->task_state_flags |= SAS_TASK_STATE_DONE;
			अगर (unlikely((task->task_state_flags &
					SAS_TASK_STATE_ABORTED))) अणु
				spin_unlock_irqrestore(&task->task_state_lock,
							flags);
				pm8001_dbg(pm8001_ha, FAIL,
					   "task 0x%p resp 0x%x  stat 0x%x but aborted by upper layer\n",
					   task, ts->resp,
					   ts->stat);
				pm8001_ccb_task_मुक्त(pm8001_ha, task, ccb, tag);
				वापस 0;
			पूर्ण अन्यथा अणु
				spin_unlock_irqrestore(&task->task_state_lock,
							flags);
				pm8001_ccb_task_मुक्त_करोne(pm8001_ha, task,
								ccb, tag);
				atomic_dec(&pm8001_ha_dev->running_req);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc,
			&sata_cmd, माप(sata_cmd), q_index);
	वापस ret;
पूर्ण

/**
 * pm80xx_chip_phy_start_req - start phy via PHY_START COMMAND
 * @pm8001_ha: our hba card inक्रमmation.
 * @phy_id: the phy id which we wanted to start up.
 */
अटल पूर्णांक
pm80xx_chip_phy_start_req(काष्ठा pm8001_hba_info *pm8001_ha, u8 phy_id)
अणु
	काष्ठा phy_start_req payload;
	काष्ठा inbound_queue_table *circularQ;
	पूर्णांक ret;
	u32 tag = 0x01;
	u32 opcode = OPC_INB_PHYSTART;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	स_रखो(&payload, 0, माप(payload));
	payload.tag = cpu_to_le32(tag);

	pm8001_dbg(pm8001_ha, INIT, "PHY START REQ for phy_id %d\n", phy_id);

	payload.ase_sh_lm_slr_phyid = cpu_to_le32(SPINHOLD_DISABLE |
			LINKMODE_AUTO | pm8001_ha->link_rate | phy_id);
	/* SSC Disable and SAS Analog ST configuration */
	/**
	payload.ase_sh_lm_slr_phyid =
		cpu_to_le32(SSC_DISABLE_30 | SAS_ASE | SPINHOLD_DISABLE |
		LINKMODE_AUTO | LINKRATE_15 | LINKRATE_30 | LINKRATE_60 |
		phy_id);
	Have to add "SAS PHY Analog Setup SPASTI 1 Byte" Based on need
	**/

	payload.sas_identअगरy.dev_type = SAS_END_DEVICE;
	payload.sas_identअगरy.initiator_bits = SAS_PROTOCOL_ALL;
	स_नकल(payload.sas_identअगरy.sas_addr,
	  &pm8001_ha->sas_addr, SAS_ADDR_SIZE);
	payload.sas_identअगरy.phy_id = phy_id;
	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opcode, &payload,
			माप(payload), 0);
	वापस ret;
पूर्ण

/**
 * pm80xx_chip_phy_stop_req - start phy via PHY_STOP COMMAND
 * @pm8001_ha: our hba card inक्रमmation.
 * @phy_id: the phy id which we wanted to start up.
 */
अटल पूर्णांक pm80xx_chip_phy_stop_req(काष्ठा pm8001_hba_info *pm8001_ha,
	u8 phy_id)
अणु
	काष्ठा phy_stop_req payload;
	काष्ठा inbound_queue_table *circularQ;
	पूर्णांक ret;
	u32 tag = 0x01;
	u32 opcode = OPC_INB_PHYSTOP;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	स_रखो(&payload, 0, माप(payload));
	payload.tag = cpu_to_le32(tag);
	payload.phy_id = cpu_to_le32(phy_id);
	ret = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opcode, &payload,
			माप(payload), 0);
	वापस ret;
पूर्ण

/*
 * see comments on pm8001_mpi_reg_resp.
 */
अटल पूर्णांक pm80xx_chip_reg_dev_req(काष्ठा pm8001_hba_info *pm8001_ha,
	काष्ठा pm8001_device *pm8001_dev, u32 flag)
अणु
	काष्ठा reg_dev_req payload;
	u32	opc;
	u32 stp_sspsmp_sata = 0x4;
	काष्ठा inbound_queue_table *circularQ;
	u32 linkrate, phy_id;
	पूर्णांक rc, tag = 0xdeadbeef;
	काष्ठा pm8001_ccb_info *ccb;
	u8 retryFlag = 0x1;
	u16 firstBurstSize = 0;
	u16 ITNT = 2000;
	काष्ठा करोमुख्य_device *dev = pm8001_dev->sas_device;
	काष्ठा करोमुख्य_device *parent_dev = dev->parent;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];

	स_रखो(&payload, 0, माप(payload));
	rc = pm8001_tag_alloc(pm8001_ha, &tag);
	अगर (rc)
		वापस rc;
	ccb = &pm8001_ha->ccb_info[tag];
	ccb->device = pm8001_dev;
	ccb->ccb_tag = tag;
	payload.tag = cpu_to_le32(tag);

	अगर (flag == 1) अणु
		stp_sspsmp_sata = 0x02; /*direct attached sata */
	पूर्ण अन्यथा अणु
		अगर (pm8001_dev->dev_type == SAS_SATA_DEV)
			stp_sspsmp_sata = 0x00; /* stp*/
		अन्यथा अगर (pm8001_dev->dev_type == SAS_END_DEVICE ||
			pm8001_dev->dev_type == SAS_EDGE_EXPANDER_DEVICE ||
			pm8001_dev->dev_type == SAS_FANOUT_EXPANDER_DEVICE)
			stp_sspsmp_sata = 0x01; /*ssp or smp*/
	पूर्ण
	अगर (parent_dev && dev_is_expander(parent_dev->dev_type))
		phy_id = parent_dev->ex_dev.ex_phy->phy_id;
	अन्यथा
		phy_id = pm8001_dev->attached_phy;

	opc = OPC_INB_REG_DEV;

	linkrate = (pm8001_dev->sas_device->linkrate < dev->port->linkrate) ?
			pm8001_dev->sas_device->linkrate : dev->port->linkrate;

	payload.phyid_portid =
		cpu_to_le32(((pm8001_dev->sas_device->port->id) & 0xFF) |
		((phy_id & 0xFF) << 8));

	payload.dtype_dlr_mcn_ir_retry = cpu_to_le32((retryFlag & 0x01) |
		((linkrate & 0x0F) << 24) |
		((stp_sspsmp_sata & 0x03) << 28));
	payload.firstburstsize_ITNexusसमयout =
		cpu_to_le32(ITNT | (firstBurstSize * 0x10000));

	स_नकल(payload.sas_addr, pm8001_dev->sas_device->sas_addr,
		SAS_ADDR_SIZE);

	rc = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload,
			माप(payload), 0);
	अगर (rc)
		pm8001_tag_मुक्त(pm8001_ha, tag);

	वापस rc;
पूर्ण

/**
 * pm80xx_chip_phy_ctl_req - support the local phy operation
 * @pm8001_ha: our hba card inक्रमmation.
 * @phyId: the phy id which we wanted to operate
 * @phy_op: phy operation to request
 */
अटल पूर्णांक pm80xx_chip_phy_ctl_req(काष्ठा pm8001_hba_info *pm8001_ha,
	u32 phyId, u32 phy_op)
अणु
	u32 tag;
	पूर्णांक rc;
	काष्ठा local_phy_ctl_req payload;
	काष्ठा inbound_queue_table *circularQ;
	u32 opc = OPC_INB_LOCAL_PHY_CONTROL;
	स_रखो(&payload, 0, माप(payload));
	rc = pm8001_tag_alloc(pm8001_ha, &tag);
	अगर (rc)
		वापस rc;
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	payload.tag = cpu_to_le32(tag);
	payload.phyop_phyid =
		cpu_to_le32(((phy_op & 0xFF) << 8) | (phyId & 0xFF));
	वापस pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload,
			माप(payload), 0);
पूर्ण

अटल u32 pm80xx_chip_is_our_पूर्णांकerrupt(काष्ठा pm8001_hba_info *pm8001_ha)
अणु
#अगर_घोषित PM8001_USE_MSIX
	वापस 1;
#अन्यथा
	u32 value;

	value = pm8001_cr32(pm8001_ha, 0, MSGU_ODR);
	अगर (value)
		वापस 1;
	वापस 0;
#पूर्ण_अगर
पूर्ण

/**
 * pm80xx_chip_isr - PM8001 isr handler.
 * @pm8001_ha: our hba card inक्रमmation.
 * @vec: irq number.
 */
अटल irqवापस_t
pm80xx_chip_isr(काष्ठा pm8001_hba_info *pm8001_ha, u8 vec)
अणु
	pm80xx_chip_पूर्णांकerrupt_disable(pm8001_ha, vec);
	pm8001_dbg(pm8001_ha, DEVIO,
		   "irq vec %d, ODMR:0x%x\n",
		   vec, pm8001_cr32(pm8001_ha, 0, 0x30));
	process_oq(pm8001_ha, vec);
	pm80xx_chip_पूर्णांकerrupt_enable(pm8001_ha, vec);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mpi_set_phy_profile_req(काष्ठा pm8001_hba_info *pm8001_ha,
				    u32 operation, u32 phyid,
				    u32 length, u32 *buf)
अणु
	u32 tag, i, j = 0;
	पूर्णांक rc;
	काष्ठा set_phy_profile_req payload;
	काष्ठा inbound_queue_table *circularQ;
	u32 opc = OPC_INB_SET_PHY_PROखाता;

	स_रखो(&payload, 0, माप(payload));
	rc = pm8001_tag_alloc(pm8001_ha, &tag);
	अगर (rc)
		pm8001_dbg(pm8001_ha, FAIL, "Invalid tag\n");
	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	payload.tag = cpu_to_le32(tag);
	payload.ppc_phyid = (((operation & 0xF) << 8) | (phyid  & 0xFF));
	pm8001_dbg(pm8001_ha, INIT,
		   " phy profile command for phy %x ,length is %d\n",
		   payload.ppc_phyid, length);
	क्रम (i = length; i < (length + PHY_DWORD_LENGTH - 1); i++) अणु
		payload.reserved[j] =  cpu_to_le32(*((u32 *)buf + i));
		j++;
	पूर्ण
	rc = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload,
			माप(payload), 0);
	अगर (rc)
		pm8001_tag_मुक्त(pm8001_ha, tag);
पूर्ण

व्योम pm8001_set_phy_profile(काष्ठा pm8001_hba_info *pm8001_ha,
	u32 length, u8 *buf)
अणु
	u32 i;

	क्रम (i = 0; i < pm8001_ha->chip->n_phy; i++) अणु
		mpi_set_phy_profile_req(pm8001_ha,
			SAS_PHY_ANALOG_SETTINGS_PAGE, i, length, (u32 *)buf);
		length = length + PHY_DWORD_LENGTH;
	पूर्ण
	pm8001_dbg(pm8001_ha, INIT, "phy settings completed\n");
पूर्ण

व्योम pm8001_set_phy_profile_single(काष्ठा pm8001_hba_info *pm8001_ha,
		u32 phy, u32 length, u32 *buf)
अणु
	u32 tag, opc;
	पूर्णांक rc, i;
	काष्ठा set_phy_profile_req payload;
	काष्ठा inbound_queue_table *circularQ;

	स_रखो(&payload, 0, माप(payload));

	rc = pm8001_tag_alloc(pm8001_ha, &tag);
	अगर (rc)
		pm8001_dbg(pm8001_ha, INIT, "Invalid tag\n");

	circularQ = &pm8001_ha->inbnd_q_tbl[0];
	opc = OPC_INB_SET_PHY_PROखाता;

	payload.tag = cpu_to_le32(tag);
	payload.ppc_phyid = (((SAS_PHY_ANALOG_SETTINGS_PAGE & 0xF) << 8)
				| (phy & 0xFF));

	क्रम (i = 0; i < length; i++)
		payload.reserved[i] = cpu_to_le32(*(buf + i));

	rc = pm8001_mpi_build_cmd(pm8001_ha, circularQ, opc, &payload,
			माप(payload), 0);
	अगर (rc)
		pm8001_tag_मुक्त(pm8001_ha, tag);

	pm8001_dbg(pm8001_ha, INIT, "PHY %d settings applied\n", phy);
पूर्ण
स्थिर काष्ठा pm8001_dispatch pm8001_80xx_dispatch = अणु
	.name			= "pmc80xx",
	.chip_init		= pm80xx_chip_init,
	.chip_soft_rst		= pm80xx_chip_soft_rst,
	.chip_rst		= pm80xx_hw_chip_rst,
	.chip_iounmap		= pm8001_chip_iounmap,
	.isr			= pm80xx_chip_isr,
	.is_our_पूर्णांकerrupt	= pm80xx_chip_is_our_पूर्णांकerrupt,
	.isr_process_oq		= process_oq,
	.पूर्णांकerrupt_enable	= pm80xx_chip_पूर्णांकerrupt_enable,
	.पूर्णांकerrupt_disable	= pm80xx_chip_पूर्णांकerrupt_disable,
	.make_prd		= pm8001_chip_make_sg,
	.smp_req		= pm80xx_chip_smp_req,
	.ssp_io_req		= pm80xx_chip_ssp_io_req,
	.sata_req		= pm80xx_chip_sata_req,
	.phy_start_req		= pm80xx_chip_phy_start_req,
	.phy_stop_req		= pm80xx_chip_phy_stop_req,
	.reg_dev_req		= pm80xx_chip_reg_dev_req,
	.dereg_dev_req		= pm8001_chip_dereg_dev_req,
	.phy_ctl_req		= pm80xx_chip_phy_ctl_req,
	.task_पात		= pm8001_chip_पात_task,
	.ssp_पंचांग_req		= pm8001_chip_ssp_पंचांग_req,
	.get_nvmd_req		= pm8001_chip_get_nvmd_req,
	.set_nvmd_req		= pm8001_chip_set_nvmd_req,
	.fw_flash_update_req	= pm8001_chip_fw_flash_update_req,
	.set_dev_state_req	= pm8001_chip_set_dev_state_req,
	.fatal_errors		= pm80xx_fatal_errors,
पूर्ण;
