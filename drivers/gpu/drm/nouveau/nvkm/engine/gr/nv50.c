<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
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
 * Authors: Ben Skeggs
 */
#समावेश "nv50.h"

#समावेश <core/client.h>
#समावेश <core/gpuobj.h>
#समावेश <engine/fअगरo.h>

#समावेश <nvअगर/class.h>

u64
nv50_gr_units(काष्ठा nvkm_gr *gr)
अणु
	वापस nvkm_rd32(gr->engine.subdev.device, 0x1540);
पूर्ण

/*******************************************************************************
 * Graphics object classes
 ******************************************************************************/

अटल पूर्णांक
nv50_gr_object_bind(काष्ठा nvkm_object *object, काष्ठा nvkm_gpuobj *parent,
		    पूर्णांक align, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	पूर्णांक ret = nvkm_gpuobj_new(object->engine->subdev.device, 16,
				  align, false, parent, pgpuobj);
	अगर (ret == 0) अणु
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x00, object->oclass);
		nvkm_wo32(*pgpuobj, 0x04, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x08, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x0c, 0x00000000);
		nvkm_करोne(*pgpuobj);
	पूर्ण
	वापस ret;
पूर्ण

स्थिर काष्ठा nvkm_object_func
nv50_gr_object = अणु
	.bind = nv50_gr_object_bind,
पूर्ण;

/*******************************************************************************
 * PGRAPH context
 ******************************************************************************/

अटल पूर्णांक
nv50_gr_chan_bind(काष्ठा nvkm_object *object, काष्ठा nvkm_gpuobj *parent,
		  पूर्णांक align, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	काष्ठा nv50_gr *gr = nv50_gr_chan(object)->gr;
	पूर्णांक ret = nvkm_gpuobj_new(gr->base.engine.subdev.device, gr->size,
				  align, true, parent, pgpuobj);
	अगर (ret == 0) अणु
		nvkm_kmap(*pgpuobj);
		nv50_grctx_fill(gr->base.engine.subdev.device, *pgpuobj);
		nvkm_करोne(*pgpuobj);
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nv50_gr_chan = अणु
	.bind = nv50_gr_chan_bind,
पूर्ण;

पूर्णांक
nv50_gr_chan_new(काष्ठा nvkm_gr *base, काष्ठा nvkm_fअगरo_chan *fअगरoch,
		 स्थिर काष्ठा nvkm_oclass *oclass, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nv50_gr *gr = nv50_gr(base);
	काष्ठा nv50_gr_chan *chan;

	अगर (!(chan = kzalloc(माप(*chan), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_object_ctor(&nv50_gr_chan, oclass, &chan->object);
	chan->gr = gr;
	*pobject = &chan->object;
	वापस 0;
पूर्ण

/*******************************************************************************
 * PGRAPH engine/subdev functions
 ******************************************************************************/

अटल स्थिर काष्ठा nvkm_bitfield nv50_mp_exec_errors[] = अणु
	अणु 0x01, "STACK_UNDERFLOW" पूर्ण,
	अणु 0x02, "STACK_MISMATCH" पूर्ण,
	अणु 0x04, "QUADON_ACTIVE" पूर्ण,
	अणु 0x08, "TIMEOUT" पूर्ण,
	अणु 0x10, "INVALID_OPCODE" पूर्ण,
	अणु 0x20, "PM_OVERFLOW" पूर्ण,
	अणु 0x40, "BREAKPOINT" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_bitfield nv50_mpc_traps[] = अणु
	अणु 0x0000001, "LOCAL_LIMIT_READ" पूर्ण,
	अणु 0x0000010, "LOCAL_LIMIT_WRITE" पूर्ण,
	अणु 0x0000040, "STACK_LIMIT" पूर्ण,
	अणु 0x0000100, "GLOBAL_LIMIT_READ" पूर्ण,
	अणु 0x0001000, "GLOBAL_LIMIT_WRITE" पूर्ण,
	अणु 0x0010000, "MP0" पूर्ण,
	अणु 0x0020000, "MP1" पूर्ण,
	अणु 0x0040000, "GLOBAL_LIMIT_RED" पूर्ण,
	अणु 0x0400000, "GLOBAL_LIMIT_ATOM" पूर्ण,
	अणु 0x4000000, "MP2" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_bitfield nv50_tex_traps[] = अणु
	अणु 0x00000001, "" पूर्ण, /* any bit set? */
	अणु 0x00000002, "FAULT" पूर्ण,
	अणु 0x00000004, "STORAGE_TYPE_MISMATCH" पूर्ण,
	अणु 0x00000008, "LINEAR_MISMATCH" पूर्ण,
	अणु 0x00000020, "WRONG_MEMTYPE" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_bitfield nv50_gr_trap_m2mf[] = अणु
	अणु 0x00000001, "NOTIFY" पूर्ण,
	अणु 0x00000002, "IN" पूर्ण,
	अणु 0x00000004, "OUT" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_bitfield nv50_gr_trap_vfetch[] = अणु
	अणु 0x00000001, "FAULT" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_bitfield nv50_gr_trap_strmout[] = अणु
	अणु 0x00000001, "FAULT" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_bitfield nv50_gr_trap_ccache[] = अणु
	अणु 0x00000001, "FAULT" पूर्ण,
	अणुपूर्ण
पूर्ण;

/* There must be a *lot* of these. Will take some समय to gather them up. */
स्थिर काष्ठा nvkm_क्रमागत nv50_data_error_names[] = अणु
	अणु 0x00000003, "INVALID_OPERATION", शून्य पूर्ण,
	अणु 0x00000004, "INVALID_VALUE", शून्य पूर्ण,
	अणु 0x00000005, "INVALID_ENUM", शून्य पूर्ण,
	अणु 0x00000008, "INVALID_OBJECT", शून्य पूर्ण,
	अणु 0x00000009, "READ_ONLY_OBJECT", शून्य पूर्ण,
	अणु 0x0000000a, "SUPERVISOR_OBJECT", शून्य पूर्ण,
	अणु 0x0000000b, "INVALID_ADDRESS_ALIGNMENT", शून्य पूर्ण,
	अणु 0x0000000c, "INVALID_BITFIELD", शून्य पूर्ण,
	अणु 0x0000000d, "BEGIN_END_ACTIVE", शून्य पूर्ण,
	अणु 0x0000000e, "SEMANTIC_COLOR_BACK_OVER_LIMIT", शून्य पूर्ण,
	अणु 0x0000000f, "VIEWPORT_ID_NEEDS_GP", शून्य पूर्ण,
	अणु 0x00000010, "RT_DOUBLE_BIND", शून्य पूर्ण,
	अणु 0x00000011, "RT_TYPES_MISMATCH", शून्य पूर्ण,
	अणु 0x00000012, "RT_LINEAR_WITH_ZETA", शून्य पूर्ण,
	अणु 0x00000015, "FP_TOO_FEW_REGS", शून्य पूर्ण,
	अणु 0x00000016, "ZETA_FORMAT_CSAA_MISMATCH", शून्य पूर्ण,
	अणु 0x00000017, "RT_LINEAR_WITH_MSAA", शून्य पूर्ण,
	अणु 0x00000018, "FP_INTERPOLANT_START_OVER_LIMIT", शून्य पूर्ण,
	अणु 0x00000019, "SEMANTIC_LAYER_OVER_LIMIT", शून्य पूर्ण,
	अणु 0x0000001a, "RT_INVALID_ALIGNMENT", शून्य पूर्ण,
	अणु 0x0000001b, "SAMPLER_OVER_LIMIT", शून्य पूर्ण,
	अणु 0x0000001c, "TEXTURE_OVER_LIMIT", शून्य पूर्ण,
	अणु 0x0000001e, "GP_TOO_MANY_OUTPUTS", शून्य पूर्ण,
	अणु 0x0000001f, "RT_BPP128_WITH_MS8", शून्य पूर्ण,
	अणु 0x00000021, "Z_OUT_OF_BOUNDS", शून्य पूर्ण,
	अणु 0x00000023, "XY_OUT_OF_BOUNDS", शून्य पूर्ण,
	अणु 0x00000024, "VP_ZERO_INPUTS", शून्य पूर्ण,
	अणु 0x00000027, "CP_MORE_PARAMS_THAN_SHARED", शून्य पूर्ण,
	अणु 0x00000028, "CP_NO_REG_SPACE_STRIPED", शून्य पूर्ण,
	अणु 0x00000029, "CP_NO_REG_SPACE_PACKED", शून्य पूर्ण,
	अणु 0x0000002a, "CP_NOT_ENOUGH_WARPS", शून्य पूर्ण,
	अणु 0x0000002b, "CP_BLOCK_SIZE_MISMATCH", शून्य पूर्ण,
	अणु 0x0000002c, "CP_NOT_ENOUGH_LOCAL_WARPS", शून्य पूर्ण,
	अणु 0x0000002d, "CP_NOT_ENOUGH_STACK_WARPS", शून्य पूर्ण,
	अणु 0x0000002e, "CP_NO_BLOCKDIM_LATCH", शून्य पूर्ण,
	अणु 0x00000031, "ENG2D_FORMAT_MISMATCH", शून्य पूर्ण,
	अणु 0x0000003f, "PRIMITIVE_ID_NEEDS_GP", शून्य पूर्ण,
	अणु 0x00000044, "SEMANTIC_VIEWPORT_OVER_LIMIT", शून्य पूर्ण,
	अणु 0x00000045, "SEMANTIC_COLOR_FRONT_OVER_LIMIT", शून्य पूर्ण,
	अणु 0x00000046, "LAYER_ID_NEEDS_GP", शून्य पूर्ण,
	अणु 0x00000047, "SEMANTIC_CLIP_OVER_LIMIT", शून्य पूर्ण,
	अणु 0x00000048, "SEMANTIC_PTSZ_OVER_LIMIT", शून्य पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_bitfield nv50_gr_पूर्णांकr_name[] = अणु
	अणु 0x00000001, "NOTIFY" पूर्ण,
	अणु 0x00000002, "COMPUTE_QUERY" पूर्ण,
	अणु 0x00000010, "ILLEGAL_MTHD" पूर्ण,
	अणु 0x00000020, "ILLEGAL_CLASS" पूर्ण,
	अणु 0x00000040, "DOUBLE_NOTIFY" पूर्ण,
	अणु 0x00001000, "CONTEXT_SWITCH" पूर्ण,
	अणु 0x00010000, "BUFFER_NOTIFY" पूर्ण,
	अणु 0x00100000, "DATA_ERROR" पूर्ण,
	अणु 0x00200000, "TRAP" पूर्ण,
	अणु 0x01000000, "SINGLE_STEP" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_bitfield nv50_gr_trap_prop[] = अणु
	अणु 0x00000004, "SURF_WIDTH_OVERRUN" पूर्ण,
	अणु 0x00000008, "SURF_HEIGHT_OVERRUN" पूर्ण,
	अणु 0x00000010, "DST2D_FAULT" पूर्ण,
	अणु 0x00000020, "ZETA_FAULT" पूर्ण,
	अणु 0x00000040, "RT_FAULT" पूर्ण,
	अणु 0x00000080, "CUDA_FAULT" पूर्ण,
	अणु 0x00000100, "DST2D_STORAGE_TYPE_MISMATCH" पूर्ण,
	अणु 0x00000200, "ZETA_STORAGE_TYPE_MISMATCH" पूर्ण,
	अणु 0x00000400, "RT_STORAGE_TYPE_MISMATCH" पूर्ण,
	अणु 0x00000800, "DST2D_LINEAR_MISMATCH" पूर्ण,
	अणु 0x00001000, "RT_LINEAR_MISMATCH" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम
nv50_gr_prop_trap(काष्ठा nv50_gr *gr, u32 ustatus_addr, u32 ustatus, u32 tp)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 e0c = nvkm_rd32(device, ustatus_addr + 0x04);
	u32 e10 = nvkm_rd32(device, ustatus_addr + 0x08);
	u32 e14 = nvkm_rd32(device, ustatus_addr + 0x0c);
	u32 e18 = nvkm_rd32(device, ustatus_addr + 0x10);
	u32 e1c = nvkm_rd32(device, ustatus_addr + 0x14);
	u32 e20 = nvkm_rd32(device, ustatus_addr + 0x18);
	u32 e24 = nvkm_rd32(device, ustatus_addr + 0x1c);
	अक्षर msg[128];

	/* CUDA memory: l[], g[] or stack. */
	अगर (ustatus & 0x00000080) अणु
		अगर (e18 & 0x80000000) अणु
			/* g[] पढ़ो fault? */
			nvkm_error(subdev, "TRAP_PROP - TP %d - CUDA_FAULT - Global read fault at address %02x%08x\n",
					 tp, e14, e10 | ((e18 >> 24) & 0x1f));
			e18 &= ~0x1f000000;
		पूर्ण अन्यथा अगर (e18 & 0xc) अणु
			/* g[] ग_लिखो fault? */
			nvkm_error(subdev, "TRAP_PROP - TP %d - CUDA_FAULT - Global write fault at address %02x%08x\n",
				 tp, e14, e10 | ((e18 >> 7) & 0x1f));
			e18 &= ~0x00000f80;
		पूर्ण अन्यथा अणु
			nvkm_error(subdev, "TRAP_PROP - TP %d - Unknown CUDA fault at address %02x%08x\n",
				 tp, e14, e10);
		पूर्ण
		ustatus &= ~0x00000080;
	पूर्ण
	अगर (ustatus) अणु
		nvkm_snprपूर्णांकbf(msg, माप(msg), nv50_gr_trap_prop, ustatus);
		nvkm_error(subdev, "TRAP_PROP - TP %d - %08x [%s] - "
				   "Address %02x%08x\n",
			   tp, ustatus, msg, e14, e10);
	पूर्ण
	nvkm_error(subdev, "TRAP_PROP - TP %d - e0c: %08x, e18: %08x, e1c: %08x, e20: %08x, e24: %08x\n",
		 tp, e0c, e18, e1c, e20, e24);
पूर्ण

अटल व्योम
nv50_gr_mp_trap(काष्ठा nv50_gr *gr, पूर्णांक tpid, पूर्णांक display)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 units = nvkm_rd32(device, 0x1540);
	u32 addr, mp10, status, pc, oplow, ophigh;
	अक्षर msg[128];
	पूर्णांक i;
	पूर्णांक mps = 0;
	क्रम (i = 0; i < 4; i++) अणु
		अगर (!(units & 1 << (i+24)))
			जारी;
		अगर (device->chipset < 0xa0)
			addr = 0x408200 + (tpid << 12) + (i << 7);
		अन्यथा
			addr = 0x408100 + (tpid << 11) + (i << 7);
		mp10 = nvkm_rd32(device, addr + 0x10);
		status = nvkm_rd32(device, addr + 0x14);
		अगर (!status)
			जारी;
		अगर (display) अणु
			nvkm_rd32(device, addr + 0x20);
			pc = nvkm_rd32(device, addr + 0x24);
			oplow = nvkm_rd32(device, addr + 0x70);
			ophigh = nvkm_rd32(device, addr + 0x74);
			nvkm_snprपूर्णांकbf(msg, माप(msg),
				       nv50_mp_exec_errors, status);
			nvkm_error(subdev, "TRAP_MP_EXEC - TP %d MP %d: "
					   "%08x [%s] at %06x warp %d, "
					   "opcode %08x %08x\n",
				   tpid, i, status, msg, pc & 0xffffff,
				   pc >> 24, oplow, ophigh);
		पूर्ण
		nvkm_wr32(device, addr + 0x10, mp10);
		nvkm_wr32(device, addr + 0x14, 0);
		mps++;
	पूर्ण
	अगर (!mps && display)
		nvkm_error(subdev, "TRAP_MP_EXEC - TP %d: "
				"No MPs claiming errors?\n", tpid);
पूर्ण

अटल व्योम
nv50_gr_tp_trap(काष्ठा nv50_gr *gr, पूर्णांक type, u32 ustatus_old,
		  u32 ustatus_new, पूर्णांक display, स्थिर अक्षर *name)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 units = nvkm_rd32(device, 0x1540);
	पूर्णांक tps = 0;
	पूर्णांक i, r;
	अक्षर msg[128];
	u32 ustatus_addr, ustatus;
	क्रम (i = 0; i < 16; i++) अणु
		अगर (!(units & (1 << i)))
			जारी;
		अगर (device->chipset < 0xa0)
			ustatus_addr = ustatus_old + (i << 12);
		अन्यथा
			ustatus_addr = ustatus_new + (i << 11);
		ustatus = nvkm_rd32(device, ustatus_addr) & 0x7fffffff;
		अगर (!ustatus)
			जारी;
		tps++;
		चयन (type) अणु
		हाल 6: /* texture error... unknown क्रम now */
			अगर (display) अणु
				nvkm_error(subdev, "magic set %d:\n", i);
				क्रम (r = ustatus_addr + 4; r <= ustatus_addr + 0x10; r += 4)
					nvkm_error(subdev, "\t%08x: %08x\n", r,
						   nvkm_rd32(device, r));
				अगर (ustatus) अणु
					nvkm_snprपूर्णांकbf(msg, माप(msg),
						       nv50_tex_traps, ustatus);
					nvkm_error(subdev,
						   "%s - TP%d: %08x [%s]\n",
						   name, i, ustatus, msg);
					ustatus = 0;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल 7: /* MP error */
			अगर (ustatus & 0x04030000) अणु
				nv50_gr_mp_trap(gr, i, display);
				ustatus &= ~0x04030000;
			पूर्ण
			अगर (ustatus && display) अणु
				nvkm_snprपूर्णांकbf(msg, माप(msg),
					       nv50_mpc_traps, ustatus);
				nvkm_error(subdev, "%s - TP%d: %08x [%s]\n",
					   name, i, ustatus, msg);
				ustatus = 0;
			पूर्ण
			अवरोध;
		हाल 8: /* PROP error */
			अगर (display)
				nv50_gr_prop_trap(
						gr, ustatus_addr, ustatus, i);
			ustatus = 0;
			अवरोध;
		पूर्ण
		अगर (ustatus) अणु
			अगर (display)
				nvkm_error(subdev, "%s - TP%d: Unhandled ustatus %08x\n", name, i, ustatus);
		पूर्ण
		nvkm_wr32(device, ustatus_addr, 0xc0000000);
	पूर्ण

	अगर (!tps && display)
		nvkm_warn(subdev, "%s - No TPs claiming errors?\n", name);
पूर्ण

अटल पूर्णांक
nv50_gr_trap_handler(काष्ठा nv50_gr *gr, u32 display,
		     पूर्णांक chid, u64 inst, स्थिर अक्षर *name)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 status = nvkm_rd32(device, 0x400108);
	u32 ustatus;
	अक्षर msg[128];

	अगर (!status && display) अणु
		nvkm_error(subdev, "TRAP: no units reporting traps?\n");
		वापस 1;
	पूर्ण

	/* DISPATCH: Relays commands to other units and handles NOTIFY,
	 * COND, QUERY. If you get a trap from it, the command is still stuck
	 * in DISPATCH and you need to करो something about it. */
	अगर (status & 0x001) अणु
		ustatus = nvkm_rd32(device, 0x400804) & 0x7fffffff;
		अगर (!ustatus && display) अणु
			nvkm_error(subdev, "TRAP_DISPATCH - no ustatus?\n");
		पूर्ण

		nvkm_wr32(device, 0x400500, 0x00000000);

		/* Known to be triggered by screwed up NOTIFY and COND... */
		अगर (ustatus & 0x00000001) अणु
			u32 addr = nvkm_rd32(device, 0x400808);
			u32 subc = (addr & 0x00070000) >> 16;
			u32 mthd = (addr & 0x00001ffc);
			u32 datal = nvkm_rd32(device, 0x40080c);
			u32 datah = nvkm_rd32(device, 0x400810);
			u32 class = nvkm_rd32(device, 0x400814);
			u32 r848 = nvkm_rd32(device, 0x400848);

			nvkm_error(subdev, "TRAP DISPATCH_FAULT\n");
			अगर (display && (addr & 0x80000000)) अणु
				nvkm_error(subdev,
					   "ch %d [%010llx %s] subc %d "
					   "class %04x mthd %04x data %08x%08x "
					   "400808 %08x 400848 %08x\n",
					   chid, inst, name, subc, class, mthd,
					   datah, datal, addr, r848);
			पूर्ण अन्यथा
			अगर (display) अणु
				nvkm_error(subdev, "no stuck command?\n");
			पूर्ण

			nvkm_wr32(device, 0x400808, 0);
			nvkm_wr32(device, 0x4008e8, nvkm_rd32(device, 0x4008e8) & 3);
			nvkm_wr32(device, 0x400848, 0);
			ustatus &= ~0x00000001;
		पूर्ण

		अगर (ustatus & 0x00000002) अणु
			u32 addr = nvkm_rd32(device, 0x40084c);
			u32 subc = (addr & 0x00070000) >> 16;
			u32 mthd = (addr & 0x00001ffc);
			u32 data = nvkm_rd32(device, 0x40085c);
			u32 class = nvkm_rd32(device, 0x400814);

			nvkm_error(subdev, "TRAP DISPATCH_QUERY\n");
			अगर (display && (addr & 0x80000000)) अणु
				nvkm_error(subdev,
					   "ch %d [%010llx %s] subc %d "
					   "class %04x mthd %04x data %08x "
					   "40084c %08x\n", chid, inst, name,
					   subc, class, mthd, data, addr);
			पूर्ण अन्यथा
			अगर (display) अणु
				nvkm_error(subdev, "no stuck command?\n");
			पूर्ण

			nvkm_wr32(device, 0x40084c, 0);
			ustatus &= ~0x00000002;
		पूर्ण

		अगर (ustatus && display) अणु
			nvkm_error(subdev, "TRAP_DISPATCH "
					   "(unknown %08x)\n", ustatus);
		पूर्ण

		nvkm_wr32(device, 0x400804, 0xc0000000);
		nvkm_wr32(device, 0x400108, 0x001);
		status &= ~0x001;
		अगर (!status)
			वापस 0;
	पूर्ण

	/* M2MF: Memory to memory copy engine. */
	अगर (status & 0x002) अणु
		u32 ustatus = nvkm_rd32(device, 0x406800) & 0x7fffffff;
		अगर (display) अणु
			nvkm_snprपूर्णांकbf(msg, माप(msg),
				       nv50_gr_trap_m2mf, ustatus);
			nvkm_error(subdev, "TRAP_M2MF %08x [%s]\n",
				   ustatus, msg);
			nvkm_error(subdev, "TRAP_M2MF %08x %08x %08x %08x\n",
				   nvkm_rd32(device, 0x406804),
				   nvkm_rd32(device, 0x406808),
				   nvkm_rd32(device, 0x40680c),
				   nvkm_rd32(device, 0x406810));
		पूर्ण

		/* No sane way found yet -- just reset the bugger. */
		nvkm_wr32(device, 0x400040, 2);
		nvkm_wr32(device, 0x400040, 0);
		nvkm_wr32(device, 0x406800, 0xc0000000);
		nvkm_wr32(device, 0x400108, 0x002);
		status &= ~0x002;
	पूर्ण

	/* VFETCH: Fetches data from vertex buffers. */
	अगर (status & 0x004) अणु
		u32 ustatus = nvkm_rd32(device, 0x400c04) & 0x7fffffff;
		अगर (display) अणु
			nvkm_snprपूर्णांकbf(msg, माप(msg),
				       nv50_gr_trap_vfetch, ustatus);
			nvkm_error(subdev, "TRAP_VFETCH %08x [%s]\n",
				   ustatus, msg);
			nvkm_error(subdev, "TRAP_VFETCH %08x %08x %08x %08x\n",
				   nvkm_rd32(device, 0x400c00),
				   nvkm_rd32(device, 0x400c08),
				   nvkm_rd32(device, 0x400c0c),
				   nvkm_rd32(device, 0x400c10));
		पूर्ण

		nvkm_wr32(device, 0x400c04, 0xc0000000);
		nvkm_wr32(device, 0x400108, 0x004);
		status &= ~0x004;
	पूर्ण

	/* STRMOUT: DirectX streamout / OpenGL transक्रमm feedback. */
	अगर (status & 0x008) अणु
		ustatus = nvkm_rd32(device, 0x401800) & 0x7fffffff;
		अगर (display) अणु
			nvkm_snprपूर्णांकbf(msg, माप(msg),
				       nv50_gr_trap_strmout, ustatus);
			nvkm_error(subdev, "TRAP_STRMOUT %08x [%s]\n",
				   ustatus, msg);
			nvkm_error(subdev, "TRAP_STRMOUT %08x %08x %08x %08x\n",
				   nvkm_rd32(device, 0x401804),
				   nvkm_rd32(device, 0x401808),
				   nvkm_rd32(device, 0x40180c),
				   nvkm_rd32(device, 0x401810));
		पूर्ण

		/* No sane way found yet -- just reset the bugger. */
		nvkm_wr32(device, 0x400040, 0x80);
		nvkm_wr32(device, 0x400040, 0);
		nvkm_wr32(device, 0x401800, 0xc0000000);
		nvkm_wr32(device, 0x400108, 0x008);
		status &= ~0x008;
	पूर्ण

	/* CCACHE: Handles code and c[] caches and fills them. */
	अगर (status & 0x010) अणु
		ustatus = nvkm_rd32(device, 0x405018) & 0x7fffffff;
		अगर (display) अणु
			nvkm_snprपूर्णांकbf(msg, माप(msg),
				       nv50_gr_trap_ccache, ustatus);
			nvkm_error(subdev, "TRAP_CCACHE %08x [%s]\n",
				   ustatus, msg);
			nvkm_error(subdev, "TRAP_CCACHE %08x %08x %08x %08x "
					   "%08x %08x %08x\n",
				   nvkm_rd32(device, 0x405000),
				   nvkm_rd32(device, 0x405004),
				   nvkm_rd32(device, 0x405008),
				   nvkm_rd32(device, 0x40500c),
				   nvkm_rd32(device, 0x405010),
				   nvkm_rd32(device, 0x405014),
				   nvkm_rd32(device, 0x40501c));
		पूर्ण

		nvkm_wr32(device, 0x405018, 0xc0000000);
		nvkm_wr32(device, 0x400108, 0x010);
		status &= ~0x010;
	पूर्ण

	/* Unknown, not seen yet... 0x402000 is the only trap status reg
	 * reमुख्यing, so try to handle it anyway. Perhaps related to that
	 * unknown DMA slot on tesla? */
	अगर (status & 0x20) अणु
		ustatus = nvkm_rd32(device, 0x402000) & 0x7fffffff;
		अगर (display)
			nvkm_error(subdev, "TRAP_UNKC04 %08x\n", ustatus);
		nvkm_wr32(device, 0x402000, 0xc0000000);
		/* no status modअगरiction on purpose */
	पूर्ण

	/* TEXTURE: CUDA texturing units */
	अगर (status & 0x040) अणु
		nv50_gr_tp_trap(gr, 6, 0x408900, 0x408600, display,
				    "TRAP_TEXTURE");
		nvkm_wr32(device, 0x400108, 0x040);
		status &= ~0x040;
	पूर्ण

	/* MP: CUDA execution engines. */
	अगर (status & 0x080) अणु
		nv50_gr_tp_trap(gr, 7, 0x408314, 0x40831c, display,
				    "TRAP_MP");
		nvkm_wr32(device, 0x400108, 0x080);
		status &= ~0x080;
	पूर्ण

	/* PROP:  Handles TP-initiated uncached memory accesses:
	 * l[], g[], stack, 2d surfaces, render tarमाला_लो. */
	अगर (status & 0x100) अणु
		nv50_gr_tp_trap(gr, 8, 0x408e08, 0x408708, display,
				    "TRAP_PROP");
		nvkm_wr32(device, 0x400108, 0x100);
		status &= ~0x100;
	पूर्ण

	अगर (status) अणु
		अगर (display)
			nvkm_error(subdev, "TRAP: unknown %08x\n", status);
		nvkm_wr32(device, 0x400108, status);
	पूर्ण

	वापस 1;
पूर्ण

व्योम
nv50_gr_पूर्णांकr(काष्ठा nvkm_gr *base)
अणु
	काष्ठा nv50_gr *gr = nv50_gr(base);
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_fअगरo_chan *chan;
	u32 stat = nvkm_rd32(device, 0x400100);
	u32 inst = nvkm_rd32(device, 0x40032c) & 0x0fffffff;
	u32 addr = nvkm_rd32(device, 0x400704);
	u32 subc = (addr & 0x00070000) >> 16;
	u32 mthd = (addr & 0x00001ffc);
	u32 data = nvkm_rd32(device, 0x400708);
	u32 class = nvkm_rd32(device, 0x400814);
	u32 show = stat, show_bitfield = stat;
	स्थिर काष्ठा nvkm_क्रमागत *en;
	अचिन्हित दीर्घ flags;
	स्थिर अक्षर *name = "unknown";
	अक्षर msg[128];
	पूर्णांक chid = -1;

	chan = nvkm_fअगरo_chan_inst(device->fअगरo, (u64)inst << 12, &flags);
	अगर (chan)  अणु
		name = chan->object.client->name;
		chid = chan->chid;
	पूर्ण

	अगर (show & 0x00100000) अणु
		u32 ecode = nvkm_rd32(device, 0x400110);
		en = nvkm_क्रमागत_find(nv50_data_error_names, ecode);
		nvkm_error(subdev, "DATA_ERROR %08x [%s]\n",
			   ecode, en ? en->name : "");
		show_bitfield &= ~0x00100000;
	पूर्ण

	अगर (stat & 0x00200000) अणु
		अगर (!nv50_gr_trap_handler(gr, show, chid, (u64)inst << 12, name))
			show &= ~0x00200000;
		show_bitfield &= ~0x00200000;
	पूर्ण

	nvkm_wr32(device, 0x400100, stat);
	nvkm_wr32(device, 0x400500, 0x00010001);

	अगर (show) अणु
		show &= show_bitfield;
		nvkm_snprपूर्णांकbf(msg, माप(msg), nv50_gr_पूर्णांकr_name, show);
		nvkm_error(subdev, "%08x [%s] ch %d [%010llx %s] subc %d "
				   "class %04x mthd %04x data %08x\n",
			   stat, msg, chid, (u64)inst << 12, name,
			   subc, class, mthd, data);
	पूर्ण

	अगर (nvkm_rd32(device, 0x400824) & (1 << 31))
		nvkm_wr32(device, 0x400824, nvkm_rd32(device, 0x400824) & ~(1 << 31));

	nvkm_fअगरo_chan_put(device->fअगरo, flags, &chan);
पूर्ण

पूर्णांक
nv50_gr_init(काष्ठा nvkm_gr *base)
अणु
	काष्ठा nv50_gr *gr = nv50_gr(base);
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	पूर्णांक ret, units, i;

	/* NV_PGRAPH_DEBUG_3_HW_CTX_SWITCH_ENABLED */
	nvkm_wr32(device, 0x40008c, 0x00000004);

	/* reset/enable traps and पूर्णांकerrupts */
	nvkm_wr32(device, 0x400804, 0xc0000000);
	nvkm_wr32(device, 0x406800, 0xc0000000);
	nvkm_wr32(device, 0x400c04, 0xc0000000);
	nvkm_wr32(device, 0x401800, 0xc0000000);
	nvkm_wr32(device, 0x405018, 0xc0000000);
	nvkm_wr32(device, 0x402000, 0xc0000000);

	units = nvkm_rd32(device, 0x001540);
	क्रम (i = 0; i < 16; i++) अणु
		अगर (!(units & (1 << i)))
			जारी;

		अगर (device->chipset < 0xa0) अणु
			nvkm_wr32(device, 0x408900 + (i << 12), 0xc0000000);
			nvkm_wr32(device, 0x408e08 + (i << 12), 0xc0000000);
			nvkm_wr32(device, 0x408314 + (i << 12), 0xc0000000);
		पूर्ण अन्यथा अणु
			nvkm_wr32(device, 0x408600 + (i << 11), 0xc0000000);
			nvkm_wr32(device, 0x408708 + (i << 11), 0xc0000000);
			nvkm_wr32(device, 0x40831c + (i << 11), 0xc0000000);
		पूर्ण
	पूर्ण

	nvkm_wr32(device, 0x400108, 0xffffffff);
	nvkm_wr32(device, 0x400138, 0xffffffff);
	nvkm_wr32(device, 0x400100, 0xffffffff);
	nvkm_wr32(device, 0x40013c, 0xffffffff);
	nvkm_wr32(device, 0x400500, 0x00010001);

	/* upload context program, initialise ctxctl शेषs */
	ret = nv50_grctx_init(device, &gr->size);
	अगर (ret)
		वापस ret;

	nvkm_wr32(device, 0x400824, 0x00000000);
	nvkm_wr32(device, 0x400828, 0x00000000);
	nvkm_wr32(device, 0x40082c, 0x00000000);
	nvkm_wr32(device, 0x400830, 0x00000000);
	nvkm_wr32(device, 0x40032c, 0x00000000);
	nvkm_wr32(device, 0x400330, 0x00000000);

	/* some unknown zcull magic */
	चयन (device->chipset & 0xf0) अणु
	हाल 0x50:
	हाल 0x80:
	हाल 0x90:
		nvkm_wr32(device, 0x402ca8, 0x00000800);
		अवरोध;
	हाल 0xa0:
	शेष:
		अगर (device->chipset == 0xa0 ||
		    device->chipset == 0xaa ||
		    device->chipset == 0xac) अणु
			nvkm_wr32(device, 0x402ca8, 0x00000802);
		पूर्ण अन्यथा अणु
			nvkm_wr32(device, 0x402cc0, 0x00000000);
			nvkm_wr32(device, 0x402ca8, 0x00000002);
		पूर्ण

		अवरोध;
	पूर्ण

	/* zero out zcull regions */
	क्रम (i = 0; i < 8; i++) अणु
		nvkm_wr32(device, 0x402c20 + (i * 0x10), 0x00000000);
		nvkm_wr32(device, 0x402c24 + (i * 0x10), 0x00000000);
		nvkm_wr32(device, 0x402c28 + (i * 0x10), 0x00000000);
		nvkm_wr32(device, 0x402c2c + (i * 0x10), 0x00000000);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
nv50_gr_new_(स्थिर काष्ठा nvkm_gr_func *func, काष्ठा nvkm_device *device,
	     क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	काष्ठा nv50_gr *gr;

	अगर (!(gr = kzalloc(माप(*gr), GFP_KERNEL)))
		वापस -ENOMEM;
	spin_lock_init(&gr->lock);
	*pgr = &gr->base;

	वापस nvkm_gr_ctor(func, device, type, inst, true, &gr->base);
पूर्ण

अटल स्थिर काष्ठा nvkm_gr_func
nv50_gr = अणु
	.init = nv50_gr_init,
	.पूर्णांकr = nv50_gr_पूर्णांकr,
	.chan_new = nv50_gr_chan_new,
	.units = nv50_gr_units,
	.sclass = अणु
		अणु -1, -1, NV_शून्य_CLASS, &nv50_gr_object पूर्ण,
		अणु -1, -1, NV50_TWOD, &nv50_gr_object पूर्ण,
		अणु -1, -1, NV50_MEMORY_TO_MEMORY_FORMAT, &nv50_gr_object पूर्ण,
		अणु -1, -1, NV50_TESLA, &nv50_gr_object पूर्ण,
		अणु -1, -1, NV50_COMPUTE, &nv50_gr_object पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv50_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस nv50_gr_new_(&nv50_gr, device, type, inst, pgr);
पूर्ण
