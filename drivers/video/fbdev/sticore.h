<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित STICORE_H
#घोषणा STICORE_H

/* generic STI काष्ठाures & functions */

#घोषणा MAX_STI_ROMS 4		/* max no. of ROMs which this driver handles */

#घोषणा STI_REGION_MAX 8	/* hardcoded STI स्थिरants */
#घोषणा STI_DEV_NAME_LENGTH 32
#घोषणा STI_MONITOR_MAX 256

#घोषणा STI_FONT_HPROMAN8 1
#घोषणा STI_FONT_KANA8 2

#घोषणा ALT_CODE_TYPE_UNKNOWN 0x00	/* alt code type values */
#घोषणा ALT_CODE_TYPE_PA_RISC_64 0x01

/* The latency of the STI functions cannot really be reduced by setting
 * this to 0;  STI करोesn't seem to be deचिन्हित to allow calling a dअगरferent
 * function (or the same function with dअगरferent arguments) after a
 * function निकासed with 1 as वापस value.
 *
 * As all of the functions below could be called from पूर्णांकerrupt context,
 * we have to spin_lock_irqsave around the करो अणु ret = bla(); पूर्ण जबतक(ret==1)
 * block.  Really bad latency there.
 *
 * Probably the best solution to all this is have the generic code manage
 * the screen buffer and a kernel thपढ़ो to call STI occasionally.
 * 
 * Luckily, the frame buffer guys have the same problem so we can just रुको
 * क्रम them to fix it and steal their solution.   prumpf
 */
 
#समावेश <यंत्र/पन.स>

#घोषणा STI_WAIT 1

#घोषणा STI_PTR(p)	( virt_to_phys(p) )
#घोषणा PTR_STI(p)	( phys_to_virt((अचिन्हित दीर्घ)p) )

#घोषणा sti_onscreen_x(sti) (sti->glob_cfg->onscreen_x)
#घोषणा sti_onscreen_y(sti) (sti->glob_cfg->onscreen_y)

/* sti_font_xy() use the native font ROM ! */
#घोषणा sti_font_x(sti) (PTR_STI(sti->font)->width)
#घोषणा sti_font_y(sti) (PTR_STI(sti->font)->height)

#अगर_घोषित CONFIG_64BIT
#घोषणा STI_LOWMEM	(GFP_KERNEL | GFP_DMA)
#अन्यथा
#घोषणा STI_LOWMEM	(GFP_KERNEL)
#पूर्ण_अगर


/* STI function configuration काष्ठाs */

प्रकार जोड़ region अणु
	काष्ठा अणु 
		u32 offset	: 14;	/* offset in 4kbyte page */
		u32 sys_only	: 1;	/* करोn't map to user space */
		u32 cache	: 1;	/* map to data cache */
		u32 btlb	: 1;	/* map to block tlb */
		u32 last	: 1;	/* last region in list */
		u32 length	: 14;	/* length in 4kbyte page */
	पूर्ण region_desc;

	u32 region;			/* complete region value */
पूर्ण region_t;

#घोषणा REGION_OFFSET_TO_PHYS( rt, hpa ) \
	(((rt).region_desc.offset << 12) + (hpa))

काष्ठा sti_glob_cfg_ext अणु
	 u8 curr_mon;			/* current monitor configured */
	 u8 मित्रly_boot;		/* in मित्रly boot mode */
	s16 घातer;			/* घातer calculation (in Watts) */
	s32 freq_ref;			/* frequency reference */
	u32 sti_mem_addr;		/* poपूर्णांकer to global sti memory (size=sti_mem_request) */
	u32 future_ptr; 		/* poपूर्णांकer to future data */
पूर्ण;

काष्ठा sti_glob_cfg अणु
	s32 text_planes;		/* number of planes used क्रम text */
	s16 onscreen_x;			/* screen width in pixels */
	s16 onscreen_y;			/* screen height in pixels */
	s16 offscreen_x;		/* offset width in pixels */
	s16 offscreen_y;		/* offset height in pixels */
	s16 total_x;			/* frame buffer width in pixels */
	s16 total_y;			/* frame buffer height in pixels */
	u32 region_ptrs[STI_REGION_MAX]; /* region poपूर्णांकers */
	s32 reent_lvl;			/* storage क्रम reentry level value */
	u32 save_addr;			/* where to save or restore reentrant state */
	u32 ext_ptr;			/* poपूर्णांकer to extended glob_cfg data काष्ठाure */
पूर्ण;


/* STI init function काष्ठाs */

काष्ठा sti_init_flags अणु
	u32 रुको : 1;		/* should routine idle रुको or not */
	u32 reset : 1;		/* hard reset the device? */
	u32 text : 1;		/* turn on text display planes? */
	u32 nontext : 1;	/* turn on non-text display planes? */
	u32 clear : 1;		/* clear text display planes? */
	u32 cmap_blk : 1;	/* non-text planes cmap black? */
	u32 enable_be_समयr : 1; /* enable bus error समयr */
	u32 enable_be_पूर्णांक : 1;	/* enable bus error समयr पूर्णांकerrupt */
	u32 no_chg_tx : 1;	/* करोn't change text settings */
	u32 no_chg_ntx : 1;	/* करोn't change non-text settings */
	u32 no_chg_bet : 1;	/* करोn't change berr समयr settings */
	u32 no_chg_bei : 1;	/* करोn't change berr पूर्णांक settings */
	u32 init_cmap_tx : 1;	/* initialize cmap क्रम text planes */
	u32 cmt_chg : 1;	/* change current monitor type */
	u32 retain_ie : 1;	/* करोn't allow reset to clear पूर्णांक enables */
	u32 caller_bootrom : 1;	/* set only by bootrom क्रम each call */
	u32 caller_kernel : 1;	/* set only by kernel क्रम each call */
	u32 caller_other : 1;	/* set only by non-[BR/K] caller */
	u32 pad	: 14;		/* pad to word boundary */
	u32 future_ptr; 	/* poपूर्णांकer to future data */
पूर्ण;

काष्ठा sti_init_inptr_ext अणु
	u8  config_mon_type;	/* configure to monitor type */
	u8  pad[1];		/* pad to word boundary */
	u16 inflight_data;	/* inflight data possible on PCI */
	u32 future_ptr; 	/* poपूर्णांकer to future data */
पूर्ण;

काष्ठा sti_init_inptr अणु
	s32 text_planes;	/* number of planes to use क्रम text */
	u32 ext_ptr;		/* poपूर्णांकer to extended init_graph inptr data काष्ठाure*/
पूर्ण;


काष्ठा sti_init_outptr अणु
	s32 त्रुटि_सं;		/* error number on failure */
	s32 text_planes;	/* number of planes used क्रम text */
	u32 future_ptr; 	/* poपूर्णांकer to future data */
पूर्ण;



/* STI configuration function काष्ठाs */

काष्ठा sti_conf_flags अणु
	u32 रुको : 1;		/* should routine idle रुको or not */
	u32 pad : 31;		/* pad to word boundary */
	u32 future_ptr; 	/* poपूर्णांकer to future data */
पूर्ण;

काष्ठा sti_conf_inptr अणु
	u32 future_ptr; 	/* poपूर्णांकer to future data */
पूर्ण;

काष्ठा sti_conf_outptr_ext अणु
	u32 crt_config[3];	/* hardware specअगरic X11/OGL inक्रमmation */	
	u32 crt_hdw[3];
	u32 future_ptr;
पूर्ण;

काष्ठा sti_conf_outptr अणु
	s32 त्रुटि_सं;		/* error number on failure */
	s16 onscreen_x;		/* screen width in pixels */
	s16 onscreen_y;		/* screen height in pixels */
	s16 offscreen_x;	/* offscreen width in pixels */
	s16 offscreen_y;	/* offscreen height in pixels */
	s16 total_x;		/* frame buffer width in pixels */
	s16 total_y;		/* frame buffer height in pixels */
	s32 bits_per_pixel;	/* bits/pixel device has configured */
	s32 bits_used;		/* bits which can be accessed */
	s32 planes;		/* number of fb planes in प्रणाली */
	 u8 dev_name[STI_DEV_NAME_LENGTH]; /* null terminated product name */
	u32 attributes;		/* flags denoting attributes */
	u32 ext_ptr;		/* poपूर्णांकer to future data */
पूर्ण;

काष्ठा sti_rom अणु
	 u8 type[4];
	 u8 res004;
	 u8 num_mons;
	 u8 revno[2];
	u32 graphics_id[2];

	u32 font_start;
	u32 statesize;
	u32 last_addr;
	u32 region_list;

	u16 reentsize;
	u16 maxसमय;
	u32 mon_tbl_addr;
	u32 user_data_addr;
	u32 sti_mem_req;

	u32 user_data_size;
	u16 घातer;
	 u8 bus_support;
	 u8 ext_bus_support;
	 u8 alt_code_type;
	 u8 ext_dd_काष्ठा[3];
	u32 cfb_addr;

	u32 init_graph;
	u32 state_mgmt;
	u32 font_unpmv;
	u32 block_move;
	u32 self_test;
	u32 excep_hdlr;
	u32 inq_conf;
	u32 set_cm_entry;
	u32 dma_ctrl;
	 u8 res040[7 * 4];
	
	u32 init_graph_addr;
	u32 state_mgmt_addr;
	u32 font_unp_addr;
	u32 block_move_addr;
	u32 self_test_addr;
	u32 excep_hdlr_addr;
	u32 inq_conf_addr;
	u32 set_cm_entry_addr;
	u32 image_unpack_addr;
	u32 pa_risx_addrs[7];
पूर्ण;

काष्ठा sti_rom_font अणु
	u16 first_अक्षर;
	u16 last_अक्षर;
	 u8 width;
	 u8 height;
	 u8 font_type;		/* language type */
	 u8 bytes_per_अक्षर;
	u32 next_font;
	 u8 underline_height;
	 u8 underline_pos;
	 u8 res008[2];
पूर्ण;

/* sticore पूर्णांकernal font handling */

काष्ठा sti_cooked_font अणु
	काष्ठा sti_rom_font *raw;	/* native ptr क्रम STI functions */
	व्योम *raw_ptr;			/* kदो_स्मृति'ed font data */
	काष्ठा sti_cooked_font *next_font;
	पूर्णांक height, width;
	पूर्णांक refcount;
	u32 crc;
पूर्ण;

काष्ठा sti_cooked_rom अणु
        काष्ठा sti_rom *raw;
	काष्ठा sti_cooked_font *font_start;
पूर्ण;

/* STI font prपूर्णांकing function काष्ठाs */

काष्ठा sti_font_inptr अणु
	u32 font_start_addr;	/* address of font start */
	s16 index;		/* index पूर्णांकo font table of अक्षरacter */
	u8 fg_color;		/* क्रमeground color of अक्षरacter */
	u8 bg_color;		/* background color of अक्षरacter */
	s16 dest_x;		/* X location of अक्षरacter upper left */
	s16 dest_y;		/* Y location of अक्षरacter upper left */
	u32 future_ptr; 	/* poपूर्णांकer to future data */
पूर्ण;

काष्ठा sti_font_flags अणु
	u32 रुको : 1;		/* should routine idle रुको or not */
	u32 non_text : 1;	/* font unpack/move in non_text planes =1, text =0 */
	u32 pad : 30;		/* pad to word boundary */
	u32 future_ptr; 	/* poपूर्णांकer to future data */
पूर्ण;
	
काष्ठा sti_font_outptr अणु
	s32 त्रुटि_सं;		/* error number on failure */
	u32 future_ptr; 	/* poपूर्णांकer to future data */
पूर्ण;

/* STI blockmove काष्ठाs */

काष्ठा sti_blkmv_flags अणु
	u32 रुको : 1;		/* should routine idle रुको or not */
	u32 color : 1;		/* change color during move? */
	u32 clear : 1;		/* clear during move? */
	u32 non_text : 1;	/* block move in non_text planes =1, text =0 */
	u32 pad : 28;		/* pad to word boundary */
	u32 future_ptr; 	/* poपूर्णांकer to future data */
पूर्ण;

काष्ठा sti_blkmv_inptr अणु
	u8 fg_color;		/* क्रमeground color after move */
	u8 bg_color;		/* background color after move */
	s16 src_x;		/* source upper left pixel x location */
	s16 src_y;		/* source upper left pixel y location */
	s16 dest_x;		/* dest upper left pixel x location */
	s16 dest_y;		/* dest upper left pixel y location */
	s16 width;		/* block width in pixels */
	s16 height;		/* block height in pixels */
	u32 future_ptr; 	/* poपूर्णांकer to future data */
पूर्ण;

काष्ठा sti_blkmv_outptr अणु
	s32 त्रुटि_सं;		/* error number on failure */
	u32 future_ptr; 	/* poपूर्णांकer to future data */
पूर्ण;


/* sti_all_data is an पूर्णांकernal काष्ठा which needs to be allocated in
 * low memory (< 4GB) अगर STI is used with 32bit STI on a 64bit kernel */

काष्ठा sti_all_data अणु
	काष्ठा sti_glob_cfg glob_cfg;
	काष्ठा sti_glob_cfg_ext glob_cfg_ext;

	काष्ठा sti_conf_inptr		inq_inptr;
	काष्ठा sti_conf_outptr		inq_outptr; /* configuration */
	काष्ठा sti_conf_outptr_ext	inq_outptr_ext;

	काष्ठा sti_init_inptr_ext	init_inptr_ext;
	काष्ठा sti_init_inptr		init_inptr;
	काष्ठा sti_init_outptr		init_outptr;

	काष्ठा sti_blkmv_inptr		blkmv_inptr;
	काष्ठा sti_blkmv_outptr		blkmv_outptr;

	काष्ठा sti_font_inptr		font_inptr;
	काष्ठा sti_font_outptr		font_outptr;

	/* leave as last entries */
	अचिन्हित दीर्घ save_addr[1024 / माप(अचिन्हित दीर्घ)];
	   /* min 256 bytes which is STI शेष, max sti->sti_mem_request */
	अचिन्हित दीर्घ sti_mem_addr[256 / माप(अचिन्हित दीर्घ)];
	/* करो not add something below here ! */
पूर्ण;

/* पूर्णांकernal generic STI काष्ठा */

काष्ठा sti_काष्ठा अणु
	spinlock_t lock;
		
	/* अक्षर **mon_strings; */
	पूर्णांक sti_mem_request;
	u32 graphics_id[2];

	काष्ठा sti_cooked_rom *rom;

	अचिन्हित दीर्घ font_unpmv;
	अचिन्हित दीर्घ block_move;
	अचिन्हित दीर्घ init_graph;
	अचिन्हित दीर्घ inq_conf;

	/* all following fields are initialized by the generic routines */
	पूर्णांक text_planes;
	region_t regions[STI_REGION_MAX];
	अचिन्हित दीर्घ regions_phys[STI_REGION_MAX];

	काष्ठा sti_glob_cfg *glob_cfg;	/* poपूर्णांकs पूर्णांकo sti_all_data */

	पूर्णांक wordmode;
	काष्ठा sti_cooked_font *font;	/* ptr to selected font (cooked) */

	काष्ठा pci_dev *pd;

	/* PCI data काष्ठाures (pg. 17ff from sti.pdf) */
	u8 rm_entry[16]; /* pci region mapper array == pci config space offset */

	/* poपूर्णांकer to the fb_info where this STI device is used */
	काष्ठा fb_info *info;

	/* poपूर्णांकer to all पूर्णांकernal data */
	काष्ठा sti_all_data *sti_data;
पूर्ण;


/* sticore पूर्णांकerface functions */

काष्ठा sti_काष्ठा *sti_get_rom(अचिन्हित पूर्णांक index); /* 0: शेष sti */
व्योम sti_font_convert_bytemode(काष्ठा sti_काष्ठा *sti, काष्ठा sti_cooked_font *f);


/* sticore मुख्य function to call STI firmware */

पूर्णांक sti_call(स्थिर काष्ठा sti_काष्ठा *sti, अचिन्हित दीर्घ func,
		स्थिर व्योम *flags, व्योम *inptr, व्योम *outptr,
		काष्ठा sti_glob_cfg *glob_cfg);


/* functions to call the STI ROM directly */

व्योम sti_अ_दो(काष्ठा sti_काष्ठा *sti, पूर्णांक c, पूर्णांक y, पूर्णांक x,
		काष्ठा sti_cooked_font *font);
व्योम sti_set(काष्ठा sti_काष्ठा *sti, पूर्णांक src_y, पूर्णांक src_x,
		पूर्णांक height, पूर्णांक width, u8 color);
व्योम sti_clear(काष्ठा sti_काष्ठा *sti, पूर्णांक src_y, पूर्णांक src_x,
		पूर्णांक height, पूर्णांक width, पूर्णांक c, काष्ठा sti_cooked_font *font);
व्योम sti_bmove(काष्ठा sti_काष्ठा *sti, पूर्णांक src_y, पूर्णांक src_x,
		पूर्णांक dst_y, पूर्णांक dst_x, पूर्णांक height, पूर्णांक width,
		काष्ठा sti_cooked_font *font);

#पूर्ण_अगर	/* STICORE_H */
