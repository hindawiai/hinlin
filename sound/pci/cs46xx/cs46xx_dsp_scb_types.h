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

#अगर_अघोषित __CS46XX_DSP_SCB_TYPES_H__
#घोषणा __CS46XX_DSP_SCB_TYPES_H__

#समावेश <यंत्र/byteorder.h>

#अगर_अघोषित ___DSP_DUAL_16BIT_ALLOC
#अगर   defined(__LITTLE_ENDIAN)
#घोषणा ___DSP_DUAL_16BIT_ALLOC(a,b) u16 a; u16 b;
#या_अगर defined(__BIG_ENDIAN)
#घोषणा ___DSP_DUAL_16BIT_ALLOC(a,b) u16 b; u16 a;
#अन्यथा
#त्रुटि Not __LITTLE_ENDIAN and not __BIG_ENDIAN, then what ???
#पूर्ण_अगर
#पूर्ण_अगर

/* This काष्ठाs are used पूर्णांकernally by the SP */

काष्ठा dsp_basic_dma_req अणु
	/* DMA Requestor Word 0 (DCW)  fields:

	   31 [30-28]27  [26:24] 23 22 21 20 [19:18] [17:16] 15 14 13  12  11 10 9 8 7 6  [5:0]
	   _______________________________________________________________________________________	
	   |S| SBT  |D|  DBT    |wb|wb|  |  |  LS  |  SS   |Opt|Do|SSG|DSG|  |  | | | | | Dword   |
	   |H|_____ |H|_________|S_|D |__|__|______|_______|___|ne|__ |__ |__|__|_|_|_|_|_Count -1|
	*/
	u32 dcw;                 /* DMA Control Word */
	u32 dmw;                 /* DMA Mode Word */
	u32 saw;                 /* Source Address Word */
	u32 daw;                 /* Destination Address Word  */
पूर्ण;

काष्ठा dsp_scatter_gather_ext अणु
	u32 npaw;                /* Next-Page Address Word */

	/* DMA Requestor Word 5 (NPCW)  fields:
     
	   31-30 29 28          [27:16]              [15:12]             [11:3]                [2:0] 				
	   _________________________________________________________________________________________	
	   |SV  |LE|SE|   Sample-end byte offset   |         | Page-map entry offset क्रम next  |    | 
	   |page|__|__| ___________________________|_________|__page, अगर !sample-end___________|____|
	*/
	u32 npcw;                /* Next-Page Control Word */
	u32 lbaw;                /* Loop-Begin Address Word */
	u32 nplbaw;              /* Next-Page after Loop-Begin Address Word */
	u32 sgaw;                /* Scatter/Gather Address Word */
पूर्ण;

काष्ठा dsp_volume_control अणु
	___DSP_DUAL_16BIT_ALLOC(
	   rightTarg,  /* Target volume क्रम left & right channels */
	   leftTarg
	)
	___DSP_DUAL_16BIT_ALLOC(
	   rightVol,   /* Current left & right channel volumes */
	   leftVol
	)
पूर्ण;

/* Generic stream control block (SCB) काष्ठाure definition */
काष्ठा dsp_generic_scb अणु
	/* For streaming I/O, the DSP should never alter any words in the DMA
	   requestor or the scatter/gather extension.  Only ad hoc DMA request
	   streams are मुक्त to alter the requestor (currently only occur in the
	   DOS-based MIDI controller and in debugger-inserted code).
    
	   If an SCB करोes not have any associated DMA requestor, these 9 पूर्णांकs
	   may be मुक्तd क्रम use by other tasks, but the poपूर्णांकer to the SCB must
	   still be such that the insOrd:nextSCB appear at offset 9 from the
	   SCB poपूर्णांकer.
     
	   Basic (non scatter/gather) DMA requestor (4 पूर्णांकs)
	*/
  
	/* Initialized by the host, only modअगरied by DMA 
	   R/O क्रम the DSP task */
	काष्ठा dsp_basic_dma_req  basic_req;  /* Optional */

	/* Scatter/gather DMA requestor extension   (5 पूर्णांकs) 
	   Initialized by the host, only modअगरied by DMA
	   DSP task never needs to even पढ़ो these.
	*/
	काष्ठा dsp_scatter_gather_ext sg_ext;  /* Optional */

	/* Sublist poपूर्णांकer & next stream control block (SCB) link.
	   Initialized & modअगरied by the host R/O क्रम the DSP task
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    next_scb,     /* REQUIRED */
	    sub_list_ptr  /* REQUIRED */
	)
  
	/* Poपूर्णांकer to this tasks parameter block & stream function poपूर्णांकer 
	   Initialized by the host  R/O क्रम the DSP task */
	___DSP_DUAL_16BIT_ALLOC(
	    entry_poपूर्णांक,  /* REQUIRED */
	    this_spb      /* REQUIRED */
	)

	/* rsConfig रेजिस्टर क्रम stream buffer (rsDMA reg. 
	   is loaded from basicReq.daw क्रम incoming streams, or 
	   basicReq.saw, क्रम outgoing streams) 

	   31 30 29  [28:24]     [23:16] 15 14 13 12 11 10 9 8 7 6  5      4      [3:0]
	   ______________________________________________________________________________
	   |DMA  |D|maxDMAsize| streamNum|dir|p|  |  |  |  | | |ds |shr 1|rev Cy | mod   |
	   |prio |_|__________|__________|___|_|__|__|__|__|_|_|___|_____|_______|_______|
	   31 30 29  [28:24]     [23:16] 15 14 13 12 11 10 9 8 7 6  5      4      [3:0]


	   Initialized by the host R/O क्रम the DSP task
	*/
	u32  strm_rs_config; /* REQUIRED */
               // 
	/* On mixer input streams: indicates mixer input stream configuration
	   On Tees, this is copied from the stream being snooped

	   Stream sample poपूर्णांकer & MAC-unit mode क्रम this stream 
     
	   Initialized by the host Updated by the DSP task
	*/
	u32  strm_buf_ptr; /* REQUIRED  */

	/* On mixer input streams: poपूर्णांकs to next mixer input and is updated by the
                                   mixer subroutine in the "parent" DSP task
				   (least-signअगरicant 16 bits are preserved, unused)
    
           On Tees, the poपूर्णांकer is copied from the stream being snooped on
	   initialization, and, subsequently, it is copied पूर्णांकo the
	   stream being snooped.

	   On wavetable/3D voices: the strmBufPtr will use all 32 bits to allow क्रम
                                   fractional phase accumulation

	   Fractional increment per output sample in the input sample buffer

	   (Not used on mixer input streams & redefined on Tees)
	   On wavetable/3D voices: this 32-bit word specअगरies the पूर्णांकeger.fractional 
	   increment per output sample.
	*/
	u32  strmPhiIncr;


	/* Standard stereo volume control
	   Initialized by the host (host updates target volumes) 

	   Current volumes update by the DSP task
	   On mixer input streams: required & updated by the mixer subroutine in the
                                   "parent" DSP task

	   On Tees, both current & target volumes are copied up on initialization,
	   and, subsequently, the target volume is copied up जबतक the current
	   volume is copied करोwn.
     
	   These two 32-bit words are redefined क्रम wavetable & 3-D voices.    
	*/
	काष्ठा dsp_volume_control vol_ctrl_t;   /* Optional */
पूर्ण;


काष्ठा dsp_spos_control_block अणु
	/* WARNING: Certain items in this काष्ठाure are modअगरied by the host
	            Any dword that can be modअगरied by the host, must not be
		    modअगरied by the SP as the host can only करो atomic dword
		    ग_लिखोs, and to करो otherwise, even a पढ़ो modअगरy ग_लिखो, 
		    may lead to corrupted data on the SP.
  
		    This rule करोes not apply to one off boot समय initialisation prior to starting the SP
	*/


	___DSP_DUAL_16BIT_ALLOC( 
	/* First element on the Hyper क्रमground task tree */
	    hfg_tree_root_ptr,  /* HOST */			    
	/* First 3 dwords are written by the host and पढ़ो-only on the DSP */
	    hfg_stack_base      /* HOST */
	)

	___DSP_DUAL_16BIT_ALLOC(
	/* Poपूर्णांक to this data काष्ठाure to enable easy access */
	    spos_cb_ptr,	 /* SP */
	    prev_task_tree_ptr   /* SP && HOST */
	)

	___DSP_DUAL_16BIT_ALLOC(
	/* Currently Unused */
	    xxपूर्णांकerval_समयr_period,
	/* Enable extension of SPOS data काष्ठाure */
	    HFGSPB_ptr
	)


	___DSP_DUAL_16BIT_ALLOC(
	    xxnum_HFG_ticks_thisInterval,
	/* Modअगरied by the DSP */
	    xxnum_tntervals
	)


	/* Set by DSP upon encountering a trap (अवरोधpoपूर्णांक) or a spurious
	   पूर्णांकerrupt.  The host must clear this dword after पढ़ोing it
	   upon receiving spInt1. */
	___DSP_DUAL_16BIT_ALLOC(
	    spurious_पूर्णांक_flag,	 /* (Host & SP) Nature of the spurious पूर्णांकerrupt */
	    trap_flag            /* (Host & SP) Nature of detected Trap */
	)

	___DSP_DUAL_16BIT_ALLOC(
	    unused2,					
	    invalid_IP_flag        /* (Host & SP ) Indicate detection of invalid inकाष्ठाion poपूर्णांकer */
	)

	___DSP_DUAL_16BIT_ALLOC(
	/* poपूर्णांकer to क्रमground task tree header क्रम use in next task search */
	    fg_task_tree_hdr_ptr,	  /* HOST */		
	/* Data काष्ठाure क्रम controlling synchronous link update */
	    hfg_sync_update_ptr           /* HOST */
	)
  
	___DSP_DUAL_16BIT_ALLOC(
	     begin_क्रमeground_FCNT,  /* SP */
	/* Place holder क्रम holding sleep timing */
	     last_FCNT_beक्रमe_sleep  /* SP */
	)

	___DSP_DUAL_16BIT_ALLOC(
	    unused7,           /* SP */
	    next_task_treePtr  /* SP */
	)

	u32 unused5;        

	___DSP_DUAL_16BIT_ALLOC(
	    active_flags,   /* SP */
	/* State flags, used to assist control of execution of Hyper Forground */
	    HFG_flags       /* SP */
	)

	___DSP_DUAL_16BIT_ALLOC(
	    unused9,
	    unused8
	)
                              
	/* Space क्रम saving enough context so that we can set up enough 
	   to save some more context.
	*/
	u32 rFE_save_क्रम_invalid_IP;
	u32 r32_save_क्रम_spurious_पूर्णांक;
	u32 r32_save_क्रम_trap;
	u32 r32_save_क्रम_HFG;
पूर्ण;

/* SPB क्रम MIX_TO_OSTREAM algorithm family */
काष्ठा dsp_mix2_ostream_spb
अणु
	/* 16b.16b पूर्णांकeger.frac approximation to the
	   number of 3 sample triplets to output each
	   frame. (approximation must be न्यूनमान, to
	   insure that the fractional error is always
	   positive)
	*/
	u32 outTripletsPerFrame;

	/* 16b.16b पूर्णांकeger.frac accumulated number of
	   output triplets since the start of group 
	*/
	u32 accumOutTriplets;  
पूर्ण;

/* SCB क्रम Timing master algorithm */
काष्ठा dsp_timing_master_scb अणु
	/* First 12 dwords from generic_scb_t */
	काष्ठा dsp_basic_dma_req  basic_req;  /* Optional */
	काष्ठा dsp_scatter_gather_ext sg_ext;  /* Optional */
	___DSP_DUAL_16BIT_ALLOC(
	    next_scb,     /* REQUIRED */
	    sub_list_ptr  /* REQUIRED */
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_poपूर्णांक,  /* REQUIRED */
	    this_spb      /* REQUIRED */
	)

	___DSP_DUAL_16BIT_ALLOC(
	/* Initial values are 0000:xxxx */
 	    reserved,
	    extra_sample_accum
	)

  
	/* Initial values are xxxx:0000
	   hi: Current CODEC output FIFO poपूर्णांकer
	       (0 to 0x0f)
           lo: Flag indicating that the CODEC
	       FIFO is sync'd (host clears to
	       resynchronize the FIFO poपूर्णांकer
	       upon start/restart) 
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    codec_FIFO_syncd, 
	    codec_FIFO_ptr
	)
  
	/* Init. 8000:0005 क्रम 44.1k
                 8000:0001 क्रम 48k
	   hi: Fractional sample accumulator 0.16b
	   lo: Number of frames reमुख्यing to be
	       processed in the current group of
	       frames
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    frac_samp_accum_qm1,
	    TM_frms_left_in_group
	) 

	/* Init. 0001:0005 क्रम 44.1k
                 0000:0001 क्रम 48k
	   hi: Fractional sample correction factor 0.16b
	       to be added every frameGroupLength frames
	       to correct क्रम truncation error in
	       nsamp_per_frm_q15
	   lo: Number of frames in the group
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    frac_samp_correction_qm1,
	    TM_frm_group_length  
	)

	/* Init. 44.1k*65536/8k = 0x00058333 क्रम 44.1k
                 48k*65536/8k = 0x00060000 क्रम 48k
	   16b.16b पूर्णांकeger.frac approximation to the
	   number of samples to output each frame.
	   (approximation must be न्यूनमान, to insure */
	u32 nsamp_per_frm_q15;
पूर्ण;

/* SCB क्रम CODEC output algorithm */
काष्ठा dsp_codec_output_scb अणु
	/* First 13 dwords from generic_scb_t */
	काष्ठा dsp_basic_dma_req  basic_req;  /* Optional */
	काष्ठा dsp_scatter_gather_ext sg_ext;  /* Optional */
	___DSP_DUAL_16BIT_ALLOC(
	    next_scb,       /* REQUIRED */
	    sub_list_ptr    /* REQUIRED */
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_poपूर्णांक,    /* REQUIRED */
	    this_spb        /* REQUIRED */
	)

	u32 strm_rs_config; /* REQUIRED */

	u32 strm_buf_ptr;   /* REQUIRED */

	/* NOTE: The CODEC output task पढ़ोs samples from the first task on its
                 sublist at the stream buffer poपूर्णांकer (init. to lag DMA destination
		 address word).  After the required number of samples is transferred,
		 the CODEC output task advances sub_list_ptr->strm_buf_ptr past the samples
		 consumed.
	*/

	/* Init. 0000:0010 क्रम SDout
                 0060:0010 क्रम SDout2
		 0080:0010 क्रम SDout3
	   hi: Base IO address of FIFO to which
	       the left-channel samples are to
	       be written.
	   lo: Displacement क्रम the base IO
	       address क्रम left-channel to obtain
	       the base IO address क्रम the FIFO
	       to which the right-channel samples
	       are to be written.
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    left_chan_base_IO_addr,
	    right_chan_IO_disp
	)


	/* Init: 0x0080:0004 क्रम non-AC-97
	   Init: 0x0080:0000 क्रम AC-97
	   hi: Exponential volume change rate
	       क्रम input stream
	   lo: Positive shअगरt count to shअगरt the
	       16-bit input sample to obtain the
	       32-bit output word
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    CO_scale_shअगरt_count, 
	    CO_exp_vol_change_rate
	)

	/* Poपूर्णांकer to SCB at end of input chain */
	___DSP_DUAL_16BIT_ALLOC(
	    reserved,
	    last_sub_ptr
	)
पूर्ण;

/* SCB क्रम CODEC input algorithm */
काष्ठा dsp_codec_input_scb अणु
	/* First 13 dwords from generic_scb_t */
	काष्ठा dsp_basic_dma_req  basic_req;  /* Optional */
	काष्ठा dsp_scatter_gather_ext sg_ext;  /* Optional */
	___DSP_DUAL_16BIT_ALLOC(
	    next_scb,       /* REQUIRED */
	    sub_list_ptr    /* REQUIRED */
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_poपूर्णांक,    /* REQUIRED */
	    this_spb        /* REQUIRED */
	)

	u32 strm_rs_config; /* REQUIRED */
	u32 strm_buf_ptr;   /* REQUIRED */

	/* NOTE: The CODEC input task पढ़ोs samples from the hardware FIFO 
                 sublist at the DMA source address word (sub_list_ptr->basic_req.saw).
                 After the required number of samples is transferred, the CODEC
                 output task advances sub_list_ptr->basic_req.saw past the samples
                 consumed.  SPuD must initialize the sub_list_ptr->basic_req.saw
                 to poपूर्णांक half-way around from the initial sub_list_ptr->strm_nuf_ptr
                 to allow क्रम lag/lead.
	*/

	/* Init. 0000:0010 क्रम SDout
                 0060:0010 क्रम SDout2
		 0080:0010 क्रम SDout3
	   hi: Base IO address of FIFO to which
	       the left-channel samples are to
	       be written.
	   lo: Displacement क्रम the base IO
	       address क्रम left-channel to obtain
	       the base IO address क्रम the FIFO
	       to which the right-channel samples
	       are to be written.
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    rightChanINdisp, 
	    left_chan_base_IN_addr
	)
	/* Init. ?:fffc
	   lo: Negative shअगरt count to shअगरt the
	       32-bit input dword to obtain the
	       16-bit sample msb-aligned (count
	       is negative to shअगरt left)
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    scaleShअगरtCount, 
	    reserver1
	)

	u32  reserved2;
पूर्ण;


काष्ठा dsp_pcm_serial_input_scb अणु
	/* First 13 dwords from generic_scb_t */
	काष्ठा dsp_basic_dma_req  basic_req;  /* Optional */
	काष्ठा dsp_scatter_gather_ext sg_ext;  /* Optional */
	___DSP_DUAL_16BIT_ALLOC(
	    next_scb,       /* REQUIRED */
	    sub_list_ptr    /* REQUIRED */
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_poपूर्णांक,    /* REQUIRED */
	    this_spb        /* REQUIRED */
	)

	u32 strm_buf_ptr;   /* REQUIRED */
	u32 strm_rs_config; /* REQUIRED */
  
	/* Init. Ptr to CODEC input SCB
	   hi: Poपूर्णांकer to the SCB containing the
	       input buffer to which CODEC input
	       samples are written
	   lo: Flag indicating the link to the CODEC
	       input task is to be initialized
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    init_codec_input_link,
	    codec_input_buf_scb
	)

	/* Initialized by the host (host updates target volumes) */
	काष्ठा dsp_volume_control psi_vol_ctrl;   
  
पूर्ण;

काष्ठा dsp_src_task_scb अणु
	___DSP_DUAL_16BIT_ALLOC(
	    frames_left_in_gof,
	    gofs_left_in_sec
	)

	___DSP_DUAL_16BIT_ALLOC(
	    स्थिर2_thirds,
	    num_extra_tnput_samples
	)

	___DSP_DUAL_16BIT_ALLOC(
	    cor_per_gof,
	    correction_per_sec 
	)

	___DSP_DUAL_16BIT_ALLOC(
	    output_buf_producer_ptr,  
	    junk_DMA_MID
	)

	___DSP_DUAL_16BIT_ALLOC(
	    gof_length,  
	    gofs_per_sec
	)

	u32 input_buf_strm_config;

	___DSP_DUAL_16BIT_ALLOC(
	    reserved_क्रम_SRC_use,
	    input_buf_consumer_ptr
	)

	u32 accum_phi;

	___DSP_DUAL_16BIT_ALLOC(
	    exp_src_vol_change_rate,
	    input_buf_producer_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    src_next_scb,
	    src_sub_list_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    src_entry_poपूर्णांक,
	    src_this_sbp
	)

	u32  src_strm_rs_config;
	u32  src_strm_buf_ptr;
  
	u32   phiIncr6पूर्णांक_26frac;
  
	काष्ठा dsp_volume_control src_vol_ctrl;
पूर्ण;

काष्ठा dsp_decimate_by_घात2_scb अणु
	/* decimationFactor = 2, 4, or 8 (larger factors waste too much memory
	                                  when compared to cascading decimators)
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    dec2_coef_base_ptr,
	    dec2_coef_increment
	)

	/* coefIncrement = 128 / decimationFactor (क्रम our ROM filter)
	   coefBasePtr = 0x8000 (क्रम our ROM filter)
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    dec2_in_samples_per_out_triplet,
	    dec2_extra_in_samples
	)
	/* extraInSamples: # of accumulated, unused input samples (init. to 0)
	   inSamplesPerOutTriplet = 3 * decimationFactor
	*/

	___DSP_DUAL_16BIT_ALLOC(
	    dec2_स्थिर2_thirds,
	    dec2_half_num_taps_mp5
	)
	/* halfNumTapsM5: (1/2 number of taps in decimation filter) minus 5
	   स्थिर2thirds: स्थिरant 2/3 in 16Q0 क्रमmat (sign.15)
	*/

	___DSP_DUAL_16BIT_ALLOC(
	    dec2_output_buf_producer_ptr,
	    dec2_junkdma_mid
	)

	u32  dec2_reserved2;

	u32  dec2_input_nuf_strm_config;
	/* inputBufStrmConfig: rsConfig क्रम the input buffer to the decimator
	   (buffer size = decimationFactor * 32 dwords)
	*/

	___DSP_DUAL_16BIT_ALLOC(
	    dec2_phi_incr,
	    dec2_input_buf_consumer_ptr
	)
	/* inputBufConsumerPtr: Input buffer पढ़ो poपूर्णांकer (पूर्णांकo SRC filter)
	   phiIncr = decimationFactor * 4
	*/

	u32 dec2_reserved3;

	___DSP_DUAL_16BIT_ALLOC(
	    dec2_exp_vol_change_rate,
	    dec2_input_buf_producer_ptr
	)
	/* inputBufProducerPtr: Input buffer ग_लिखो poपूर्णांकer
	   expVolChangeRate: Exponential volume change rate क्रम possible
	                     future mixer on input streams
	*/

	___DSP_DUAL_16BIT_ALLOC(
	    dec2_next_scb,
	    dec2_sub_list_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    dec2_entry_poपूर्णांक,
	    dec2_this_spb
	)

	u32  dec2_strm_rs_config;
	u32  dec2_strm_buf_ptr;

	u32  dec2_reserved4;

	काष्ठा dsp_volume_control dec2_vol_ctrl; /* Not used! */
पूर्ण;

काष्ठा dsp_vari_decimate_scb अणु
	___DSP_DUAL_16BIT_ALLOC(
	    vdec_frames_left_in_gof,
	    vdec_gofs_left_in_sec
	)

	___DSP_DUAL_16BIT_ALLOC(
	    vdec_स्थिर2_thirds,
	    vdec_extra_in_samples
	)
	/* extraInSamples: # of accumulated, unused input samples (init. to 0)
	   स्थिर2thirds: स्थिरant 2/3 in 16Q0 क्रमmat (sign.15) */

	___DSP_DUAL_16BIT_ALLOC(
	    vdec_cor_per_gof,
	    vdec_correction_per_sec
	)

	___DSP_DUAL_16BIT_ALLOC(
	    vdec_output_buf_producer_ptr,
	    vdec_input_buf_consumer_ptr
	)
	/* inputBufConsumerPtr: Input buffer पढ़ो poपूर्णांकer (पूर्णांकo SRC filter) */
	___DSP_DUAL_16BIT_ALLOC(
	    vdec_gof_length,
	    vdec_gofs_per_sec
	)

	u32  vdec_input_buf_strm_config;
	/* inputBufStrmConfig: rsConfig क्रम the input buffer to the decimator
	   (buffer size = 64 dwords) */
	u32  vdec_coef_increment;
	/* coefIncrement = - 128.0 / decimationFactor (as a 32Q15 number) */

	u32  vdec_accumphi;
	/* accumPhi: accumulated fractional phase increment (6.26) */

	___DSP_DUAL_16BIT_ALLOC(
 	    vdec_exp_vol_change_rate,
	    vdec_input_buf_producer_ptr
	)
	/* inputBufProducerPtr: Input buffer ग_लिखो poपूर्णांकer
	   expVolChangeRate: Exponential volume change rate क्रम possible
	   future mixer on input streams */

	___DSP_DUAL_16BIT_ALLOC(
	    vdec_next_scb,
	    vdec_sub_list_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    vdec_entry_poपूर्णांक,
	    vdec_this_spb
	)

	u32 vdec_strm_rs_config;
	u32 vdec_strm_buf_ptr;

	u32 vdec_phi_incr_6पूर्णांक_26frac;

	काष्ठा dsp_volume_control vdec_vol_ctrl;
पूर्ण;


/* SCB क्रम MIX_TO_OSTREAM algorithm family */
काष्ठा dsp_mix2_ostream_scb अणु
	/* First 13 dwords from generic_scb_t */
	काष्ठा dsp_basic_dma_req  basic_req;  /* Optional */
	काष्ठा dsp_scatter_gather_ext sg_ext;  /* Optional */
	___DSP_DUAL_16BIT_ALLOC(
	    next_scb,       /* REQUIRED */
	    sub_list_ptr    /* REQUIRED */
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_poपूर्णांक,    /* REQUIRED */
	    this_spb        /* REQUIRED */
	)

	u32 strm_rs_config; /* REQUIRED */
	u32 strm_buf_ptr;   /* REQUIRED */


	/* hi: Number of mixed-करोwn input triplets
	       computed since start of group
	   lo: Number of frames reमुख्यing to be
	       processed in the current group of
	       frames
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    frames_left_in_group,
	    accum_input_triplets
	)

	/* hi: Exponential volume change rate
	       क्रम mixer on input streams
	   lo: Number of frames in the group
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    frame_group_length,
	    exp_vol_change_rate
	)
  
	___DSP_DUAL_16BIT_ALLOC(
	    स्थिर_FFFF,
	    स्थिर_zero
	)
पूर्ण;


/* SCB क्रम S16_MIX algorithm */
काष्ठा dsp_mix_only_scb अणु
	/* First 13 dwords from generic_scb_t */
	काष्ठा dsp_basic_dma_req  basic_req;  /* Optional */
	काष्ठा dsp_scatter_gather_ext sg_ext;  /* Optional */
	___DSP_DUAL_16BIT_ALLOC(
	    next_scb,       /* REQUIRED */
	    sub_list_ptr    /* REQUIRED */
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_poपूर्णांक,    /* REQUIRED */
	    this_spb        /* REQUIRED */
	)

	u32 strm_rs_config; /* REQUIRED */
	u32 strm_buf_ptr;   /* REQUIRED */

	u32 reserved;
	काष्ठा dsp_volume_control vol_ctrl;
पूर्ण;

/* SCB क्रम the async. CODEC input algorithm */
काष्ठा dsp_async_codec_input_scb अणु
	u32 io_मुक्त2;     
  
	u32 io_current_total;
	u32 io_previous_total;
  
	u16 io_count;
	u16 io_count_limit;
  
	u16 o_fअगरo_base_addr;            
	u16 ost_mo_क्रमmat;
	/* 1 = stereo; 0 = mono 
	   xxx क्रम ASER 1 (not allowed); 118 क्रम ASER2 */

	u32  ostrm_rs_config;
	u32  ostrm_buf_ptr;
  
	___DSP_DUAL_16BIT_ALLOC(
	    io_sclks_per_lr_clk,
	    io_io_enable
	)

	u32  io_मुक्त4;

	___DSP_DUAL_16BIT_ALLOC(  
	    io_next_scb,
	    io_sub_list_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    io_entry_poपूर्णांक,
	    io_this_spb
	)

	u32 istrm_rs_config;
	u32 istrm_buf_ptr;

	/* Init. 0000:8042: क्रम ASER1
                 0000:8044: क्रम ASER2  */
	___DSP_DUAL_16BIT_ALLOC(
	    io_stat_reg_addr,
	    iofअगरo_poपूर्णांकer
	)

	/* Init 1 stero:100 ASER1
	   Init 0 mono:110 ASER2 
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    अगरअगरo_base_addr,            
	    ist_mo_क्रमmat
	)

	u32 i_मुक्त;
पूर्ण;


/* SCB क्रम the SP/DIF CODEC input and output */
काष्ठा dsp_spdअगरiscb अणु
	___DSP_DUAL_16BIT_ALLOC(
	    status_ptr,     
	    status_start_ptr
	)

	u32 current_total;
	u32 previous_total;

	___DSP_DUAL_16BIT_ALLOC(
	    count,
	    count_limit
	)

	u32 status_data;

	___DSP_DUAL_16BIT_ALLOC(  
	    status,
	    मुक्त4
	)

	u32 मुक्त3;

	___DSP_DUAL_16BIT_ALLOC(  
	    मुक्त2,
	    bit_count
	)

	u32  temp_status;
  
	___DSP_DUAL_16BIT_ALLOC(
	    next_SCB,
	    sub_list_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_poपूर्णांक,
	    this_spb
	)

	u32  strm_rs_config;
	u32  strm_buf_ptr;
  
	___DSP_DUAL_16BIT_ALLOC(
	    stat_reg_addr, 
	    fअगरo_poपूर्णांकer
	)

	___DSP_DUAL_16BIT_ALLOC(
	    fअगरo_base_addr, 
	    st_mo_क्रमmat
	)

	u32  मुक्त1;
पूर्ण;


/* SCB क्रम the SP/DIF CODEC input and output  */
काष्ठा dsp_spdअगरoscb अणु		 

	u32 मुक्त2;     

	u32 मुक्त3[4];             

	/* Need to be here क्रम compatibility with AsynchFGTxCode */
	u32 strm_rs_config;
                               
	u32 strm_buf_ptr;

	___DSP_DUAL_16BIT_ALLOC(  
	    status,
	    मुक्त5
	)

	u32 मुक्त4;

	___DSP_DUAL_16BIT_ALLOC(  
	    next_scb,
	    sub_list_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_poपूर्णांक,
	    this_spb
	)

	u32 मुक्त6[2];
  
	___DSP_DUAL_16BIT_ALLOC(
	    stat_reg_addr, 
	    fअगरo_poपूर्णांकer
	)

	___DSP_DUAL_16BIT_ALLOC(
	    fअगरo_base_addr,
	    st_mo_क्रमmat
	)

	u32  मुक्त1;                                         
पूर्ण;


काष्ठा dsp_asynch_fg_rx_scb अणु
	___DSP_DUAL_16BIT_ALLOC(
	    bot_buf_mask,
	    buf_Mask
	)

	___DSP_DUAL_16BIT_ALLOC(
	    max,
	    min
	)

	___DSP_DUAL_16BIT_ALLOC(
	    old_producer_poपूर्णांकer,
	    hfg_scb_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    delta,
	    adjust_count
	)

	u32 unused2[5];  

	___DSP_DUAL_16BIT_ALLOC(  
	    sibling_ptr,  
	    child_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    code_ptr,
	    this_ptr
	)

	u32 strm_rs_config; 

	u32 strm_buf_ptr;
  
	u32 unused_phi_incr;
  
	___DSP_DUAL_16BIT_ALLOC(
	    right_targ,   
	    left_targ
	)

	___DSP_DUAL_16BIT_ALLOC(
	    right_vol,
	    left_vol
	)
पूर्ण;


काष्ठा dsp_asynch_fg_tx_scb अणु
	___DSP_DUAL_16BIT_ALLOC(
	    not_buf_mask,
	    buf_mask
	)

	___DSP_DUAL_16BIT_ALLOC(
	    max,
	    min
	)

	___DSP_DUAL_16BIT_ALLOC(
	    unused1,
	    hfg_scb_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    delta,
	    adjust_count
	)

	u32 accum_phi;

	___DSP_DUAL_16BIT_ALLOC(
	    unused2,
	    स्थिर_one_third
	)

	u32 unused3[3];

	___DSP_DUAL_16BIT_ALLOC(
	    sibling_ptr,
	    child_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    codePtr,
	    this_ptr
	)

	u32 strm_rs_config;

	u32 strm_buf_ptr;

	u32 phi_incr;

	___DSP_DUAL_16BIT_ALLOC(
	    unused_right_targ,
	    unused_left_targ
	)

	___DSP_DUAL_16BIT_ALLOC(
	    unused_right_vol,
	    unused_left_vol
	)
पूर्ण;


काष्ठा dsp_output_snoop_scb अणु
	/* First 13 dwords from generic_scb_t */
	काष्ठा dsp_basic_dma_req  basic_req;  /* Optional */
	काष्ठा dsp_scatter_gather_ext sg_ext;  /* Optional */
	___DSP_DUAL_16BIT_ALLOC(
	    next_scb,       /* REQUIRED */
	    sub_list_ptr    /* REQUIRED */
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_poपूर्णांक,    /* REQUIRED */
	    this_spb        /* REQUIRED */
	)

	u32 strm_rs_config; /* REQUIRED */
	u32 strm_buf_ptr;   /* REQUIRED */

	___DSP_DUAL_16BIT_ALLOC(
	    init_snoop_input_link,
	    snoop_child_input_scb
	)

	u32 snoop_input_buf_ptr;

	___DSP_DUAL_16BIT_ALLOC(
	    reserved,
	    input_scb
	)
पूर्ण;

काष्ठा dsp_spio_ग_लिखो_scb अणु
	___DSP_DUAL_16BIT_ALLOC(
	    address1,
	    address2
	)

	u32 data1;

	u32 data2;

	___DSP_DUAL_16BIT_ALLOC(
	    address3,
	    address4
	)

	u32 data3;

	u32 data4;

	___DSP_DUAL_16BIT_ALLOC(
	    unused1,
	    data_ptr
	)

	u32 unused2[2];

	___DSP_DUAL_16BIT_ALLOC(
	    sibling_ptr,
	    child_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_poपूर्णांक,
	    this_ptr
	)

	u32 unused3[5];
पूर्ण;

काष्ठा dsp_magic_snoop_task अणु
	u32 i0;
	u32 i1;

	u32 strm_buf_ptr1;
  
	u16 i2;
	u16 snoop_scb;

	u32 i3;
	u32 i4;
	u32 i5;
	u32 i6;

	u32 i7;

	___DSP_DUAL_16BIT_ALLOC(
	    next_scb,
	    sub_list_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_poपूर्णांक,
	    this_ptr
	)

	u32 strm_buf_config;
	u32 strm_buf_ptr2;

	u32 i8;

	काष्ठा dsp_volume_control vdec_vol_ctrl;
पूर्ण;


काष्ठा dsp_filter_scb अणु
	___DSP_DUAL_16BIT_ALLOC(
	      a0_right,          /* 0x00 */
	      a0_left
	)
	___DSP_DUAL_16BIT_ALLOC(
	      a1_right,          /* 0x01 */
	      a1_left
	)
	___DSP_DUAL_16BIT_ALLOC(
	      a2_right,          /* 0x02 */
	      a2_left
	)
	___DSP_DUAL_16BIT_ALLOC(
	      output_buf_ptr,    /* 0x03 */
	      init
	)

	___DSP_DUAL_16BIT_ALLOC(
	      filter_unused3,    /* 0x04 */
	      filter_unused2
	)

	u32 prev_sample_output1; /* 0x05 */
	u32 prev_sample_output2; /* 0x06 */
	u32 prev_sample_input1;  /* 0x07 */
	u32 prev_sample_input2;  /* 0x08 */

	___DSP_DUAL_16BIT_ALLOC(
	      next_scb_ptr,      /* 0x09 */
	      sub_list_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	      entry_poपूर्णांक,       /* 0x0A */
	      spb_ptr
	)

	u32  strm_rs_config;     /* 0x0B */
	u32  strm_buf_ptr;       /* 0x0C */

	___DSP_DUAL_16BIT_ALLOC(
              b0_right,          /* 0x0D */
	      b0_left
	)
	___DSP_DUAL_16BIT_ALLOC(
              b1_right,          /* 0x0E */
	      b1_left
	)
	___DSP_DUAL_16BIT_ALLOC(
              b2_right,          /* 0x0F */
	      b2_left
	)
पूर्ण;
#पूर्ण_अगर /* __DSP_SCB_TYPES_H__ */
