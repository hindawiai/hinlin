<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * Copyright 2013-2016 Freescale Semiconductor Inc.
 *
 * I/O services to send MC commands to the MC hardware
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/io-64-nonatomic-hi-lo.h>
#समावेश <linux/fsl/mc.h>

#समावेश "fsl-mc-private.h"

/**
 * Timeout in milliseconds to रुको क्रम the completion of an MC command
 */
#घोषणा MC_CMD_COMPLETION_TIMEOUT_MS	500

/*
 * usleep_range() min and max values used to throttle करोwn polling
 * iterations जबतक रुकोing क्रम MC command completion
 */
#घोषणा MC_CMD_COMPLETION_POLLING_MIN_SLEEP_USECS    10
#घोषणा MC_CMD_COMPLETION_POLLING_MAX_SLEEP_USECS    500

अटल क्रमागत mc_cmd_status mc_cmd_hdr_पढ़ो_status(काष्ठा fsl_mc_command *cmd)
अणु
	काष्ठा mc_cmd_header *hdr = (काष्ठा mc_cmd_header *)&cmd->header;

	वापस (क्रमागत mc_cmd_status)hdr->status;
पूर्ण

u16 mc_cmd_hdr_पढ़ो_cmdid(काष्ठा fsl_mc_command *cmd)
अणु
	काष्ठा mc_cmd_header *hdr = (काष्ठा mc_cmd_header *)&cmd->header;
	u16 cmd_id = le16_to_cpu(hdr->cmd_id);

	वापस cmd_id;
पूर्ण

अटल पूर्णांक mc_status_to_error(क्रमागत mc_cmd_status status)
अणु
	अटल स्थिर पूर्णांक mc_status_to_error_map[] = अणु
		[MC_CMD_STATUS_OK] = 0,
		[MC_CMD_STATUS_AUTH_ERR] = -EACCES,
		[MC_CMD_STATUS_NO_PRIVILEGE] = -EPERM,
		[MC_CMD_STATUS_DMA_ERR] = -EIO,
		[MC_CMD_STATUS_CONFIG_ERR] = -ENXIO,
		[MC_CMD_STATUS_TIMEOUT] = -ETIMEDOUT,
		[MC_CMD_STATUS_NO_RESOURCE] = -ENAVAIL,
		[MC_CMD_STATUS_NO_MEMORY] = -ENOMEM,
		[MC_CMD_STATUS_BUSY] = -EBUSY,
		[MC_CMD_STATUS_UNSUPPORTED_OP] = -ENOTSUPP,
		[MC_CMD_STATUS_INVALID_STATE] = -ENODEV,
	पूर्ण;

	अगर ((u32)status >= ARRAY_SIZE(mc_status_to_error_map))
		वापस -EINVAL;

	वापस mc_status_to_error_map[status];
पूर्ण

अटल स्थिर अक्षर *mc_status_to_string(क्रमागत mc_cmd_status status)
अणु
	अटल स्थिर अक्षर *स्थिर status_strings[] = अणु
		[MC_CMD_STATUS_OK] = "Command completed successfully",
		[MC_CMD_STATUS_READY] = "Command ready to be processed",
		[MC_CMD_STATUS_AUTH_ERR] = "Authentication error",
		[MC_CMD_STATUS_NO_PRIVILEGE] = "No privilege",
		[MC_CMD_STATUS_DMA_ERR] = "DMA or I/O error",
		[MC_CMD_STATUS_CONFIG_ERR] = "Configuration error",
		[MC_CMD_STATUS_TIMEOUT] = "Operation timed out",
		[MC_CMD_STATUS_NO_RESOURCE] = "No resources",
		[MC_CMD_STATUS_NO_MEMORY] = "No memory available",
		[MC_CMD_STATUS_BUSY] = "Device is busy",
		[MC_CMD_STATUS_UNSUPPORTED_OP] = "Unsupported operation",
		[MC_CMD_STATUS_INVALID_STATE] = "Invalid state"
	पूर्ण;

	अगर ((अचिन्हित पूर्णांक)status >= ARRAY_SIZE(status_strings))
		वापस "Unknown MC error";

	वापस status_strings[status];
पूर्ण

/**
 * mc_ग_लिखो_command - ग_लिखोs a command to a Management Complex (MC) portal
 *
 * @portal: poपूर्णांकer to an MC portal
 * @cmd: poपूर्णांकer to a filled command
 */
अटल अंतरभूत व्योम mc_ग_लिखो_command(काष्ठा fsl_mc_command __iomem *portal,
				    काष्ठा fsl_mc_command *cmd)
अणु
	पूर्णांक i;

	/* copy command parameters पूर्णांकo the portal */
	क्रम (i = 0; i < MC_CMD_NUM_OF_PARAMS; i++)
		/*
		 * Data is alपढ़ोy in the expected LE byte-order. Do an
		 * extra LE -> CPU conversion so that the CPU -> LE करोne in
		 * the device io ग_लिखो api माला_दो it back in the right order.
		 */
		ग_लिखोq_relaxed(le64_to_cpu(cmd->params[i]), &portal->params[i]);

	/* submit the command by writing the header */
	ग_लिखोq(le64_to_cpu(cmd->header), &portal->header);
पूर्ण

/**
 * mc_पढ़ो_response - पढ़ोs the response क्रम the last MC command from a
 * Management Complex (MC) portal
 *
 * @portal: poपूर्णांकer to an MC portal
 * @resp: poपूर्णांकer to command response buffer
 *
 * Returns MC_CMD_STATUS_OK on Success; Error code otherwise.
 */
अटल अंतरभूत क्रमागत mc_cmd_status mc_पढ़ो_response(काष्ठा fsl_mc_command __iomem
						  *portal,
						  काष्ठा fsl_mc_command *resp)
अणु
	पूर्णांक i;
	क्रमागत mc_cmd_status status;

	/* Copy command response header from MC portal: */
	resp->header = cpu_to_le64(पढ़ोq_relaxed(&portal->header));
	status = mc_cmd_hdr_पढ़ो_status(resp);
	अगर (status != MC_CMD_STATUS_OK)
		वापस status;

	/* Copy command response data from MC portal: */
	क्रम (i = 0; i < MC_CMD_NUM_OF_PARAMS; i++)
		/*
		 * Data is expected to be in LE byte-order. Do an
		 * extra CPU -> LE to revert the LE -> CPU करोne in
		 * the device io पढ़ो api.
		 */
		resp->params[i] =
			cpu_to_le64(पढ़ोq_relaxed(&portal->params[i]));

	वापस status;
पूर्ण

/**
 * Waits क्रम the completion of an MC command करोing preemptible polling.
 * uslepp_range() is called between polling iterations.
 *
 * @mc_io: MC I/O object to be used
 * @cmd: command buffer to receive MC response
 * @mc_status: MC command completion status
 */
अटल पूर्णांक mc_polling_रुको_preemptible(काष्ठा fsl_mc_io *mc_io,
				       काष्ठा fsl_mc_command *cmd,
				       क्रमागत mc_cmd_status *mc_status)
अणु
	क्रमागत mc_cmd_status status;
	अचिन्हित दीर्घ jअगरfies_until_समयout =
		jअगरfies + msecs_to_jअगरfies(MC_CMD_COMPLETION_TIMEOUT_MS);

	/*
	 * Wait क्रम response from the MC hardware:
	 */
	क्रम (;;) अणु
		status = mc_पढ़ो_response(mc_io->portal_virt_addr, cmd);
		अगर (status != MC_CMD_STATUS_READY)
			अवरोध;

		/*
		 * TODO: When MC command completion पूर्णांकerrupts are supported
		 * call रुको function here instead of usleep_range()
		 */
		usleep_range(MC_CMD_COMPLETION_POLLING_MIN_SLEEP_USECS,
			     MC_CMD_COMPLETION_POLLING_MAX_SLEEP_USECS);

		अगर (समय_after_eq(jअगरfies, jअगरfies_until_समयout)) अणु
			dev_dbg(mc_io->dev,
				"MC command timed out (portal: %pa, dprc handle: %#x, command: %#x)\n",
				 &mc_io->portal_phys_addr,
				 (अचिन्हित पूर्णांक)mc_cmd_hdr_पढ़ो_token(cmd),
				 (अचिन्हित पूर्णांक)mc_cmd_hdr_पढ़ो_cmdid(cmd));

			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	*mc_status = status;
	वापस 0;
पूर्ण

/**
 * Waits क्रम the completion of an MC command करोing atomic polling.
 * udelay() is called between polling iterations.
 *
 * @mc_io: MC I/O object to be used
 * @cmd: command buffer to receive MC response
 * @mc_status: MC command completion status
 */
अटल पूर्णांक mc_polling_रुको_atomic(काष्ठा fsl_mc_io *mc_io,
				  काष्ठा fsl_mc_command *cmd,
				  क्रमागत mc_cmd_status *mc_status)
अणु
	क्रमागत mc_cmd_status status;
	अचिन्हित दीर्घ समयout_usecs = MC_CMD_COMPLETION_TIMEOUT_MS * 1000;

	BUILD_BUG_ON((MC_CMD_COMPLETION_TIMEOUT_MS * 1000) %
		     MC_CMD_COMPLETION_POLLING_MAX_SLEEP_USECS != 0);

	क्रम (;;) अणु
		status = mc_पढ़ो_response(mc_io->portal_virt_addr, cmd);
		अगर (status != MC_CMD_STATUS_READY)
			अवरोध;

		udelay(MC_CMD_COMPLETION_POLLING_MAX_SLEEP_USECS);
		समयout_usecs -= MC_CMD_COMPLETION_POLLING_MAX_SLEEP_USECS;
		अगर (समयout_usecs == 0) अणु
			dev_dbg(mc_io->dev,
				"MC command timed out (portal: %pa, dprc handle: %#x, command: %#x)\n",
				 &mc_io->portal_phys_addr,
				 (अचिन्हित पूर्णांक)mc_cmd_hdr_पढ़ो_token(cmd),
				 (अचिन्हित पूर्णांक)mc_cmd_hdr_पढ़ो_cmdid(cmd));

			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	*mc_status = status;
	वापस 0;
पूर्ण

/**
 * Sends a command to the MC device using the given MC I/O object
 *
 * @mc_io: MC I/O object to be used
 * @cmd: command to be sent
 *
 * Returns '0' on Success; Error code otherwise.
 */
पूर्णांक mc_send_command(काष्ठा fsl_mc_io *mc_io, काष्ठा fsl_mc_command *cmd)
अणु
	पूर्णांक error;
	क्रमागत mc_cmd_status status;
	अचिन्हित दीर्घ irq_flags = 0;

	अगर (in_irq() && !(mc_io->flags & FSL_MC_IO_ATOMIC_CONTEXT_PORTAL))
		वापस -EINVAL;

	अगर (mc_io->flags & FSL_MC_IO_ATOMIC_CONTEXT_PORTAL)
		raw_spin_lock_irqsave(&mc_io->spinlock, irq_flags);
	अन्यथा
		mutex_lock(&mc_io->mutex);

	/*
	 * Send command to the MC hardware:
	 */
	mc_ग_लिखो_command(mc_io->portal_virt_addr, cmd);

	/*
	 * Wait क्रम response from the MC hardware:
	 */
	अगर (!(mc_io->flags & FSL_MC_IO_ATOMIC_CONTEXT_PORTAL))
		error = mc_polling_रुको_preemptible(mc_io, cmd, &status);
	अन्यथा
		error = mc_polling_रुको_atomic(mc_io, cmd, &status);

	अगर (error < 0)
		जाओ common_निकास;

	अगर (status != MC_CMD_STATUS_OK) अणु
		dev_dbg(mc_io->dev,
			"MC command failed: portal: %pa, dprc handle: %#x, command: %#x, status: %s (%#x)\n",
			 &mc_io->portal_phys_addr,
			 (अचिन्हित पूर्णांक)mc_cmd_hdr_पढ़ो_token(cmd),
			 (अचिन्हित पूर्णांक)mc_cmd_hdr_पढ़ो_cmdid(cmd),
			 mc_status_to_string(status),
			 (अचिन्हित पूर्णांक)status);

		error = mc_status_to_error(status);
		जाओ common_निकास;
	पूर्ण

	error = 0;
common_निकास:
	अगर (mc_io->flags & FSL_MC_IO_ATOMIC_CONTEXT_PORTAL)
		raw_spin_unlock_irqrestore(&mc_io->spinlock, irq_flags);
	अन्यथा
		mutex_unlock(&mc_io->mutex);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(mc_send_command);
