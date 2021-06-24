<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_GRCTX_H__
#घोषणा __NVKM_GRCTX_H__
#समावेश <core/gpuobj.h>

काष्ठा nvkm_grctx अणु
	काष्ठा nvkm_device *device;

	क्रमागत अणु
		NVKM_GRCTX_PROG,
		NVKM_GRCTX_VALS
	पूर्ण mode;
	u32 *ucode;
	काष्ठा nvkm_gpuobj *data;

	u32 ctxprog_max;
	u32 ctxprog_len;
	u32 ctxprog_reg;
	पूर्णांक ctxprog_label[32];
	u32 ctxvals_pos;
	u32 ctxvals_base;
पूर्ण;

अटल अंतरभूत व्योम
cp_out(काष्ठा nvkm_grctx *ctx, u32 inst)
अणु
	u32 *ctxprog = ctx->ucode;

	अगर (ctx->mode != NVKM_GRCTX_PROG)
		वापस;

	BUG_ON(ctx->ctxprog_len == ctx->ctxprog_max);
	ctxprog[ctx->ctxprog_len++] = inst;
पूर्ण

अटल अंतरभूत व्योम
cp_lsr(काष्ठा nvkm_grctx *ctx, u32 val)
अणु
	cp_out(ctx, CP_LOAD_SR | val);
पूर्ण

अटल अंतरभूत व्योम
cp_ctx(काष्ठा nvkm_grctx *ctx, u32 reg, u32 length)
अणु
	ctx->ctxprog_reg = (reg - 0x00400000) >> 2;

	ctx->ctxvals_base = ctx->ctxvals_pos;
	ctx->ctxvals_pos = ctx->ctxvals_base + length;

	अगर (length > (CP_CTX_COUNT >> CP_CTX_COUNT_SHIFT)) अणु
		cp_lsr(ctx, length);
		length = 0;
	पूर्ण

	cp_out(ctx, CP_CTX | (length << CP_CTX_COUNT_SHIFT) | ctx->ctxprog_reg);
पूर्ण

अटल अंतरभूत व्योम
cp_name(काष्ठा nvkm_grctx *ctx, पूर्णांक name)
अणु
	u32 *ctxprog = ctx->ucode;
	पूर्णांक i;

	अगर (ctx->mode != NVKM_GRCTX_PROG)
		वापस;

	ctx->ctxprog_label[name] = ctx->ctxprog_len;
	क्रम (i = 0; i < ctx->ctxprog_len; i++) अणु
		अगर ((ctxprog[i] & 0xfff00000) != 0xff400000)
			जारी;
		अगर ((ctxprog[i] & CP_BRA_IP) != ((name) << CP_BRA_IP_SHIFT))
			जारी;
		ctxprog[i] = (ctxprog[i] & 0x00ff00ff) |
			     (ctx->ctxprog_len << CP_BRA_IP_SHIFT);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
_cp_bra(काष्ठा nvkm_grctx *ctx, u32 mod, पूर्णांक flag, पूर्णांक state, पूर्णांक name)
अणु
	पूर्णांक ip = 0;

	अगर (mod != 2) अणु
		ip = ctx->ctxprog_label[name] << CP_BRA_IP_SHIFT;
		अगर (ip == 0)
			ip = 0xff000000 | (name << CP_BRA_IP_SHIFT);
	पूर्ण

	cp_out(ctx, CP_BRA | (mod << 18) | ip | flag |
		    (state ? 0 : CP_BRA_IF_CLEAR));
पूर्ण
#घोषणा cp_bra(c, f, s, n) _cp_bra((c), 0, CP_FLAG_##f, CP_FLAG_##f##_##s, n)
#घोषणा cp_cal(c, f, s, n) _cp_bra((c), 1, CP_FLAG_##f, CP_FLAG_##f##_##s, n)
#घोषणा cp_ret(c, f, s) _cp_bra((c), 2, CP_FLAG_##f, CP_FLAG_##f##_##s, 0)

अटल अंतरभूत व्योम
_cp_रुको(काष्ठा nvkm_grctx *ctx, पूर्णांक flag, पूर्णांक state)
अणु
	cp_out(ctx, CP_WAIT | flag | (state ? CP_WAIT_SET : 0));
पूर्ण
#घोषणा cp_रुको(c, f, s) _cp_रुको((c), CP_FLAG_##f, CP_FLAG_##f##_##s)

अटल अंतरभूत व्योम
_cp_set(काष्ठा nvkm_grctx *ctx, पूर्णांक flag, पूर्णांक state)
अणु
	cp_out(ctx, CP_SET | flag | (state ? CP_SET_1 : 0));
पूर्ण
#घोषणा cp_set(c, f, s) _cp_set((c), CP_FLAG_##f, CP_FLAG_##f##_##s)

अटल अंतरभूत व्योम
cp_pos(काष्ठा nvkm_grctx *ctx, पूर्णांक offset)
अणु
	ctx->ctxvals_pos = offset;
	ctx->ctxvals_base = ctx->ctxvals_pos;

	cp_lsr(ctx, ctx->ctxvals_pos);
	cp_out(ctx, CP_SET_CONTEXT_POINTER);
पूर्ण

अटल अंतरभूत व्योम
gr_def(काष्ठा nvkm_grctx *ctx, u32 reg, u32 val)
अणु
	अगर (ctx->mode != NVKM_GRCTX_VALS)
		वापस;

	reg = (reg - 0x00400000) / 4;
	reg = (reg - ctx->ctxprog_reg) + ctx->ctxvals_base;

	nvkm_wo32(ctx->data, reg * 4, val);
पूर्ण
#पूर्ण_अगर
