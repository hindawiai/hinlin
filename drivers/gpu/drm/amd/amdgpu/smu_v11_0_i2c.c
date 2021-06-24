<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश "smuio/smuio_11_0_0_offset.h"
#समावेश "smuio/smuio_11_0_0_sh_mask.h"

#समावेश "smu_v11_0_i2c.h"
#समावेश "amdgpu.h"
#समावेश "soc15_common.h"
#समावेश <drm/drm_fixed.h>
#समावेश <drm/drm_drv.h>
#समावेश "amdgpu_amdkfd.h"
#समावेश <linux/i2c.h>
#समावेश <linux/pci.h>

/* error codes */
#घोषणा I2C_OK                0
#घोषणा I2C_NAK_7B_ADDR_NOACK 1
#घोषणा I2C_NAK_TXDATA_NOACK  2
#घोषणा I2C_TIMEOUT           4
#घोषणा I2C_SW_TIMEOUT        8
#घोषणा I2C_ABORT             0x10

/* I2C transaction flags */
#घोषणा I2C_NO_STOP	1
#घोषणा I2C_RESTART	2

#घोषणा to_amdgpu_device(x) (container_of(x, काष्ठा amdgpu_device, pm.smu_i2c))

अटल व्योम smu_v11_0_i2c_set_घड़ी_gating(काष्ठा i2c_adapter *control, bool en)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);
	uपूर्णांक32_t reg = RREG32_SOC15(SMUIO, 0, mmSMUIO_PWRMGT);

	reg = REG_SET_FIELD(reg, SMUIO_PWRMGT, i2c_clk_gate_en, en ? 1 : 0);
	WREG32_SOC15(SMUIO, 0, mmSMUIO_PWRMGT, reg);
पूर्ण


अटल व्योम smu_v11_0_i2c_enable(काष्ठा i2c_adapter *control, bool enable)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);

	WREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_ENABLE, enable ? 1 : 0);
पूर्ण

अटल व्योम smu_v11_0_i2c_clear_status(काष्ठा i2c_adapter *control)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);
	/* करो */
	अणु
		RREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_CLR_INTR);

	पूर्ण /* जबतक (reg_CKSVII2C_ic_clr_पूर्णांकr == 0) */
पूर्ण

अटल व्योम smu_v11_0_i2c_configure(काष्ठा i2c_adapter *control)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);
	uपूर्णांक32_t reg = 0;

	reg = REG_SET_FIELD(reg, CKSVII2C_IC_CON, IC_SLAVE_DISABLE, 1);
	reg = REG_SET_FIELD(reg, CKSVII2C_IC_CON, IC_RESTART_EN, 1);
	reg = REG_SET_FIELD(reg, CKSVII2C_IC_CON, IC_10BITADDR_MASTER, 0);
	reg = REG_SET_FIELD(reg, CKSVII2C_IC_CON, IC_10BITADDR_SLAVE, 0);
	/* Standard mode */
	reg = REG_SET_FIELD(reg, CKSVII2C_IC_CON, IC_MAX_SPEED_MODE, 2);
	reg = REG_SET_FIELD(reg, CKSVII2C_IC_CON, IC_MASTER_MODE, 1);

	WREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_CON, reg);
पूर्ण

अटल व्योम smu_v11_0_i2c_set_घड़ी(काष्ठा i2c_adapter *control)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);

	/*
	 * Standard mode speed, These values are taken from SMUIO MAS,
	 * but are dअगरferent from what is given is
	 * Synopsys spec. The values here are based on assumption
	 * that refघड़ी is 100MHz
	 *
	 * Configuration क्रम standard mode; Speed = 100kbps
	 * Scale linearly, क्रम now only support standard speed घड़ी
	 * This will work only with 100M ref घड़ी
	 *
	 * TBD:Change the calculation to take पूर्णांकo account ref घड़ी values also.
	 */

	WREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_FS_SPKLEN, 2);
	WREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_SS_SCL_HCNT, 120);
	WREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_SS_SCL_LCNT, 130);
	WREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_SDA_HOLD, 20);
पूर्ण

अटल व्योम smu_v11_0_i2c_set_address(काष्ठा i2c_adapter *control, uपूर्णांक8_t address)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);

	/* Convert fromr 8-bit to 7-bit address */
	address >>= 1;
	WREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_TAR, (address & 0xFF));
पूर्ण

अटल uपूर्णांक32_t smu_v11_0_i2c_poll_tx_status(काष्ठा i2c_adapter *control)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);
	uपूर्णांक32_t ret = I2C_OK;
	uपूर्णांक32_t reg, reg_c_tx_abrt_source;

	/*Check अगर transmission is completed */
	अचिन्हित दीर्घ  समयout_counter = jअगरfies + msecs_to_jअगरfies(20);

	करो अणु
		अगर (समय_after(jअगरfies, समयout_counter)) अणु
			ret |= I2C_SW_TIMEOUT;
			अवरोध;
		पूर्ण

		reg = RREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_STATUS);

	पूर्ण जबतक (REG_GET_FIELD(reg, CKSVII2C_IC_STATUS, TFE) == 0);

	अगर (ret != I2C_OK)
		वापस ret;

	/* This only checks अगर NAK is received and transaction got पातed */
	reg = RREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_INTR_STAT);

	अगर (REG_GET_FIELD(reg, CKSVII2C_IC_INTR_STAT, R_TX_ABRT) == 1) अणु
		reg_c_tx_abrt_source = RREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_TX_ABRT_SOURCE);
		DRM_INFO("TX was terminated, IC_TX_ABRT_SOURCE val is:%x", reg_c_tx_abrt_source);

		/* Check क्रम stop due to NACK */
		अगर (REG_GET_FIELD(reg_c_tx_abrt_source,
				  CKSVII2C_IC_TX_ABRT_SOURCE,
				  ABRT_TXDATA_NOACK) == 1) अणु

			ret |= I2C_NAK_TXDATA_NOACK;

		पूर्ण अन्यथा अगर (REG_GET_FIELD(reg_c_tx_abrt_source,
					 CKSVII2C_IC_TX_ABRT_SOURCE,
					 ABRT_7B_ADDR_NOACK) == 1) अणु

			ret |= I2C_NAK_7B_ADDR_NOACK;
		पूर्ण अन्यथा अणु
			ret |= I2C_ABORT;
		पूर्ण

		smu_v11_0_i2c_clear_status(control);
	पूर्ण

	वापस ret;
पूर्ण

अटल uपूर्णांक32_t smu_v11_0_i2c_poll_rx_status(काष्ठा i2c_adapter *control)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);
	uपूर्णांक32_t ret = I2C_OK;
	uपूर्णांक32_t reg_ic_status, reg_c_tx_abrt_source;

	reg_c_tx_abrt_source = RREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_TX_ABRT_SOURCE);

	/* If slave is not present */
	अगर (REG_GET_FIELD(reg_c_tx_abrt_source,
			  CKSVII2C_IC_TX_ABRT_SOURCE,
			  ABRT_7B_ADDR_NOACK) == 1) अणु
		ret |= I2C_NAK_7B_ADDR_NOACK;

		smu_v11_0_i2c_clear_status(control);
	पूर्ण अन्यथा अणु  /* रुको till some data is there in RXFIFO */
		/* Poll क्रम some byte in RXFIFO */
		अचिन्हित दीर्घ  समयout_counter = jअगरfies + msecs_to_jअगरfies(20);

		करो अणु
			अगर (समय_after(jअगरfies, समयout_counter)) अणु
				ret |= I2C_SW_TIMEOUT;
				अवरोध;
			पूर्ण

			reg_ic_status = RREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_STATUS);

		पूर्ण जबतक (REG_GET_FIELD(reg_ic_status, CKSVII2C_IC_STATUS, RFNE) == 0);
	पूर्ण

	वापस ret;
पूर्ण




/**
 * smu_v11_0_i2c_transmit - Send a block of data over the I2C bus to a slave device.
 *
 * @control: I2C adapter reference
 * @address: The I2C address of the slave device.
 * @data: The data to transmit over the bus.
 * @numbytes: The amount of data to transmit.
 * @i2c_flag: Flags क्रम transmission
 *
 * Returns 0 on success or error.
 */
अटल uपूर्णांक32_t smu_v11_0_i2c_transmit(काष्ठा i2c_adapter *control,
				  uपूर्णांक8_t address, uपूर्णांक8_t *data,
				  uपूर्णांक32_t numbytes, uपूर्णांक32_t i2c_flag)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);
	uपूर्णांक32_t bytes_sent, reg, ret = 0;
	अचिन्हित दीर्घ  समयout_counter;

	bytes_sent = 0;

	DRM_DEBUG_DRIVER("I2C_Transmit(), address = %x, bytes = %d , data: ",
		 (uपूर्णांक16_t)address, numbytes);

	अगर (drm_debug_enabled(DRM_UT_DRIVER)) अणु
		prपूर्णांक_hex_dump(KERN_INFO, "data: ", DUMP_PREFIX_NONE,
			       16, 1, data, numbytes, false);
	पूर्ण

	/* Set the I2C slave address */
	smu_v11_0_i2c_set_address(control, address);
	/* Enable I2C */
	smu_v11_0_i2c_enable(control, true);

	/* Clear status bits */
	smu_v11_0_i2c_clear_status(control);


	समयout_counter = jअगरfies + msecs_to_jअगरfies(20);

	जबतक (numbytes > 0) अणु
		reg = RREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_STATUS);
		अगर (REG_GET_FIELD(reg, CKSVII2C_IC_STATUS, TFNF)) अणु
			करो अणु
				reg = 0;
				/*
				 * Prepare transaction, no need to set RESTART. I2C engine will send
				 * START as soon as it sees data in TXFIFO
				 */
				अगर (bytes_sent == 0)
					reg = REG_SET_FIELD(reg, CKSVII2C_IC_DATA_CMD, RESTART,
							    (i2c_flag & I2C_RESTART) ? 1 : 0);
				reg = REG_SET_FIELD(reg, CKSVII2C_IC_DATA_CMD, DAT, data[bytes_sent]);

				/* determine अगर we need to send STOP bit or not */
				अगर (numbytes == 1)
					/* Final transaction, so send stop unless I2C_NO_STOP */
					reg = REG_SET_FIELD(reg, CKSVII2C_IC_DATA_CMD, STOP,
							    (i2c_flag & I2C_NO_STOP) ? 0 : 1);
				/* Write */
				reg = REG_SET_FIELD(reg, CKSVII2C_IC_DATA_CMD, CMD, 0);
				WREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_DATA_CMD, reg);

				/* Record that the bytes were transmitted */
				bytes_sent++;
				numbytes--;

				reg = RREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_STATUS);

			पूर्ण जबतक (numbytes &&  REG_GET_FIELD(reg, CKSVII2C_IC_STATUS, TFNF));
		पूर्ण

		/*
		 * We रुकोed too दीर्घ क्रम the transmission FIFO to become not-full.
		 * Exit the loop with error.
		 */
		अगर (समय_after(jअगरfies, समयout_counter)) अणु
			ret |= I2C_SW_TIMEOUT;
			जाओ Err;
		पूर्ण
	पूर्ण

	ret = smu_v11_0_i2c_poll_tx_status(control);

Err:
	/* Any error, no poपूर्णांक in proceeding */
	अगर (ret != I2C_OK) अणु
		अगर (ret & I2C_SW_TIMEOUT)
			DRM_ERROR("TIMEOUT ERROR !!!");

		अगर (ret & I2C_NAK_7B_ADDR_NOACK)
			DRM_ERROR("Received I2C_NAK_7B_ADDR_NOACK !!!");


		अगर (ret & I2C_NAK_TXDATA_NOACK)
			DRM_ERROR("Received I2C_NAK_TXDATA_NOACK !!!");
	पूर्ण

	वापस ret;
पूर्ण


/**
 * smu_v11_0_i2c_receive - Receive a block of data over the I2C bus from a slave device.
 *
 * @control: I2C adapter reference
 * @address: The I2C address of the slave device.
 * @data: Placeholder to store received data.
 * @numbytes: The amount of data to transmit.
 * @i2c_flag: Flags क्रम transmission
 *
 * Returns 0 on success or error.
 */
अटल uपूर्णांक32_t smu_v11_0_i2c_receive(काष्ठा i2c_adapter *control,
				 uपूर्णांक8_t address, uपूर्णांक8_t *data,
				 uपूर्णांक32_t numbytes, uपूर्णांक8_t i2c_flag)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);
	uपूर्णांक32_t bytes_received, ret = I2C_OK;

	bytes_received = 0;

	/* Set the I2C slave address */
	smu_v11_0_i2c_set_address(control, address);

	/* Enable I2C */
	smu_v11_0_i2c_enable(control, true);

	जबतक (numbytes > 0) अणु
		uपूर्णांक32_t reg = 0;

		smu_v11_0_i2c_clear_status(control);


		/* Prepare transaction */

		/* Each समय we disable I2C, so this is not a restart */
		अगर (bytes_received == 0)
			reg = REG_SET_FIELD(reg, CKSVII2C_IC_DATA_CMD, RESTART,
					    (i2c_flag & I2C_RESTART) ? 1 : 0);

		reg = REG_SET_FIELD(reg, CKSVII2C_IC_DATA_CMD, DAT, 0);
		/* Read */
		reg = REG_SET_FIELD(reg, CKSVII2C_IC_DATA_CMD, CMD, 1);

		/* Transmitting last byte */
		अगर (numbytes == 1)
			/* Final transaction, so send stop अगर requested */
			reg = REG_SET_FIELD(reg, CKSVII2C_IC_DATA_CMD, STOP,
					    (i2c_flag & I2C_NO_STOP) ? 0 : 1);

		WREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_DATA_CMD, reg);

		ret = smu_v11_0_i2c_poll_rx_status(control);

		/* Any error, no poपूर्णांक in proceeding */
		अगर (ret != I2C_OK) अणु
			अगर (ret & I2C_SW_TIMEOUT)
				DRM_ERROR("TIMEOUT ERROR !!!");

			अगर (ret & I2C_NAK_7B_ADDR_NOACK)
				DRM_ERROR("Received I2C_NAK_7B_ADDR_NOACK !!!");

			अगर (ret & I2C_NAK_TXDATA_NOACK)
				DRM_ERROR("Received I2C_NAK_TXDATA_NOACK !!!");

			अवरोध;
		पूर्ण

		reg = RREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_DATA_CMD);
		data[bytes_received] = REG_GET_FIELD(reg, CKSVII2C_IC_DATA_CMD, DAT);

		/* Record that the bytes were received */
		bytes_received++;
		numbytes--;
	पूर्ण

	DRM_DEBUG_DRIVER("I2C_Receive(), address = %x, bytes = %d, data :",
		  (uपूर्णांक16_t)address, bytes_received);

	अगर (drm_debug_enabled(DRM_UT_DRIVER)) अणु
		prपूर्णांक_hex_dump(KERN_INFO, "data: ", DUMP_PREFIX_NONE,
			       16, 1, data, bytes_received, false);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम smu_v11_0_i2c_पात(काष्ठा i2c_adapter *control)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);
	uपूर्णांक32_t reg = 0;

	/* Enable I2C engine; */
	reg = REG_SET_FIELD(reg, CKSVII2C_IC_ENABLE, ENABLE, 1);
	WREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_ENABLE, reg);

	/* Abort previous transaction */
	reg = REG_SET_FIELD(reg, CKSVII2C_IC_ENABLE, ABORT, 1);
	WREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_ENABLE, reg);

	DRM_DEBUG_DRIVER("I2C_Abort() Done.");
पूर्ण


अटल bool smu_v11_0_i2c_activity_करोne(काष्ठा i2c_adapter *control)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);

	स्थिर uपूर्णांक32_t IDLE_TIMEOUT = 1024;
	uपूर्णांक32_t समयout_count = 0;
	uपूर्णांक32_t reg_ic_enable, reg_ic_enable_status, reg_ic_clr_activity;

	reg_ic_enable_status = RREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_ENABLE_STATUS);
	reg_ic_enable = RREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_ENABLE);


	अगर ((REG_GET_FIELD(reg_ic_enable, CKSVII2C_IC_ENABLE, ENABLE) == 0) &&
	    (REG_GET_FIELD(reg_ic_enable_status, CKSVII2C_IC_ENABLE_STATUS, IC_EN) == 1)) अणु
		/*
		 * Nobody is using I2C engine, but engine reमुख्यs active because
		 * someone missed to send STOP
		 */
		smu_v11_0_i2c_पात(control);
	पूर्ण अन्यथा अगर (REG_GET_FIELD(reg_ic_enable, CKSVII2C_IC_ENABLE, ENABLE) == 0) अणु
		/* Nobody is using I2C engine */
		वापस true;
	पूर्ण

	/* Keep पढ़ोing activity bit until it's cleared */
	करो अणु
		reg_ic_clr_activity = RREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_CLR_ACTIVITY);

		अगर (REG_GET_FIELD(reg_ic_clr_activity,
		    CKSVII2C_IC_CLR_ACTIVITY, CLR_ACTIVITY) == 0)
			वापस true;

		++समयout_count;

	पूर्ण जबतक (समयout_count < IDLE_TIMEOUT);

	वापस false;
पूर्ण

अटल व्योम smu_v11_0_i2c_init(काष्ठा i2c_adapter *control)
अणु
	/* Disable घड़ी gating */
	smu_v11_0_i2c_set_घड़ी_gating(control, false);

	अगर (!smu_v11_0_i2c_activity_करोne(control))
		DRM_WARN("I2C busy !");

	/* Disable I2C */
	smu_v11_0_i2c_enable(control, false);

	/* Configure I2C to operate as master and in standard mode */
	smu_v11_0_i2c_configure(control);

	/* Initialize the घड़ी to 50 kHz शेष */
	smu_v11_0_i2c_set_घड़ी(control);

पूर्ण

अटल व्योम smu_v11_0_i2c_fini(काष्ठा i2c_adapter *control)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);
	uपूर्णांक32_t reg_ic_enable_status, reg_ic_enable;

	smu_v11_0_i2c_enable(control, false);

	/* Double check अगर disabled, अन्यथा क्रमce पात */
	reg_ic_enable_status = RREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_ENABLE_STATUS);
	reg_ic_enable = RREG32_SOC15(SMUIO, 0, mmCKSVII2C_IC_ENABLE);

	अगर ((REG_GET_FIELD(reg_ic_enable, CKSVII2C_IC_ENABLE, ENABLE) == 0) &&
	    (REG_GET_FIELD(reg_ic_enable_status,
			   CKSVII2C_IC_ENABLE_STATUS, IC_EN) == 1)) अणु
		/*
		 * Nobody is using I2C engine, but engine reमुख्यs active because
		 * someone missed to send STOP
		 */
		smu_v11_0_i2c_पात(control);
	पूर्ण

	/* Restore घड़ी gating */

	/*
	 * TODO Reenabling घड़ी gating seems to अवरोध subsequent SMU operation
	 *      on the I2C bus. My guess is that SMU करोesn't disable घड़ी gating like
	 *      we करो here beक्रमe working with the bus. So क्रम now just करोn't restore
	 *      it but later work with SMU to see अगर they have this issue and can
	 *      update their code appropriately
	 */
	/* smu_v11_0_i2c_set_घड़ी_gating(control, true); */

पूर्ण

अटल bool smu_v11_0_i2c_bus_lock(काष्ठा i2c_adapter *control)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);

	/* Send  PPSMC_MSG_RequestI2CBus */
	अगर (!amdgpu_dpm_smu_i2c_bus_access(adev, true))
		वापस true;

	वापस false;
पूर्ण

अटल bool smu_v11_0_i2c_bus_unlock(काष्ठा i2c_adapter *control)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);

	/* Send  PPSMC_MSG_ReleaseI2CBus */
	अगर (!amdgpu_dpm_smu_i2c_bus_access(adev, false))
		वापस true;

	वापस false;
पूर्ण

/***************************** I2C GLUE ****************************/

अटल uपूर्णांक32_t smu_v11_0_i2c_पढ़ो_data(काष्ठा i2c_adapter *control,
					uपूर्णांक8_t address,
					uपूर्णांक8_t *data,
					uपूर्णांक32_t numbytes)
अणु
	uपूर्णांक32_t  ret = 0;

	/* First 2 bytes are dummy ग_लिखो to set EEPROM address */
	ret = smu_v11_0_i2c_transmit(control, address, data, 2, I2C_NO_STOP);
	अगर (ret != I2C_OK)
		जाओ Fail;

	/* Now पढ़ो data starting with that address */
	ret = smu_v11_0_i2c_receive(control, address, data + 2, numbytes - 2,
				    I2C_RESTART);

Fail:
	अगर (ret != I2C_OK)
		DRM_ERROR("ReadData() - I2C error occurred :%x", ret);

	वापस ret;
पूर्ण

अटल uपूर्णांक32_t smu_v11_0_i2c_ग_लिखो_data(काष्ठा i2c_adapter *control,
					 uपूर्णांक8_t address,
					 uपूर्णांक8_t *data,
					 uपूर्णांक32_t numbytes)
अणु
	uपूर्णांक32_t  ret;

	ret = smu_v11_0_i2c_transmit(control, address, data, numbytes, 0);

	अगर (ret != I2C_OK)
		DRM_ERROR("WriteI2CData() - I2C error occurred :%x", ret);
	अन्यथा
		/*
		 * According to EEPROM spec there is a MAX of 10 ms required क्रम
		 * EEPROM to flush पूर्णांकernal RX buffer after STOP was issued at the
		 * end of ग_लिखो transaction. During this समय the EEPROM will not be
		 * responsive to any more commands - so रुको a bit more.
		 *
		 * TODO Improve to रुको क्रम first ACK क्रम slave address after
		 * पूर्णांकernal ग_लिखो cycle करोne.
		 */
		msleep(10);

	वापस ret;

पूर्ण

अटल व्योम lock_bus(काष्ठा i2c_adapter *i2c, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(i2c);

	अगर (!smu_v11_0_i2c_bus_lock(i2c)) अणु
		DRM_ERROR("Failed to lock the bus from SMU");
		वापस;
	पूर्ण

	adev->pm.bus_locked = true;
पूर्ण

अटल पूर्णांक trylock_bus(काष्ठा i2c_adapter *i2c, अचिन्हित पूर्णांक flags)
अणु
	WARN_ONCE(1, "This operation not supposed to run in atomic context!");
	वापस false;
पूर्ण

अटल व्योम unlock_bus(काष्ठा i2c_adapter *i2c, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(i2c);

	अगर (!smu_v11_0_i2c_bus_unlock(i2c)) अणु
		DRM_ERROR("Failed to unlock the bus from SMU");
		वापस;
	पूर्ण

	adev->pm.bus_locked = false;
पूर्ण

अटल स्थिर काष्ठा i2c_lock_operations smu_v11_0_i2c_i2c_lock_ops = अणु
	.lock_bus = lock_bus,
	.trylock_bus = trylock_bus,
	.unlock_bus = unlock_bus,
पूर्ण;

अटल पूर्णांक smu_v11_0_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
			      काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	पूर्णांक i, ret;
	काष्ठा amdgpu_device *adev = to_amdgpu_device(i2c_adap);

	अगर (!adev->pm.bus_locked) अणु
		DRM_ERROR("I2C bus unlocked, stopping transaction!");
		वापस -EIO;
	पूर्ण

	smu_v11_0_i2c_init(i2c_adap);

	क्रम (i = 0; i < num; i++) अणु
		अगर (msgs[i].flags & I2C_M_RD)
			ret = smu_v11_0_i2c_पढ़ो_data(i2c_adap,
						      (uपूर्णांक8_t)msgs[i].addr,
						      msgs[i].buf, msgs[i].len);
		अन्यथा
			ret = smu_v11_0_i2c_ग_लिखो_data(i2c_adap,
						       (uपूर्णांक8_t)msgs[i].addr,
						       msgs[i].buf, msgs[i].len);

		अगर (ret != I2C_OK) अणु
			num = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण

	smu_v11_0_i2c_fini(i2c_adap);
	वापस num;
पूर्ण

अटल u32 smu_v11_0_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण


अटल स्थिर काष्ठा i2c_algorithm smu_v11_0_i2c_algo = अणु
	.master_xfer = smu_v11_0_i2c_xfer,
	.functionality = smu_v11_0_i2c_func,
पूर्ण;

पूर्णांक smu_v11_0_i2c_control_init(काष्ठा i2c_adapter *control)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);
	पूर्णांक res;

	control->owner = THIS_MODULE;
	control->class = I2C_CLASS_SPD;
	control->dev.parent = &adev->pdev->dev;
	control->algo = &smu_v11_0_i2c_algo;
	snम_लिखो(control->name, माप(control->name), "AMDGPU SMU");
	control->lock_ops = &smu_v11_0_i2c_i2c_lock_ops;

	res = i2c_add_adapter(control);
	अगर (res)
		DRM_ERROR("Failed to register hw i2c, err: %d\n", res);

	वापस res;
पूर्ण

व्योम smu_v11_0_i2c_control_fini(काष्ठा i2c_adapter *control)
अणु
	i2c_del_adapter(control);
पूर्ण

/*
 * Keep this क्रम future unit test अगर bugs arise
 */
#अगर 0
#घोषणा I2C_TARGET_ADDR 0xA0

bool smu_v11_0_i2c_test_bus(काष्ठा i2c_adapter *control)
अणु

	uपूर्णांक32_t ret = I2C_OK;
	uपूर्णांक8_t data[6] = अणु0xf, 0, 0xde, 0xad, 0xbe, 0xefपूर्ण;


	DRM_INFO("Begin");

	अगर (!smu_v11_0_i2c_bus_lock(control)) अणु
		DRM_ERROR("Failed to lock the bus!.");
		वापस false;
	पूर्ण

	smu_v11_0_i2c_init(control);

	/* Write 0xde to address 0x0000 on the EEPROM */
	ret = smu_v11_0_i2c_ग_लिखो_data(control, I2C_TARGET_ADDR, data, 6);

	ret = smu_v11_0_i2c_पढ़ो_data(control, I2C_TARGET_ADDR, data, 6);

	smu_v11_0_i2c_fini(control);

	smu_v11_0_i2c_bus_unlock(control);


	DRM_INFO("End");
	वापस true;
पूर्ण
#पूर्ण_अगर
