<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

/*
 * nfp_nsp.c
 * Author: Jakub Kicinski <jakub.kicinski@netronome.com>
 *         Jason McMullan <jason.mcmullan@netronome.com>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/overflow.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>

#घोषणा NFP_SUBSYS "nfp_nsp"

#समावेश "nfp.h"
#समावेश "nfp_cpp.h"
#समावेश "nfp_nsp.h"

#घोषणा NFP_NSP_TIMEOUT_DEFAULT	30
#घोषणा NFP_NSP_TIMEOUT_BOOT	30

/* Offsets relative to the CSR base */
#घोषणा NSP_STATUS		0x00
#घोषणा   NSP_STATUS_MAGIC	GENMASK_ULL(63, 48)
#घोषणा   NSP_STATUS_MAJOR	GENMASK_ULL(47, 44)
#घोषणा   NSP_STATUS_MINOR	GENMASK_ULL(43, 32)
#घोषणा   NSP_STATUS_CODE	GENMASK_ULL(31, 16)
#घोषणा   NSP_STATUS_RESULT	GENMASK_ULL(15, 8)
#घोषणा   NSP_STATUS_BUSY	BIT_ULL(0)

#घोषणा NSP_COMMAND		0x08
#घोषणा   NSP_COMMAND_OPTION	GENMASK_ULL(63, 32)
#घोषणा   NSP_COMMAND_CODE	GENMASK_ULL(31, 16)
#घोषणा   NSP_COMMAND_DMA_BUF	BIT_ULL(1)
#घोषणा   NSP_COMMAND_START	BIT_ULL(0)

/* CPP address to retrieve the data from */
#घोषणा NSP_BUFFER		0x10
#घोषणा   NSP_BUFFER_CPP	GENMASK_ULL(63, 40)
#घोषणा   NSP_BUFFER_ADDRESS	GENMASK_ULL(39, 0)

#घोषणा NSP_DFLT_BUFFER		0x18
#घोषणा   NSP_DFLT_BUFFER_CPP	GENMASK_ULL(63, 40)
#घोषणा   NSP_DFLT_BUFFER_ADDRESS	GENMASK_ULL(39, 0)

#घोषणा NSP_DFLT_BUFFER_CONFIG	0x20
#घोषणा   NSP_DFLT_BUFFER_DMA_CHUNK_ORDER	GENMASK_ULL(63, 58)
#घोषणा   NSP_DFLT_BUFFER_SIZE_4KB	GENMASK_ULL(15, 8)
#घोषणा   NSP_DFLT_BUFFER_SIZE_MB	GENMASK_ULL(7, 0)

#घोषणा NFP_CAP_CMD_DMA_SG	0x28

#घोषणा NSP_MAGIC		0xab10
#घोषणा NSP_MAJOR		0
#घोषणा NSP_MINOR		8

#घोषणा NSP_CODE_MAJOR		GENMASK(15, 12)
#घोषणा NSP_CODE_MINOR		GENMASK(11, 0)

#घोषणा NFP_FW_LOAD_RET_MAJOR	GENMASK(15, 8)
#घोषणा NFP_FW_LOAD_RET_MINOR	GENMASK(23, 16)

#घोषणा NFP_HWINFO_LOOKUP_SIZE	GENMASK(11, 0)

#घोषणा NFP_VERSIONS_SIZE	GENMASK(11, 0)
#घोषणा NFP_VERSIONS_CNT_OFF	0
#घोषणा NFP_VERSIONS_BSP_OFF	2
#घोषणा NFP_VERSIONS_CPLD_OFF	6
#घोषणा NFP_VERSIONS_APP_OFF	10
#घोषणा NFP_VERSIONS_BUNDLE_OFF	14
#घोषणा NFP_VERSIONS_UNDI_OFF	18
#घोषणा NFP_VERSIONS_NCSI_OFF	22
#घोषणा NFP_VERSIONS_CFGR_OFF	26

#घोषणा NSP_SFF_EEPROM_BLOCK_LEN	8

क्रमागत nfp_nsp_cmd अणु
	SPCODE_NOOP		= 0, /* No operation */
	SPCODE_SOFT_RESET	= 1, /* Soft reset the NFP */
	SPCODE_FW_DEFAULT	= 2, /* Load शेष (UNDI) FW */
	SPCODE_PHY_INIT		= 3, /* Initialize the PHY */
	SPCODE_MAC_INIT		= 4, /* Initialize the MAC */
	SPCODE_PHY_RXADAPT	= 5, /* Re-run PHY RX Adaptation */
	SPCODE_FW_LOAD		= 6, /* Load fw from buffer, len in option */
	SPCODE_ETH_RESCAN	= 7, /* Rescan ETHs, ग_लिखो ETH_TABLE to buf */
	SPCODE_ETH_CONTROL	= 8, /* Update media config from buffer */
	SPCODE_NSP_WRITE_FLASH	= 11, /* Load and flash image from buffer */
	SPCODE_NSP_SENSORS	= 12, /* Read NSP sensor(s) */
	SPCODE_NSP_IDENTIFY	= 13, /* Read NSP version */
	SPCODE_FW_STORED	= 16, /* If no FW loaded, load flash app FW */
	SPCODE_HWINFO_LOOKUP	= 17, /* Lookup HWinfo with overग_लिखोs etc. */
	SPCODE_HWINFO_SET	= 18, /* Set HWinfo entry */
	SPCODE_FW_LOADED	= 19, /* Is application firmware loaded */
	SPCODE_VERSIONS		= 21, /* Report FW versions */
	SPCODE_READ_SFF_EEPROM	= 22, /* Read module EEPROM */
पूर्ण;

काष्ठा nfp_nsp_dma_buf अणु
	__le32 chunk_cnt;
	__le32 reserved[3];
	काष्ठा अणु
		__le32 size;
		__le32 reserved;
		__le64 addr;
	पूर्ण descs[];
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक code;
	स्थिर अक्षर *msg;
पूर्ण nsp_errors[] = अणु
	अणु 6010, "could not map to phy for port" पूर्ण,
	अणु 6011, "not an allowed rate/lanes for port" पूर्ण,
	अणु 6012, "not an allowed rate/lanes for port" पूर्ण,
	अणु 6013, "high/low error, change other port first" पूर्ण,
	अणु 6014, "config not found in flash" पूर्ण,
पूर्ण;

काष्ठा nfp_nsp अणु
	काष्ठा nfp_cpp *cpp;
	काष्ठा nfp_resource *res;
	काष्ठा अणु
		u16 major;
		u16 minor;
	पूर्ण ver;

	/* Eth table config state */
	bool modअगरied;
	अचिन्हित पूर्णांक idx;
	व्योम *entries;
पूर्ण;

/**
 * काष्ठा nfp_nsp_command_arg - NFP command argument काष्ठाure
 * @code:	NFP SP Command Code
 * @dma:	@buf poपूर्णांकs to a host buffer, not NSP buffer
 * @समयout_sec:Timeout value to रुको क्रम completion in seconds
 * @option:	NFP SP Command Argument
 * @buf:	NFP SP Buffer Address
 * @error_cb:	Callback क्रम पूर्णांकerpreting option अगर error occurred
 * @error_quiet:Don't prपूर्णांक command error/warning. Protocol errors are still
 *		    logged.
 */
काष्ठा nfp_nsp_command_arg अणु
	u16 code;
	bool dma;
	अचिन्हित पूर्णांक समयout_sec;
	u32 option;
	u64 buf;
	व्योम (*error_cb)(काष्ठा nfp_nsp *state, u32 ret_val);
	bool error_quiet;
पूर्ण;

/**
 * काष्ठा nfp_nsp_command_buf_arg - NFP command with buffer argument काष्ठाure
 * @arg:	NFP command argument काष्ठाure
 * @in_buf:	Buffer with data क्रम input
 * @in_size:	Size of @in_buf
 * @out_buf:	Buffer क्रम output data
 * @out_size:	Size of @out_buf
 */
काष्ठा nfp_nsp_command_buf_arg अणु
	काष्ठा nfp_nsp_command_arg arg;
	स्थिर व्योम *in_buf;
	अचिन्हित पूर्णांक in_size;
	व्योम *out_buf;
	अचिन्हित पूर्णांक out_size;
पूर्ण;

काष्ठा nfp_cpp *nfp_nsp_cpp(काष्ठा nfp_nsp *state)
अणु
	वापस state->cpp;
पूर्ण

bool nfp_nsp_config_modअगरied(काष्ठा nfp_nsp *state)
अणु
	वापस state->modअगरied;
पूर्ण

व्योम nfp_nsp_config_set_modअगरied(काष्ठा nfp_nsp *state, bool modअगरied)
अणु
	state->modअगरied = modअगरied;
पूर्ण

व्योम *nfp_nsp_config_entries(काष्ठा nfp_nsp *state)
अणु
	वापस state->entries;
पूर्ण

अचिन्हित पूर्णांक nfp_nsp_config_idx(काष्ठा nfp_nsp *state)
अणु
	वापस state->idx;
पूर्ण

व्योम
nfp_nsp_config_set_state(काष्ठा nfp_nsp *state, व्योम *entries, अचिन्हित पूर्णांक idx)
अणु
	state->entries = entries;
	state->idx = idx;
पूर्ण

व्योम nfp_nsp_config_clear_state(काष्ठा nfp_nsp *state)
अणु
	state->entries = शून्य;
	state->idx = 0;
पूर्ण

अटल व्योम nfp_nsp_prपूर्णांक_extended_error(काष्ठा nfp_nsp *state, u32 ret_val)
अणु
	पूर्णांक i;

	अगर (!ret_val)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(nsp_errors); i++)
		अगर (ret_val == nsp_errors[i].code)
			nfp_err(state->cpp, "err msg: %s\n", nsp_errors[i].msg);
पूर्ण

अटल पूर्णांक nfp_nsp_check(काष्ठा nfp_nsp *state)
अणु
	काष्ठा nfp_cpp *cpp = state->cpp;
	u64 nsp_status, reg;
	u32 nsp_cpp;
	पूर्णांक err;

	nsp_cpp = nfp_resource_cpp_id(state->res);
	nsp_status = nfp_resource_address(state->res) + NSP_STATUS;

	err = nfp_cpp_पढ़ोq(cpp, nsp_cpp, nsp_status, &reg);
	अगर (err < 0)
		वापस err;

	अगर (FIELD_GET(NSP_STATUS_MAGIC, reg) != NSP_MAGIC) अणु
		nfp_err(cpp, "Cannot detect NFP Service Processor\n");
		वापस -ENODEV;
	पूर्ण

	state->ver.major = FIELD_GET(NSP_STATUS_MAJOR, reg);
	state->ver.minor = FIELD_GET(NSP_STATUS_MINOR, reg);

	अगर (state->ver.major != NSP_MAJOR) अणु
		nfp_err(cpp, "Unsupported ABI %hu.%hu\n",
			state->ver.major, state->ver.minor);
		वापस -EINVAL;
	पूर्ण
	अगर (state->ver.minor < NSP_MINOR) अणु
		nfp_err(cpp, "ABI too old to support NIC operation (%u.%hu < %u.%u), please update the management FW on the flash\n",
			NSP_MAJOR, state->ver.minor, NSP_MAJOR, NSP_MINOR);
		वापस -EINVAL;
	पूर्ण

	अगर (reg & NSP_STATUS_BUSY) अणु
		nfp_err(cpp, "Service processor busy!\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * nfp_nsp_खोलो() - Prepare क्रम communication and lock the NSP resource.
 * @cpp:	NFP CPP Handle
 */
काष्ठा nfp_nsp *nfp_nsp_खोलो(काष्ठा nfp_cpp *cpp)
अणु
	काष्ठा nfp_resource *res;
	काष्ठा nfp_nsp *state;
	पूर्णांक err;

	res = nfp_resource_acquire(cpp, NFP_RESOURCE_NSP);
	अगर (IS_ERR(res))
		वापस (व्योम *)res;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state) अणु
		nfp_resource_release(res);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	state->cpp = cpp;
	state->res = res;

	err = nfp_nsp_check(state);
	अगर (err) अणु
		nfp_nsp_बंद(state);
		वापस ERR_PTR(err);
	पूर्ण

	वापस state;
पूर्ण

/**
 * nfp_nsp_बंद() - Clean up and unlock the NSP resource.
 * @state:	NFP SP state
 */
व्योम nfp_nsp_बंद(काष्ठा nfp_nsp *state)
अणु
	nfp_resource_release(state->res);
	kमुक्त(state);
पूर्ण

u16 nfp_nsp_get_abi_ver_major(काष्ठा nfp_nsp *state)
अणु
	वापस state->ver.major;
पूर्ण

u16 nfp_nsp_get_abi_ver_minor(काष्ठा nfp_nsp *state)
अणु
	वापस state->ver.minor;
पूर्ण

अटल पूर्णांक
nfp_nsp_रुको_reg(काष्ठा nfp_cpp *cpp, u64 *reg, u32 nsp_cpp, u64 addr,
		 u64 mask, u64 val, u32 समयout_sec)
अणु
	स्थिर अचिन्हित दीर्घ रुको_until = jअगरfies + समयout_sec * HZ;
	पूर्णांक err;

	क्रम (;;) अणु
		स्थिर अचिन्हित दीर्घ start_समय = jअगरfies;

		err = nfp_cpp_पढ़ोq(cpp, nsp_cpp, addr, reg);
		अगर (err < 0)
			वापस err;

		अगर ((*reg & mask) == val)
			वापस 0;

		msleep(25);

		अगर (समय_after(start_समय, रुको_until))
			वापस -ETIMEDOUT;
	पूर्ण
पूर्ण

/**
 * __nfp_nsp_command() - Execute a command on the NFP Service Processor
 * @state:	NFP SP state
 * @arg:	NFP command argument काष्ठाure
 *
 * Return: 0 क्रम success with no result
 *
 *	 positive value क्रम NSP completion with a result code
 *
 *	-EAGAIN अगर the NSP is not yet present
 *	-ENODEV अगर the NSP is not a supported model
 *	-EBUSY अगर the NSP is stuck
 *	-EINTR अगर पूर्णांकerrupted जबतक रुकोing क्रम completion
 *	-ETIMEDOUT अगर the NSP took दीर्घer than @समयout_sec seconds to complete
 */
अटल पूर्णांक
__nfp_nsp_command(काष्ठा nfp_nsp *state, स्थिर काष्ठा nfp_nsp_command_arg *arg)
अणु
	u64 reg, ret_val, nsp_base, nsp_buffer, nsp_status, nsp_command;
	काष्ठा nfp_cpp *cpp = state->cpp;
	u32 nsp_cpp;
	पूर्णांक err;

	nsp_cpp = nfp_resource_cpp_id(state->res);
	nsp_base = nfp_resource_address(state->res);
	nsp_status = nsp_base + NSP_STATUS;
	nsp_command = nsp_base + NSP_COMMAND;
	nsp_buffer = nsp_base + NSP_BUFFER;

	err = nfp_nsp_check(state);
	अगर (err)
		वापस err;

	err = nfp_cpp_ग_लिखोq(cpp, nsp_cpp, nsp_buffer, arg->buf);
	अगर (err < 0)
		वापस err;

	err = nfp_cpp_ग_लिखोq(cpp, nsp_cpp, nsp_command,
			     FIELD_PREP(NSP_COMMAND_OPTION, arg->option) |
			     FIELD_PREP(NSP_COMMAND_CODE, arg->code) |
			     FIELD_PREP(NSP_COMMAND_DMA_BUF, arg->dma) |
			     FIELD_PREP(NSP_COMMAND_START, 1));
	अगर (err < 0)
		वापस err;

	/* Wait क्रम NSP_COMMAND_START to go to 0 */
	err = nfp_nsp_रुको_reg(cpp, &reg, nsp_cpp, nsp_command,
			       NSP_COMMAND_START, 0, NFP_NSP_TIMEOUT_DEFAULT);
	अगर (err) अणु
		nfp_err(cpp, "Error %d waiting for code 0x%04x to start\n",
			err, arg->code);
		वापस err;
	पूर्ण

	/* Wait क्रम NSP_STATUS_BUSY to go to 0 */
	err = nfp_nsp_रुको_reg(cpp, &reg, nsp_cpp, nsp_status, NSP_STATUS_BUSY,
			       0, arg->समयout_sec ?: NFP_NSP_TIMEOUT_DEFAULT);
	अगर (err) अणु
		nfp_err(cpp, "Error %d waiting for code 0x%04x to complete\n",
			err, arg->code);
		वापस err;
	पूर्ण

	err = nfp_cpp_पढ़ोq(cpp, nsp_cpp, nsp_command, &ret_val);
	अगर (err < 0)
		वापस err;
	ret_val = FIELD_GET(NSP_COMMAND_OPTION, ret_val);

	err = FIELD_GET(NSP_STATUS_RESULT, reg);
	अगर (err) अणु
		अगर (!arg->error_quiet)
			nfp_warn(cpp, "Result (error) code set: %d (%d) command: %d\n",
				 -err, (पूर्णांक)ret_val, arg->code);

		अगर (arg->error_cb)
			arg->error_cb(state, ret_val);
		अन्यथा
			nfp_nsp_prपूर्णांक_extended_error(state, ret_val);
		वापस -err;
	पूर्ण

	वापस ret_val;
पूर्ण

अटल पूर्णांक nfp_nsp_command(काष्ठा nfp_nsp *state, u16 code)
अणु
	स्थिर काष्ठा nfp_nsp_command_arg arg = अणु
		.code		= code,
	पूर्ण;

	वापस __nfp_nsp_command(state, &arg);
पूर्ण

अटल पूर्णांक
nfp_nsp_command_buf_def(काष्ठा nfp_nsp *nsp,
			काष्ठा nfp_nsp_command_buf_arg *arg)
अणु
	काष्ठा nfp_cpp *cpp = nsp->cpp;
	u64 reg, cpp_buf;
	पूर्णांक err, ret;
	u32 cpp_id;

	err = nfp_cpp_पढ़ोq(cpp, nfp_resource_cpp_id(nsp->res),
			    nfp_resource_address(nsp->res) +
			    NSP_DFLT_BUFFER,
			    &reg);
	अगर (err < 0)
		वापस err;

	cpp_id = FIELD_GET(NSP_DFLT_BUFFER_CPP, reg) << 8;
	cpp_buf = FIELD_GET(NSP_DFLT_BUFFER_ADDRESS, reg);

	अगर (arg->in_buf && arg->in_size) अणु
		err = nfp_cpp_ग_लिखो(cpp, cpp_id, cpp_buf,
				    arg->in_buf, arg->in_size);
		अगर (err < 0)
			वापस err;
	पूर्ण
	/* Zero out reमुख्यing part of the buffer */
	अगर (arg->out_buf && arg->out_size && arg->out_size > arg->in_size) अणु
		err = nfp_cpp_ग_लिखो(cpp, cpp_id, cpp_buf + arg->in_size,
				    arg->out_buf, arg->out_size - arg->in_size);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (!FIELD_FIT(NSP_BUFFER_CPP, cpp_id >> 8) ||
	    !FIELD_FIT(NSP_BUFFER_ADDRESS, cpp_buf)) अणु
		nfp_err(cpp, "Buffer out of reach %08x %016llx\n",
			cpp_id, cpp_buf);
		वापस -EINVAL;
	पूर्ण

	arg->arg.buf = FIELD_PREP(NSP_BUFFER_CPP, cpp_id >> 8) |
		       FIELD_PREP(NSP_BUFFER_ADDRESS, cpp_buf);
	ret = __nfp_nsp_command(nsp, &arg->arg);
	अगर (ret < 0)
		वापस ret;

	अगर (arg->out_buf && arg->out_size) अणु
		err = nfp_cpp_पढ़ो(cpp, cpp_id, cpp_buf,
				   arg->out_buf, arg->out_size);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
nfp_nsp_command_buf_dma_sg(काष्ठा nfp_nsp *nsp,
			   काष्ठा nfp_nsp_command_buf_arg *arg,
			   अचिन्हित पूर्णांक max_size, अचिन्हित पूर्णांक chunk_order,
			   अचिन्हित पूर्णांक dma_order)
अणु
	काष्ठा nfp_cpp *cpp = nsp->cpp;
	काष्ठा nfp_nsp_dma_buf *desc;
	काष्ठा अणु
		dma_addr_t dma_addr;
		अचिन्हित दीर्घ len;
		व्योम *chunk;
	पूर्ण *chunks;
	माप_प्रकार chunk_size, dma_size;
	dma_addr_t dma_desc;
	काष्ठा device *dev;
	अचिन्हित दीर्घ off;
	पूर्णांक i, ret, nseg;
	माप_प्रकार desc_sz;

	chunk_size = BIT_ULL(chunk_order);
	dma_size = BIT_ULL(dma_order);
	nseg = DIV_ROUND_UP(max_size, chunk_size);

	chunks = kzalloc(array_size(माप(*chunks), nseg), GFP_KERNEL);
	अगर (!chunks)
		वापस -ENOMEM;

	off = 0;
	ret = -ENOMEM;
	क्रम (i = 0; i < nseg; i++) अणु
		अचिन्हित दीर्घ coff;

		chunks[i].chunk = kदो_स्मृति(chunk_size,
					  GFP_KERNEL | __GFP_NOWARN);
		अगर (!chunks[i].chunk)
			जाओ निकास_मुक्त_prev;

		chunks[i].len = min_t(u64, chunk_size, max_size - off);

		coff = 0;
		अगर (arg->in_size > off) अणु
			coff = min_t(u64, arg->in_size - off, chunk_size);
			स_नकल(chunks[i].chunk, arg->in_buf + off, coff);
		पूर्ण
		स_रखो(chunks[i].chunk + coff, 0, chunk_size - coff);

		off += chunks[i].len;
	पूर्ण

	dev = nfp_cpp_device(cpp)->parent;

	क्रम (i = 0; i < nseg; i++) अणु
		dma_addr_t addr;

		addr = dma_map_single(dev, chunks[i].chunk, chunks[i].len,
				      DMA_BIसूचीECTIONAL);
		chunks[i].dma_addr = addr;

		ret = dma_mapping_error(dev, addr);
		अगर (ret)
			जाओ निकास_unmap_prev;

		अगर (WARN_ONCE(round_करोwn(addr, dma_size) !=
			      round_करोwn(addr + chunks[i].len - 1, dma_size),
			      "unaligned DMA address: %pad %lu %zd\n",
			      &addr, chunks[i].len, dma_size)) अणु
			ret = -EFAULT;
			i++;
			जाओ निकास_unmap_prev;
		पूर्ण
	पूर्ण

	desc_sz = काष्ठा_size(desc, descs, nseg);
	desc = kदो_स्मृति(desc_sz, GFP_KERNEL);
	अगर (!desc) अणु
		ret = -ENOMEM;
		जाओ निकास_unmap_all;
	पूर्ण

	desc->chunk_cnt = cpu_to_le32(nseg);
	क्रम (i = 0; i < nseg; i++) अणु
		desc->descs[i].size = cpu_to_le32(chunks[i].len);
		desc->descs[i].addr = cpu_to_le64(chunks[i].dma_addr);
	पूर्ण

	dma_desc = dma_map_single(dev, desc, desc_sz, DMA_TO_DEVICE);
	ret = dma_mapping_error(dev, dma_desc);
	अगर (ret)
		जाओ निकास_मुक्त_desc;

	arg->arg.dma = true;
	arg->arg.buf = dma_desc;
	ret = __nfp_nsp_command(nsp, &arg->arg);
	अगर (ret < 0)
		जाओ निकास_unmap_desc;

	i = 0;
	off = 0;
	जबतक (off < arg->out_size) अणु
		अचिन्हित पूर्णांक len;

		len = min_t(u64, chunks[i].len, arg->out_size - off);
		स_नकल(arg->out_buf + off, chunks[i].chunk, len);
		off += len;
		i++;
	पूर्ण

निकास_unmap_desc:
	dma_unmap_single(dev, dma_desc, desc_sz, DMA_TO_DEVICE);
निकास_मुक्त_desc:
	kमुक्त(desc);
निकास_unmap_all:
	i = nseg;
निकास_unmap_prev:
	जबतक (--i >= 0)
		dma_unmap_single(dev, chunks[i].dma_addr, chunks[i].len,
				 DMA_BIसूचीECTIONAL);
	i = nseg;
निकास_मुक्त_prev:
	जबतक (--i >= 0)
		kमुक्त(chunks[i].chunk);
	kमुक्त(chunks);
	अगर (ret < 0)
		nfp_err(cpp, "NSP: SG DMA failed for command 0x%04x: %d (sz:%d cord:%d)\n",
			arg->arg.code, ret, max_size, chunk_order);
	वापस ret;
पूर्ण

अटल पूर्णांक
nfp_nsp_command_buf_dma(काष्ठा nfp_nsp *nsp,
			काष्ठा nfp_nsp_command_buf_arg *arg,
			अचिन्हित पूर्णांक max_size, अचिन्हित पूर्णांक dma_order)
अणु
	अचिन्हित पूर्णांक chunk_order, buf_order;
	काष्ठा nfp_cpp *cpp = nsp->cpp;
	bool sg_ok;
	u64 reg;
	पूर्णांक err;

	buf_order = order_base_2(roundup_घात_of_two(max_size));

	err = nfp_cpp_पढ़ोq(cpp, nfp_resource_cpp_id(nsp->res),
			    nfp_resource_address(nsp->res) + NFP_CAP_CMD_DMA_SG,
			    &reg);
	अगर (err < 0)
		वापस err;
	sg_ok = reg & BIT_ULL(arg->arg.code - 1);

	अगर (!sg_ok) अणु
		अगर (buf_order > dma_order) अणु
			nfp_err(cpp, "NSP: can't service non-SG DMA for command 0x%04x\n",
				arg->arg.code);
			वापस -ENOMEM;
		पूर्ण
		chunk_order = buf_order;
	पूर्ण अन्यथा अणु
		chunk_order = min_t(अचिन्हित पूर्णांक, dma_order, PAGE_SHIFT);
	पूर्ण

	वापस nfp_nsp_command_buf_dma_sg(nsp, arg, max_size, chunk_order,
					  dma_order);
पूर्ण

अटल पूर्णांक
nfp_nsp_command_buf(काष्ठा nfp_nsp *nsp, काष्ठा nfp_nsp_command_buf_arg *arg)
अणु
	अचिन्हित पूर्णांक dma_order, def_size, max_size;
	काष्ठा nfp_cpp *cpp = nsp->cpp;
	u64 reg;
	पूर्णांक err;

	अगर (nsp->ver.minor < 13) अणु
		nfp_err(cpp, "NSP: Code 0x%04x with buffer not supported (ABI %hu.%hu)\n",
			arg->arg.code, nsp->ver.major, nsp->ver.minor);
		वापस -EOPNOTSUPP;
	पूर्ण

	err = nfp_cpp_पढ़ोq(cpp, nfp_resource_cpp_id(nsp->res),
			    nfp_resource_address(nsp->res) +
			    NSP_DFLT_BUFFER_CONFIG,
			    &reg);
	अगर (err < 0)
		वापस err;

	/* Zero out undefined part of the out buffer */
	अगर (arg->out_buf && arg->out_size && arg->out_size > arg->in_size)
		स_रखो(arg->out_buf, 0, arg->out_size - arg->in_size);

	max_size = max(arg->in_size, arg->out_size);
	def_size = FIELD_GET(NSP_DFLT_BUFFER_SIZE_MB, reg) * SZ_1M +
		   FIELD_GET(NSP_DFLT_BUFFER_SIZE_4KB, reg) * SZ_4K;
	dma_order = FIELD_GET(NSP_DFLT_BUFFER_DMA_CHUNK_ORDER, reg);
	अगर (def_size >= max_size) अणु
		वापस nfp_nsp_command_buf_def(nsp, arg);
	पूर्ण अन्यथा अगर (!dma_order) अणु
		nfp_err(cpp, "NSP: default buffer too small for command 0x%04x (%u < %u)\n",
			arg->arg.code, def_size, max_size);
		वापस -EINVAL;
	पूर्ण

	वापस nfp_nsp_command_buf_dma(nsp, arg, max_size, dma_order);
पूर्ण

पूर्णांक nfp_nsp_रुको(काष्ठा nfp_nsp *state)
अणु
	स्थिर अचिन्हित दीर्घ रुको_until = jअगरfies + NFP_NSP_TIMEOUT_BOOT * HZ;
	पूर्णांक err;

	nfp_dbg(state->cpp, "Waiting for NSP to respond (%u sec max).\n",
		NFP_NSP_TIMEOUT_BOOT);

	क्रम (;;) अणु
		स्थिर अचिन्हित दीर्घ start_समय = jअगरfies;

		err = nfp_nsp_command(state, SPCODE_NOOP);
		अगर (err != -EAGAIN)
			अवरोध;

		अगर (msleep_पूर्णांकerruptible(25)) अणु
			err = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		अगर (समय_after(start_समय, रुको_until)) अणु
			err = -ETIMEDOUT;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (err)
		nfp_err(state->cpp, "NSP failed to respond %d\n", err);

	वापस err;
पूर्ण

पूर्णांक nfp_nsp_device_soft_reset(काष्ठा nfp_nsp *state)
अणु
	वापस nfp_nsp_command(state, SPCODE_SOFT_RESET);
पूर्ण

पूर्णांक nfp_nsp_mac_reinit(काष्ठा nfp_nsp *state)
अणु
	वापस nfp_nsp_command(state, SPCODE_MAC_INIT);
पूर्ण

अटल व्योम nfp_nsp_load_fw_extended_msg(काष्ठा nfp_nsp *state, u32 ret_val)
अणु
	अटल स्थिर अक्षर * स्थिर major_msg[] = अणु
		/* 0 */ "Firmware from driver loaded",
		/* 1 */ "Firmware from flash loaded",
		/* 2 */ "Firmware loading failure",
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर minor_msg[] = अणु
		/*  0 */ "",
		/*  1 */ "no named partition on flash",
		/*  2 */ "error reading from flash",
		/*  3 */ "can not deflate",
		/*  4 */ "not a trusted file",
		/*  5 */ "can not parse FW file",
		/*  6 */ "MIP not found in FW file",
		/*  7 */ "null firmware name in MIP",
		/*  8 */ "FW version none",
		/*  9 */ "FW build number none",
		/* 10 */ "no FW selection policy HWInfo key found",
		/* 11 */ "static FW selection policy",
		/* 12 */ "FW version has precedence",
		/* 13 */ "different FW application load requested",
		/* 14 */ "development build",
	पूर्ण;
	अचिन्हित पूर्णांक major, minor;
	स्थिर अक्षर *level;

	major = FIELD_GET(NFP_FW_LOAD_RET_MAJOR, ret_val);
	minor = FIELD_GET(NFP_FW_LOAD_RET_MINOR, ret_val);

	अगर (!nfp_nsp_has_stored_fw_load(state))
		वापस;

	/* Lower the message level in legacy हाल */
	अगर (major == 0 && (minor == 0 || minor == 10))
		level = KERN_DEBUG;
	अन्यथा अगर (major == 2)
		level = KERN_ERR;
	अन्यथा
		level = KERN_INFO;

	अगर (major >= ARRAY_SIZE(major_msg))
		nfp_prपूर्णांकk(level, state->cpp, "FW loading status: %x\n",
			   ret_val);
	अन्यथा अगर (minor >= ARRAY_SIZE(minor_msg))
		nfp_prपूर्णांकk(level, state->cpp, "%s, reason code: %d\n",
			   major_msg[major], minor);
	अन्यथा
		nfp_prपूर्णांकk(level, state->cpp, "%s%c %s\n",
			   major_msg[major], minor ? ',' : '.',
			   minor_msg[minor]);
पूर्ण

पूर्णांक nfp_nsp_load_fw(काष्ठा nfp_nsp *state, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा nfp_nsp_command_buf_arg load_fw = अणु
		अणु
			.code		= SPCODE_FW_LOAD,
			.option		= fw->size,
			.error_cb	= nfp_nsp_load_fw_extended_msg,
		पूर्ण,
		.in_buf		= fw->data,
		.in_size	= fw->size,
	पूर्ण;
	पूर्णांक ret;

	ret = nfp_nsp_command_buf(state, &load_fw);
	अगर (ret < 0)
		वापस ret;

	nfp_nsp_load_fw_extended_msg(state, ret);
	वापस 0;
पूर्ण

पूर्णांक nfp_nsp_ग_लिखो_flash(काष्ठा nfp_nsp *state, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा nfp_nsp_command_buf_arg ग_लिखो_flash = अणु
		अणु
			.code		= SPCODE_NSP_WRITE_FLASH,
			.option		= fw->size,
			.समयout_sec	= 900,
		पूर्ण,
		.in_buf		= fw->data,
		.in_size	= fw->size,
	पूर्ण;

	वापस nfp_nsp_command_buf(state, &ग_लिखो_flash);
पूर्ण

पूर्णांक nfp_nsp_पढ़ो_eth_table(काष्ठा nfp_nsp *state, व्योम *buf, अचिन्हित पूर्णांक size)
अणु
	काष्ठा nfp_nsp_command_buf_arg eth_rescan = अणु
		अणु
			.code		= SPCODE_ETH_RESCAN,
			.option		= size,
		पूर्ण,
		.out_buf	= buf,
		.out_size	= size,
	पूर्ण;

	वापस nfp_nsp_command_buf(state, &eth_rescan);
पूर्ण

पूर्णांक nfp_nsp_ग_लिखो_eth_table(काष्ठा nfp_nsp *state,
			    स्थिर व्योम *buf, अचिन्हित पूर्णांक size)
अणु
	काष्ठा nfp_nsp_command_buf_arg eth_ctrl = अणु
		अणु
			.code		= SPCODE_ETH_CONTROL,
			.option		= size,
		पूर्ण,
		.in_buf		= buf,
		.in_size	= size,
	पूर्ण;

	वापस nfp_nsp_command_buf(state, &eth_ctrl);
पूर्ण

पूर्णांक nfp_nsp_पढ़ो_identअगरy(काष्ठा nfp_nsp *state, व्योम *buf, अचिन्हित पूर्णांक size)
अणु
	काष्ठा nfp_nsp_command_buf_arg identअगरy = अणु
		अणु
			.code		= SPCODE_NSP_IDENTIFY,
			.option		= size,
		पूर्ण,
		.out_buf	= buf,
		.out_size	= size,
	पूर्ण;

	वापस nfp_nsp_command_buf(state, &identअगरy);
पूर्ण

पूर्णांक nfp_nsp_पढ़ो_sensors(काष्ठा nfp_nsp *state, अचिन्हित पूर्णांक sensor_mask,
			 व्योम *buf, अचिन्हित पूर्णांक size)
अणु
	काष्ठा nfp_nsp_command_buf_arg sensors = अणु
		अणु
			.code		= SPCODE_NSP_SENSORS,
			.option		= sensor_mask,
		पूर्ण,
		.out_buf	= buf,
		.out_size	= size,
	पूर्ण;

	वापस nfp_nsp_command_buf(state, &sensors);
पूर्ण

पूर्णांक nfp_nsp_load_stored_fw(काष्ठा nfp_nsp *state)
अणु
	स्थिर काष्ठा nfp_nsp_command_arg arg = अणु
		.code		= SPCODE_FW_STORED,
		.error_cb	= nfp_nsp_load_fw_extended_msg,
	पूर्ण;
	पूर्णांक ret;

	ret = __nfp_nsp_command(state, &arg);
	अगर (ret < 0)
		वापस ret;

	nfp_nsp_load_fw_extended_msg(state, ret);
	वापस 0;
पूर्ण

अटल पूर्णांक
__nfp_nsp_hwinfo_lookup(काष्ठा nfp_nsp *state, व्योम *buf, अचिन्हित पूर्णांक size,
			bool optional)
अणु
	काष्ठा nfp_nsp_command_buf_arg hwinfo_lookup = अणु
		अणु
			.code		= SPCODE_HWINFO_LOOKUP,
			.option		= size,
			.error_quiet	= optional,
		पूर्ण,
		.in_buf		= buf,
		.in_size	= size,
		.out_buf	= buf,
		.out_size	= size,
	पूर्ण;

	वापस nfp_nsp_command_buf(state, &hwinfo_lookup);
पूर्ण

पूर्णांक nfp_nsp_hwinfo_lookup(काष्ठा nfp_nsp *state, व्योम *buf, अचिन्हित पूर्णांक size)
अणु
	पूर्णांक err;

	size = min_t(u32, size, NFP_HWINFO_LOOKUP_SIZE);

	err = __nfp_nsp_hwinfo_lookup(state, buf, size, false);
	अगर (err)
		वापस err;

	अगर (strnlen(buf, size) == size) अणु
		nfp_err(state->cpp, "NSP HWinfo value not NULL-terminated\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक nfp_nsp_hwinfo_lookup_optional(काष्ठा nfp_nsp *state, व्योम *buf,
				   अचिन्हित पूर्णांक size, स्थिर अक्षर *शेष_val)
अणु
	पूर्णांक err;

	/* Ensure that the शेष value is usable irrespective of whether
	 * it is actually going to be used.
	 */
	अगर (strnlen(शेष_val, size) == size)
		वापस -EINVAL;

	अगर (!nfp_nsp_has_hwinfo_lookup(state)) अणु
		म_नकल(buf, शेष_val);
		वापस 0;
	पूर्ण

	size = min_t(u32, size, NFP_HWINFO_LOOKUP_SIZE);

	err = __nfp_nsp_hwinfo_lookup(state, buf, size, true);
	अगर (err) अणु
		अगर (err == -ENOENT) अणु
			म_नकल(buf, शेष_val);
			वापस 0;
		पूर्ण

		nfp_err(state->cpp, "NSP HWinfo lookup failed: %d\n", err);
		वापस err;
	पूर्ण

	अगर (strnlen(buf, size) == size) अणु
		nfp_err(state->cpp, "NSP HWinfo value not NULL-terminated\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक nfp_nsp_hwinfo_set(काष्ठा nfp_nsp *state, व्योम *buf, अचिन्हित पूर्णांक size)
अणु
	काष्ठा nfp_nsp_command_buf_arg hwinfo_set = अणु
		अणु
			.code		= SPCODE_HWINFO_SET,
			.option		= size,
		पूर्ण,
		.in_buf		= buf,
		.in_size	= size,
	पूर्ण;

	वापस nfp_nsp_command_buf(state, &hwinfo_set);
पूर्ण

पूर्णांक nfp_nsp_fw_loaded(काष्ठा nfp_nsp *state)
अणु
	स्थिर काष्ठा nfp_nsp_command_arg arg = अणु
		.code		= SPCODE_FW_LOADED,
	पूर्ण;

	वापस __nfp_nsp_command(state, &arg);
पूर्ण

पूर्णांक nfp_nsp_versions(काष्ठा nfp_nsp *state, व्योम *buf, अचिन्हित पूर्णांक size)
अणु
	काष्ठा nfp_nsp_command_buf_arg versions = अणु
		अणु
			.code		= SPCODE_VERSIONS,
			.option		= min_t(u32, size, NFP_VERSIONS_SIZE),
		पूर्ण,
		.out_buf	= buf,
		.out_size	= min_t(u32, size, NFP_VERSIONS_SIZE),
	पूर्ण;

	वापस nfp_nsp_command_buf(state, &versions);
पूर्ण

स्थिर अक्षर *nfp_nsp_versions_get(क्रमागत nfp_nsp_versions id, bool flash,
				 स्थिर u8 *buf, अचिन्हित पूर्णांक size)
अणु
	अटल स्थिर u32 id2off[] = अणु
		[NFP_VERSIONS_BSP] =	NFP_VERSIONS_BSP_OFF,
		[NFP_VERSIONS_CPLD] =	NFP_VERSIONS_CPLD_OFF,
		[NFP_VERSIONS_APP] =	NFP_VERSIONS_APP_OFF,
		[NFP_VERSIONS_BUNDLE] =	NFP_VERSIONS_BUNDLE_OFF,
		[NFP_VERSIONS_UNDI] =	NFP_VERSIONS_UNDI_OFF,
		[NFP_VERSIONS_NCSI] =	NFP_VERSIONS_NCSI_OFF,
		[NFP_VERSIONS_CFGR] =	NFP_VERSIONS_CFGR_OFF,
	पूर्ण;
	अचिन्हित पूर्णांक field, buf_field_cnt, buf_off;

	अगर (id >= ARRAY_SIZE(id2off) || !id2off[id])
		वापस ERR_PTR(-EINVAL);

	field = id * 2 + flash;

	buf_field_cnt = get_unaligned_le16(buf);
	अगर (buf_field_cnt <= field)
		वापस ERR_PTR(-ENOENT);

	buf_off = get_unaligned_le16(buf + id2off[id] + flash * 2);
	अगर (!buf_off)
		वापस ERR_PTR(-ENOENT);

	अगर (buf_off >= size)
		वापस ERR_PTR(-EINVAL);
	अगर (strnlen(&buf[buf_off], size - buf_off) == size - buf_off)
		वापस ERR_PTR(-EINVAL);

	वापस (स्थिर अक्षर *)&buf[buf_off];
पूर्ण

अटल पूर्णांक
__nfp_nsp_module_eeprom(काष्ठा nfp_nsp *state, व्योम *buf, अचिन्हित पूर्णांक size)
अणु
	काष्ठा nfp_nsp_command_buf_arg module_eeprom = अणु
		अणु
			.code		= SPCODE_READ_SFF_EEPROM,
			.option		= size,
		पूर्ण,
		.in_buf		= buf,
		.in_size	= size,
		.out_buf	= buf,
		.out_size	= size,
	पूर्ण;

	वापस nfp_nsp_command_buf(state, &module_eeprom);
पूर्ण

पूर्णांक nfp_nsp_पढ़ो_module_eeprom(काष्ठा nfp_nsp *state, पूर्णांक eth_index,
			       अचिन्हित पूर्णांक offset, व्योम *data,
			       अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक *पढ़ो_len)
अणु
	काष्ठा eeprom_buf अणु
		u8 metalen;
		__le16 length;
		__le16 offset;
		__le16 पढ़ोlen;
		u8 eth_index;
		u8 data[];
	पूर्ण __packed *buf;
	पूर्णांक bufsz, ret;

	BUILD_BUG_ON(दुरत्व(काष्ठा eeprom_buf, data) % 8);

	/* Buffer must be large enough and rounded to the next block size. */
	bufsz = काष्ठा_size(buf, data, round_up(len, NSP_SFF_EEPROM_BLOCK_LEN));
	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	buf->metalen =
		दुरत्व(काष्ठा eeprom_buf, data) / NSP_SFF_EEPROM_BLOCK_LEN;
	buf->length = cpu_to_le16(len);
	buf->offset = cpu_to_le16(offset);
	buf->eth_index = eth_index;

	ret = __nfp_nsp_module_eeprom(state, buf, bufsz);

	*पढ़ो_len = min_t(अचिन्हित पूर्णांक, len, le16_to_cpu(buf->पढ़ोlen));
	अगर (*पढ़ो_len)
		स_नकल(data, buf->data, *पढ़ो_len);

	अगर (!ret && *पढ़ो_len < len)
		ret = -EIO;

	kमुक्त(buf);

	वापस ret;
पूर्ण
