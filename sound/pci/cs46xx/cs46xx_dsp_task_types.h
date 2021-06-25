<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  The driver क्रम the Cirrus Logic's Sound Fusion CS46XX based soundcards
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *
 * NOTE: comments are copy/paste from cwcemb80.lst 
 * provided by Tom Woller at Cirrus (my only
 * करोcumentation about the SP OS running inside
 * the DSP) 
 */

#अगर_अघोषित __CS46XX_DSP_TASK_TYPES_H__
#घोषणा __CS46XX_DSP_TASK_TYPES_H__

#समावेश "cs46xx_dsp_scb_types.h"

/*********************************************************************************************
Example hierarchy of stream control blocks in the SP

hfgTree
Ptr____Call (c)
       \
 -------+------         -------------      -------------      -------------      -----
| SBlaster IF  |______\| Foreground  |___\| Middlegr'nd |___\| Background  |___\| Nul |
|              |Goto  /| tree header |g  /| tree header |g  /| tree header |g  /| SCB |r
 -------------- (g)     -------------      -------------      -------------      -----
       |c                     |c                 |c                 |c
       |                      |                  |                  |
      \/                  -------------      -------------      -------------   
                       | Foreground  |_\  | Middlegr'nd |_\  | Background  |_\
                       |     tree    |g/  |    tree     |g/  |     tree    |g/
                        -------------      -------------      -------------   
                              |c                 |c                 |c
                              |                  |                  | 
                             \/                 \/                 \/ 

*********************************************************************************************/

#घोषणा		HFG_FIRST_EXECUTE_MODE			0x0001
#घोषणा		HFG_FIRST_EXECUTE_MODE_BIT		0
#घोषणा		HFG_CONTEXT_SWITCH_MODE			0x0002
#घोषणा		HFG_CONTEXT_SWITCH_MODE_BIT		1

#घोषणा MAX_FG_STACK_SIZE 	32			/* THESE NEED TO BE COMPUTED PROPERLY */
#घोषणा MAX_MG_STACK_SIZE 	16
#घोषणा MAX_BG_STACK_SIZE 	9
#घोषणा MAX_HFG_STACK_SIZE	4

#घोषणा SLEEP_ACTIVE_INCREMENT		0		/* Enable task tree thपढ़ो to go to sleep
											   This should only ever be used on the Background thपढ़ो */
#घोषणा STANDARD_ACTIVE_INCREMENT	1		/* Task tree thपढ़ो normal operation */
#घोषणा SUSPEND_ACTIVE_INCREMENT	2		/* Cause execution to suspend in the task tree thपढ़ो
                                               This should only ever be used on the Background thपढ़ो */

#घोषणा HOSTFLAGS_DISABLE_BG_SLEEP  0       /* Host-controlled flag that determines whether we go to sleep
                                               at the end of BG */

/* Minimal context save area क्रम Hyper Forground */
काष्ठा dsp_hf_save_area अणु
	u32	r10_save;
	u32	r54_save;
	u32	r98_save;

	___DSP_DUAL_16BIT_ALLOC(
	    status_save,
	    ind_save
	)

	___DSP_DUAL_16BIT_ALLOC(
	    rci1_save,
	    rci0_save
	)

	u32	r32_save;
	u32	r76_save;
	u32	rsd2_save;

       	___DSP_DUAL_16BIT_ALLOC(
	      rsi2_save,	  /* See TaskTreeParameterBlock क्रम 
				     reमुख्यder of रेजिस्टरs  */
	      rsa2Save
	)
	/* saved as part of HFG context  */
पूर्ण;


/* Task link data काष्ठाure */
काष्ठा dsp_tree_link अणु
	___DSP_DUAL_16BIT_ALLOC(
	/* Poपूर्णांकer to sibling task control block */
	    next_scb,
	/* Poपूर्णांकer to child task control block */
	    sub_ptr
	)
  
	___DSP_DUAL_16BIT_ALLOC(
	/* Poपूर्णांकer to code entry poपूर्णांक */
	    entry_poपूर्णांक, 
	/* Poपूर्णांकer to local data */
	    this_spb
	)
पूर्ण;


काष्ठा dsp_task_tree_data अणु
	___DSP_DUAL_16BIT_ALLOC(
	/* Initial tock count; controls task tree execution rate */
	    tock_count_limit,
	/* Tock करोwn counter */
	    tock_count
	)

	/* Add to ActiveCount when TockCountLimit reached: 
	   Subtract on task tree termination */
	___DSP_DUAL_16BIT_ALLOC(
	    active_tncrement,		
	/* Number of pending activations क्रम task tree */
	    active_count
	)

        ___DSP_DUAL_16BIT_ALLOC(
	/* BitNumber to enable modअगरication of correct bit in ActiveTaskFlags */
	    active_bit,	    
	/* Poपूर्णांकer to OS location क्रम indicating current activity on task level */
	    active_task_flags_ptr
	)

	/* Data काष्ठाure क्रम controlling movement of memory blocks:- 
	   currently unused */
	___DSP_DUAL_16BIT_ALLOC(
	    mem_upd_ptr,
	/* Data काष्ठाure क्रम controlling synchronous link update */
	    link_upd_ptr
	)
  
	___DSP_DUAL_16BIT_ALLOC(
	/* Save area क्रम reमुख्यder of full context. */
	    save_area,
	/* Address of start of local stack क्रम data storage */
	    data_stack_base_ptr
	)

पूर्ण;


काष्ठा dsp_पूर्णांकerval_समयr_data
अणु
	/* These data items have the same relative locations to those */
	___DSP_DUAL_16BIT_ALLOC(
	     पूर्णांकerval_समयr_period,
	     itd_unused
	)

	/* used क्रम this data in the SPOS control block क्रम SPOS 1.0 */
	___DSP_DUAL_16BIT_ALLOC(
	     num_FG_ticks_this_पूर्णांकerval,        
	     num_पूर्णांकervals
	)
पूर्ण;


/* This काष्ठाure contains extra storage क्रम the task tree
   Currently, this additional data is related only to a full context save */
काष्ठा dsp_task_tree_context_block अणु
	/* Up to 10 values are saved onto the stack.  8 क्रम the task tree, 1 क्रम
	   The access to the context चयन (call or पूर्णांकerrupt), and 1 spare that
	   users should never use.  This last may be required by the प्रणाली */
	___DSP_DUAL_16BIT_ALLOC(
	     stack1,
	     stack0
	)
	___DSP_DUAL_16BIT_ALLOC(
	     stack3,
	     stack2
	)
	___DSP_DUAL_16BIT_ALLOC(
	     stack5,
	     stack4
	)
	___DSP_DUAL_16BIT_ALLOC(
	     stack7,
	     stack6
	)
	___DSP_DUAL_16BIT_ALLOC(
	     stack9,
	     stack8
	)

	u32	  saverfe;					

	/* Value may be overwritten by stack save algorithm.
	   Retain the size of the stack data saved here अगर used */
	___DSP_DUAL_16BIT_ALLOC(
             reserved1,	
  	     stack_size
	)
	u32		saverba;	  /* (HFG) */
	u32		saverdc;
	u32		savers_config_23; /* (HFG) */
	u32		savers_DMA23;	  /* (HFG) */
	u32		saversa0;
	u32		saversi0;
	u32		saversa1;
	u32		saversi1;
	u32		saversa3;
	u32		saversd0;
	u32		saversd1;
	u32		saversd3;
	u32		savers_config01;
	u32		savers_DMA01;
	u32		saveacc0hl;
	u32		saveacc1hl;
	u32		saveacc0xacc1x;
	u32		saveacc2hl;
	u32		saveacc3hl;
	u32		saveacc2xacc3x;
	u32		saveaux0hl;
	u32		saveaux1hl;
	u32		saveaux0xaux1x;
	u32		saveaux2hl;
	u32		saveaux3hl;
	u32		saveaux2xaux3x;
	u32		savershouthl;
	u32		savershoutxmacmode;
पूर्ण;
                

काष्ठा dsp_task_tree_control_block अणु
	काष्ठा dsp_hf_save_area			context;
	काष्ठा dsp_tree_link			links;
	काष्ठा dsp_task_tree_data		data;
	काष्ठा dsp_task_tree_context_block	context_blk;
	काष्ठा dsp_पूर्णांकerval_समयr_data		पूर्णांक_समयr;
पूर्ण;


#पूर्ण_अगर /* __DSP_TASK_TYPES_H__ */
