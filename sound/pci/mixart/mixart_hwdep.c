<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Digigram miXart soundcards
 *
 * DSP firmware management
 *
 * Copyright (c) 2003 by Digigram <alsa@digigram.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/firmware.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश "mixart.h"
#समावेश "mixart_mixer.h"
#समावेश "mixart_core.h"
#समावेश "mixart_hwdep.h"


/**
 * mixart_रुको_nice_क्रम_रेजिस्टर_value - रुको क्रम a value on a peuकरो रेजिस्टर,
 * निकास with a समयout
 *
 * @mgr: poपूर्णांकer to miXart manager काष्ठाure
 * @offset: अचिन्हित pseuकरो_रेजिस्टर base + offset of value
 * @is_egal: रुको क्रम the equal value
 * @value: value
 * @समयout: समयout in centisenconds
 */
अटल पूर्णांक mixart_रुको_nice_क्रम_रेजिस्टर_value(काष्ठा mixart_mgr *mgr,
					       u32 offset, पूर्णांक is_egal,
					       u32 value, अचिन्हित दीर्घ समयout)
अणु
	अचिन्हित दीर्घ end_समय = jअगरfies + (समयout * HZ / 100);
	u32 पढ़ो;

	करो अणु	/* we may take too दीर्घ समय in this loop.
		 * so give controls back to kernel अगर needed.
		 */
		cond_resched();

		पढ़ो = पढ़ोl_be( MIXART_MEM( mgr, offset ));
		अगर(is_egal) अणु
			अगर(पढ़ो == value) वापस 0;
		पूर्ण
		अन्यथा अणु /* रुको क्रम dअगरferent value */
			अगर(पढ़ो != value) वापस 0;
		पूर्ण
	पूर्ण जबतक ( समय_after_eq(end_समय, jअगरfies) );

	वापस -EBUSY;
पूर्ण


/*
  काष्ठाures needed to upload elf code packets 
 */
काष्ठा snd_mixart_elf32_ehdr अणु
	u8      e_ident[16];
	__be16  e_type;
	__be16  e_machine;
	__be32  e_version;
	__be32  e_entry;
	__be32  e_phoff;
	__be32  e_shoff;
	__be32  e_flags;
	__be16  e_ehsize;
	__be16  e_phentsize;
	__be16  e_phnum;
	__be16  e_shentsize;
	__be16  e_shnum;
	__be16  e_shstrndx;
पूर्ण;

काष्ठा snd_mixart_elf32_phdr अणु
	__be32  p_type;
	__be32  p_offset;
	__be32  p_vaddr;
	__be32  p_paddr;
	__be32  p_filesz;
	__be32  p_memsz;
	__be32  p_flags;
	__be32  p_align;
पूर्ण;

अटल पूर्णांक mixart_load_elf(काष्ठा mixart_mgr *mgr, स्थिर काष्ठा firmware *dsp )
अणु
	अक्षर                    elf32_magic_number[4] = अणु0x7f,'E','L','F'पूर्ण;
	काष्ठा snd_mixart_elf32_ehdr *elf_header;
	पूर्णांक                     i;

	elf_header = (काष्ठा snd_mixart_elf32_ehdr *)dsp->data;
	क्रम( i=0; i<4; i++ )
		अगर ( elf32_magic_number[i] != elf_header->e_ident[i] )
			वापस -EINVAL;

	अगर( elf_header->e_phoff != 0 ) अणु
		काष्ठा snd_mixart_elf32_phdr     elf_programheader;

		क्रम( i=0; i < be16_to_cpu(elf_header->e_phnum); i++ ) अणु
			u32 pos = be32_to_cpu(elf_header->e_phoff) + (u32)(i * be16_to_cpu(elf_header->e_phentsize));

			स_नकल( &elf_programheader, dsp->data + pos, माप(elf_programheader) );

			अगर(elf_programheader.p_type != 0) अणु
				अगर( elf_programheader.p_filesz != 0 ) अणु
					स_नकल_toio( MIXART_MEM( mgr, be32_to_cpu(elf_programheader.p_vaddr)),
						     dsp->data + be32_to_cpu( elf_programheader.p_offset ),
						     be32_to_cpu( elf_programheader.p_filesz ));
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * get basic inक्रमmation and init miXart
 */

/* audio IDs क्रम request to the board */
#घोषणा MIXART_FIRST_ANA_AUDIO_ID       0
#घोषणा MIXART_FIRST_DIG_AUDIO_ID       8

अटल पूर्णांक mixart_क्रमागत_connectors(काष्ठा mixart_mgr *mgr)
अणु
	u32 k;
	पूर्णांक err;
	काष्ठा mixart_msg request;
	काष्ठा mixart_क्रमागत_connector_resp *connector;
	काष्ठा mixart_audio_info_req  *audio_info_req;
	काष्ठा mixart_audio_info_resp *audio_info;

	connector = kदो_स्मृति(माप(*connector), GFP_KERNEL);
	audio_info_req = kदो_स्मृति(माप(*audio_info_req), GFP_KERNEL);
	audio_info = kदो_स्मृति(माप(*audio_info), GFP_KERNEL);
	अगर (! connector || ! audio_info_req || ! audio_info) अणु
		err = -ENOMEM;
		जाओ __error;
	पूर्ण

	audio_info_req->line_max_level = MIXART_FLOAT_P_22_0_TO_HEX;
	audio_info_req->micro_max_level = MIXART_FLOAT_M_20_0_TO_HEX;
	audio_info_req->cd_max_level = MIXART_FLOAT____0_0_TO_HEX;

	request.message_id = MSG_SYSTEM_ENUM_PLAY_CONNECTOR;
	request.uid = (काष्ठा mixart_uid)अणु0,0पूर्ण;  /* board num = 0 */
	request.data = शून्य;
	request.size = 0;

	err = snd_mixart_send_msg(mgr, &request, माप(*connector), connector);
	अगर((err < 0) || (connector->error_code) || (connector->uid_count > MIXART_MAX_PHYS_CONNECTORS)) अणु
		dev_err(&mgr->pci->dev,
			"error MSG_SYSTEM_ENUM_PLAY_CONNECTOR\n");
		err = -EINVAL;
		जाओ __error;
	पूर्ण

	क्रम(k=0; k < connector->uid_count; k++) अणु
		काष्ठा mixart_pipe *pipe;

		अगर(k < MIXART_FIRST_DIG_AUDIO_ID) अणु
			pipe = &mgr->chip[k/2]->pipe_out_ana;
		पूर्ण अन्यथा अणु
			pipe = &mgr->chip[(k-MIXART_FIRST_DIG_AUDIO_ID)/2]->pipe_out_dig;
		पूर्ण
		अगर(k & 1) अणु
			pipe->uid_right_connector = connector->uid[k];   /* odd */
		पूर्ण अन्यथा अणु
			pipe->uid_left_connector = connector->uid[k];    /* even */
		पूर्ण

		/* dev_dbg(&mgr->pci->dev, "playback connector[%d].object_id = %x\n", k, connector->uid[k].object_id); */

		/* TODO: really need send_msg MSG_CONNECTOR_GET_AUDIO_INFO क्रम each connector ? perhaps क्रम analog level caps ? */
		request.message_id = MSG_CONNECTOR_GET_AUDIO_INFO;
		request.uid = connector->uid[k];
		request.data = audio_info_req;
		request.size = माप(*audio_info_req);

		err = snd_mixart_send_msg(mgr, &request, माप(*audio_info), audio_info);
		अगर( err < 0 ) अणु
			dev_err(&mgr->pci->dev,
				"error MSG_CONNECTOR_GET_AUDIO_INFO\n");
			जाओ __error;
		पूर्ण
		/*dev_dbg(&mgr->pci->dev, "play  analog_info.analog_level_present = %x\n", audio_info->info.analog_info.analog_level_present);*/
	पूर्ण

	request.message_id = MSG_SYSTEM_ENUM_RECORD_CONNECTOR;
	request.uid = (काष्ठा mixart_uid)अणु0,0पूर्ण;  /* board num = 0 */
	request.data = शून्य;
	request.size = 0;

	err = snd_mixart_send_msg(mgr, &request, माप(*connector), connector);
	अगर((err < 0) || (connector->error_code) || (connector->uid_count > MIXART_MAX_PHYS_CONNECTORS)) अणु
		dev_err(&mgr->pci->dev,
			"error MSG_SYSTEM_ENUM_RECORD_CONNECTOR\n");
		err = -EINVAL;
		जाओ __error;
	पूर्ण

	क्रम(k=0; k < connector->uid_count; k++) अणु
		काष्ठा mixart_pipe *pipe;

		अगर(k < MIXART_FIRST_DIG_AUDIO_ID) अणु
			pipe = &mgr->chip[k/2]->pipe_in_ana;
		पूर्ण अन्यथा अणु
			pipe = &mgr->chip[(k-MIXART_FIRST_DIG_AUDIO_ID)/2]->pipe_in_dig;
		पूर्ण
		अगर(k & 1) अणु
			pipe->uid_right_connector = connector->uid[k];   /* odd */
		पूर्ण अन्यथा अणु
			pipe->uid_left_connector = connector->uid[k];    /* even */
		पूर्ण

		/* dev_dbg(&mgr->pci->dev, "capture connector[%d].object_id = %x\n", k, connector->uid[k].object_id); */

		/* TODO: really need send_msg MSG_CONNECTOR_GET_AUDIO_INFO क्रम each connector ? perhaps क्रम analog level caps ? */
		request.message_id = MSG_CONNECTOR_GET_AUDIO_INFO;
		request.uid = connector->uid[k];
		request.data = audio_info_req;
		request.size = माप(*audio_info_req);

		err = snd_mixart_send_msg(mgr, &request, माप(*audio_info), audio_info);
		अगर( err < 0 ) अणु
			dev_err(&mgr->pci->dev,
				"error MSG_CONNECTOR_GET_AUDIO_INFO\n");
			जाओ __error;
		पूर्ण
		/*dev_dbg(&mgr->pci->dev, "rec  analog_info.analog_level_present = %x\n", audio_info->info.analog_info.analog_level_present);*/
	पूर्ण
	err = 0;

 __error:
	kमुक्त(connector);
	kमुक्त(audio_info_req);
	kमुक्त(audio_info);

	वापस err;
पूर्ण

अटल पूर्णांक mixart_क्रमागत_physio(काष्ठा mixart_mgr *mgr)
अणु
	u32 k;
	पूर्णांक err;
	काष्ठा mixart_msg request;
	काष्ठा mixart_uid get_console_mgr;
	काष्ठा mixart_वापस_uid console_mgr;
	काष्ठा mixart_uid_क्रमागतeration phys_io;

	/* get the uid क्रम the console manager */
	get_console_mgr.object_id = 0;
	get_console_mgr.desc = MSG_CONSOLE_MANAGER | 0; /* cardindex = 0 */

	request.message_id = MSG_CONSOLE_GET_CLOCK_UID;
	request.uid = get_console_mgr;
	request.data = &get_console_mgr;
	request.size = माप(get_console_mgr);

	err = snd_mixart_send_msg(mgr, &request, माप(console_mgr), &console_mgr);

	अगर( (err < 0) || (console_mgr.error_code != 0) ) अणु
		dev_dbg(&mgr->pci->dev,
			"error MSG_CONSOLE_GET_CLOCK_UID : err=%x\n",
			console_mgr.error_code);
		वापस -EINVAL;
	पूर्ण

	/* used later क्रम घड़ी issues ! */
	mgr->uid_console_manager = console_mgr.uid;

	request.message_id = MSG_SYSTEM_ENUM_PHYSICAL_IO;
	request.uid = (काष्ठा mixart_uid)अणु0,0पूर्ण;
	request.data = &console_mgr.uid;
	request.size = माप(console_mgr.uid);

	err = snd_mixart_send_msg(mgr, &request, माप(phys_io), &phys_io);
	अगर( (err < 0) || ( phys_io.error_code != 0 ) ) अणु
		dev_err(&mgr->pci->dev,
			"error MSG_SYSTEM_ENUM_PHYSICAL_IO err(%x) error_code(%x)\n",
			err, phys_io.error_code);
		वापस -EINVAL;
	पूर्ण

	/* min 2 phys io per card (analog in + analog out) */
	अगर (phys_io.nb_uid < MIXART_MAX_CARDS * 2)
		वापस -EINVAL;

	क्रम(k=0; k<mgr->num_cards; k++) अणु
		mgr->chip[k]->uid_in_analog_physio = phys_io.uid[k];
		mgr->chip[k]->uid_out_analog_physio = phys_io.uid[phys_io.nb_uid/2 + k]; 
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक mixart_first_init(काष्ठा mixart_mgr *mgr)
अणु
	u32 k;
	पूर्णांक err;
	काष्ठा mixart_msg request;

	अगर((err = mixart_क्रमागत_connectors(mgr)) < 0) वापस err;

	अगर((err = mixart_क्रमागत_physio(mgr)) < 0) वापस err;

	/* send a synchro command to card (necessary to करो this beक्रमe first MSG_STREAM_START_STREAM_GRP_PACKET) */
	/* though why not here */
	request.message_id = MSG_SYSTEM_SEND_SYNCHRO_CMD;
	request.uid = (काष्ठा mixart_uid)अणु0,0पूर्ण;
	request.data = शून्य;
	request.size = 0;
	/* this command has no data. response is a 32 bit status */
	err = snd_mixart_send_msg(mgr, &request, माप(k), &k);
	अगर( (err < 0) || (k != 0) ) अणु
		dev_err(&mgr->pci->dev, "error MSG_SYSTEM_SEND_SYNCHRO_CMD\n");
		वापस err == 0 ? -EINVAL : err;
	पूर्ण

	वापस 0;
पूर्ण


/* firmware base addresses (when hard coded) */
#घोषणा MIXART_MOTHERBOARD_XLX_BASE_ADDRESS   0x00600000

अटल पूर्णांक mixart_dsp_load(काष्ठा mixart_mgr* mgr, पूर्णांक index, स्थिर काष्ठा firmware *dsp)
अणु
	पूर्णांक           err, card_index;
	u32           status_xilinx, status_elf, status_daught;
	u32           val;

	/* पढ़ो motherboard xilinx status */
	status_xilinx = पढ़ोl_be( MIXART_MEM( mgr,MIXART_PSEUDOREG_MXLX_STATUS_OFFSET ));
	/* पढ़ो elf status */
	status_elf = पढ़ोl_be( MIXART_MEM( mgr,MIXART_PSEUDOREG_ELF_STATUS_OFFSET ));
	/* पढ़ो daughterboard xilinx status */
	status_daught = पढ़ोl_be( MIXART_MEM( mgr,MIXART_PSEUDOREG_DXLX_STATUS_OFFSET ));

	/* motherboard xilinx status 5 will say that the board is perक्रमming a reset */
	अगर (status_xilinx == 5) अणु
		dev_err(&mgr->pci->dev, "miXart is resetting !\n");
		वापस -EAGAIN; /* try again later */
	पूर्ण

	चयन (index)   अणु
	हाल MIXART_MOTHERBOARD_XLX_INDEX:

		/* xilinx alपढ़ोy loaded ? */ 
		अगर (status_xilinx == 4) अणु
			dev_dbg(&mgr->pci->dev, "xilinx is already loaded !\n");
			वापस 0;
		पूर्ण
		/* the status should be 0 == "idle" */
		अगर (status_xilinx != 0) अणु
			dev_err(&mgr->pci->dev,
				"xilinx load error ! status = %d\n",
				   status_xilinx);
			वापस -EIO; /* modprob -r may help ? */
		पूर्ण

		/* check xilinx validity */
		अगर (((u32*)(dsp->data))[0] == 0xffffffff)
			वापस -EINVAL;
		अगर (dsp->size % 4)
			वापस -EINVAL;

		/* set xilinx status to copying */
		ग_लिखोl_be( 1, MIXART_MEM( mgr, MIXART_PSEUDOREG_MXLX_STATUS_OFFSET ));

		/* setup xilinx base address */
		ग_लिखोl_be( MIXART_MOTHERBOARD_XLX_BASE_ADDRESS, MIXART_MEM( mgr,MIXART_PSEUDOREG_MXLX_BASE_ADDR_OFFSET ));
		/* setup code size क्रम xilinx file */
		ग_लिखोl_be( dsp->size, MIXART_MEM( mgr, MIXART_PSEUDOREG_MXLX_SIZE_OFFSET ));

		/* copy xilinx code */
		स_नकल_toio(  MIXART_MEM( mgr, MIXART_MOTHERBOARD_XLX_BASE_ADDRESS),  dsp->data,  dsp->size);
    
		/* set xilinx status to copy finished */
		ग_लिखोl_be( 2, MIXART_MEM( mgr, MIXART_PSEUDOREG_MXLX_STATUS_OFFSET ));

		/* वापस, because no further processing needed */
		वापस 0;

	हाल MIXART_MOTHERBOARD_ELF_INDEX:

		अगर (status_elf == 4) अणु
			dev_dbg(&mgr->pci->dev, "elf file already loaded !\n");
			वापस 0;
		पूर्ण

		/* the status should be 0 == "idle" */
		अगर (status_elf != 0) अणु
			dev_err(&mgr->pci->dev,
				"elf load error ! status = %d\n",
				   status_elf);
			वापस -EIO; /* modprob -r may help ? */
		पूर्ण

		/* रुको क्रम xilinx status == 4 */
		err = mixart_रुको_nice_क्रम_रेजिस्टर_value( mgr, MIXART_PSEUDOREG_MXLX_STATUS_OFFSET, 1, 4, 500); /* 5sec */
		अगर (err < 0) अणु
			dev_err(&mgr->pci->dev, "xilinx was not loaded or "
				   "could not be started\n");
			वापस err;
		पूर्ण

		/* init some data on the card */
		ग_लिखोl_be( 0, MIXART_MEM( mgr, MIXART_PSEUDOREG_BOARDNUMBER ) ); /* set miXart boardnumber to 0 */
		ग_लिखोl_be( 0, MIXART_MEM( mgr, MIXART_FLOWTABLE_PTR ) );         /* reset poपूर्णांकer to flow table on miXart */

		/* set elf status to copying */
		ग_लिखोl_be( 1, MIXART_MEM( mgr, MIXART_PSEUDOREG_ELF_STATUS_OFFSET ));

		/* process the copying of the elf packets */
		err = mixart_load_elf( mgr, dsp );
		अगर (err < 0) वापस err;

		/* set elf status to copy finished */
		ग_लिखोl_be( 2, MIXART_MEM( mgr, MIXART_PSEUDOREG_ELF_STATUS_OFFSET ));

		/* रुको क्रम elf status == 4 */
		err = mixart_रुको_nice_क्रम_रेजिस्टर_value( mgr, MIXART_PSEUDOREG_ELF_STATUS_OFFSET, 1, 4, 300); /* 3sec */
		अगर (err < 0) अणु
			dev_err(&mgr->pci->dev, "elf could not be started\n");
			वापस err;
		पूर्ण

		/* miXart रुकोs at this poपूर्णांक on the poपूर्णांकer to the flow table */
		ग_लिखोl_be( (u32)mgr->flowinfo.addr, MIXART_MEM( mgr, MIXART_FLOWTABLE_PTR ) ); /* give poपूर्णांकer of flow table to miXart */

		वापस 0;  /* वापस, another xilinx file has to be loaded beक्रमe */

	हाल MIXART_AESEBUBOARD_XLX_INDEX:
	शेष:

		/* elf and xilinx should be loaded */
		अगर (status_elf != 4 || status_xilinx != 4) अणु
			dev_err(&mgr->pci->dev, "xilinx or elf not "
			       "successfully loaded\n");
			वापस -EIO; /* modprob -r may help ? */
		पूर्ण

		/* रुको क्रम daughter detection != 0 */
		err = mixart_रुको_nice_क्रम_रेजिस्टर_value( mgr, MIXART_PSEUDOREG_DBRD_PRESENCE_OFFSET, 0, 0, 30); /* 300msec */
		अगर (err < 0) अणु
			dev_err(&mgr->pci->dev, "error starting elf file\n");
			वापस err;
		पूर्ण

		/* the board type can now be retrieved */
		mgr->board_type = (DAUGHTER_TYPE_MASK & पढ़ोl_be( MIXART_MEM( mgr, MIXART_PSEUDOREG_DBRD_TYPE_OFFSET)));

		अगर (mgr->board_type == MIXART_DAUGHTER_TYPE_NONE)
			अवरोध;  /* no daughter board; the file करोes not have to be loaded, जारी after the चयन */

		/* only अगर aesebu daughter board presence (elf code must run)  */ 
		अगर (mgr->board_type != MIXART_DAUGHTER_TYPE_AES )
			वापस -EINVAL;

		/* daughter should be idle */
		अगर (status_daught != 0) अणु
			dev_err(&mgr->pci->dev,
				"daughter load error ! status = %d\n",
			       status_daught);
			वापस -EIO; /* modprob -r may help ? */
		पूर्ण
 
		/* check daughterboard xilinx validity */
		अगर (((u32*)(dsp->data))[0] == 0xffffffff)
			वापस -EINVAL;
		अगर (dsp->size % 4)
			वापस -EINVAL;

		/* inक्रमm mixart about the size of the file */
		ग_लिखोl_be( dsp->size, MIXART_MEM( mgr, MIXART_PSEUDOREG_DXLX_SIZE_OFFSET ));

		/* set daughterboard status to 1 */
		ग_लिखोl_be( 1, MIXART_MEM( mgr, MIXART_PSEUDOREG_DXLX_STATUS_OFFSET ));

		/* रुको क्रम status == 2 */
		err = mixart_रुको_nice_क्रम_रेजिस्टर_value( mgr, MIXART_PSEUDOREG_DXLX_STATUS_OFFSET, 1, 2, 30); /* 300msec */
		अगर (err < 0) अणु
			dev_err(&mgr->pci->dev, "daughter board load error\n");
			वापस err;
		पूर्ण

		/* get the address where to ग_लिखो the file */
		val = पढ़ोl_be( MIXART_MEM( mgr, MIXART_PSEUDOREG_DXLX_BASE_ADDR_OFFSET ));
		अगर (!val)
			वापस -EINVAL;

		/* copy daughterboard xilinx code */
		स_नकल_toio(  MIXART_MEM( mgr, val),  dsp->data,  dsp->size);

		/* set daughterboard status to 4 */
		ग_लिखोl_be( 4, MIXART_MEM( mgr, MIXART_PSEUDOREG_DXLX_STATUS_OFFSET ));

		/* जारी with init */
		अवरोध;
	पूर्ण /* end of चयन file index*/

        /* रुको क्रम daughter status == 3 */
        err = mixart_रुको_nice_क्रम_रेजिस्टर_value( mgr, MIXART_PSEUDOREG_DXLX_STATUS_OFFSET, 1, 3, 300); /* 3sec */
        अगर (err < 0) अणु
		dev_err(&mgr->pci->dev,
			   "daughter board could not be initialised\n");
		वापस err;
	पूर्ण

	/* init mailbox (communication with embedded) */
	snd_mixart_init_mailbox(mgr);

	/* first communication with embedded */
	err = mixart_first_init(mgr);
        अगर (err < 0) अणु
		dev_err(&mgr->pci->dev, "miXart could not be set up\n");
		वापस err;
	पूर्ण

       	/* create devices and mixer in accordance with HW options*/
        क्रम (card_index = 0; card_index < mgr->num_cards; card_index++) अणु
		काष्ठा snd_mixart *chip = mgr->chip[card_index];

		अगर ((err = snd_mixart_create_pcm(chip)) < 0)
			वापस err;

		अगर (card_index == 0) अणु
			अगर ((err = snd_mixart_create_mixer(chip->mgr)) < 0)
	        		वापस err;
		पूर्ण

		अगर ((err = snd_card_रेजिस्टर(chip->card)) < 0)
			वापस err;
	पूर्ण

	dev_dbg(&mgr->pci->dev,
		"miXart firmware downloaded and successfully set up\n");

	वापस 0;
पूर्ण


पूर्णांक snd_mixart_setup_firmware(काष्ठा mixart_mgr *mgr)
अणु
	अटल स्थिर अक्षर * स्थिर fw_files[3] = अणु
		"miXart8.xlx", "miXart8.elf", "miXart8AES.xlx"
	पूर्ण;
	अक्षर path[32];

	स्थिर काष्ठा firmware *fw_entry;
	पूर्णांक i, err;

	क्रम (i = 0; i < 3; i++) अणु
		प्र_लिखो(path, "mixart/%s", fw_files[i]);
		अगर (request_firmware(&fw_entry, path, &mgr->pci->dev)) अणु
			dev_err(&mgr->pci->dev,
				"miXart: can't load firmware %s\n", path);
			वापस -ENOENT;
		पूर्ण
		/* fake hwdep dsp record */
		err = mixart_dsp_load(mgr, i, fw_entry);
		release_firmware(fw_entry);
		अगर (err < 0)
			वापस err;
		mgr->dsp_loaded |= 1 << i;
	पूर्ण
	वापस 0;
पूर्ण

MODULE_FIRMWARE("mixart/miXart8.xlx");
MODULE_FIRMWARE("mixart/miXart8.elf");
MODULE_FIRMWARE("mixart/miXart8AES.xlx");
