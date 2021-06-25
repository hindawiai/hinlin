<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
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
 * Author: Stanislaw Skowronek
 */

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <drm/drm_util.h>

#घोषणा ATOM_DEBUG

#समावेश "atom.h"
#समावेश "atom-names.h"
#समावेश "atom-bits.h"
#समावेश "amdgpu.h"

#घोषणा ATOM_COND_ABOVE		0
#घोषणा ATOM_COND_ABOVEOREQUAL	1
#घोषणा ATOM_COND_ALWAYS	2
#घोषणा ATOM_COND_BELOW		3
#घोषणा ATOM_COND_BELOWOREQUAL	4
#घोषणा ATOM_COND_EQUAL		5
#घोषणा ATOM_COND_NOTEQUAL	6

#घोषणा ATOM_PORT_ATI	0
#घोषणा ATOM_PORT_PCI	1
#घोषणा ATOM_PORT_SYSIO	2

#घोषणा ATOM_UNIT_MICROSEC	0
#घोषणा ATOM_UNIT_MILLISEC	1

#घोषणा PLL_INDEX	2
#घोषणा PLL_DATA	3

#घोषणा ATOM_CMD_TIMEOUT_SEC	20

प्रकार काष्ठा अणु
	काष्ठा atom_context *ctx;
	uपूर्णांक32_t *ps, *ws;
	पूर्णांक ps_shअगरt;
	uपूर्णांक16_t start;
	अचिन्हित last_jump;
	अचिन्हित दीर्घ last_jump_jअगरfies;
	bool पात;
पूर्ण atom_exec_context;

पूर्णांक amdgpu_atom_debug;
अटल पूर्णांक amdgpu_atom_execute_table_locked(काष्ठा atom_context *ctx, पूर्णांक index, uपूर्णांक32_t *params);
पूर्णांक amdgpu_atom_execute_table(काष्ठा atom_context *ctx, पूर्णांक index, uपूर्णांक32_t *params);

अटल uपूर्णांक32_t atom_arg_mask[8] =
	अणु 0xFFFFFFFF, 0xFFFF, 0xFFFF00, 0xFFFF0000, 0xFF, 0xFF00, 0xFF0000,
	  0xFF000000 पूर्ण;
अटल पूर्णांक atom_arg_shअगरt[8] = अणु 0, 0, 8, 16, 0, 8, 16, 24 पूर्ण;

अटल पूर्णांक atom_dst_to_src[8][4] = अणु
	/* translate destination alignment field to the source alignment encoding */
	अणु0, 0, 0, 0पूर्ण,
	अणु1, 2, 3, 0पूर्ण,
	अणु1, 2, 3, 0पूर्ण,
	अणु1, 2, 3, 0पूर्ण,
	अणु4, 5, 6, 7पूर्ण,
	अणु4, 5, 6, 7पूर्ण,
	अणु4, 5, 6, 7पूर्ण,
	अणु4, 5, 6, 7पूर्ण,
पूर्ण;
अटल पूर्णांक atom_def_dst[8] = अणु 0, 0, 1, 2, 0, 1, 2, 3 पूर्ण;

अटल पूर्णांक debug_depth;
#अगर_घोषित ATOM_DEBUG
अटल व्योम debug_prपूर्णांक_spaces(पूर्णांक n)
अणु
	जबतक (n--)
		prपूर्णांकk("   ");
पूर्ण

#घोषणा DEBUG(...) करो अगर (amdgpu_atom_debug) अणु prपूर्णांकk(KERN_DEBUG __VA_ARGS__); पूर्ण जबतक (0)
#घोषणा SDEBUG(...) करो अगर (amdgpu_atom_debug) अणु prपूर्णांकk(KERN_DEBUG); debug_prपूर्णांक_spaces(debug_depth); prपूर्णांकk(__VA_ARGS__); पूर्ण जबतक (0)
#अन्यथा
#घोषणा DEBUG(...) करो अणु पूर्ण जबतक (0)
#घोषणा SDEBUG(...) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल uपूर्णांक32_t atom_iio_execute(काष्ठा atom_context *ctx, पूर्णांक base,
				 uपूर्णांक32_t index, uपूर्णांक32_t data)
अणु
	uपूर्णांक32_t temp = 0xCDCDCDCD;

	जबतक (1)
		चयन (CU8(base)) अणु
		हाल ATOM_IIO_NOP:
			base++;
			अवरोध;
		हाल ATOM_IIO_READ:
			temp = ctx->card->reg_पढ़ो(ctx->card, CU16(base + 1));
			base += 3;
			अवरोध;
		हाल ATOM_IIO_WRITE:
			ctx->card->reg_ग_लिखो(ctx->card, CU16(base + 1), temp);
			base += 3;
			अवरोध;
		हाल ATOM_IIO_CLEAR:
			temp &=
			    ~((0xFFFFFFFF >> (32 - CU8(base + 1))) <<
			      CU8(base + 2));
			base += 3;
			अवरोध;
		हाल ATOM_IIO_SET:
			temp |=
			    (0xFFFFFFFF >> (32 - CU8(base + 1))) << CU8(base +
									2);
			base += 3;
			अवरोध;
		हाल ATOM_IIO_MOVE_INDEX:
			temp &=
			    ~((0xFFFFFFFF >> (32 - CU8(base + 1))) <<
			      CU8(base + 3));
			temp |=
			    ((index >> CU8(base + 2)) &
			     (0xFFFFFFFF >> (32 - CU8(base + 1)))) << CU8(base +
									  3);
			base += 4;
			अवरोध;
		हाल ATOM_IIO_MOVE_DATA:
			temp &=
			    ~((0xFFFFFFFF >> (32 - CU8(base + 1))) <<
			      CU8(base + 3));
			temp |=
			    ((data >> CU8(base + 2)) &
			     (0xFFFFFFFF >> (32 - CU8(base + 1)))) << CU8(base +
									  3);
			base += 4;
			अवरोध;
		हाल ATOM_IIO_MOVE_ATTR:
			temp &=
			    ~((0xFFFFFFFF >> (32 - CU8(base + 1))) <<
			      CU8(base + 3));
			temp |=
			    ((ctx->
			      io_attr >> CU8(base + 2)) & (0xFFFFFFFF >> (32 -
									  CU8
									  (base
									   +
									   1))))
			    << CU8(base + 3);
			base += 4;
			अवरोध;
		हाल ATOM_IIO_END:
			वापस temp;
		शेष:
			pr_info("Unknown IIO opcode\n");
			वापस 0;
		पूर्ण
पूर्ण

अटल uपूर्णांक32_t atom_get_src_पूर्णांक(atom_exec_context *ctx, uपूर्णांक8_t attr,
				 पूर्णांक *ptr, uपूर्णांक32_t *saved, पूर्णांक prपूर्णांक)
अणु
	uपूर्णांक32_t idx, val = 0xCDCDCDCD, align, arg;
	काष्ठा atom_context *gctx = ctx->ctx;
	arg = attr & 7;
	align = (attr >> 3) & 7;
	चयन (arg) अणु
	हाल ATOM_ARG_REG:
		idx = U16(*ptr);
		(*ptr) += 2;
		अगर (prपूर्णांक)
			DEBUG("REG[0x%04X]", idx);
		idx += gctx->reg_block;
		चयन (gctx->io_mode) अणु
		हाल ATOM_IO_MM:
			val = gctx->card->reg_पढ़ो(gctx->card, idx);
			अवरोध;
		हाल ATOM_IO_PCI:
			pr_info("PCI registers are not implemented\n");
			वापस 0;
		हाल ATOM_IO_SYSIO:
			pr_info("SYSIO registers are not implemented\n");
			वापस 0;
		शेष:
			अगर (!(gctx->io_mode & 0x80)) अणु
				pr_info("Bad IO mode\n");
				वापस 0;
			पूर्ण
			अगर (!gctx->iio[gctx->io_mode & 0x7F]) अणु
				pr_info("Undefined indirect IO read method %d\n",
					gctx->io_mode & 0x7F);
				वापस 0;
			पूर्ण
			val =
			    atom_iio_execute(gctx,
					     gctx->iio[gctx->io_mode & 0x7F],
					     idx, 0);
		पूर्ण
		अवरोध;
	हाल ATOM_ARG_PS:
		idx = U8(*ptr);
		(*ptr)++;
		/* get_unaligned_le32 aव्योमs unaligned accesses from atombios
		 * tables, noticed on a DEC Alpha. */
		val = get_unaligned_le32((u32 *)&ctx->ps[idx]);
		अगर (prपूर्णांक)
			DEBUG("PS[0x%02X,0x%04X]", idx, val);
		अवरोध;
	हाल ATOM_ARG_WS:
		idx = U8(*ptr);
		(*ptr)++;
		अगर (prपूर्णांक)
			DEBUG("WS[0x%02X]", idx);
		चयन (idx) अणु
		हाल ATOM_WS_QUOTIENT:
			val = gctx->भागmul[0];
			अवरोध;
		हाल ATOM_WS_REMAINDER:
			val = gctx->भागmul[1];
			अवरोध;
		हाल ATOM_WS_DATAPTR:
			val = gctx->data_block;
			अवरोध;
		हाल ATOM_WS_SHIFT:
			val = gctx->shअगरt;
			अवरोध;
		हाल ATOM_WS_OR_MASK:
			val = 1 << gctx->shअगरt;
			अवरोध;
		हाल ATOM_WS_AND_MASK:
			val = ~(1 << gctx->shअगरt);
			अवरोध;
		हाल ATOM_WS_FB_WINDOW:
			val = gctx->fb_base;
			अवरोध;
		हाल ATOM_WS_ATTRIBUTES:
			val = gctx->io_attr;
			अवरोध;
		हाल ATOM_WS_REGPTR:
			val = gctx->reg_block;
			अवरोध;
		शेष:
			val = ctx->ws[idx];
		पूर्ण
		अवरोध;
	हाल ATOM_ARG_ID:
		idx = U16(*ptr);
		(*ptr) += 2;
		अगर (prपूर्णांक) अणु
			अगर (gctx->data_block)
				DEBUG("ID[0x%04X+%04X]", idx, gctx->data_block);
			अन्यथा
				DEBUG("ID[0x%04X]", idx);
		पूर्ण
		val = U32(idx + gctx->data_block);
		अवरोध;
	हाल ATOM_ARG_FB:
		idx = U8(*ptr);
		(*ptr)++;
		अगर ((gctx->fb_base + (idx * 4)) > gctx->scratch_size_bytes) अणु
			DRM_ERROR("ATOM: fb read beyond scratch region: %d vs. %d\n",
				  gctx->fb_base + (idx * 4), gctx->scratch_size_bytes);
			val = 0;
		पूर्ण अन्यथा
			val = gctx->scratch[(gctx->fb_base / 4) + idx];
		अगर (prपूर्णांक)
			DEBUG("FB[0x%02X]", idx);
		अवरोध;
	हाल ATOM_ARG_IMM:
		चयन (align) अणु
		हाल ATOM_SRC_DWORD:
			val = U32(*ptr);
			(*ptr) += 4;
			अगर (prपूर्णांक)
				DEBUG("IMM 0x%08X\n", val);
			वापस val;
		हाल ATOM_SRC_WORD0:
		हाल ATOM_SRC_WORD8:
		हाल ATOM_SRC_WORD16:
			val = U16(*ptr);
			(*ptr) += 2;
			अगर (prपूर्णांक)
				DEBUG("IMM 0x%04X\n", val);
			वापस val;
		हाल ATOM_SRC_BYTE0:
		हाल ATOM_SRC_BYTE8:
		हाल ATOM_SRC_BYTE16:
		हाल ATOM_SRC_BYTE24:
			val = U8(*ptr);
			(*ptr)++;
			अगर (prपूर्णांक)
				DEBUG("IMM 0x%02X\n", val);
			वापस val;
		पूर्ण
		वापस 0;
	हाल ATOM_ARG_PLL:
		idx = U8(*ptr);
		(*ptr)++;
		अगर (prपूर्णांक)
			DEBUG("PLL[0x%02X]", idx);
		val = gctx->card->pll_पढ़ो(gctx->card, idx);
		अवरोध;
	हाल ATOM_ARG_MC:
		idx = U8(*ptr);
		(*ptr)++;
		अगर (prपूर्णांक)
			DEBUG("MC[0x%02X]", idx);
		val = gctx->card->mc_पढ़ो(gctx->card, idx);
		अवरोध;
	पूर्ण
	अगर (saved)
		*saved = val;
	val &= atom_arg_mask[align];
	val >>= atom_arg_shअगरt[align];
	अगर (prपूर्णांक)
		चयन (align) अणु
		हाल ATOM_SRC_DWORD:
			DEBUG(".[31:0] -> 0x%08X\n", val);
			अवरोध;
		हाल ATOM_SRC_WORD0:
			DEBUG(".[15:0] -> 0x%04X\n", val);
			अवरोध;
		हाल ATOM_SRC_WORD8:
			DEBUG(".[23:8] -> 0x%04X\n", val);
			अवरोध;
		हाल ATOM_SRC_WORD16:
			DEBUG(".[31:16] -> 0x%04X\n", val);
			अवरोध;
		हाल ATOM_SRC_BYTE0:
			DEBUG(".[7:0] -> 0x%02X\n", val);
			अवरोध;
		हाल ATOM_SRC_BYTE8:
			DEBUG(".[15:8] -> 0x%02X\n", val);
			अवरोध;
		हाल ATOM_SRC_BYTE16:
			DEBUG(".[23:16] -> 0x%02X\n", val);
			अवरोध;
		हाल ATOM_SRC_BYTE24:
			DEBUG(".[31:24] -> 0x%02X\n", val);
			अवरोध;
		पूर्ण
	वापस val;
पूर्ण

अटल व्योम atom_skip_src_पूर्णांक(atom_exec_context *ctx, uपूर्णांक8_t attr, पूर्णांक *ptr)
अणु
	uपूर्णांक32_t align = (attr >> 3) & 7, arg = attr & 7;
	चयन (arg) अणु
	हाल ATOM_ARG_REG:
	हाल ATOM_ARG_ID:
		(*ptr) += 2;
		अवरोध;
	हाल ATOM_ARG_PLL:
	हाल ATOM_ARG_MC:
	हाल ATOM_ARG_PS:
	हाल ATOM_ARG_WS:
	हाल ATOM_ARG_FB:
		(*ptr)++;
		अवरोध;
	हाल ATOM_ARG_IMM:
		चयन (align) अणु
		हाल ATOM_SRC_DWORD:
			(*ptr) += 4;
			वापस;
		हाल ATOM_SRC_WORD0:
		हाल ATOM_SRC_WORD8:
		हाल ATOM_SRC_WORD16:
			(*ptr) += 2;
			वापस;
		हाल ATOM_SRC_BYTE0:
		हाल ATOM_SRC_BYTE8:
		हाल ATOM_SRC_BYTE16:
		हाल ATOM_SRC_BYTE24:
			(*ptr)++;
			वापस;
		पूर्ण
		वापस;
	पूर्ण
पूर्ण

अटल uपूर्णांक32_t atom_get_src(atom_exec_context *ctx, uपूर्णांक8_t attr, पूर्णांक *ptr)
अणु
	वापस atom_get_src_पूर्णांक(ctx, attr, ptr, शून्य, 1);
पूर्ण

अटल uपूर्णांक32_t atom_get_src_direct(atom_exec_context *ctx, uपूर्णांक8_t align, पूर्णांक *ptr)
अणु
	uपूर्णांक32_t val = 0xCDCDCDCD;

	चयन (align) अणु
	हाल ATOM_SRC_DWORD:
		val = U32(*ptr);
		(*ptr) += 4;
		अवरोध;
	हाल ATOM_SRC_WORD0:
	हाल ATOM_SRC_WORD8:
	हाल ATOM_SRC_WORD16:
		val = U16(*ptr);
		(*ptr) += 2;
		अवरोध;
	हाल ATOM_SRC_BYTE0:
	हाल ATOM_SRC_BYTE8:
	हाल ATOM_SRC_BYTE16:
	हाल ATOM_SRC_BYTE24:
		val = U8(*ptr);
		(*ptr)++;
		अवरोध;
	पूर्ण
	वापस val;
पूर्ण

अटल uपूर्णांक32_t atom_get_dst(atom_exec_context *ctx, पूर्णांक arg, uपूर्णांक8_t attr,
			     पूर्णांक *ptr, uपूर्णांक32_t *saved, पूर्णांक prपूर्णांक)
अणु
	वापस atom_get_src_पूर्णांक(ctx,
				arg | atom_dst_to_src[(attr >> 3) &
						      7][(attr >> 6) & 3] << 3,
				ptr, saved, prपूर्णांक);
पूर्ण

अटल व्योम atom_skip_dst(atom_exec_context *ctx, पूर्णांक arg, uपूर्णांक8_t attr, पूर्णांक *ptr)
अणु
	atom_skip_src_पूर्णांक(ctx,
			  arg | atom_dst_to_src[(attr >> 3) & 7][(attr >> 6) &
								 3] << 3, ptr);
पूर्ण

अटल व्योम atom_put_dst(atom_exec_context *ctx, पूर्णांक arg, uपूर्णांक8_t attr,
			 पूर्णांक *ptr, uपूर्णांक32_t val, uपूर्णांक32_t saved)
अणु
	uपूर्णांक32_t align =
	    atom_dst_to_src[(attr >> 3) & 7][(attr >> 6) & 3], old_val =
	    val, idx;
	काष्ठा atom_context *gctx = ctx->ctx;
	old_val &= atom_arg_mask[align] >> atom_arg_shअगरt[align];
	val <<= atom_arg_shअगरt[align];
	val &= atom_arg_mask[align];
	saved &= ~atom_arg_mask[align];
	val |= saved;
	चयन (arg) अणु
	हाल ATOM_ARG_REG:
		idx = U16(*ptr);
		(*ptr) += 2;
		DEBUG("REG[0x%04X]", idx);
		idx += gctx->reg_block;
		चयन (gctx->io_mode) अणु
		हाल ATOM_IO_MM:
			अगर (idx == 0)
				gctx->card->reg_ग_लिखो(gctx->card, idx,
						      val << 2);
			अन्यथा
				gctx->card->reg_ग_लिखो(gctx->card, idx, val);
			अवरोध;
		हाल ATOM_IO_PCI:
			pr_info("PCI registers are not implemented\n");
			वापस;
		हाल ATOM_IO_SYSIO:
			pr_info("SYSIO registers are not implemented\n");
			वापस;
		शेष:
			अगर (!(gctx->io_mode & 0x80)) अणु
				pr_info("Bad IO mode\n");
				वापस;
			पूर्ण
			अगर (!gctx->iio[gctx->io_mode & 0xFF]) अणु
				pr_info("Undefined indirect IO write method %d\n",
					gctx->io_mode & 0x7F);
				वापस;
			पूर्ण
			atom_iio_execute(gctx, gctx->iio[gctx->io_mode & 0xFF],
					 idx, val);
		पूर्ण
		अवरोध;
	हाल ATOM_ARG_PS:
		idx = U8(*ptr);
		(*ptr)++;
		DEBUG("PS[0x%02X]", idx);
		ctx->ps[idx] = cpu_to_le32(val);
		अवरोध;
	हाल ATOM_ARG_WS:
		idx = U8(*ptr);
		(*ptr)++;
		DEBUG("WS[0x%02X]", idx);
		चयन (idx) अणु
		हाल ATOM_WS_QUOTIENT:
			gctx->भागmul[0] = val;
			अवरोध;
		हाल ATOM_WS_REMAINDER:
			gctx->भागmul[1] = val;
			अवरोध;
		हाल ATOM_WS_DATAPTR:
			gctx->data_block = val;
			अवरोध;
		हाल ATOM_WS_SHIFT:
			gctx->shअगरt = val;
			अवरोध;
		हाल ATOM_WS_OR_MASK:
		हाल ATOM_WS_AND_MASK:
			अवरोध;
		हाल ATOM_WS_FB_WINDOW:
			gctx->fb_base = val;
			अवरोध;
		हाल ATOM_WS_ATTRIBUTES:
			gctx->io_attr = val;
			अवरोध;
		हाल ATOM_WS_REGPTR:
			gctx->reg_block = val;
			अवरोध;
		शेष:
			ctx->ws[idx] = val;
		पूर्ण
		अवरोध;
	हाल ATOM_ARG_FB:
		idx = U8(*ptr);
		(*ptr)++;
		अगर ((gctx->fb_base + (idx * 4)) > gctx->scratch_size_bytes) अणु
			DRM_ERROR("ATOM: fb write beyond scratch region: %d vs. %d\n",
				  gctx->fb_base + (idx * 4), gctx->scratch_size_bytes);
		पूर्ण अन्यथा
			gctx->scratch[(gctx->fb_base / 4) + idx] = val;
		DEBUG("FB[0x%02X]", idx);
		अवरोध;
	हाल ATOM_ARG_PLL:
		idx = U8(*ptr);
		(*ptr)++;
		DEBUG("PLL[0x%02X]", idx);
		gctx->card->pll_ग_लिखो(gctx->card, idx, val);
		अवरोध;
	हाल ATOM_ARG_MC:
		idx = U8(*ptr);
		(*ptr)++;
		DEBUG("MC[0x%02X]", idx);
		gctx->card->mc_ग_लिखो(gctx->card, idx, val);
		वापस;
	पूर्ण
	चयन (align) अणु
	हाल ATOM_SRC_DWORD:
		DEBUG(".[31:0] <- 0x%08X\n", old_val);
		अवरोध;
	हाल ATOM_SRC_WORD0:
		DEBUG(".[15:0] <- 0x%04X\n", old_val);
		अवरोध;
	हाल ATOM_SRC_WORD8:
		DEBUG(".[23:8] <- 0x%04X\n", old_val);
		अवरोध;
	हाल ATOM_SRC_WORD16:
		DEBUG(".[31:16] <- 0x%04X\n", old_val);
		अवरोध;
	हाल ATOM_SRC_BYTE0:
		DEBUG(".[7:0] <- 0x%02X\n", old_val);
		अवरोध;
	हाल ATOM_SRC_BYTE8:
		DEBUG(".[15:8] <- 0x%02X\n", old_val);
		अवरोध;
	हाल ATOM_SRC_BYTE16:
		DEBUG(".[23:16] <- 0x%02X\n", old_val);
		अवरोध;
	हाल ATOM_SRC_BYTE24:
		DEBUG(".[31:24] <- 0x%02X\n", old_val);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम atom_op_add(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक8_t attr = U8((*ptr)++);
	uपूर्णांक32_t dst, src, saved;
	पूर्णांक dptr = *ptr;
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, &saved, 1);
	SDEBUG("   src: ");
	src = atom_get_src(ctx, attr, ptr);
	dst += src;
	SDEBUG("   dst: ");
	atom_put_dst(ctx, arg, attr, &dptr, dst, saved);
पूर्ण

अटल व्योम atom_op_and(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक8_t attr = U8((*ptr)++);
	uपूर्णांक32_t dst, src, saved;
	पूर्णांक dptr = *ptr;
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, &saved, 1);
	SDEBUG("   src: ");
	src = atom_get_src(ctx, attr, ptr);
	dst &= src;
	SDEBUG("   dst: ");
	atom_put_dst(ctx, arg, attr, &dptr, dst, saved);
पूर्ण

अटल व्योम atom_op_beep(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	prपूर्णांकk("ATOM BIOS beeped!\n");
पूर्ण

अटल व्योम atom_op_calltable(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	पूर्णांक idx = U8((*ptr)++);
	पूर्णांक r = 0;

	अगर (idx < ATOM_TABLE_NAMES_CNT)
		SDEBUG("   table: %d (%s)\n", idx, atom_table_names[idx]);
	अन्यथा
		SDEBUG("   table: %d\n", idx);
	अगर (U16(ctx->ctx->cmd_table + 4 + 2 * idx))
		r = amdgpu_atom_execute_table_locked(ctx->ctx, idx, ctx->ps + ctx->ps_shअगरt);
	अगर (r) अणु
		ctx->पात = true;
	पूर्ण
पूर्ण

अटल व्योम atom_op_clear(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक8_t attr = U8((*ptr)++);
	uपूर्णांक32_t saved;
	पूर्णांक dptr = *ptr;
	attr &= 0x38;
	attr |= atom_def_dst[attr >> 3] << 6;
	atom_get_dst(ctx, arg, attr, ptr, &saved, 0);
	SDEBUG("   dst: ");
	atom_put_dst(ctx, arg, attr, &dptr, 0, saved);
पूर्ण

अटल व्योम atom_op_compare(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक8_t attr = U8((*ptr)++);
	uपूर्णांक32_t dst, src;
	SDEBUG("   src1: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, शून्य, 1);
	SDEBUG("   src2: ");
	src = atom_get_src(ctx, attr, ptr);
	ctx->ctx->cs_equal = (dst == src);
	ctx->ctx->cs_above = (dst > src);
	SDEBUG("   result: %s %s\n", ctx->ctx->cs_equal ? "EQ" : "NE",
	       ctx->ctx->cs_above ? "GT" : "LE");
पूर्ण

अटल व्योम atom_op_delay(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	अचिन्हित count = U8((*ptr)++);
	SDEBUG("   count: %d\n", count);
	अगर (arg == ATOM_UNIT_MICROSEC)
		udelay(count);
	अन्यथा अगर (!drm_can_sleep())
		mdelay(count);
	अन्यथा
		msleep(count);
पूर्ण

अटल व्योम atom_op_भाग(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक8_t attr = U8((*ptr)++);
	uपूर्णांक32_t dst, src;
	SDEBUG("   src1: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, शून्य, 1);
	SDEBUG("   src2: ");
	src = atom_get_src(ctx, attr, ptr);
	अगर (src != 0) अणु
		ctx->ctx->भागmul[0] = dst / src;
		ctx->ctx->भागmul[1] = dst % src;
	पूर्ण अन्यथा अणु
		ctx->ctx->भागmul[0] = 0;
		ctx->ctx->भागmul[1] = 0;
	पूर्ण
पूर्ण

अटल व्योम atom_op_भाग32(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक64_t val64;
	uपूर्णांक8_t attr = U8((*ptr)++);
	uपूर्णांक32_t dst, src;
	SDEBUG("   src1: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, शून्य, 1);
	SDEBUG("   src2: ");
	src = atom_get_src(ctx, attr, ptr);
	अगर (src != 0) अणु
		val64 = dst;
		val64 |= ((uपूर्णांक64_t)ctx->ctx->भागmul[1]) << 32;
		करो_भाग(val64, src);
		ctx->ctx->भागmul[0] = lower_32_bits(val64);
		ctx->ctx->भागmul[1] = upper_32_bits(val64);
	पूर्ण अन्यथा अणु
		ctx->ctx->भागmul[0] = 0;
		ctx->ctx->भागmul[1] = 0;
	पूर्ण
पूर्ण

अटल व्योम atom_op_eot(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	/* functionally, a nop */
पूर्ण

अटल व्योम atom_op_jump(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	पूर्णांक execute = 0, target = U16(*ptr);
	अचिन्हित दीर्घ cjअगरfies;

	(*ptr) += 2;
	चयन (arg) अणु
	हाल ATOM_COND_ABOVE:
		execute = ctx->ctx->cs_above;
		अवरोध;
	हाल ATOM_COND_ABOVEOREQUAL:
		execute = ctx->ctx->cs_above || ctx->ctx->cs_equal;
		अवरोध;
	हाल ATOM_COND_ALWAYS:
		execute = 1;
		अवरोध;
	हाल ATOM_COND_BELOW:
		execute = !(ctx->ctx->cs_above || ctx->ctx->cs_equal);
		अवरोध;
	हाल ATOM_COND_BELOWOREQUAL:
		execute = !ctx->ctx->cs_above;
		अवरोध;
	हाल ATOM_COND_EQUAL:
		execute = ctx->ctx->cs_equal;
		अवरोध;
	हाल ATOM_COND_NOTEQUAL:
		execute = !ctx->ctx->cs_equal;
		अवरोध;
	पूर्ण
	अगर (arg != ATOM_COND_ALWAYS)
		SDEBUG("   taken: %s\n", execute ? "yes" : "no");
	SDEBUG("   target: 0x%04X\n", target);
	अगर (execute) अणु
		अगर (ctx->last_jump == (ctx->start + target)) अणु
			cjअगरfies = jअगरfies;
			अगर (समय_after(cjअगरfies, ctx->last_jump_jअगरfies)) अणु
				cjअगरfies -= ctx->last_jump_jअगरfies;
				अगर ((jअगरfies_to_msecs(cjअगरfies) > ATOM_CMD_TIMEOUT_SEC*1000)) अणु
					DRM_ERROR("atombios stuck in loop for more than %dsecs aborting\n",
						  ATOM_CMD_TIMEOUT_SEC);
					ctx->पात = true;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* jअगरfies wrap around we will just रुको a little दीर्घer */
				ctx->last_jump_jअगरfies = jअगरfies;
			पूर्ण
		पूर्ण अन्यथा अणु
			ctx->last_jump = ctx->start + target;
			ctx->last_jump_jअगरfies = jअगरfies;
		पूर्ण
		*ptr = ctx->start + target;
	पूर्ण
पूर्ण

अटल व्योम atom_op_mask(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक8_t attr = U8((*ptr)++);
	uपूर्णांक32_t dst, mask, src, saved;
	पूर्णांक dptr = *ptr;
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, &saved, 1);
	mask = atom_get_src_direct(ctx, ((attr >> 3) & 7), ptr);
	SDEBUG("   mask: 0x%08x", mask);
	SDEBUG("   src: ");
	src = atom_get_src(ctx, attr, ptr);
	dst &= mask;
	dst |= src;
	SDEBUG("   dst: ");
	atom_put_dst(ctx, arg, attr, &dptr, dst, saved);
पूर्ण

अटल व्योम atom_op_move(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक8_t attr = U8((*ptr)++);
	uपूर्णांक32_t src, saved;
	पूर्णांक dptr = *ptr;
	अगर (((attr >> 3) & 7) != ATOM_SRC_DWORD)
		atom_get_dst(ctx, arg, attr, ptr, &saved, 0);
	अन्यथा अणु
		atom_skip_dst(ctx, arg, attr, ptr);
		saved = 0xCDCDCDCD;
	पूर्ण
	SDEBUG("   src: ");
	src = atom_get_src(ctx, attr, ptr);
	SDEBUG("   dst: ");
	atom_put_dst(ctx, arg, attr, &dptr, src, saved);
पूर्ण

अटल व्योम atom_op_mul(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक8_t attr = U8((*ptr)++);
	uपूर्णांक32_t dst, src;
	SDEBUG("   src1: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, शून्य, 1);
	SDEBUG("   src2: ");
	src = atom_get_src(ctx, attr, ptr);
	ctx->ctx->भागmul[0] = dst * src;
पूर्ण

अटल व्योम atom_op_mul32(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक64_t val64;
	uपूर्णांक8_t attr = U8((*ptr)++);
	uपूर्णांक32_t dst, src;
	SDEBUG("   src1: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, शून्य, 1);
	SDEBUG("   src2: ");
	src = atom_get_src(ctx, attr, ptr);
	val64 = (uपूर्णांक64_t)dst * (uपूर्णांक64_t)src;
	ctx->ctx->भागmul[0] = lower_32_bits(val64);
	ctx->ctx->भागmul[1] = upper_32_bits(val64);
पूर्ण

अटल व्योम atom_op_nop(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	/* nothing */
पूर्ण

अटल व्योम atom_op_or(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक8_t attr = U8((*ptr)++);
	uपूर्णांक32_t dst, src, saved;
	पूर्णांक dptr = *ptr;
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, &saved, 1);
	SDEBUG("   src: ");
	src = atom_get_src(ctx, attr, ptr);
	dst |= src;
	SDEBUG("   dst: ");
	atom_put_dst(ctx, arg, attr, &dptr, dst, saved);
पूर्ण

अटल व्योम atom_op_postcard(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक8_t val = U8((*ptr)++);
	SDEBUG("POST card output: 0x%02X\n", val);
पूर्ण

अटल व्योम atom_op_repeat(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	pr_info("unimplemented!\n");
पूर्ण

अटल व्योम atom_op_restorereg(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	pr_info("unimplemented!\n");
पूर्ण

अटल व्योम atom_op_savereg(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	pr_info("unimplemented!\n");
पूर्ण

अटल व्योम atom_op_setdatablock(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	पूर्णांक idx = U8(*ptr);
	(*ptr)++;
	SDEBUG("   block: %d\n", idx);
	अगर (!idx)
		ctx->ctx->data_block = 0;
	अन्यथा अगर (idx == 255)
		ctx->ctx->data_block = ctx->start;
	अन्यथा
		ctx->ctx->data_block = U16(ctx->ctx->data_table + 4 + 2 * idx);
	SDEBUG("   base: 0x%04X\n", ctx->ctx->data_block);
पूर्ण

अटल व्योम atom_op_setfbbase(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक8_t attr = U8((*ptr)++);
	SDEBUG("   fb_base: ");
	ctx->ctx->fb_base = atom_get_src(ctx, attr, ptr);
पूर्ण

अटल व्योम atom_op_setport(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	पूर्णांक port;
	चयन (arg) अणु
	हाल ATOM_PORT_ATI:
		port = U16(*ptr);
		अगर (port < ATOM_IO_NAMES_CNT)
			SDEBUG("   port: %d (%s)\n", port, atom_io_names[port]);
		अन्यथा
			SDEBUG("   port: %d\n", port);
		अगर (!port)
			ctx->ctx->io_mode = ATOM_IO_MM;
		अन्यथा
			ctx->ctx->io_mode = ATOM_IO_IIO | port;
		(*ptr) += 2;
		अवरोध;
	हाल ATOM_PORT_PCI:
		ctx->ctx->io_mode = ATOM_IO_PCI;
		(*ptr)++;
		अवरोध;
	हाल ATOM_PORT_SYSIO:
		ctx->ctx->io_mode = ATOM_IO_SYSIO;
		(*ptr)++;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम atom_op_setregblock(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	ctx->ctx->reg_block = U16(*ptr);
	(*ptr) += 2;
	SDEBUG("   base: 0x%04X\n", ctx->ctx->reg_block);
पूर्ण

अटल व्योम atom_op_shअगरt_left(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक8_t attr = U8((*ptr)++), shअगरt;
	uपूर्णांक32_t saved, dst;
	पूर्णांक dptr = *ptr;
	attr &= 0x38;
	attr |= atom_def_dst[attr >> 3] << 6;
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, &saved, 1);
	shअगरt = atom_get_src_direct(ctx, ATOM_SRC_BYTE0, ptr);
	SDEBUG("   shift: %d\n", shअगरt);
	dst <<= shअगरt;
	SDEBUG("   dst: ");
	atom_put_dst(ctx, arg, attr, &dptr, dst, saved);
पूर्ण

अटल व्योम atom_op_shअगरt_right(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक8_t attr = U8((*ptr)++), shअगरt;
	uपूर्णांक32_t saved, dst;
	पूर्णांक dptr = *ptr;
	attr &= 0x38;
	attr |= atom_def_dst[attr >> 3] << 6;
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, &saved, 1);
	shअगरt = atom_get_src_direct(ctx, ATOM_SRC_BYTE0, ptr);
	SDEBUG("   shift: %d\n", shअगरt);
	dst >>= shअगरt;
	SDEBUG("   dst: ");
	atom_put_dst(ctx, arg, attr, &dptr, dst, saved);
पूर्ण

अटल व्योम atom_op_shl(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक8_t attr = U8((*ptr)++), shअगरt;
	uपूर्णांक32_t saved, dst;
	पूर्णांक dptr = *ptr;
	uपूर्णांक32_t dst_align = atom_dst_to_src[(attr >> 3) & 7][(attr >> 6) & 3];
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, &saved, 1);
	/* op needs to full dst value */
	dst = saved;
	shअगरt = atom_get_src(ctx, attr, ptr);
	SDEBUG("   shift: %d\n", shअगरt);
	dst <<= shअगरt;
	dst &= atom_arg_mask[dst_align];
	dst >>= atom_arg_shअगरt[dst_align];
	SDEBUG("   dst: ");
	atom_put_dst(ctx, arg, attr, &dptr, dst, saved);
पूर्ण

अटल व्योम atom_op_shr(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक8_t attr = U8((*ptr)++), shअगरt;
	uपूर्णांक32_t saved, dst;
	पूर्णांक dptr = *ptr;
	uपूर्णांक32_t dst_align = atom_dst_to_src[(attr >> 3) & 7][(attr >> 6) & 3];
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, &saved, 1);
	/* op needs to full dst value */
	dst = saved;
	shअगरt = atom_get_src(ctx, attr, ptr);
	SDEBUG("   shift: %d\n", shअगरt);
	dst >>= shअगरt;
	dst &= atom_arg_mask[dst_align];
	dst >>= atom_arg_shअगरt[dst_align];
	SDEBUG("   dst: ");
	atom_put_dst(ctx, arg, attr, &dptr, dst, saved);
पूर्ण

अटल व्योम atom_op_sub(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक8_t attr = U8((*ptr)++);
	uपूर्णांक32_t dst, src, saved;
	पूर्णांक dptr = *ptr;
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, &saved, 1);
	SDEBUG("   src: ");
	src = atom_get_src(ctx, attr, ptr);
	dst -= src;
	SDEBUG("   dst: ");
	atom_put_dst(ctx, arg, attr, &dptr, dst, saved);
पूर्ण

अटल व्योम atom_op_चयन(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक8_t attr = U8((*ptr)++);
	uपूर्णांक32_t src, val, target;
	SDEBUG("   switch: ");
	src = atom_get_src(ctx, attr, ptr);
	जबतक (U16(*ptr) != ATOM_CASE_END)
		अगर (U8(*ptr) == ATOM_CASE_MAGIC) अणु
			(*ptr)++;
			SDEBUG("   case: ");
			val =
			    atom_get_src(ctx, (attr & 0x38) | ATOM_ARG_IMM,
					 ptr);
			target = U16(*ptr);
			अगर (val == src) अणु
				SDEBUG("   target: %04X\n", target);
				*ptr = ctx->start + target;
				वापस;
			पूर्ण
			(*ptr) += 2;
		पूर्ण अन्यथा अणु
			pr_info("Bad case\n");
			वापस;
		पूर्ण
	(*ptr) += 2;
पूर्ण

अटल व्योम atom_op_test(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक8_t attr = U8((*ptr)++);
	uपूर्णांक32_t dst, src;
	SDEBUG("   src1: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, शून्य, 1);
	SDEBUG("   src2: ");
	src = atom_get_src(ctx, attr, ptr);
	ctx->ctx->cs_equal = ((dst & src) == 0);
	SDEBUG("   result: %s\n", ctx->ctx->cs_equal ? "EQ" : "NE");
पूर्ण

अटल व्योम atom_op_xor(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक8_t attr = U8((*ptr)++);
	uपूर्णांक32_t dst, src, saved;
	पूर्णांक dptr = *ptr;
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, &saved, 1);
	SDEBUG("   src: ");
	src = atom_get_src(ctx, attr, ptr);
	dst ^= src;
	SDEBUG("   dst: ");
	atom_put_dst(ctx, arg, attr, &dptr, dst, saved);
पूर्ण

अटल व्योम atom_op_debug(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक8_t val = U8((*ptr)++);
	SDEBUG("DEBUG output: 0x%02X\n", val);
पूर्ण

अटल व्योम atom_op_processds(atom_exec_context *ctx, पूर्णांक *ptr, पूर्णांक arg)
अणु
	uपूर्णांक16_t val = U16(*ptr);
	(*ptr) += val + 2;
	SDEBUG("PROCESSDS output: 0x%02X\n", val);
पूर्ण

अटल काष्ठा अणु
	व्योम (*func) (atom_exec_context *, पूर्णांक *, पूर्णांक);
	पूर्णांक arg;
पूर्ण opcode_table[ATOM_OP_CNT] = अणु
	अणु
	शून्य, 0पूर्ण, अणु
	atom_op_move, ATOM_ARG_REGपूर्ण, अणु
	atom_op_move, ATOM_ARG_PSपूर्ण, अणु
	atom_op_move, ATOM_ARG_WSपूर्ण, अणु
	atom_op_move, ATOM_ARG_FBपूर्ण, अणु
	atom_op_move, ATOM_ARG_PLLपूर्ण, अणु
	atom_op_move, ATOM_ARG_MCपूर्ण, अणु
	atom_op_and, ATOM_ARG_REGपूर्ण, अणु
	atom_op_and, ATOM_ARG_PSपूर्ण, अणु
	atom_op_and, ATOM_ARG_WSपूर्ण, अणु
	atom_op_and, ATOM_ARG_FBपूर्ण, अणु
	atom_op_and, ATOM_ARG_PLLपूर्ण, अणु
	atom_op_and, ATOM_ARG_MCपूर्ण, अणु
	atom_op_or, ATOM_ARG_REGपूर्ण, अणु
	atom_op_or, ATOM_ARG_PSपूर्ण, अणु
	atom_op_or, ATOM_ARG_WSपूर्ण, अणु
	atom_op_or, ATOM_ARG_FBपूर्ण, अणु
	atom_op_or, ATOM_ARG_PLLपूर्ण, अणु
	atom_op_or, ATOM_ARG_MCपूर्ण, अणु
	atom_op_shअगरt_left, ATOM_ARG_REGपूर्ण, अणु
	atom_op_shअगरt_left, ATOM_ARG_PSपूर्ण, अणु
	atom_op_shअगरt_left, ATOM_ARG_WSपूर्ण, अणु
	atom_op_shअगरt_left, ATOM_ARG_FBपूर्ण, अणु
	atom_op_shअगरt_left, ATOM_ARG_PLLपूर्ण, अणु
	atom_op_shअगरt_left, ATOM_ARG_MCपूर्ण, अणु
	atom_op_shअगरt_right, ATOM_ARG_REGपूर्ण, अणु
	atom_op_shअगरt_right, ATOM_ARG_PSपूर्ण, अणु
	atom_op_shअगरt_right, ATOM_ARG_WSपूर्ण, अणु
	atom_op_shअगरt_right, ATOM_ARG_FBपूर्ण, अणु
	atom_op_shअगरt_right, ATOM_ARG_PLLपूर्ण, अणु
	atom_op_shअगरt_right, ATOM_ARG_MCपूर्ण, अणु
	atom_op_mul, ATOM_ARG_REGपूर्ण, अणु
	atom_op_mul, ATOM_ARG_PSपूर्ण, अणु
	atom_op_mul, ATOM_ARG_WSपूर्ण, अणु
	atom_op_mul, ATOM_ARG_FBपूर्ण, अणु
	atom_op_mul, ATOM_ARG_PLLपूर्ण, अणु
	atom_op_mul, ATOM_ARG_MCपूर्ण, अणु
	atom_op_भाग, ATOM_ARG_REGपूर्ण, अणु
	atom_op_भाग, ATOM_ARG_PSपूर्ण, अणु
	atom_op_भाग, ATOM_ARG_WSपूर्ण, अणु
	atom_op_भाग, ATOM_ARG_FBपूर्ण, अणु
	atom_op_भाग, ATOM_ARG_PLLपूर्ण, अणु
	atom_op_भाग, ATOM_ARG_MCपूर्ण, अणु
	atom_op_add, ATOM_ARG_REGपूर्ण, अणु
	atom_op_add, ATOM_ARG_PSपूर्ण, अणु
	atom_op_add, ATOM_ARG_WSपूर्ण, अणु
	atom_op_add, ATOM_ARG_FBपूर्ण, अणु
	atom_op_add, ATOM_ARG_PLLपूर्ण, अणु
	atom_op_add, ATOM_ARG_MCपूर्ण, अणु
	atom_op_sub, ATOM_ARG_REGपूर्ण, अणु
	atom_op_sub, ATOM_ARG_PSपूर्ण, अणु
	atom_op_sub, ATOM_ARG_WSपूर्ण, अणु
	atom_op_sub, ATOM_ARG_FBपूर्ण, अणु
	atom_op_sub, ATOM_ARG_PLLपूर्ण, अणु
	atom_op_sub, ATOM_ARG_MCपूर्ण, अणु
	atom_op_setport, ATOM_PORT_ATIपूर्ण, अणु
	atom_op_setport, ATOM_PORT_PCIपूर्ण, अणु
	atom_op_setport, ATOM_PORT_SYSIOपूर्ण, अणु
	atom_op_setregblock, 0पूर्ण, अणु
	atom_op_setfbbase, 0पूर्ण, अणु
	atom_op_compare, ATOM_ARG_REGपूर्ण, अणु
	atom_op_compare, ATOM_ARG_PSपूर्ण, अणु
	atom_op_compare, ATOM_ARG_WSपूर्ण, अणु
	atom_op_compare, ATOM_ARG_FBपूर्ण, अणु
	atom_op_compare, ATOM_ARG_PLLपूर्ण, अणु
	atom_op_compare, ATOM_ARG_MCपूर्ण, अणु
	atom_op_चयन, 0पूर्ण, अणु
	atom_op_jump, ATOM_COND_ALWAYSपूर्ण, अणु
	atom_op_jump, ATOM_COND_EQUALपूर्ण, अणु
	atom_op_jump, ATOM_COND_BELOWपूर्ण, अणु
	atom_op_jump, ATOM_COND_ABOVEपूर्ण, अणु
	atom_op_jump, ATOM_COND_BELOWOREQUALपूर्ण, अणु
	atom_op_jump, ATOM_COND_ABOVEOREQUALपूर्ण, अणु
	atom_op_jump, ATOM_COND_NOTEQUALपूर्ण, अणु
	atom_op_test, ATOM_ARG_REGपूर्ण, अणु
	atom_op_test, ATOM_ARG_PSपूर्ण, अणु
	atom_op_test, ATOM_ARG_WSपूर्ण, अणु
	atom_op_test, ATOM_ARG_FBपूर्ण, अणु
	atom_op_test, ATOM_ARG_PLLपूर्ण, अणु
	atom_op_test, ATOM_ARG_MCपूर्ण, अणु
	atom_op_delay, ATOM_UNIT_MILLISECपूर्ण, अणु
	atom_op_delay, ATOM_UNIT_MICROSECपूर्ण, अणु
	atom_op_calltable, 0पूर्ण, अणु
	atom_op_repeat, 0पूर्ण, अणु
	atom_op_clear, ATOM_ARG_REGपूर्ण, अणु
	atom_op_clear, ATOM_ARG_PSपूर्ण, अणु
	atom_op_clear, ATOM_ARG_WSपूर्ण, अणु
	atom_op_clear, ATOM_ARG_FBपूर्ण, अणु
	atom_op_clear, ATOM_ARG_PLLपूर्ण, अणु
	atom_op_clear, ATOM_ARG_MCपूर्ण, अणु
	atom_op_nop, 0पूर्ण, अणु
	atom_op_eot, 0पूर्ण, अणु
	atom_op_mask, ATOM_ARG_REGपूर्ण, अणु
	atom_op_mask, ATOM_ARG_PSपूर्ण, अणु
	atom_op_mask, ATOM_ARG_WSपूर्ण, अणु
	atom_op_mask, ATOM_ARG_FBपूर्ण, अणु
	atom_op_mask, ATOM_ARG_PLLपूर्ण, अणु
	atom_op_mask, ATOM_ARG_MCपूर्ण, अणु
	atom_op_postcard, 0पूर्ण, अणु
	atom_op_beep, 0पूर्ण, अणु
	atom_op_savereg, 0पूर्ण, अणु
	atom_op_restorereg, 0पूर्ण, अणु
	atom_op_setdatablock, 0पूर्ण, अणु
	atom_op_xor, ATOM_ARG_REGपूर्ण, अणु
	atom_op_xor, ATOM_ARG_PSपूर्ण, अणु
	atom_op_xor, ATOM_ARG_WSपूर्ण, अणु
	atom_op_xor, ATOM_ARG_FBपूर्ण, अणु
	atom_op_xor, ATOM_ARG_PLLपूर्ण, अणु
	atom_op_xor, ATOM_ARG_MCपूर्ण, अणु
	atom_op_shl, ATOM_ARG_REGपूर्ण, अणु
	atom_op_shl, ATOM_ARG_PSपूर्ण, अणु
	atom_op_shl, ATOM_ARG_WSपूर्ण, अणु
	atom_op_shl, ATOM_ARG_FBपूर्ण, अणु
	atom_op_shl, ATOM_ARG_PLLपूर्ण, अणु
	atom_op_shl, ATOM_ARG_MCपूर्ण, अणु
	atom_op_shr, ATOM_ARG_REGपूर्ण, अणु
	atom_op_shr, ATOM_ARG_PSपूर्ण, अणु
	atom_op_shr, ATOM_ARG_WSपूर्ण, अणु
	atom_op_shr, ATOM_ARG_FBपूर्ण, अणु
	atom_op_shr, ATOM_ARG_PLLपूर्ण, अणु
	atom_op_shr, ATOM_ARG_MCपूर्ण, अणु
	atom_op_debug, 0पूर्ण, अणु
	atom_op_processds, 0पूर्ण, अणु
	atom_op_mul32, ATOM_ARG_PSपूर्ण, अणु
	atom_op_mul32, ATOM_ARG_WSपूर्ण, अणु
	atom_op_भाग32, ATOM_ARG_PSपूर्ण, अणु
	atom_op_भाग32, ATOM_ARG_WSपूर्ण,
पूर्ण;

अटल पूर्णांक amdgpu_atom_execute_table_locked(काष्ठा atom_context *ctx, पूर्णांक index, uपूर्णांक32_t *params)
अणु
	पूर्णांक base = CU16(ctx->cmd_table + 4 + 2 * index);
	पूर्णांक len, ws, ps, ptr;
	अचिन्हित अक्षर op;
	atom_exec_context ectx;
	पूर्णांक ret = 0;

	अगर (!base)
		वापस -EINVAL;

	len = CU16(base + ATOM_CT_SIZE_PTR);
	ws = CU8(base + ATOM_CT_WS_PTR);
	ps = CU8(base + ATOM_CT_PS_PTR) & ATOM_CT_PS_MASK;
	ptr = base + ATOM_CT_CODE_PTR;

	SDEBUG(">> execute %04X (len %d, WS %d, PS %d)\n", base, len, ws, ps);

	ectx.ctx = ctx;
	ectx.ps_shअगरt = ps / 4;
	ectx.start = base;
	ectx.ps = params;
	ectx.पात = false;
	ectx.last_jump = 0;
	अगर (ws)
		ectx.ws = kसुस्मृति(4, ws, GFP_KERNEL);
	अन्यथा
		ectx.ws = शून्य;

	debug_depth++;
	जबतक (1) अणु
		op = CU8(ptr++);
		अगर (op < ATOM_OP_NAMES_CNT)
			SDEBUG("%s @ 0x%04X\n", atom_op_names[op], ptr - 1);
		अन्यथा
			SDEBUG("[%d] @ 0x%04X\n", op, ptr - 1);
		अगर (ectx.पात) अणु
			DRM_ERROR("atombios stuck executing %04X (len %d, WS %d, PS %d) @ 0x%04X\n",
				base, len, ws, ps, ptr - 1);
			ret = -EINVAL;
			जाओ मुक्त;
		पूर्ण

		अगर (op < ATOM_OP_CNT && op > 0)
			opcode_table[op].func(&ectx, &ptr,
					      opcode_table[op].arg);
		अन्यथा
			अवरोध;

		अगर (op == ATOM_OP_EOT)
			अवरोध;
	पूर्ण
	debug_depth--;
	SDEBUG("<<\n");

मुक्त:
	अगर (ws)
		kमुक्त(ectx.ws);
	वापस ret;
पूर्ण

पूर्णांक amdgpu_atom_execute_table(काष्ठा atom_context *ctx, पूर्णांक index, uपूर्णांक32_t *params)
अणु
	पूर्णांक r;

	mutex_lock(&ctx->mutex);
	/* reset data block */
	ctx->data_block = 0;
	/* reset reg block */
	ctx->reg_block = 0;
	/* reset fb winकरोw */
	ctx->fb_base = 0;
	/* reset io mode */
	ctx->io_mode = ATOM_IO_MM;
	/* reset भागmul */
	ctx->भागmul[0] = 0;
	ctx->भागmul[1] = 0;
	r = amdgpu_atom_execute_table_locked(ctx, index, params);
	mutex_unlock(&ctx->mutex);
	वापस r;
पूर्ण

अटल पूर्णांक atom_iio_len[] = अणु 1, 2, 3, 3, 3, 3, 4, 4, 4, 3 पूर्ण;

अटल व्योम atom_index_iio(काष्ठा atom_context *ctx, पूर्णांक base)
अणु
	ctx->iio = kzalloc(2 * 256, GFP_KERNEL);
	अगर (!ctx->iio)
		वापस;
	जबतक (CU8(base) == ATOM_IIO_START) अणु
		ctx->iio[CU8(base + 1)] = base + 2;
		base += 2;
		जबतक (CU8(base) != ATOM_IIO_END)
			base += atom_iio_len[CU8(base)];
		base += 3;
	पूर्ण
पूर्ण

काष्ठा atom_context *amdgpu_atom_parse(काष्ठा card_info *card, व्योम *bios)
अणु
	पूर्णांक base;
	काष्ठा atom_context *ctx =
	    kzalloc(माप(काष्ठा atom_context), GFP_KERNEL);
	अक्षर *str;
	u16 idx;

	अगर (!ctx)
		वापस शून्य;

	ctx->card = card;
	ctx->bios = bios;

	अगर (CU16(0) != ATOM_BIOS_MAGIC) अणु
		pr_info("Invalid BIOS magic\n");
		kमुक्त(ctx);
		वापस शून्य;
	पूर्ण
	अगर (म_भेदन
	    (CSTR(ATOM_ATI_MAGIC_PTR), ATOM_ATI_MAGIC,
	     म_माप(ATOM_ATI_MAGIC))) अणु
		pr_info("Invalid ATI magic\n");
		kमुक्त(ctx);
		वापस शून्य;
	पूर्ण

	base = CU16(ATOM_ROM_TABLE_PTR);
	अगर (म_भेदन
	    (CSTR(base + ATOM_ROM_MAGIC_PTR), ATOM_ROM_MAGIC,
	     म_माप(ATOM_ROM_MAGIC))) अणु
		pr_info("Invalid ATOM magic\n");
		kमुक्त(ctx);
		वापस शून्य;
	पूर्ण

	ctx->cmd_table = CU16(base + ATOM_ROM_CMD_PTR);
	ctx->data_table = CU16(base + ATOM_ROM_DATA_PTR);
	atom_index_iio(ctx, CU16(ctx->data_table + ATOM_DATA_IIO_PTR) + 4);
	अगर (!ctx->iio) अणु
		amdgpu_atom_destroy(ctx);
		वापस शून्य;
	पूर्ण

	idx = CU16(ATOM_ROM_PART_NUMBER_PTR);
	अगर (idx == 0)
		idx = 0x80;

	str = CSTR(idx);
	अगर (*str != '\0') अणु
		pr_info("ATOM BIOS: %s\n", str);
		strlcpy(ctx->vbios_version, str, माप(ctx->vbios_version));
	पूर्ण


	वापस ctx;
पूर्ण

पूर्णांक amdgpu_atom_asic_init(काष्ठा atom_context *ctx)
अणु
	पूर्णांक hwi = CU16(ctx->data_table + ATOM_DATA_FWI_PTR);
	uपूर्णांक32_t ps[16];
	पूर्णांक ret;

	स_रखो(ps, 0, 64);

	ps[0] = cpu_to_le32(CU32(hwi + ATOM_FWI_DEFSCLK_PTR));
	ps[1] = cpu_to_le32(CU32(hwi + ATOM_FWI_DEFMCLK_PTR));
	अगर (!ps[0] || !ps[1])
		वापस 1;

	अगर (!CU16(ctx->cmd_table + 4 + 2 * ATOM_CMD_INIT))
		वापस 1;
	ret = amdgpu_atom_execute_table(ctx, ATOM_CMD_INIT, ps);
	अगर (ret)
		वापस ret;

	स_रखो(ps, 0, 64);

	वापस ret;
पूर्ण

व्योम amdgpu_atom_destroy(काष्ठा atom_context *ctx)
अणु
	kमुक्त(ctx->iio);
	kमुक्त(ctx);
पूर्ण

bool amdgpu_atom_parse_data_header(काष्ठा atom_context *ctx, पूर्णांक index,
			    uपूर्णांक16_t *size, uपूर्णांक8_t *frev, uपूर्णांक8_t *crev,
			    uपूर्णांक16_t *data_start)
अणु
	पूर्णांक offset = index * 2 + 4;
	पूर्णांक idx = CU16(ctx->data_table + offset);
	u16 *mdt = (u16 *)(ctx->bios + ctx->data_table + 4);

	अगर (!mdt[index])
		वापस false;

	अगर (size)
		*size = CU16(idx);
	अगर (frev)
		*frev = CU8(idx + 2);
	अगर (crev)
		*crev = CU8(idx + 3);
	*data_start = idx;
	वापस true;
पूर्ण

bool amdgpu_atom_parse_cmd_header(काष्ठा atom_context *ctx, पूर्णांक index, uपूर्णांक8_t *frev,
			   uपूर्णांक8_t *crev)
अणु
	पूर्णांक offset = index * 2 + 4;
	पूर्णांक idx = CU16(ctx->cmd_table + offset);
	u16 *mct = (u16 *)(ctx->bios + ctx->cmd_table + 4);

	अगर (!mct[index])
		वापस false;

	अगर (frev)
		*frev = CU8(idx + 2);
	अगर (crev)
		*crev = CU8(idx + 3);
	वापस true;
पूर्ण

