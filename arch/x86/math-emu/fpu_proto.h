<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FPU_PROTO_H
#घोषणा _FPU_PROTO_H

/* errors.c */
बाह्य व्योम FPU_illegal(व्योम);
बाह्य व्योम FPU_prपूर्णांकall(व्योम);
यंत्रlinkage व्योम FPU_exception(पूर्णांक n);
बाह्य पूर्णांक real_1op_NaN(FPU_REG *a);
बाह्य पूर्णांक real_2op_NaN(FPU_REG स्थिर *b, u_अक्षर tagb, पूर्णांक deststnr,
			FPU_REG स्थिर *शेषNaN);
यंत्रlinkage पूर्णांक arith_invalid(पूर्णांक deststnr);
यंत्रlinkage पूर्णांक FPU_भागide_by_zero(पूर्णांक deststnr, u_अक्षर sign);
बाह्य पूर्णांक set_precision_flag(पूर्णांक flags);
यंत्रlinkage व्योम set_precision_flag_up(व्योम);
यंत्रlinkage व्योम set_precision_flag_करोwn(व्योम);
यंत्रlinkage पूर्णांक denormal_opeअक्रम(व्योम);
यंत्रlinkage पूर्णांक arith_overflow(FPU_REG *dest);
यंत्रlinkage पूर्णांक arith_underflow(FPU_REG *dest);
बाह्य व्योम FPU_stack_overflow(व्योम);
बाह्य व्योम FPU_stack_underflow(व्योम);
बाह्य व्योम FPU_stack_underflow_i(पूर्णांक i);
बाह्य व्योम FPU_stack_underflow_pop(पूर्णांक i);
/* fpu_arith.c */
बाह्य व्योम fadd__(व्योम);
बाह्य व्योम fmul__(व्योम);
बाह्य व्योम fsub__(व्योम);
बाह्य व्योम fsubr_(व्योम);
बाह्य व्योम fभाग__(व्योम);
बाह्य व्योम fभागr_(व्योम);
बाह्य व्योम fadd_i(व्योम);
बाह्य व्योम fmul_i(व्योम);
बाह्य व्योम fsubri(व्योम);
बाह्य व्योम fsub_i(व्योम);
बाह्य व्योम fभागri(व्योम);
बाह्य व्योम fभाग_i(व्योम);
बाह्य व्योम faddp_(व्योम);
बाह्य व्योम fmulp_(व्योम);
बाह्य व्योम fsubrp(व्योम);
बाह्य व्योम fsubp_(व्योम);
बाह्य व्योम fभागrp(व्योम);
बाह्य व्योम fभागp_(व्योम);
/* fpu_aux.c */
बाह्य व्योम finit(व्योम);
बाह्य व्योम finit_(व्योम);
बाह्य व्योम fstsw_(व्योम);
बाह्य व्योम fp_nop(व्योम);
बाह्य व्योम fld_i_(व्योम);
बाह्य व्योम fxch_i(व्योम);
बाह्य व्योम fcmovb(व्योम);
बाह्य व्योम fcmove(व्योम);
बाह्य व्योम fcmovbe(व्योम);
बाह्य व्योम fcmovu(व्योम);
बाह्य व्योम fcmovnb(व्योम);
बाह्य व्योम fcmovne(व्योम);
बाह्य व्योम fcmovnbe(व्योम);
बाह्य व्योम fcmovnu(व्योम);
बाह्य व्योम fमुक्त_(व्योम);
बाह्य व्योम fमुक्तp(व्योम);
बाह्य व्योम fst_i_(व्योम);
बाह्य व्योम fstp_i(व्योम);
/* fpu_entry.c */
बाह्य व्योम math_emulate(काष्ठा math_emu_info *info);
बाह्य व्योम math_पात(काष्ठा math_emu_info *info, अचिन्हित पूर्णांक संकेत);
/* fpu_etc.c */
बाह्य व्योम FPU_etc(व्योम);
/* fpu_tags.c */
बाह्य पूर्णांक FPU_gettag0(व्योम);
बाह्य पूर्णांक FPU_gettagi(पूर्णांक stnr);
बाह्य पूर्णांक FPU_gettag(पूर्णांक regnr);
बाह्य व्योम FPU_settag0(पूर्णांक tag);
बाह्य व्योम FPU_settagi(पूर्णांक stnr, पूर्णांक tag);
बाह्य व्योम FPU_settag(पूर्णांक regnr, पूर्णांक tag);
बाह्य पूर्णांक FPU_Special(FPU_REG स्थिर *ptr);
बाह्य पूर्णांक isNaN(FPU_REG स्थिर *ptr);
बाह्य व्योम FPU_pop(व्योम);
बाह्य पूर्णांक FPU_empty_i(पूर्णांक stnr);
बाह्य पूर्णांक FPU_stackoverflow(FPU_REG ** st_new_ptr);
बाह्य व्योम FPU_copy_to_regi(FPU_REG स्थिर *r, u_अक्षर tag, पूर्णांक stnr);
बाह्य व्योम FPU_copy_to_reg1(FPU_REG स्थिर *r, u_अक्षर tag);
बाह्य व्योम FPU_copy_to_reg0(FPU_REG स्थिर *r, u_अक्षर tag);
/* fpu_trig.c */
बाह्य व्योम FPU_triga(व्योम);
बाह्य व्योम FPU_trigb(व्योम);
/* get_address.c */
बाह्य व्योम __user *FPU_get_address(u_अक्षर FPU_modrm, अचिन्हित दीर्घ *fpu_eip,
				    काष्ठा address *addr,
				    fpu_addr_modes addr_modes);
बाह्य व्योम __user *FPU_get_address_16(u_अक्षर FPU_modrm, अचिन्हित दीर्घ *fpu_eip,
				       काष्ठा address *addr,
				       fpu_addr_modes addr_modes);
/* load_store.c */
बाह्य पूर्णांक FPU_load_store(u_अक्षर type, fpu_addr_modes addr_modes,
			  व्योम __user * data_address);
/* poly_2xm1.c */
बाह्य पूर्णांक poly_2xm1(u_अक्षर sign, FPU_REG * arg, FPU_REG *result);
/* poly_atan.c */
बाह्य व्योम poly_atan(FPU_REG * st0_ptr, u_अक्षर st0_tag, FPU_REG *st1_ptr,
		      u_अक्षर st1_tag);
/* poly_l2.c */
बाह्य व्योम poly_l2(FPU_REG *st0_ptr, FPU_REG *st1_ptr, u_अक्षर st1_sign);
बाह्य पूर्णांक poly_l2p1(u_अक्षर s0, u_अक्षर s1, FPU_REG *r0, FPU_REG *r1,
		     FPU_REG * d);
/* poly_sin.c */
बाह्य व्योम poly_sine(FPU_REG *st0_ptr);
बाह्य व्योम poly_cos(FPU_REG *st0_ptr);
/* poly_tan.c */
बाह्य व्योम poly_tan(FPU_REG *st0_ptr);
/* reg_add_sub.c */
बाह्य पूर्णांक FPU_add(FPU_REG स्थिर *b, u_अक्षर tagb, पूर्णांक destrnr, पूर्णांक control_w);
बाह्य पूर्णांक FPU_sub(पूर्णांक flags, पूर्णांक rm, पूर्णांक control_w);
/* reg_compare.c */
बाह्य पूर्णांक FPU_compare_st_data(FPU_REG स्थिर *loaded_data, u_अक्षर loaded_tag);
बाह्य व्योम fcom_st(व्योम);
बाह्य व्योम fcompst(व्योम);
बाह्य व्योम fcompp(व्योम);
बाह्य व्योम fucom_(व्योम);
बाह्य व्योम fucomp(व्योम);
बाह्य व्योम fucompp(व्योम);
बाह्य व्योम fcomi_(व्योम);
बाह्य व्योम fcomip(व्योम);
बाह्य व्योम fucomi_(व्योम);
बाह्य व्योम fucomip(व्योम);
/* reg_स्थिरant.c */
बाह्य व्योम fस्थिर(व्योम);
/* reg_ld_str.c */
बाह्य पूर्णांक FPU_load_extended(दीर्घ द्विगुन __user *s, पूर्णांक stnr);
बाह्य पूर्णांक FPU_load_द्विगुन(द्विगुन __user *dभग्न, FPU_REG *loaded_data);
बाह्य पूर्णांक FPU_load_single(भग्न __user *single, FPU_REG *loaded_data);
बाह्य पूर्णांक FPU_load_पूर्णांक64(दीर्घ दीर्घ __user *_s);
बाह्य पूर्णांक FPU_load_पूर्णांक32(दीर्घ __user *_s, FPU_REG *loaded_data);
बाह्य पूर्णांक FPU_load_पूर्णांक16(लघु __user *_s, FPU_REG *loaded_data);
बाह्य पूर्णांक FPU_load_bcd(u_अक्षर __user *s);
बाह्य पूर्णांक FPU_store_extended(FPU_REG *st0_ptr, u_अक्षर st0_tag,
			      दीर्घ द्विगुन __user * d);
बाह्य पूर्णांक FPU_store_द्विगुन(FPU_REG *st0_ptr, u_अक्षर st0_tag,
			    द्विगुन __user * dभग्न);
बाह्य पूर्णांक FPU_store_single(FPU_REG *st0_ptr, u_अक्षर st0_tag,
			    भग्न __user * single);
बाह्य पूर्णांक FPU_store_पूर्णांक64(FPU_REG *st0_ptr, u_अक्षर st0_tag,
			   दीर्घ दीर्घ __user * d);
बाह्य पूर्णांक FPU_store_पूर्णांक32(FPU_REG *st0_ptr, u_अक्षर st0_tag, दीर्घ __user *d);
बाह्य पूर्णांक FPU_store_पूर्णांक16(FPU_REG *st0_ptr, u_अक्षर st0_tag, लघु __user *d);
बाह्य पूर्णांक FPU_store_bcd(FPU_REG *st0_ptr, u_अक्षर st0_tag, u_अक्षर __user *d);
बाह्य पूर्णांक FPU_round_to_पूर्णांक(FPU_REG *r, u_अक्षर tag);
बाह्य u_अक्षर __user *fldenv(fpu_addr_modes addr_modes, u_अक्षर __user *s);
बाह्य व्योम frstor(fpu_addr_modes addr_modes, u_अक्षर __user *data_address);
बाह्य u_अक्षर __user *fstenv(fpu_addr_modes addr_modes, u_अक्षर __user *d);
बाह्य व्योम fsave(fpu_addr_modes addr_modes, u_अक्षर __user *data_address);
बाह्य पूर्णांक FPU_tagof(FPU_REG *ptr);
/* reg_mul.c */
बाह्य पूर्णांक FPU_mul(FPU_REG स्थिर *b, u_अक्षर tagb, पूर्णांक deststnr, पूर्णांक control_w);

बाह्य पूर्णांक FPU_भाग(पूर्णांक flags, पूर्णांक regrm, पूर्णांक control_w);
/* reg_convert.c */
बाह्य पूर्णांक FPU_to_exp16(FPU_REG स्थिर *a, FPU_REG *x);
#पूर्ण_अगर /* _FPU_PROTO_H */
