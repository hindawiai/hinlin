<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ASM_X86_SIGCONTEXT_H
#घोषणा _UAPI_ASM_X86_SIGCONTEXT_H

/*
 * Linux संकेत context definitions. The sigcontext includes a complex
 * hierarchy of CPU and FPU state, available to user-space (on the stack) when
 * a संकेत handler is executed.
 *
 * As over the years this ABI grew from its very simple roots towards
 * supporting more and more CPU state organically, some of the details (which
 * were rather clever hacks back in the days) became a bit quirky by today.
 *
 * The current ABI includes flexible provisions क्रम future extensions, so we
 * won't have to grow new quirks क्रम quite some समय. Promise!
 */

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

#घोषणा FP_XSTATE_MAGIC1		0x46505853U
#घोषणा FP_XSTATE_MAGIC2		0x46505845U
#घोषणा FP_XSTATE_MAGIC2_SIZE		माप(FP_XSTATE_MAGIC2)

/*
 * Bytes 464..511 in the current 512-byte layout of the FXSAVE/FXRSTOR frame
 * are reserved क्रम SW usage. On CPUs supporting XSAVE/XRSTOR, these bytes are
 * used to extend the fpstate poपूर्णांकer in the sigcontext, which now includes the
 * extended state inक्रमmation aदीर्घ with fpstate inक्रमmation.
 *
 * If sw_reserved.magic1 == FP_XSTATE_MAGIC1 then there's a
 * sw_reserved.extended_size bytes large extended context area present. (The
 * last 32-bit word of this extended area (at the
 * fpstate+extended_size-FP_XSTATE_MAGIC2_SIZE address) is set to
 * FP_XSTATE_MAGIC2 so that you can sanity check your size calculations.)
 *
 * This extended area typically grows with newer CPUs that have larger and
 * larger XSAVE areas.
 */
काष्ठा _fpx_sw_bytes अणु
	/*
	 * If set to FP_XSTATE_MAGIC1 then this is an xstate context.
	 * 0 अगर a legacy frame.
	 */
	__u32				magic1;

	/*
	 * Total size of the fpstate area:
	 *
	 *  - अगर magic1 == 0 then it's माप(काष्ठा _fpstate)
	 *  - अगर magic1 == FP_XSTATE_MAGIC1 then it's माप(काष्ठा _xstate)
	 *    plus extensions (अगर any)
	 */
	__u32				extended_size;

	/*
	 * Feature bit mask (including FP/SSE/extended state) that is present
	 * in the memory layout:
	 */
	__u64				xfeatures;

	/*
	 * Actual XSAVE state size, based on the xfeatures saved in the layout.
	 * 'extended_size' is greater than 'xstate_size':
	 */
	__u32				xstate_size;

	/* For future use: */
	__u32				padding[7];
पूर्ण;

/*
 * As करोcumented in the iBCS2 standard:
 *
 * The first part of "struct _fpstate" is just the normal i387 hardware setup,
 * the extra "status" word is used to save the coprocessor status word beक्रमe
 * entering the handler.
 *
 * The FPU state data काष्ठाure has had to grow to accommodate the extended FPU
 * state required by the Streaming SIMD Extensions.  There is no करोcumented
 * standard to accomplish this at the moment.
 */

/* 10-byte legacy भग्नing poपूर्णांक रेजिस्टर: */
काष्ठा _fpreg अणु
	__u16				signअगरicand[4];
	__u16				exponent;
पूर्ण;

/* 16-byte भग्नing poपूर्णांक रेजिस्टर: */
काष्ठा _fpxreg अणु
	__u16				signअगरicand[4];
	__u16				exponent;
	__u16				padding[3];
पूर्ण;

/* 16-byte XMM रेजिस्टर: */
काष्ठा _xmmreg अणु
	__u32				element[4];
पूर्ण;

#घोषणा X86_FXSR_MAGIC			0x0000

/*
 * The 32-bit FPU frame:
 */
काष्ठा _fpstate_32 अणु
	/* Legacy FPU environment: */
	__u32				cw;
	__u32				sw;
	__u32				tag;
	__u32				ipoff;
	__u32				cssel;
	__u32				dataoff;
	__u32				datasel;
	काष्ठा _fpreg			_st[8];
	__u16				status;
	__u16				magic;		/* 0xffff: regular FPU data only */
							/* 0x0000: FXSR FPU data */

	/* FXSR FPU environment */
	__u32				_fxsr_env[6];	/* FXSR FPU env is ignored */
	__u32				mxcsr;
	__u32				reserved;
	काष्ठा _fpxreg			_fxsr_st[8];	/* FXSR FPU reg data is ignored */
	काष्ठा _xmmreg			_xmm[8];	/* First 8 XMM रेजिस्टरs */
	जोड़ अणु
		__u32			padding1[44];	/* Second 8 XMM रेजिस्टरs plus padding */
		__u32			padding[44];	/* Alias name क्रम old user-space */
	पूर्ण;

	जोड़ अणु
		__u32			padding2[12];
		काष्ठा _fpx_sw_bytes	sw_reserved;	/* Potential extended state is encoded here */
	पूर्ण;
पूर्ण;

/*
 * The 64-bit FPU frame. (FXSAVE क्रमmat and later)
 *
 * Note1: If sw_reserved.magic1 == FP_XSTATE_MAGIC1 then the काष्ठाure is
 *        larger: 'struct _xstate'. Note that 'struct _xstate' embeds
 *        'struct _fpstate' so that you can always assume the _fpstate portion
 *        exists so that you can check the magic value.
 *
 * Note2: Reserved fields may someday contain valuable data. Always
 *	  save/restore them when you change संकेत frames.
 */
काष्ठा _fpstate_64 अणु
	__u16				cwd;
	__u16				swd;
	/* Note this is not the same as the 32-bit/x87/FSAVE twd: */
	__u16				twd;
	__u16				fop;
	__u64				rip;
	__u64				rdp;
	__u32				mxcsr;
	__u32				mxcsr_mask;
	__u32				st_space[32];	/*  8x  FP रेजिस्टरs, 16 bytes each */
	__u32				xmm_space[64];	/* 16x XMM रेजिस्टरs, 16 bytes each */
	__u32				reserved2[12];
	जोड़ अणु
		__u32			reserved3[12];
		काष्ठा _fpx_sw_bytes	sw_reserved;	/* Potential extended state is encoded here */
	पूर्ण;
पूर्ण;

#अगर_घोषित __i386__
# define _fpstate _fpstate_32
#अन्यथा
# define _fpstate _fpstate_64
#पूर्ण_अगर

काष्ठा _header अणु
	__u64				xfeatures;
	__u64				reserved1[2];
	__u64				reserved2[5];
पूर्ण;

काष्ठा _ymmh_state अणु
	/* 16x YMM रेजिस्टरs, 16 bytes each: */
	__u32				ymmh_space[64];
पूर्ण;

/*
 * Extended state poपूर्णांकed to by sigcontext::fpstate.
 *
 * In addition to the fpstate, inक्रमmation encoded in _xstate::xstate_hdr
 * indicates the presence of other extended state inक्रमmation supported
 * by the CPU and kernel:
 */
काष्ठा _xstate अणु
	काष्ठा _fpstate			fpstate;
	काष्ठा _header			xstate_hdr;
	काष्ठा _ymmh_state		ymmh;
	/* New processor state extensions go here: */
पूर्ण;

/*
 * The 32-bit संकेत frame:
 */
काष्ठा sigcontext_32 अणु
	__u16				gs, __gsh;
	__u16				fs, __fsh;
	__u16				es, __esh;
	__u16				ds, __dsh;
	__u32				di;
	__u32				si;
	__u32				bp;
	__u32				sp;
	__u32				bx;
	__u32				dx;
	__u32				cx;
	__u32				ax;
	__u32				trapno;
	__u32				err;
	__u32				ip;
	__u16				cs, __csh;
	__u32				flags;
	__u32				sp_at_संकेत;
	__u16				ss, __ssh;

	/*
	 * fpstate is really (काष्ठा _fpstate *) or (काष्ठा _xstate *)
	 * depending on the FP_XSTATE_MAGIC1 encoded in the SW reserved
	 * bytes of (काष्ठा _fpstate) and FP_XSTATE_MAGIC2 present at the end
	 * of extended memory layout. See comments at the definition of
	 * (काष्ठा _fpx_sw_bytes)
	 */
	__u32				fpstate; /* Zero when no FPU/extended context */
	__u32				oldmask;
	__u32				cr2;
पूर्ण;

/*
 * The 64-bit संकेत frame:
 */
काष्ठा sigcontext_64 अणु
	__u64				r8;
	__u64				r9;
	__u64				r10;
	__u64				r11;
	__u64				r12;
	__u64				r13;
	__u64				r14;
	__u64				r15;
	__u64				di;
	__u64				si;
	__u64				bp;
	__u64				bx;
	__u64				dx;
	__u64				ax;
	__u64				cx;
	__u64				sp;
	__u64				ip;
	__u64				flags;
	__u16				cs;
	__u16				gs;
	__u16				fs;
	__u16				ss;
	__u64				err;
	__u64				trapno;
	__u64				oldmask;
	__u64				cr2;

	/*
	 * fpstate is really (काष्ठा _fpstate *) or (काष्ठा _xstate *)
	 * depending on the FP_XSTATE_MAGIC1 encoded in the SW reserved
	 * bytes of (काष्ठा _fpstate) and FP_XSTATE_MAGIC2 present at the end
	 * of extended memory layout. See comments at the definition of
	 * (काष्ठा _fpx_sw_bytes)
	 */
	__u64				fpstate; /* Zero when no FPU/extended context */
	__u64				reserved1[8];
पूर्ण;

/*
 * Create the real 'struct sigcontext' type:
 */
#अगर_घोषित __KERNEL__
# अगरdef __i386__
#  define sigcontext sigcontext_32
# अन्यथा
#  define sigcontext sigcontext_64
# endअगर
#पूर्ण_अगर

/*
 * The old user-space sigcontext definition, just in हाल user-space still
 * relies on it. The kernel definition (in यंत्र/sigcontext.h) has unअगरied
 * field names but otherwise the same layout.
 */
#अगर_अघोषित __KERNEL__

#घोषणा _fpstate_ia32			_fpstate_32
#घोषणा sigcontext_ia32			sigcontext_32


# अगरdef __i386__
काष्ठा sigcontext अणु
	__u16				gs, __gsh;
	__u16				fs, __fsh;
	__u16				es, __esh;
	__u16				ds, __dsh;
	__u32				edi;
	__u32				esi;
	__u32				ebp;
	__u32				esp;
	__u32				ebx;
	__u32				edx;
	__u32				ecx;
	__u32				eax;
	__u32				trapno;
	__u32				err;
	__u32				eip;
	__u16				cs, __csh;
	__u32				eflags;
	__u32				esp_at_संकेत;
	__u16				ss, __ssh;
	काष्ठा _fpstate __user		*fpstate;
	__u32				oldmask;
	__u32				cr2;
पूर्ण;
# अन्यथा /* __x86_64__: */
काष्ठा sigcontext अणु
	__u64				r8;
	__u64				r9;
	__u64				r10;
	__u64				r11;
	__u64				r12;
	__u64				r13;
	__u64				r14;
	__u64				r15;
	__u64				rdi;
	__u64				rsi;
	__u64				rbp;
	__u64				rbx;
	__u64				rdx;
	__u64				rax;
	__u64				rcx;
	__u64				rsp;
	__u64				rip;
	__u64				eflags;		/* RFLAGS */
	__u16				cs;

	/*
	 * Prior to 2.5.64 ("[PATCH] x86-64 updates for 2.5.64-bk3"),
	 * Linux saved and restored fs and gs in these slots.  This
	 * was counterproductive, as fsbase and gsbase were never
	 * saved, so arch_prctl was presumably unreliable.
	 *
	 * These slots should never be reused without extreme caution:
	 *
	 *  - Some DOSEMU versions stash fs and gs in these slots manually,
	 *    thus overwriting anything the kernel expects to be preserved
	 *    in these slots.
	 *
	 *  - If these slots are ever needed क्रम any other purpose,
	 *    there is some risk that very old 64-bit binaries could get
	 *    confused.  I करोubt that many such binaries still work,
	 *    though, since the same patch in 2.5.64 also हटाओd the
	 *    64-bit set_thपढ़ो_area syscall, so it appears that there
	 *    is no TLS API beyond modअगरy_ldt that works in both pre-
	 *    and post-2.5.64 kernels.
	 *
	 * If the kernel ever adds explicit fs, gs, fsbase, and gsbase
	 * save/restore, it will most likely need to be opt-in and use
	 * dअगरferent context slots.
	 */
	__u16				gs;
	__u16				fs;
	जोड़ अणु
		__u16			ss;	/* If UC_SIGCONTEXT_SS */
		__u16			__pad0;	/* Alias name क्रम old (!UC_SIGCONTEXT_SS) user-space */
	पूर्ण;
	__u64				err;
	__u64				trapno;
	__u64				oldmask;
	__u64				cr2;
	काष्ठा _fpstate __user		*fpstate;	/* Zero when no FPU context */
#  अगरdef __ILP32__
	__u32				__fpstate_pad;
#  endअगर
	__u64				reserved1[8];
पूर्ण;
# endअगर /* __x86_64__ */
#पूर्ण_अगर /* !__KERNEL__ */

#पूर्ण_अगर /* _UAPI_ASM_X86_SIGCONTEXT_H */
