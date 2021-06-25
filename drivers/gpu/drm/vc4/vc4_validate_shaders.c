<शैली गुरु>
/*
 * Copyright तऊ 2014 Broadcom
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

/**
 * DOC: Shader validator क्रम VC4.
 *
 * Since the VC4 has no IOMMU between it and प्रणाली memory, a user
 * with access to execute shaders could escalate privilege by
 * overwriting प्रणाली memory (using the VPM ग_लिखो address रेजिस्टर in
 * the general-purpose DMA mode) or पढ़ोing प्रणाली memory it shouldn't
 * (पढ़ोing it as a texture, unअगरorm data, or direct-addressed TMU
 * lookup).
 *
 * The shader validator walks over a shader's BO, ensuring that its
 * accesses are appropriately bounded, and recording where texture
 * accesses are made so that we can करो relocations क्रम them in the
 * unअगरorm stream.
 *
 * Shader BO are immutable क्रम their lअगरeबार (enक्रमced by not
 * allowing mmaps, GEM prime export, or rendering to from a CL), so
 * this validation is only perक्रमmed at BO creation समय.
 */

#समावेश "vc4_drv.h"
#समावेश "vc4_qpu_defines.h"

#घोषणा LIVE_REG_COUNT (32 + 32 + 4)

काष्ठा vc4_shader_validation_state अणु
	/* Current IP being validated. */
	uपूर्णांक32_t ip;

	/* IP at the end of the BO, करो not पढ़ो shader[max_ip] */
	uपूर्णांक32_t max_ip;

	uपूर्णांक64_t *shader;

	काष्ठा vc4_texture_sample_info पंचांगu_setup[2];
	पूर्णांक पंचांगu_ग_लिखो_count[2];

	/* For रेजिस्टरs that were last written to by a MIN inकाष्ठाion with
	 * one argument being a unअगरorm, the address of the unअगरorm.
	 * Otherwise, ~0.
	 *
	 * This is used क्रम the validation of direct address memory पढ़ोs.
	 */
	uपूर्णांक32_t live_min_clamp_offsets[LIVE_REG_COUNT];
	bool live_max_clamp_regs[LIVE_REG_COUNT];
	uपूर्णांक32_t live_immediates[LIVE_REG_COUNT];

	/* Bitfield of which IPs are used as branch tarमाला_लो.
	 *
	 * Used क्रम validation that the unअगरorm stream is updated at the right
	 * poपूर्णांकs and clearing the texturing/clamping state.
	 */
	अचिन्हित दीर्घ *branch_tarमाला_लो;

	/* Set when entering a basic block, and cleared when the unअगरorm
	 * address update is found.  This is used to make sure that we करोn't
	 * पढ़ो unअगरorms when the address is undefined.
	 */
	bool needs_unअगरorm_address_update;

	/* Set when we find a backwards branch.  If the branch is backwards,
	 * the taraget is probably करोing an address reset to पढ़ो unअगरorms,
	 * and so we need to be sure that a unअगरorms address is present in the
	 * stream, even अगर the shader didn't need to पढ़ो unअगरorms in later
	 * basic blocks.
	 */
	bool needs_unअगरorm_address_क्रम_loop;

	/* Set when we find an inकाष्ठाion writing the top half of the
	 * रेजिस्टर files.  If we allowed writing the unusable regs in
	 * a thपढ़ोed shader, then the other shader running on our
	 * QPU's clamp validation would be invalid.
	 */
	bool all_रेजिस्टरs_used;
पूर्ण;

अटल uपूर्णांक32_t
waddr_to_live_reg_index(uपूर्णांक32_t waddr, bool is_b)
अणु
	अगर (waddr < 32) अणु
		अगर (is_b)
			वापस 32 + waddr;
		अन्यथा
			वापस waddr;
	पूर्ण अन्यथा अगर (waddr <= QPU_W_ACC3) अणु
		वापस 64 + waddr - QPU_W_ACC0;
	पूर्ण अन्यथा अणु
		वापस ~0;
	पूर्ण
पूर्ण

अटल uपूर्णांक32_t
raddr_add_a_to_live_reg_index(uपूर्णांक64_t inst)
अणु
	uपूर्णांक32_t sig = QPU_GET_FIELD(inst, QPU_SIG);
	uपूर्णांक32_t add_a = QPU_GET_FIELD(inst, QPU_ADD_A);
	uपूर्णांक32_t raddr_a = QPU_GET_FIELD(inst, QPU_RADDR_A);
	uपूर्णांक32_t raddr_b = QPU_GET_FIELD(inst, QPU_RADDR_B);

	अगर (add_a == QPU_MUX_A)
		वापस raddr_a;
	अन्यथा अगर (add_a == QPU_MUX_B && sig != QPU_SIG_SMALL_IMM)
		वापस 32 + raddr_b;
	अन्यथा अगर (add_a <= QPU_MUX_R3)
		वापस 64 + add_a;
	अन्यथा
		वापस ~0;
पूर्ण

अटल bool
live_reg_is_upper_half(uपूर्णांक32_t lri)
अणु
	वापस	(lri >= 16 && lri < 32) ||
		(lri >= 32 + 16 && lri < 32 + 32);
पूर्ण

अटल bool
is_पंचांगu_submit(uपूर्णांक32_t waddr)
अणु
	वापस (waddr == QPU_W_TMU0_S ||
		waddr == QPU_W_TMU1_S);
पूर्ण

अटल bool
is_पंचांगu_ग_लिखो(uपूर्णांक32_t waddr)
अणु
	वापस (waddr >= QPU_W_TMU0_S &&
		waddr <= QPU_W_TMU1_B);
पूर्ण

अटल bool
record_texture_sample(काष्ठा vc4_validated_shader_info *validated_shader,
		      काष्ठा vc4_shader_validation_state *validation_state,
		      पूर्णांक पंचांगu)
अणु
	uपूर्णांक32_t s = validated_shader->num_texture_samples;
	पूर्णांक i;
	काष्ठा vc4_texture_sample_info *temp_samples;

	temp_samples = kपुनः_स्मृति(validated_shader->texture_samples,
				(s + 1) * माप(*temp_samples),
				GFP_KERNEL);
	अगर (!temp_samples)
		वापस false;

	स_नकल(&temp_samples[s],
	       &validation_state->पंचांगu_setup[पंचांगu],
	       माप(*temp_samples));

	validated_shader->num_texture_samples = s + 1;
	validated_shader->texture_samples = temp_samples;

	क्रम (i = 0; i < 4; i++)
		validation_state->पंचांगu_setup[पंचांगu].p_offset[i] = ~0;

	वापस true;
पूर्ण

अटल bool
check_पंचांगu_ग_लिखो(काष्ठा vc4_validated_shader_info *validated_shader,
		काष्ठा vc4_shader_validation_state *validation_state,
		bool is_mul)
अणु
	uपूर्णांक64_t inst = validation_state->shader[validation_state->ip];
	uपूर्णांक32_t waddr = (is_mul ?
			  QPU_GET_FIELD(inst, QPU_WADDR_MUL) :
			  QPU_GET_FIELD(inst, QPU_WADDR_ADD));
	uपूर्णांक32_t raddr_a = QPU_GET_FIELD(inst, QPU_RADDR_A);
	uपूर्णांक32_t raddr_b = QPU_GET_FIELD(inst, QPU_RADDR_B);
	पूर्णांक पंचांगu = waddr > QPU_W_TMU0_B;
	bool submit = is_पंचांगu_submit(waddr);
	bool is_direct = submit && validation_state->पंचांगu_ग_लिखो_count[पंचांगu] == 0;
	uपूर्णांक32_t sig = QPU_GET_FIELD(inst, QPU_SIG);

	अगर (is_direct) अणु
		uपूर्णांक32_t add_b = QPU_GET_FIELD(inst, QPU_ADD_B);
		uपूर्णांक32_t clamp_reg, clamp_offset;

		अगर (sig == QPU_SIG_SMALL_IMM) अणु
			DRM_DEBUG("direct TMU read used small immediate\n");
			वापस false;
		पूर्ण

		/* Make sure that this texture load is an add of the base
		 * address of the UBO to a clamped offset within the UBO.
		 */
		अगर (is_mul ||
		    QPU_GET_FIELD(inst, QPU_OP_ADD) != QPU_A_ADD) अणु
			DRM_DEBUG("direct TMU load wasn't an add\n");
			वापस false;
		पूर्ण

		/* We निश्चित that the clamped address is the first
		 * argument, and the UBO base address is the second argument.
		 * This is arbitrary, but simpler than supporting flipping the
		 * two either way.
		 */
		clamp_reg = raddr_add_a_to_live_reg_index(inst);
		अगर (clamp_reg == ~0) अणु
			DRM_DEBUG("direct TMU load wasn't clamped\n");
			वापस false;
		पूर्ण

		clamp_offset = validation_state->live_min_clamp_offsets[clamp_reg];
		अगर (clamp_offset == ~0) अणु
			DRM_DEBUG("direct TMU load wasn't clamped\n");
			वापस false;
		पूर्ण

		/* Store the clamp value's offset in p1 (see reloc_tex() in
		 * vc4_validate.c).
		 */
		validation_state->पंचांगu_setup[पंचांगu].p_offset[1] =
			clamp_offset;

		अगर (!(add_b == QPU_MUX_A && raddr_a == QPU_R_UNIF) &&
		    !(add_b == QPU_MUX_B && raddr_b == QPU_R_UNIF)) अणु
			DRM_DEBUG("direct TMU load didn't add to a uniform\n");
			वापस false;
		पूर्ण

		validation_state->पंचांगu_setup[पंचांगu].is_direct = true;
	पूर्ण अन्यथा अणु
		अगर (raddr_a == QPU_R_UNIF || (sig != QPU_SIG_SMALL_IMM &&
					      raddr_b == QPU_R_UNIF)) अणु
			DRM_DEBUG("uniform read in the same instruction as "
				  "texture setup.\n");
			वापस false;
		पूर्ण
	पूर्ण

	अगर (validation_state->पंचांगu_ग_लिखो_count[पंचांगu] >= 4) अणु
		DRM_DEBUG("TMU%d got too many parameters before dispatch\n",
			  पंचांगu);
		वापस false;
	पूर्ण
	validation_state->पंचांगu_setup[पंचांगu].p_offset[validation_state->पंचांगu_ग_लिखो_count[पंचांगu]] =
		validated_shader->unअगरorms_size;
	validation_state->पंचांगu_ग_लिखो_count[पंचांगu]++;
	/* Since direct uses a RADDR unअगरorm reference, it will get counted in
	 * check_inकाष्ठाion_पढ़ोs()
	 */
	अगर (!is_direct) अणु
		अगर (validation_state->needs_unअगरorm_address_update) अणु
			DRM_DEBUG("Texturing with undefined uniform address\n");
			वापस false;
		पूर्ण

		validated_shader->unअगरorms_size += 4;
	पूर्ण

	अगर (submit) अणु
		अगर (!record_texture_sample(validated_shader,
					   validation_state, पंचांगu)) अणु
			वापस false;
		पूर्ण

		validation_state->पंचांगu_ग_लिखो_count[पंचांगu] = 0;
	पूर्ण

	वापस true;
पूर्ण

अटल bool require_unअगरorm_address_unअगरorm(काष्ठा vc4_validated_shader_info *validated_shader)
अणु
	uपूर्णांक32_t o = validated_shader->num_unअगरorm_addr_offsets;
	uपूर्णांक32_t num_unअगरorms = validated_shader->unअगरorms_size / 4;

	validated_shader->unअगरorm_addr_offsets =
		kपुनः_स्मृति(validated_shader->unअगरorm_addr_offsets,
			 (o + 1) *
			 माप(*validated_shader->unअगरorm_addr_offsets),
			 GFP_KERNEL);
	अगर (!validated_shader->unअगरorm_addr_offsets)
		वापस false;

	validated_shader->unअगरorm_addr_offsets[o] = num_unअगरorms;
	validated_shader->num_unअगरorm_addr_offsets++;

	वापस true;
पूर्ण

अटल bool
validate_unअगरorm_address_ग_लिखो(काष्ठा vc4_validated_shader_info *validated_shader,
			       काष्ठा vc4_shader_validation_state *validation_state,
			       bool is_mul)
अणु
	uपूर्णांक64_t inst = validation_state->shader[validation_state->ip];
	u32 add_b = QPU_GET_FIELD(inst, QPU_ADD_B);
	u32 raddr_a = QPU_GET_FIELD(inst, QPU_RADDR_A);
	u32 raddr_b = QPU_GET_FIELD(inst, QPU_RADDR_B);
	u32 add_lri = raddr_add_a_to_live_reg_index(inst);
	/* We want our reset to be poपूर्णांकing at whatever unअगरorm follows the
	 * unअगरorms base address.
	 */
	u32 expected_offset = validated_shader->unअगरorms_size + 4;

	/* We only support असलolute unअगरorm address changes, and we
	 * require that they be in the current basic block beक्रमe any
	 * of its unअगरorm पढ़ोs.
	 *
	 * One could potentially emit more efficient QPU code, by
	 * noticing that (say) an अगर statement करोes unअगरorm control
	 * flow क्रम all thपढ़ोs and that the अगर पढ़ोs the same number
	 * of unअगरorms on each side.  However, this scheme is easy to
	 * validate so it's all we allow क्रम now.
	 */
	चयन (QPU_GET_FIELD(inst, QPU_SIG)) अणु
	हाल QPU_SIG_NONE:
	हाल QPU_SIG_SCOREBOARD_UNLOCK:
	हाल QPU_SIG_COLOR_LOAD:
	हाल QPU_SIG_LOAD_TMU0:
	हाल QPU_SIG_LOAD_TMU1:
		अवरोध;
	शेष:
		DRM_DEBUG("uniforms address change must be "
			  "normal math\n");
		वापस false;
	पूर्ण

	अगर (is_mul || QPU_GET_FIELD(inst, QPU_OP_ADD) != QPU_A_ADD) अणु
		DRM_DEBUG("Uniform address reset must be an ADD.\n");
		वापस false;
	पूर्ण

	अगर (QPU_GET_FIELD(inst, QPU_COND_ADD) != QPU_COND_ALWAYS) अणु
		DRM_DEBUG("Uniform address reset must be unconditional.\n");
		वापस false;
	पूर्ण

	अगर (QPU_GET_FIELD(inst, QPU_PACK) != QPU_PACK_A_NOP &&
	    !(inst & QPU_PM)) अणु
		DRM_DEBUG("No packing allowed on uniforms reset\n");
		वापस false;
	पूर्ण

	अगर (add_lri == -1) अणु
		DRM_DEBUG("First argument of uniform address write must be "
			  "an immediate value.\n");
		वापस false;
	पूर्ण

	अगर (validation_state->live_immediates[add_lri] != expected_offset) अणु
		DRM_DEBUG("Resetting uniforms with offset %db instead of %db\n",
			  validation_state->live_immediates[add_lri],
			  expected_offset);
		वापस false;
	पूर्ण

	अगर (!(add_b == QPU_MUX_A && raddr_a == QPU_R_UNIF) &&
	    !(add_b == QPU_MUX_B && raddr_b == QPU_R_UNIF)) अणु
		DRM_DEBUG("Second argument of uniform address write must be "
			  "a uniform.\n");
		वापस false;
	पूर्ण

	validation_state->needs_unअगरorm_address_update = false;
	validation_state->needs_unअगरorm_address_क्रम_loop = false;
	वापस require_unअगरorm_address_unअगरorm(validated_shader);
पूर्ण

अटल bool
check_reg_ग_लिखो(काष्ठा vc4_validated_shader_info *validated_shader,
		काष्ठा vc4_shader_validation_state *validation_state,
		bool is_mul)
अणु
	uपूर्णांक64_t inst = validation_state->shader[validation_state->ip];
	uपूर्णांक32_t waddr = (is_mul ?
			  QPU_GET_FIELD(inst, QPU_WADDR_MUL) :
			  QPU_GET_FIELD(inst, QPU_WADDR_ADD));
	uपूर्णांक32_t sig = QPU_GET_FIELD(inst, QPU_SIG);
	bool ws = inst & QPU_WS;
	bool is_b = is_mul ^ ws;
	u32 lri = waddr_to_live_reg_index(waddr, is_b);

	अगर (lri != -1) अणु
		uपूर्णांक32_t cond_add = QPU_GET_FIELD(inst, QPU_COND_ADD);
		uपूर्णांक32_t cond_mul = QPU_GET_FIELD(inst, QPU_COND_MUL);

		अगर (sig == QPU_SIG_LOAD_IMM &&
		    QPU_GET_FIELD(inst, QPU_PACK) == QPU_PACK_A_NOP &&
		    ((is_mul && cond_mul == QPU_COND_ALWAYS) ||
		     (!is_mul && cond_add == QPU_COND_ALWAYS))) अणु
			validation_state->live_immediates[lri] =
				QPU_GET_FIELD(inst, QPU_LOAD_IMM);
		पूर्ण अन्यथा अणु
			validation_state->live_immediates[lri] = ~0;
		पूर्ण

		अगर (live_reg_is_upper_half(lri))
			validation_state->all_रेजिस्टरs_used = true;
	पूर्ण

	चयन (waddr) अणु
	हाल QPU_W_UNIFORMS_ADDRESS:
		अगर (is_b) अणु
			DRM_DEBUG("relative uniforms address change "
				  "unsupported\n");
			वापस false;
		पूर्ण

		वापस validate_unअगरorm_address_ग_लिखो(validated_shader,
						      validation_state,
						      is_mul);

	हाल QPU_W_TLB_COLOR_MS:
	हाल QPU_W_TLB_COLOR_ALL:
	हाल QPU_W_TLB_Z:
		/* These only पूर्णांकeract with the tile buffer, not मुख्य memory,
		 * so they're safe.
		 */
		वापस true;

	हाल QPU_W_TMU0_S:
	हाल QPU_W_TMU0_T:
	हाल QPU_W_TMU0_R:
	हाल QPU_W_TMU0_B:
	हाल QPU_W_TMU1_S:
	हाल QPU_W_TMU1_T:
	हाल QPU_W_TMU1_R:
	हाल QPU_W_TMU1_B:
		वापस check_पंचांगu_ग_लिखो(validated_shader, validation_state,
				       is_mul);

	हाल QPU_W_HOST_INT:
	हाल QPU_W_TMU_NOSWAP:
	हाल QPU_W_TLB_ALPHA_MASK:
	हाल QPU_W_MUTEX_RELEASE:
		/* XXX: I haven't thought about these, so don't support them
		 * क्रम now.
		 */
		DRM_DEBUG("Unsupported waddr %d\n", waddr);
		वापस false;

	हाल QPU_W_VPM_ADDR:
		DRM_DEBUG("General VPM DMA unsupported\n");
		वापस false;

	हाल QPU_W_VPM:
	हाल QPU_W_VPMVCD_SETUP:
		/* We allow VPM setup in general, even including VPM DMA
		 * configuration setup, because the (unsafe) DMA can only be
		 * triggered by QPU_W_VPM_ADDR ग_लिखोs.
		 */
		वापस true;

	हाल QPU_W_TLB_STENCIL_SETUP:
		वापस true;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम
track_live_clamps(काष्ठा vc4_validated_shader_info *validated_shader,
		  काष्ठा vc4_shader_validation_state *validation_state)
अणु
	uपूर्णांक64_t inst = validation_state->shader[validation_state->ip];
	uपूर्णांक32_t op_add = QPU_GET_FIELD(inst, QPU_OP_ADD);
	uपूर्णांक32_t waddr_add = QPU_GET_FIELD(inst, QPU_WADDR_ADD);
	uपूर्णांक32_t waddr_mul = QPU_GET_FIELD(inst, QPU_WADDR_MUL);
	uपूर्णांक32_t cond_add = QPU_GET_FIELD(inst, QPU_COND_ADD);
	uपूर्णांक32_t add_a = QPU_GET_FIELD(inst, QPU_ADD_A);
	uपूर्णांक32_t add_b = QPU_GET_FIELD(inst, QPU_ADD_B);
	uपूर्णांक32_t raddr_a = QPU_GET_FIELD(inst, QPU_RADDR_A);
	uपूर्णांक32_t raddr_b = QPU_GET_FIELD(inst, QPU_RADDR_B);
	uपूर्णांक32_t sig = QPU_GET_FIELD(inst, QPU_SIG);
	bool ws = inst & QPU_WS;
	uपूर्णांक32_t lri_add_a, lri_add, lri_mul;
	bool add_a_is_min_0;

	/* Check whether OP_ADD's A argumennt comes from a live MAX(x, 0),
	 * beक्रमe we clear previous live state.
	 */
	lri_add_a = raddr_add_a_to_live_reg_index(inst);
	add_a_is_min_0 = (lri_add_a != ~0 &&
			  validation_state->live_max_clamp_regs[lri_add_a]);

	/* Clear live state क्रम रेजिस्टरs written by our inकाष्ठाion. */
	lri_add = waddr_to_live_reg_index(waddr_add, ws);
	lri_mul = waddr_to_live_reg_index(waddr_mul, !ws);
	अगर (lri_mul != ~0) अणु
		validation_state->live_max_clamp_regs[lri_mul] = false;
		validation_state->live_min_clamp_offsets[lri_mul] = ~0;
	पूर्ण
	अगर (lri_add != ~0) अणु
		validation_state->live_max_clamp_regs[lri_add] = false;
		validation_state->live_min_clamp_offsets[lri_add] = ~0;
	पूर्ण अन्यथा अणु
		/* Nothing further to करो क्रम live tracking, since only ADDs
		 * generate new live clamp रेजिस्टरs.
		 */
		वापस;
	पूर्ण

	/* Now, handle reमुख्यing live clamp tracking क्रम the ADD operation. */

	अगर (cond_add != QPU_COND_ALWAYS)
		वापस;

	अगर (op_add == QPU_A_MAX) अणु
		/* Track live clamps of a value to a minimum of 0 (in either
		 * arg).
		 */
		अगर (sig != QPU_SIG_SMALL_IMM || raddr_b != 0 ||
		    (add_a != QPU_MUX_B && add_b != QPU_MUX_B)) अणु
			वापस;
		पूर्ण

		validation_state->live_max_clamp_regs[lri_add] = true;
	पूर्ण अन्यथा अगर (op_add == QPU_A_MIN) अणु
		/* Track live clamps of a value clamped to a minimum of 0 and
		 * a maximum of some unअगरorm's offset.
		 */
		अगर (!add_a_is_min_0)
			वापस;

		अगर (!(add_b == QPU_MUX_A && raddr_a == QPU_R_UNIF) &&
		    !(add_b == QPU_MUX_B && raddr_b == QPU_R_UNIF &&
		      sig != QPU_SIG_SMALL_IMM)) अणु
			वापस;
		पूर्ण

		validation_state->live_min_clamp_offsets[lri_add] =
			validated_shader->unअगरorms_size;
	पूर्ण
पूर्ण

अटल bool
check_inकाष्ठाion_ग_लिखोs(काष्ठा vc4_validated_shader_info *validated_shader,
			 काष्ठा vc4_shader_validation_state *validation_state)
अणु
	uपूर्णांक64_t inst = validation_state->shader[validation_state->ip];
	uपूर्णांक32_t waddr_add = QPU_GET_FIELD(inst, QPU_WADDR_ADD);
	uपूर्णांक32_t waddr_mul = QPU_GET_FIELD(inst, QPU_WADDR_MUL);
	bool ok;

	अगर (is_पंचांगu_ग_लिखो(waddr_add) && is_पंचांगu_ग_लिखो(waddr_mul)) अणु
		DRM_DEBUG("ADD and MUL both set up textures\n");
		वापस false;
	पूर्ण

	ok = (check_reg_ग_लिखो(validated_shader, validation_state, false) &&
	      check_reg_ग_लिखो(validated_shader, validation_state, true));

	track_live_clamps(validated_shader, validation_state);

	वापस ok;
पूर्ण

अटल bool
check_branch(uपूर्णांक64_t inst,
	     काष्ठा vc4_validated_shader_info *validated_shader,
	     काष्ठा vc4_shader_validation_state *validation_state,
	     पूर्णांक ip)
अणु
	पूर्णांक32_t branch_imm = QPU_GET_FIELD(inst, QPU_BRANCH_TARGET);
	uपूर्णांक32_t waddr_add = QPU_GET_FIELD(inst, QPU_WADDR_ADD);
	uपूर्णांक32_t waddr_mul = QPU_GET_FIELD(inst, QPU_WADDR_MUL);

	अगर ((पूर्णांक)branch_imm < 0)
		validation_state->needs_unअगरorm_address_क्रम_loop = true;

	/* We करोn't want to have to worry about validation of this, and
	 * there's no need क्रम it.
	 */
	अगर (waddr_add != QPU_W_NOP || waddr_mul != QPU_W_NOP) अणु
		DRM_DEBUG("branch instruction at %d wrote a register.\n",
			  validation_state->ip);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool
check_inकाष्ठाion_पढ़ोs(काष्ठा vc4_validated_shader_info *validated_shader,
			काष्ठा vc4_shader_validation_state *validation_state)
अणु
	uपूर्णांक64_t inst = validation_state->shader[validation_state->ip];
	uपूर्णांक32_t raddr_a = QPU_GET_FIELD(inst, QPU_RADDR_A);
	uपूर्णांक32_t raddr_b = QPU_GET_FIELD(inst, QPU_RADDR_B);
	uपूर्णांक32_t sig = QPU_GET_FIELD(inst, QPU_SIG);

	अगर (raddr_a == QPU_R_UNIF ||
	    (raddr_b == QPU_R_UNIF && sig != QPU_SIG_SMALL_IMM)) अणु
		/* This can't overflow the uint32_t, because we're पढ़ोing 8
		 * bytes of inकाष्ठाion to increment by 4 here, so we'd
		 * alपढ़ोy be OOM.
		 */
		validated_shader->unअगरorms_size += 4;

		अगर (validation_state->needs_unअगरorm_address_update) अणु
			DRM_DEBUG("Uniform read with undefined uniform "
				  "address\n");
			वापस false;
		पूर्ण
	पूर्ण

	अगर ((raddr_a >= 16 && raddr_a < 32) ||
	    (raddr_b >= 16 && raddr_b < 32 && sig != QPU_SIG_SMALL_IMM)) अणु
		validation_state->all_रेजिस्टरs_used = true;
	पूर्ण

	वापस true;
पूर्ण

/* Make sure that all branches are असलolute and poपूर्णांक within the shader, and
 * note their tarमाला_लो क्रम later.
 */
अटल bool
vc4_validate_branches(काष्ठा vc4_shader_validation_state *validation_state)
अणु
	uपूर्णांक32_t max_branch_target = 0;
	पूर्णांक ip;
	पूर्णांक last_branch = -2;

	क्रम (ip = 0; ip < validation_state->max_ip; ip++) अणु
		uपूर्णांक64_t inst = validation_state->shader[ip];
		पूर्णांक32_t branch_imm = QPU_GET_FIELD(inst, QPU_BRANCH_TARGET);
		uपूर्णांक32_t sig = QPU_GET_FIELD(inst, QPU_SIG);
		uपूर्णांक32_t after_delay_ip = ip + 4;
		uपूर्णांक32_t branch_target_ip;

		अगर (sig == QPU_SIG_PROG_END) अणु
			/* There are two delay slots after program end is
			 * संकेतed that are still executed, then we're
			 * finished.  validation_state->max_ip is the
			 * inकाष्ठाion after the last valid inकाष्ठाion in the
			 * program.
			 */
			validation_state->max_ip = ip + 3;
			जारी;
		पूर्ण

		अगर (sig != QPU_SIG_BRANCH)
			जारी;

		अगर (ip - last_branch < 4) अणु
			DRM_DEBUG("Branch at %d during delay slots\n", ip);
			वापस false;
		पूर्ण
		last_branch = ip;

		अगर (inst & QPU_BRANCH_REG) अणु
			DRM_DEBUG("branching from register relative "
				  "not supported\n");
			वापस false;
		पूर्ण

		अगर (!(inst & QPU_BRANCH_REL)) अणु
			DRM_DEBUG("relative branching required\n");
			वापस false;
		पूर्ण

		/* The actual branch target is the inकाष्ठाion after the delay
		 * slots, plus whatever byte offset is in the low 32 bits of
		 * the inकाष्ठाion.  Make sure we're not branching beyond the
		 * end of the shader object.
		 */
		अगर (branch_imm % माप(inst) != 0) अणु
			DRM_DEBUG("branch target not aligned\n");
			वापस false;
		पूर्ण

		branch_target_ip = after_delay_ip + (branch_imm >> 3);
		अगर (branch_target_ip >= validation_state->max_ip) अणु
			DRM_DEBUG("Branch at %d outside of shader (ip %d/%d)\n",
				  ip, branch_target_ip,
				  validation_state->max_ip);
			वापस false;
		पूर्ण
		set_bit(branch_target_ip, validation_state->branch_tarमाला_लो);

		/* Make sure that the non-branching path is also not outside
		 * the shader.
		 */
		अगर (after_delay_ip >= validation_state->max_ip) अणु
			DRM_DEBUG("Branch at %d continues past shader end "
				  "(%d/%d)\n",
				  ip, after_delay_ip, validation_state->max_ip);
			वापस false;
		पूर्ण
		set_bit(after_delay_ip, validation_state->branch_tarमाला_लो);
		max_branch_target = max(max_branch_target, after_delay_ip);
	पूर्ण

	अगर (max_branch_target > validation_state->max_ip - 3) अणु
		DRM_DEBUG("Branch landed after QPU_SIG_PROG_END");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* Resets any known state क्रम the shader, used when we may be branched to from
 * multiple locations in the program (or at shader start).
 */
अटल व्योम
reset_validation_state(काष्ठा vc4_shader_validation_state *validation_state)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++)
		validation_state->पंचांगu_setup[i / 4].p_offset[i % 4] = ~0;

	क्रम (i = 0; i < LIVE_REG_COUNT; i++) अणु
		validation_state->live_min_clamp_offsets[i] = ~0;
		validation_state->live_max_clamp_regs[i] = false;
		validation_state->live_immediates[i] = ~0;
	पूर्ण
पूर्ण

अटल bool
texturing_in_progress(काष्ठा vc4_shader_validation_state *validation_state)
अणु
	वापस (validation_state->पंचांगu_ग_लिखो_count[0] != 0 ||
		validation_state->पंचांगu_ग_लिखो_count[1] != 0);
पूर्ण

अटल bool
vc4_handle_branch_target(काष्ठा vc4_shader_validation_state *validation_state)
अणु
	uपूर्णांक32_t ip = validation_state->ip;

	अगर (!test_bit(ip, validation_state->branch_tarमाला_लो))
		वापस true;

	अगर (texturing_in_progress(validation_state)) अणु
		DRM_DEBUG("Branch target landed during TMU setup\n");
		वापस false;
	पूर्ण

	/* Reset our live values tracking, since this inकाष्ठाion may have
	 * multiple predecessors.
	 *
	 * One could potentially करो analysis to determine that, क्रम
	 * example, all predecessors have a live max clamp in the same
	 * रेजिस्टर, but we करोn't bother with that.
	 */
	reset_validation_state(validation_state);

	/* Since we've entered a basic block from potentially multiple
	 * predecessors, we need the unअगरorms address to be updated beक्रमe any
	 * unक्रमms are पढ़ो.  We require that after any branch poपूर्णांक, the next
	 * unअगरorm to be loaded is a unअगरorm address offset.  That unअगरorm's
	 * offset will be marked by the unअगरorm address रेजिस्टर ग_लिखो
	 * validation, or a one-off the end-of-program check.
	 */
	validation_state->needs_unअगरorm_address_update = true;

	वापस true;
पूर्ण

काष्ठा vc4_validated_shader_info *
vc4_validate_shader(काष्ठा drm_gem_cma_object *shader_obj)
अणु
	bool found_shader_end = false;
	पूर्णांक shader_end_ip = 0;
	uपूर्णांक32_t last_thपढ़ो_चयन_ip = -3;
	uपूर्णांक32_t ip;
	काष्ठा vc4_validated_shader_info *validated_shader = शून्य;
	काष्ठा vc4_shader_validation_state validation_state;

	स_रखो(&validation_state, 0, माप(validation_state));
	validation_state.shader = shader_obj->vaddr;
	validation_state.max_ip = shader_obj->base.size / माप(uपूर्णांक64_t);

	reset_validation_state(&validation_state);

	validation_state.branch_tarमाला_लो =
		kसुस्मृति(BITS_TO_LONGS(validation_state.max_ip),
			माप(अचिन्हित दीर्घ), GFP_KERNEL);
	अगर (!validation_state.branch_tarमाला_लो)
		जाओ fail;

	validated_shader = kसुस्मृति(1, माप(*validated_shader), GFP_KERNEL);
	अगर (!validated_shader)
		जाओ fail;

	अगर (!vc4_validate_branches(&validation_state))
		जाओ fail;

	क्रम (ip = 0; ip < validation_state.max_ip; ip++) अणु
		uपूर्णांक64_t inst = validation_state.shader[ip];
		uपूर्णांक32_t sig = QPU_GET_FIELD(inst, QPU_SIG);

		validation_state.ip = ip;

		अगर (!vc4_handle_branch_target(&validation_state))
			जाओ fail;

		अगर (ip == last_thपढ़ो_चयन_ip + 3) अणु
			/* Reset r0-r3 live clamp data */
			पूर्णांक i;

			क्रम (i = 64; i < LIVE_REG_COUNT; i++) अणु
				validation_state.live_min_clamp_offsets[i] = ~0;
				validation_state.live_max_clamp_regs[i] = false;
				validation_state.live_immediates[i] = ~0;
			पूर्ण
		पूर्ण

		चयन (sig) अणु
		हाल QPU_SIG_NONE:
		हाल QPU_SIG_WAIT_FOR_SCOREBOARD:
		हाल QPU_SIG_SCOREBOARD_UNLOCK:
		हाल QPU_SIG_COLOR_LOAD:
		हाल QPU_SIG_LOAD_TMU0:
		हाल QPU_SIG_LOAD_TMU1:
		हाल QPU_SIG_PROG_END:
		हाल QPU_SIG_SMALL_IMM:
		हाल QPU_SIG_THREAD_SWITCH:
		हाल QPU_SIG_LAST_THREAD_SWITCH:
			अगर (!check_inकाष्ठाion_ग_लिखोs(validated_shader,
						      &validation_state)) अणु
				DRM_DEBUG("Bad write at ip %d\n", ip);
				जाओ fail;
			पूर्ण

			अगर (!check_inकाष्ठाion_पढ़ोs(validated_shader,
						     &validation_state))
				जाओ fail;

			अगर (sig == QPU_SIG_PROG_END) अणु
				found_shader_end = true;
				shader_end_ip = ip;
			पूर्ण

			अगर (sig == QPU_SIG_THREAD_SWITCH ||
			    sig == QPU_SIG_LAST_THREAD_SWITCH) अणु
				validated_shader->is_thपढ़ोed = true;

				अगर (ip < last_thपढ़ो_चयन_ip + 3) अणु
					DRM_DEBUG("Thread switch too soon after "
						  "last switch at ip %d\n", ip);
					जाओ fail;
				पूर्ण
				last_thपढ़ो_चयन_ip = ip;
			पूर्ण

			अवरोध;

		हाल QPU_SIG_LOAD_IMM:
			अगर (!check_inकाष्ठाion_ग_लिखोs(validated_shader,
						      &validation_state)) अणु
				DRM_DEBUG("Bad LOAD_IMM write at ip %d\n", ip);
				जाओ fail;
			पूर्ण
			अवरोध;

		हाल QPU_SIG_BRANCH:
			अगर (!check_branch(inst, validated_shader,
					  &validation_state, ip))
				जाओ fail;

			अगर (ip < last_thपढ़ो_चयन_ip + 3) अणु
				DRM_DEBUG("Branch in thread switch at ip %d",
					  ip);
				जाओ fail;
			पूर्ण

			अवरोध;
		शेष:
			DRM_DEBUG("Unsupported QPU signal %d at "
				  "instruction %d\n", sig, ip);
			जाओ fail;
		पूर्ण

		/* There are two delay slots after program end is संकेतed
		 * that are still executed, then we're finished.
		 */
		अगर (found_shader_end && ip == shader_end_ip + 2)
			अवरोध;
	पूर्ण

	अगर (ip == validation_state.max_ip) अणु
		DRM_DEBUG("shader failed to terminate before "
			  "shader BO end at %zd\n",
			  shader_obj->base.size);
		जाओ fail;
	पूर्ण

	/* Might corrupt other thपढ़ो */
	अगर (validated_shader->is_thपढ़ोed &&
	    validation_state.all_रेजिस्टरs_used) अणु
		DRM_DEBUG("Shader uses threading, but uses the upper "
			  "half of the registers, too\n");
		जाओ fail;
	पूर्ण

	/* If we did a backwards branch and we haven't emitted a unअगरorms
	 * reset since then, we still need the unअगरorms stream to have the
	 * unअगरorms address available so that the backwards branch can करो its
	 * unअगरorms reset.
	 *
	 * We could potentially prove that the backwards branch करोesn't
	 * contain any uses of unअगरorms until program निकास, but that करोesn't
	 * seem to be worth the trouble.
	 */
	अगर (validation_state.needs_unअगरorm_address_क्रम_loop) अणु
		अगर (!require_unअगरorm_address_unअगरorm(validated_shader))
			जाओ fail;
		validated_shader->unअगरorms_size += 4;
	पूर्ण

	/* Again, no chance of पूर्णांकeger overflow here because the worst हाल
	 * scenario is 8 bytes of unअगरorms plus handles per 8-byte
	 * inकाष्ठाion.
	 */
	validated_shader->unअगरorms_src_size =
		(validated_shader->unअगरorms_size +
		 4 * validated_shader->num_texture_samples);

	kमुक्त(validation_state.branch_tarमाला_लो);

	वापस validated_shader;

fail:
	kमुक्त(validation_state.branch_tarमाला_लो);
	अगर (validated_shader) अणु
		kमुक्त(validated_shader->unअगरorm_addr_offsets);
		kमुक्त(validated_shader->texture_samples);
		kमुक्त(validated_shader);
	पूर्ण
	वापस शून्य;
पूर्ण
