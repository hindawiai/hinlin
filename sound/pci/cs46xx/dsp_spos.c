<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

/*
 * 2002-07 Benny Sjostअक्रम benny@hosपंचांगobility.com
 */


#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mutex.h>

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/info.h>
#समावेश <sound/asoundef.h>
#समावेश "cs46xx.h"

#समावेश "cs46xx_lib.h"
#समावेश "dsp_spos.h"

अटल पूर्णांक cs46xx_dsp_async_init (काष्ठा snd_cs46xx *chip,
				  काष्ठा dsp_scb_descriptor * fg_entry);

अटल स्थिर क्रमागत wide_opcode wide_opcodes[] = अणु
	WIDE_FOR_BEGIN_LOOP,
	WIDE_FOR_BEGIN_LOOP2,
	WIDE_COND_GOTO_ADDR,
	WIDE_COND_GOTO_CALL,
	WIDE_TBEQ_COND_GOTO_ADDR,
	WIDE_TBEQ_COND_CALL_ADDR,
	WIDE_TBEQ_NCOND_GOTO_ADDR,
	WIDE_TBEQ_NCOND_CALL_ADDR,
	WIDE_TBEQ_COND_GOTO1_ADDR,
	WIDE_TBEQ_COND_CALL1_ADDR,
	WIDE_TBEQ_NCOND_GOTOI_ADDR,
	WIDE_TBEQ_NCOND_CALL1_ADDR
पूर्ण;

अटल पूर्णांक shaकरोw_and_पुनः_स्मृतिate_code (काष्ठा snd_cs46xx * chip, u32 * data, u32 size,
				       u32 overlay_begin_address)
अणु
	अचिन्हित पूर्णांक i = 0, j, nपुनः_स्मृतिated = 0;
	u32 hival,loval,address;
	u32 mop_opeअक्रमs,mop_type,wide_op;
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	अगर (snd_BUG_ON(size %2))
		वापस -EINVAL;
  
	जबतक (i < size) अणु
		loval = data[i++];
		hival = data[i++];

		अगर (ins->code.offset > 0) अणु
			mop_opeअक्रमs = (hival >> 6) & 0x03fff;
			mop_type = mop_opeअक्रमs >> 10;
      
			/* check क्रम wide type inकाष्ठाion */
			अगर (mop_type == 0 &&
			    (mop_opeअक्रमs & WIDE_LADD_INSTR_MASK) == 0 &&
			    (mop_opeअक्रमs & WIDE_INSTR_MASK) != 0) अणु
				wide_op = loval & 0x7f;
				क्रम (j = 0;j < ARRAY_SIZE(wide_opcodes); ++j) अणु
					अगर (wide_opcodes[j] == wide_op) अणु
						/* need to पुनः_स्मृतिate inकाष्ठाion */
						address  = (hival & 0x00FFF) << 5;
						address |=  loval >> 15;
            
						dev_dbg(chip->card->dev,
							"handle_wideop[1]: %05x:%05x addr %04x\n",
							hival, loval, address);
            
						अगर ( !(address & 0x8000) ) अणु
							address += (ins->code.offset / 2) - overlay_begin_address;
						पूर्ण अन्यथा अणु
							dev_dbg(chip->card->dev,
								"handle_wideop[1]: ROM symbol not reallocated\n");
						पूर्ण
            
						hival &= 0xFF000;
						loval &= 0x07FFF;
            
						hival |= ( (address >> 5)  & 0x00FFF);
						loval |= ( (address << 15) & 0xF8000);
            
						address  = (hival & 0x00FFF) << 5;
						address |=  loval >> 15;
            
						dev_dbg(chip->card->dev,
							"handle_wideop:[2] %05x:%05x addr %04x\n",
							hival, loval, address);
						nपुनः_स्मृतिated++;
					पूर्ण /* wide_opcodes[j] == wide_op */
				पूर्ण /* क्रम */
			पूर्ण /* mod_type == 0 ... */
		पूर्ण /* ins->code.offset > 0 */

		ins->code.data[ins->code.size++] = loval;
		ins->code.data[ins->code.size++] = hival;
	पूर्ण

	dev_dbg(chip->card->dev,
		"dsp_spos: %d instructions reallocated\n", nपुनः_स्मृतिated);
	वापस nपुनः_स्मृतिated;
पूर्ण

अटल काष्ठा dsp_segment_desc * get_segment_desc (काष्ठा dsp_module_desc * module, पूर्णांक seg_type)
अणु
	पूर्णांक i;
	क्रम (i = 0;i < module->nsegments; ++i) अणु
		अगर (module->segments[i].segment_type == seg_type) अणु
			वापस (module->segments + i);
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण;

अटल पूर्णांक find_मुक्त_symbol_index (काष्ठा dsp_spos_instance * ins)
अणु
	पूर्णांक index = ins->symbol_table.nsymbols,i;

	क्रम (i = ins->symbol_table.highest_frag_index; i < ins->symbol_table.nsymbols; ++i) अणु
		अगर (ins->symbol_table.symbols[i].deleted) अणु
			index = i;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस index;
पूर्ण

अटल पूर्णांक add_symbols (काष्ठा snd_cs46xx * chip, काष्ठा dsp_module_desc * module)
अणु
	पूर्णांक i;
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	अगर (module->symbol_table.nsymbols > 0) अणु
		अगर (!म_भेद(module->symbol_table.symbols[0].symbol_name, "OVERLAYBEGINADDRESS") &&
		    module->symbol_table.symbols[0].symbol_type == SYMBOL_CONSTANT ) अणु
			module->overlay_begin_address = module->symbol_table.symbols[0].address;
		पूर्ण
	पूर्ण

	क्रम (i = 0;i < module->symbol_table.nsymbols; ++i) अणु
		अगर (ins->symbol_table.nsymbols == (DSP_MAX_SYMBOLS - 1)) अणु
			dev_err(chip->card->dev,
				"dsp_spos: symbol table is full\n");
			वापस -ENOMEM;
		पूर्ण


		अगर (cs46xx_dsp_lookup_symbol(chip,
					     module->symbol_table.symbols[i].symbol_name,
					     module->symbol_table.symbols[i].symbol_type) == शून्य) अणु

			ins->symbol_table.symbols[ins->symbol_table.nsymbols] = module->symbol_table.symbols[i];
			ins->symbol_table.symbols[ins->symbol_table.nsymbols].address += ((ins->code.offset / 2) - module->overlay_begin_address);
			ins->symbol_table.symbols[ins->symbol_table.nsymbols].module = module;
			ins->symbol_table.symbols[ins->symbol_table.nsymbols].deleted = 0;

			अगर (ins->symbol_table.nsymbols > ins->symbol_table.highest_frag_index) 
				ins->symbol_table.highest_frag_index = ins->symbol_table.nsymbols;

			ins->symbol_table.nsymbols++;
		पूर्ण अन्यथा अणु
#अगर 0
			dev_dbg(chip->card->dev,
				"dsp_spos: symbol <%s> duplicated, probably nothing wrong with that (Cirrus?)\n",
				module->symbol_table.symbols[i].symbol_name); */
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dsp_symbol_entry *
add_symbol (काष्ठा snd_cs46xx * chip, अक्षर * symbol_name, u32 address, पूर्णांक type)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	काष्ठा dsp_symbol_entry * symbol = शून्य;
	पूर्णांक index;

	अगर (ins->symbol_table.nsymbols == (DSP_MAX_SYMBOLS - 1)) अणु
		dev_err(chip->card->dev, "dsp_spos: symbol table is full\n");
		वापस शून्य;
	पूर्ण
  
	अगर (cs46xx_dsp_lookup_symbol(chip,
				     symbol_name,
				     type) != शून्य) अणु
		dev_err(chip->card->dev,
			"dsp_spos: symbol <%s> duplicated\n", symbol_name);
		वापस शून्य;
	पूर्ण

	index = find_मुक्त_symbol_index (ins);

	म_नकल (ins->symbol_table.symbols[index].symbol_name, symbol_name);
	ins->symbol_table.symbols[index].address = address;
	ins->symbol_table.symbols[index].symbol_type = type;
	ins->symbol_table.symbols[index].module = शून्य;
	ins->symbol_table.symbols[index].deleted = 0;
	symbol = (ins->symbol_table.symbols + index);

	अगर (index > ins->symbol_table.highest_frag_index) 
		ins->symbol_table.highest_frag_index = index;

	अगर (index == ins->symbol_table.nsymbols)
		ins->symbol_table.nsymbols++; /* no frag. in list */

	वापस symbol;
पूर्ण

काष्ठा dsp_spos_instance *cs46xx_dsp_spos_create (काष्ठा snd_cs46xx * chip)
अणु
	काष्ठा dsp_spos_instance * ins = kzalloc(माप(काष्ठा dsp_spos_instance), GFP_KERNEL);

	अगर (ins == शून्य)
		वापस शून्य;

	/* better to use vदो_स्मृति क्रम this big table */
	ins->symbol_table.symbols =
		vदो_स्मृति(array_size(DSP_MAX_SYMBOLS,
				   माप(काष्ठा dsp_symbol_entry)));
	ins->code.data = kदो_स्मृति(DSP_CODE_BYTE_SIZE, GFP_KERNEL);
	ins->modules = kदो_स्मृति_array(DSP_MAX_MODULES,
				     माप(काष्ठा dsp_module_desc),
				     GFP_KERNEL);
	अगर (!ins->symbol_table.symbols || !ins->code.data || !ins->modules) अणु
		cs46xx_dsp_spos_destroy(chip);
		जाओ error;
	पूर्ण
	ins->symbol_table.nsymbols = 0;
	ins->symbol_table.highest_frag_index = 0;
	ins->code.offset = 0;
	ins->code.size = 0;
	ins->nscb = 0;
	ins->ntask = 0;
	ins->nmodules = 0;

	/* शेष SPDIF input sample rate
	   to 48000 khz */
	ins->spdअगर_in_sample_rate = 48000;

	/* maximize volume */
	ins->dac_volume_right = 0x8000;
	ins->dac_volume_left = 0x8000;
	ins->spdअगर_input_volume_right = 0x8000;
	ins->spdअगर_input_volume_left = 0x8000;

	/* set left and right validity bits and
	   शेष channel status */
	ins->spdअगर_csuv_शेष =
		ins->spdअगर_csuv_stream =
	 /* byte 0 */  ((अचिन्हित पूर्णांक)_wrap_all_bits(  (SNDRV_PCM_DEFAULT_CON_SPDIF        & 0xff)) << 24) |
	 /* byte 1 */  ((अचिन्हित पूर्णांक)_wrap_all_bits( ((SNDRV_PCM_DEFAULT_CON_SPDIF >> 8) & 0xff)) << 16) |
	 /* byte 3 */   (अचिन्हित पूर्णांक)_wrap_all_bits(  (SNDRV_PCM_DEFAULT_CON_SPDIF >> 24) & 0xff) |
	 /* left and right validity bits */ (1 << 13) | (1 << 12);

	वापस ins;

error:
	kमुक्त(ins->modules);
	kमुक्त(ins->code.data);
	vमुक्त(ins->symbol_table.symbols);
	kमुक्त(ins);
	वापस शून्य;
पूर्ण

व्योम  cs46xx_dsp_spos_destroy (काष्ठा snd_cs46xx * chip)
अणु
	पूर्णांक i;
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	अगर (snd_BUG_ON(!ins))
		वापस;

	mutex_lock(&chip->spos_mutex);
	क्रम (i = 0; i < ins->nscb; ++i) अणु
		अगर (ins->scbs[i].deleted) जारी;

		cs46xx_dsp_proc_मुक्त_scb_desc ( (ins->scbs + i) );
#अगर_घोषित CONFIG_PM_SLEEP
		kमुक्त(ins->scbs[i].data);
#पूर्ण_अगर
	पूर्ण

	kमुक्त(ins->code.data);
	vमुक्त(ins->symbol_table.symbols);
	kमुक्त(ins->modules);
	kमुक्त(ins);
	mutex_unlock(&chip->spos_mutex);
पूर्ण

अटल पूर्णांक dsp_load_parameter(काष्ठा snd_cs46xx *chip,
			      काष्ठा dsp_segment_desc *parameter)
अणु
	u32 करोffset, dsize;

	अगर (!parameter) अणु
		dev_dbg(chip->card->dev,
			"dsp_spos: module got no parameter segment\n");
		वापस 0;
	पूर्ण

	करोffset = (parameter->offset * 4 + DSP_PARAMETER_BYTE_OFFSET);
	dsize   = parameter->size * 4;

	dev_dbg(chip->card->dev,
		"dsp_spos: downloading parameter data to chip (%08x-%08x)\n",
		    करोffset,करोffset + dsize);
	अगर (snd_cs46xx_करोwnload (chip, parameter->data, करोffset, dsize)) अणु
		dev_err(chip->card->dev,
			"dsp_spos: failed to download parameter data to DSP\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dsp_load_sample(काष्ठा snd_cs46xx *chip,
			   काष्ठा dsp_segment_desc *sample)
अणु
	u32 करोffset, dsize;

	अगर (!sample) अणु
		dev_dbg(chip->card->dev,
			"dsp_spos: module got no sample segment\n");
		वापस 0;
	पूर्ण

	करोffset = (sample->offset * 4  + DSP_SAMPLE_BYTE_OFFSET);
	dsize   =  sample->size * 4;

	dev_dbg(chip->card->dev,
		"dsp_spos: downloading sample data to chip (%08x-%08x)\n",
		    करोffset,करोffset + dsize);

	अगर (snd_cs46xx_करोwnload (chip,sample->data,करोffset,dsize)) अणु
		dev_err(chip->card->dev,
			"dsp_spos: failed to sample data to DSP\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cs46xx_dsp_load_module (काष्ठा snd_cs46xx * chip, काष्ठा dsp_module_desc * module)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	काष्ठा dsp_segment_desc * code = get_segment_desc (module,SEGTYPE_SP_PROGRAM);
	u32 करोffset, dsize;
	पूर्णांक err;

	अगर (ins->nmodules == DSP_MAX_MODULES - 1) अणु
		dev_err(chip->card->dev,
			"dsp_spos: to many modules loaded into DSP\n");
		वापस -ENOMEM;
	पूर्ण

	dev_dbg(chip->card->dev,
		"dsp_spos: loading module %s into DSP\n", module->module_name);
  
	अगर (ins->nmodules == 0) अणु
		dev_dbg(chip->card->dev, "dsp_spos: clearing parameter area\n");
		snd_cs46xx_clear_BA1(chip, DSP_PARAMETER_BYTE_OFFSET, DSP_PARAMETER_BYTE_SIZE);
	पूर्ण
  
	err = dsp_load_parameter(chip, get_segment_desc(module,
							SEGTYPE_SP_PARAMETER));
	अगर (err < 0)
		वापस err;

	अगर (ins->nmodules == 0) अणु
		dev_dbg(chip->card->dev, "dsp_spos: clearing sample area\n");
		snd_cs46xx_clear_BA1(chip, DSP_SAMPLE_BYTE_OFFSET, DSP_SAMPLE_BYTE_SIZE);
	पूर्ण

	err = dsp_load_sample(chip, get_segment_desc(module,
						     SEGTYPE_SP_SAMPLE));
	अगर (err < 0)
		वापस err;

	अगर (ins->nmodules == 0) अणु
		dev_dbg(chip->card->dev, "dsp_spos: clearing code area\n");
		snd_cs46xx_clear_BA1(chip, DSP_CODE_BYTE_OFFSET, DSP_CODE_BYTE_SIZE);
	पूर्ण

	अगर (code == शून्य) अणु
		dev_dbg(chip->card->dev,
			"dsp_spos: module got no code segment\n");
	पूर्ण अन्यथा अणु
		अगर (ins->code.offset + code->size > DSP_CODE_BYTE_SIZE) अणु
			dev_err(chip->card->dev,
				"dsp_spos: no space available in DSP\n");
			वापस -ENOMEM;
		पूर्ण

		module->load_address = ins->code.offset;
		module->overlay_begin_address = 0x000;

		/* अगर module has a code segment it must have
		   symbol table */
		अगर (snd_BUG_ON(!module->symbol_table.symbols))
			वापस -ENOMEM;
		अगर (add_symbols(chip,module)) अणु
			dev_err(chip->card->dev,
				"dsp_spos: failed to load symbol table\n");
			वापस -ENOMEM;
		पूर्ण
    
		करोffset = (code->offset * 4 + ins->code.offset * 4 + DSP_CODE_BYTE_OFFSET);
		dsize   = code->size * 4;
		dev_dbg(chip->card->dev,
			"dsp_spos: downloading code to chip (%08x-%08x)\n",
			    करोffset,करोffset + dsize);   

		module->nfixups = shaकरोw_and_पुनः_स्मृतिate_code(chip,code->data,code->size,module->overlay_begin_address);

		अगर (snd_cs46xx_करोwnload (chip,(ins->code.data + ins->code.offset),करोffset,dsize)) अणु
			dev_err(chip->card->dev,
				"dsp_spos: failed to download code to DSP\n");
			वापस -EINVAL;
		पूर्ण

		ins->code.offset += code->size;
	पूर्ण

	/* NOTE: module segments and symbol table must be
	   अटलally allocated. Case that module data is
	   not generated by the ospparser */
	ins->modules[ins->nmodules] = *module;
	ins->nmodules++;

	वापस 0;
पूर्ण

काष्ठा dsp_symbol_entry *
cs46xx_dsp_lookup_symbol (काष्ठा snd_cs46xx * chip, अक्षर * symbol_name, पूर्णांक symbol_type)
अणु
	पूर्णांक i;
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	क्रम ( i = 0; i < ins->symbol_table.nsymbols; ++i ) अणु

		अगर (ins->symbol_table.symbols[i].deleted)
			जारी;

		अगर (!म_भेद(ins->symbol_table.symbols[i].symbol_name,symbol_name) &&
		    ins->symbol_table.symbols[i].symbol_type == symbol_type) अणु
			वापस (ins->symbol_table.symbols + i);
		पूर्ण
	पूर्ण

#अगर 0
	dev_err(chip->card->dev, "dsp_spos: symbol <%s> type %02x not found\n",
		symbol_name,symbol_type);
#पूर्ण_अगर

	वापस शून्य;
पूर्ण


#अगर_घोषित CONFIG_SND_PROC_FS
अटल काष्ठा dsp_symbol_entry *
cs46xx_dsp_lookup_symbol_addr (काष्ठा snd_cs46xx * chip, u32 address, पूर्णांक symbol_type)
अणु
	पूर्णांक i;
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	क्रम ( i = 0; i < ins->symbol_table.nsymbols; ++i ) अणु

		अगर (ins->symbol_table.symbols[i].deleted)
			जारी;

		अगर (ins->symbol_table.symbols[i].address == address &&
		    ins->symbol_table.symbols[i].symbol_type == symbol_type) अणु
			वापस (ins->symbol_table.symbols + i);
		पूर्ण
	पूर्ण


	वापस शून्य;
पूर्ण


अटल व्योम cs46xx_dsp_proc_symbol_table_पढ़ो (काष्ठा snd_info_entry *entry,
					       काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_cs46xx *chip = entry->निजी_data;
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	पूर्णांक i;

	snd_iम_लिखो(buffer, "SYMBOLS:\n");
	क्रम ( i = 0; i < ins->symbol_table.nsymbols; ++i ) अणु
		अक्षर *module_str = "system";

		अगर (ins->symbol_table.symbols[i].deleted)
			जारी;

		अगर (ins->symbol_table.symbols[i].module != शून्य) अणु
			module_str = ins->symbol_table.symbols[i].module->module_name;
		पूर्ण

    
		snd_iम_लिखो(buffer, "%04X <%02X> %s [%s]\n",
			    ins->symbol_table.symbols[i].address,
			    ins->symbol_table.symbols[i].symbol_type,
			    ins->symbol_table.symbols[i].symbol_name,
			    module_str);    
	पूर्ण
पूर्ण


अटल व्योम cs46xx_dsp_proc_modules_पढ़ो (काष्ठा snd_info_entry *entry,
					  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_cs46xx *chip = entry->निजी_data;
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	पूर्णांक i,j;

	mutex_lock(&chip->spos_mutex);
	snd_iम_लिखो(buffer, "MODULES:\n");
	क्रम ( i = 0; i < ins->nmodules; ++i ) अणु
		snd_iम_लिखो(buffer, "\n%s:\n", ins->modules[i].module_name);
		snd_iम_लिखो(buffer, "   %d symbols\n", ins->modules[i].symbol_table.nsymbols);
		snd_iम_लिखो(buffer, "   %d fixups\n", ins->modules[i].nfixups);

		क्रम (j = 0; j < ins->modules[i].nsegments; ++ j) अणु
			काष्ठा dsp_segment_desc * desc = (ins->modules[i].segments + j);
			snd_iम_लिखो(buffer, "   segment %02x offset %08x size %08x\n",
				    desc->segment_type,desc->offset, desc->size);
		पूर्ण
	पूर्ण
	mutex_unlock(&chip->spos_mutex);
पूर्ण

अटल व्योम cs46xx_dsp_proc_task_tree_पढ़ो (काष्ठा snd_info_entry *entry,
					    काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_cs46xx *chip = entry->निजी_data;
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	पूर्णांक i, j, col;
	व्योम __iomem *dst = chip->region.idx[1].remap_addr + DSP_PARAMETER_BYTE_OFFSET;

	mutex_lock(&chip->spos_mutex);
	snd_iम_लिखो(buffer, "TASK TREES:\n");
	क्रम ( i = 0; i < ins->ntask; ++i) अणु
		snd_iम_लिखो(buffer,"\n%04x %s:\n",ins->tasks[i].address,ins->tasks[i].task_name);

		क्रम (col = 0,j = 0;j < ins->tasks[i].size; j++,col++) अणु
			u32 val;
			अगर (col == 4) अणु
				snd_iम_लिखो(buffer,"\n");
				col = 0;
			पूर्ण
			val = पढ़ोl(dst + (ins->tasks[i].address + j) * माप(u32));
			snd_iम_लिखो(buffer,"%08x ",val);
		पूर्ण
	पूर्ण

	snd_iम_लिखो(buffer,"\n");  
	mutex_unlock(&chip->spos_mutex);
पूर्ण

अटल व्योम cs46xx_dsp_proc_scb_पढ़ो (काष्ठा snd_info_entry *entry,
				      काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_cs46xx *chip = entry->निजी_data;
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	पूर्णांक i;

	mutex_lock(&chip->spos_mutex);
	snd_iम_लिखो(buffer, "SCB's:\n");
	क्रम ( i = 0; i < ins->nscb; ++i) अणु
		अगर (ins->scbs[i].deleted)
			जारी;
		snd_iम_लिखो(buffer,"\n%04x %s:\n\n",ins->scbs[i].address,ins->scbs[i].scb_name);

		अगर (ins->scbs[i].parent_scb_ptr != शून्य) अणु
			snd_iम_लिखो(buffer,"parent [%s:%04x] ", 
				    ins->scbs[i].parent_scb_ptr->scb_name,
				    ins->scbs[i].parent_scb_ptr->address);
		पूर्ण अन्यथा snd_iम_लिखो(buffer,"parent [none] ");

		snd_iम_लिखो(buffer,"sub_list_ptr [%s:%04x]\nnext_scb_ptr [%s:%04x]  task_entry [%s:%04x]\n",
			    ins->scbs[i].sub_list_ptr->scb_name,
			    ins->scbs[i].sub_list_ptr->address,
			    ins->scbs[i].next_scb_ptr->scb_name,
			    ins->scbs[i].next_scb_ptr->address,
			    ins->scbs[i].task_entry->symbol_name,
			    ins->scbs[i].task_entry->address);
	पूर्ण

	snd_iम_लिखो(buffer,"\n");
	mutex_unlock(&chip->spos_mutex);
पूर्ण

अटल व्योम cs46xx_dsp_proc_parameter_dump_पढ़ो (काष्ठा snd_info_entry *entry,
						 काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_cs46xx *chip = entry->निजी_data;
	/*काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance; */
	अचिन्हित पूर्णांक i, col = 0;
	व्योम __iomem *dst = chip->region.idx[1].remap_addr + DSP_PARAMETER_BYTE_OFFSET;
	काष्ठा dsp_symbol_entry * symbol; 

	क्रम (i = 0;i < DSP_PARAMETER_BYTE_SIZE; i += माप(u32),col ++) अणु
		अगर (col == 4) अणु
			snd_iम_लिखो(buffer,"\n");
			col = 0;
		पूर्ण

		अगर ( (symbol = cs46xx_dsp_lookup_symbol_addr (chip,i / माप(u32), SYMBOL_PARAMETER)) != शून्य) अणु
			col = 0;
			snd_iम_लिखो (buffer,"\n%s:\n",symbol->symbol_name);
		पूर्ण

		अगर (col == 0) अणु
			snd_iम_लिखो(buffer, "%04X ", i / (अचिन्हित पूर्णांक)माप(u32));
		पूर्ण

		snd_iम_लिखो(buffer,"%08X ",पढ़ोl(dst + i));
	पूर्ण
पूर्ण

अटल व्योम cs46xx_dsp_proc_sample_dump_पढ़ो (काष्ठा snd_info_entry *entry,
					      काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_cs46xx *chip = entry->निजी_data;
	पूर्णांक i,col = 0;
	व्योम __iomem *dst = chip->region.idx[2].remap_addr;

	snd_iम_लिखो(buffer,"PCMREADER:\n");
	क्रम (i = PCM_READER_BUF1;i < PCM_READER_BUF1 + 0x30; i += माप(u32),col ++) अणु
		अगर (col == 4) अणु
			snd_iम_लिखो(buffer,"\n");
			col = 0;
		पूर्ण

		अगर (col == 0) अणु
			snd_iम_लिखो(buffer, "%04X ",i);
		पूर्ण

		snd_iम_लिखो(buffer,"%08X ",पढ़ोl(dst + i));
	पूर्ण

	snd_iम_लिखो(buffer,"\nMIX_SAMPLE_BUF1:\n");

	col = 0;
	क्रम (i = MIX_SAMPLE_BUF1;i < MIX_SAMPLE_BUF1 + 0x40; i += माप(u32),col ++) अणु
		अगर (col == 4) अणु
			snd_iम_लिखो(buffer,"\n");
			col = 0;
		पूर्ण

		अगर (col == 0) अणु
			snd_iम_लिखो(buffer, "%04X ",i);
		पूर्ण

		snd_iम_लिखो(buffer,"%08X ",पढ़ोl(dst + i));
	पूर्ण

	snd_iम_लिखो(buffer,"\nSRC_TASK_SCB1:\n");
	col = 0;
	क्रम (i = 0x2480 ; i < 0x2480 + 0x40 ; i += माप(u32),col ++) अणु
		अगर (col == 4) अणु
			snd_iम_लिखो(buffer,"\n");
			col = 0;
		पूर्ण
		
		अगर (col == 0) अणु
			snd_iम_लिखो(buffer, "%04X ",i);
		पूर्ण

		snd_iम_लिखो(buffer,"%08X ",पढ़ोl(dst + i));
	पूर्ण


	snd_iम_लिखो(buffer,"\nSPDIFO_BUFFER:\n");
	col = 0;
	क्रम (i = SPDIFO_IP_OUTPUT_BUFFER1;i < SPDIFO_IP_OUTPUT_BUFFER1 + 0x30; i += माप(u32),col ++) अणु
		अगर (col == 4) अणु
			snd_iम_लिखो(buffer,"\n");
			col = 0;
		पूर्ण

		अगर (col == 0) अणु
			snd_iम_लिखो(buffer, "%04X ",i);
		पूर्ण

		snd_iम_लिखो(buffer,"%08X ",पढ़ोl(dst + i));
	पूर्ण

	snd_iम_लिखो(buffer,"\n...\n");
	col = 0;

	क्रम (i = SPDIFO_IP_OUTPUT_BUFFER1+0xD0;i < SPDIFO_IP_OUTPUT_BUFFER1 + 0x110; i += माप(u32),col ++) अणु
		अगर (col == 4) अणु
			snd_iम_लिखो(buffer,"\n");
			col = 0;
		पूर्ण

		अगर (col == 0) अणु
			snd_iम_लिखो(buffer, "%04X ",i);
		पूर्ण

		snd_iम_लिखो(buffer,"%08X ",पढ़ोl(dst + i));
	पूर्ण


	snd_iम_लिखो(buffer,"\nOUTPUT_SNOOP:\n");
	col = 0;
	क्रम (i = OUTPUT_SNOOP_BUFFER;i < OUTPUT_SNOOP_BUFFER + 0x40; i += माप(u32),col ++) अणु
		अगर (col == 4) अणु
			snd_iम_लिखो(buffer,"\n");
			col = 0;
		पूर्ण

		अगर (col == 0) अणु
			snd_iम_लिखो(buffer, "%04X ",i);
		पूर्ण

		snd_iम_लिखो(buffer,"%08X ",पढ़ोl(dst + i));
	पूर्ण

	snd_iम_लिखो(buffer,"\nCODEC_INPUT_BUF1: \n");
	col = 0;
	क्रम (i = CODEC_INPUT_BUF1;i < CODEC_INPUT_BUF1 + 0x40; i += माप(u32),col ++) अणु
		अगर (col == 4) अणु
			snd_iम_लिखो(buffer,"\n");
			col = 0;
		पूर्ण

		अगर (col == 0) अणु
			snd_iम_लिखो(buffer, "%04X ",i);
		पूर्ण

		snd_iम_लिखो(buffer,"%08X ",पढ़ोl(dst + i));
	पूर्ण
#अगर 0
	snd_iम_लिखो(buffer,"\nWRITE_BACK_BUF1: \n");
	col = 0;
	क्रम (i = WRITE_BACK_BUF1;i < WRITE_BACK_BUF1 + 0x40; i += माप(u32),col ++) अणु
		अगर (col == 4) अणु
			snd_iम_लिखो(buffer,"\n");
			col = 0;
		पूर्ण

		अगर (col == 0) अणु
			snd_iम_लिखो(buffer, "%04X ",i);
		पूर्ण

		snd_iम_लिखो(buffer,"%08X ",पढ़ोl(dst + i));
	पूर्ण
#पूर्ण_अगर

	snd_iम_लिखो(buffer,"\nSPDIFI_IP_OUTPUT_BUFFER1: \n");
	col = 0;
	क्रम (i = SPDIFI_IP_OUTPUT_BUFFER1;i < SPDIFI_IP_OUTPUT_BUFFER1 + 0x80; i += माप(u32),col ++) अणु
		अगर (col == 4) अणु
			snd_iम_लिखो(buffer,"\n");
			col = 0;
		पूर्ण

		अगर (col == 0) अणु
			snd_iम_लिखो(buffer, "%04X ",i);
		पूर्ण
		
		snd_iम_लिखो(buffer,"%08X ",पढ़ोl(dst + i));
	पूर्ण
	snd_iम_लिखो(buffer,"\n");
पूर्ण

पूर्णांक cs46xx_dsp_proc_init (काष्ठा snd_card *card, काष्ठा snd_cs46xx *chip)
अणु
	काष्ठा snd_info_entry *entry;
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	पूर्णांक i;

	ins->snd_card = card;

	entry = snd_info_create_card_entry(card, "dsp", card->proc_root);
	अगर (entry)
		entry->mode = S_IFसूची | 0555;
	ins->proc_dsp_dir = entry;

	अगर (!ins->proc_dsp_dir)
		वापस -ENOMEM;

	entry = snd_info_create_card_entry(card, "spos_symbols",
					   ins->proc_dsp_dir);
	अगर (entry)
		snd_info_set_text_ops(entry, chip,
				      cs46xx_dsp_proc_symbol_table_पढ़ो);
    
	entry = snd_info_create_card_entry(card, "spos_modules",
					   ins->proc_dsp_dir);
	अगर (entry)
		snd_info_set_text_ops(entry, chip,
				      cs46xx_dsp_proc_modules_पढ़ो);

	entry = snd_info_create_card_entry(card, "parameter",
					   ins->proc_dsp_dir);
	अगर (entry)
		snd_info_set_text_ops(entry, chip,
				      cs46xx_dsp_proc_parameter_dump_पढ़ो);

	entry = snd_info_create_card_entry(card, "sample",
					   ins->proc_dsp_dir);
	अगर (entry)
		snd_info_set_text_ops(entry, chip,
				      cs46xx_dsp_proc_sample_dump_पढ़ो);

	entry = snd_info_create_card_entry(card, "task_tree",
					   ins->proc_dsp_dir);
	अगर (entry)
		snd_info_set_text_ops(entry, chip,
				      cs46xx_dsp_proc_task_tree_पढ़ो);

	entry = snd_info_create_card_entry(card, "scb_info",
					   ins->proc_dsp_dir);
	अगर (entry)
		snd_info_set_text_ops(entry, chip,
				      cs46xx_dsp_proc_scb_पढ़ो);

	mutex_lock(&chip->spos_mutex);
	/* रेजिस्टर/update SCB's entries on proc */
	क्रम (i = 0; i < ins->nscb; ++i) अणु
		अगर (ins->scbs[i].deleted) जारी;

		cs46xx_dsp_proc_रेजिस्टर_scb_desc (chip, (ins->scbs + i));
	पूर्ण
	mutex_unlock(&chip->spos_mutex);

	वापस 0;
पूर्ण

पूर्णांक cs46xx_dsp_proc_करोne (काष्ठा snd_cs46xx *chip)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	पूर्णांक i;

	अगर (!ins)
		वापस 0;

	mutex_lock(&chip->spos_mutex);
	क्रम (i = 0; i < ins->nscb; ++i) अणु
		अगर (ins->scbs[i].deleted) जारी;
		cs46xx_dsp_proc_मुक्त_scb_desc ( (ins->scbs + i) );
	पूर्ण
	mutex_unlock(&chip->spos_mutex);

	snd_info_मुक्त_entry(ins->proc_dsp_dir);
	ins->proc_dsp_dir = शून्य;

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_PROC_FS */

अटल व्योम _dsp_create_task_tree (काष्ठा snd_cs46xx *chip, u32 * task_data,
				   u32  dest, पूर्णांक size)
अणु
	व्योम __iomem *spdst = chip->region.idx[1].remap_addr + 
		DSP_PARAMETER_BYTE_OFFSET + dest * माप(u32);
	पूर्णांक i;

	क्रम (i = 0; i < size; ++i) अणु
		dev_dbg(chip->card->dev, "addr %p, val %08x\n",
			spdst, task_data[i]);
		ग_लिखोl(task_data[i],spdst);
		spdst += माप(u32);
	पूर्ण
पूर्ण

अटल व्योम _dsp_create_scb (काष्ठा snd_cs46xx *chip, u32 * scb_data, u32 dest)
अणु
	व्योम __iomem *spdst = chip->region.idx[1].remap_addr + 
		DSP_PARAMETER_BYTE_OFFSET + dest * माप(u32);
	पूर्णांक i;

	क्रम (i = 0; i < 0x10; ++i) अणु
		dev_dbg(chip->card->dev, "addr %p, val %08x\n",
			spdst, scb_data[i]);
		ग_लिखोl(scb_data[i],spdst);
		spdst += माप(u32);
	पूर्ण
पूर्ण

अटल पूर्णांक find_मुक्त_scb_index (काष्ठा dsp_spos_instance * ins)
अणु
	पूर्णांक index = ins->nscb, i;

	क्रम (i = ins->scb_highest_frag_index; i < ins->nscb; ++i) अणु
		अगर (ins->scbs[i].deleted) अणु
			index = i;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस index;
पूर्ण

अटल काष्ठा dsp_scb_descriptor * _map_scb (काष्ठा snd_cs46xx *chip, अक्षर * name, u32 dest)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	काष्ठा dsp_scb_descriptor * desc = शून्य;
	पूर्णांक index;

	अगर (ins->nscb == DSP_MAX_SCB_DESC - 1) अणु
		dev_err(chip->card->dev,
			"dsp_spos: got no place for other SCB\n");
		वापस शून्य;
	पूर्ण

	index = find_मुक्त_scb_index (ins);

	स_रखो(&ins->scbs[index], 0, माप(ins->scbs[index]));
	म_नकल(ins->scbs[index].scb_name, name);
	ins->scbs[index].address = dest;
	ins->scbs[index].index = index;
	ins->scbs[index].ref_count = 1;

	desc = (ins->scbs + index);
	ins->scbs[index].scb_symbol = add_symbol (chip, name, dest, SYMBOL_PARAMETER);

	अगर (index > ins->scb_highest_frag_index)
		ins->scb_highest_frag_index = index;

	अगर (index == ins->nscb)
		ins->nscb++;

	वापस desc;
पूर्ण

अटल काष्ठा dsp_task_descriptor *
_map_task_tree (काष्ठा snd_cs46xx *chip, अक्षर * name, u32 dest, u32 size)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	काष्ठा dsp_task_descriptor * desc = शून्य;

	अगर (ins->ntask == DSP_MAX_TASK_DESC - 1) अणु
		dev_err(chip->card->dev,
			"dsp_spos: got no place for other TASK\n");
		वापस शून्य;
	पूर्ण

	अगर (name)
		म_नकल(ins->tasks[ins->ntask].task_name, name);
	अन्यथा
		म_नकल(ins->tasks[ins->ntask].task_name, "(NULL)");
	ins->tasks[ins->ntask].address = dest;
	ins->tasks[ins->ntask].size = size;

	/* quick find in list */
	ins->tasks[ins->ntask].index = ins->ntask;
	desc = (ins->tasks + ins->ntask);
	ins->ntask++;

	अगर (name)
		add_symbol (chip,name,dest,SYMBOL_PARAMETER);
	वापस desc;
पूर्ण

#घोषणा SCB_BYTES	(0x10 * 4)

काष्ठा dsp_scb_descriptor *
cs46xx_dsp_create_scb (काष्ठा snd_cs46xx *chip, अक्षर * name, u32 * scb_data, u32 dest)
अणु
	काष्ठा dsp_scb_descriptor * desc;

#अगर_घोषित CONFIG_PM_SLEEP
	/* copy the data क्रम resume */
	scb_data = kmemdup(scb_data, SCB_BYTES, GFP_KERNEL);
	अगर (!scb_data)
		वापस शून्य;
#पूर्ण_अगर

	desc = _map_scb (chip,name,dest);
	अगर (desc) अणु
		desc->data = scb_data;
		_dsp_create_scb(chip,scb_data,dest);
	पूर्ण अन्यथा अणु
		dev_err(chip->card->dev, "dsp_spos: failed to map SCB\n");
#अगर_घोषित CONFIG_PM_SLEEP
		kमुक्त(scb_data);
#पूर्ण_अगर
	पूर्ण

	वापस desc;
पूर्ण


अटल काष्ठा dsp_task_descriptor *
cs46xx_dsp_create_task_tree (काष्ठा snd_cs46xx *chip, अक्षर * name, u32 * task_data,
			     u32 dest, पूर्णांक size)
अणु
	काष्ठा dsp_task_descriptor * desc;

	desc = _map_task_tree (chip,name,dest,size);
	अगर (desc) अणु
		desc->data = task_data;
		_dsp_create_task_tree(chip,task_data,dest,size);
	पूर्ण अन्यथा अणु
		dev_err(chip->card->dev, "dsp_spos: failed to map TASK\n");
	पूर्ण

	वापस desc;
पूर्ण

पूर्णांक cs46xx_dsp_scb_and_task_init (काष्ठा snd_cs46xx *chip)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	काष्ठा dsp_symbol_entry * fg_task_tree_header_code;
	काष्ठा dsp_symbol_entry * task_tree_header_code;
	काष्ठा dsp_symbol_entry * task_tree_thपढ़ो;
	काष्ठा dsp_symbol_entry * null_algorithm;
	काष्ठा dsp_symbol_entry * magic_snoop_task;

	काष्ठा dsp_scb_descriptor * timing_master_scb;
	काष्ठा dsp_scb_descriptor * codec_out_scb;
	काष्ठा dsp_scb_descriptor * codec_in_scb;
	काष्ठा dsp_scb_descriptor * src_task_scb;
	काष्ठा dsp_scb_descriptor * master_mix_scb;
	काष्ठा dsp_scb_descriptor * rear_mix_scb;
	काष्ठा dsp_scb_descriptor * record_mix_scb;
	काष्ठा dsp_scb_descriptor * ग_लिखो_back_scb;
	काष्ठा dsp_scb_descriptor * vari_decimate_scb;
	काष्ठा dsp_scb_descriptor * rear_codec_out_scb;
	काष्ठा dsp_scb_descriptor * clfe_codec_out_scb;
	काष्ठा dsp_scb_descriptor * magic_snoop_scb;
	
	पूर्णांक fअगरo_addr, fअगरo_span, valid_slots;

	अटल स्थिर काष्ठा dsp_spos_control_block sposcb = अणु
		/* 0 */ HFG_TREE_SCB,HFG_STACK,
		/* 1 */ SPOSCB_ADDR,BG_TREE_SCB_ADDR,
		/* 2 */ DSP_SPOS_DC,0,
		/* 3 */ DSP_SPOS_DC,DSP_SPOS_DC,
		/* 4 */ 0,0,
		/* 5 */ DSP_SPOS_UU,0,
		/* 6 */ FG_TASK_HEADER_ADDR,0,
		/* 7 */ 0,0,
		/* 8 */ DSP_SPOS_UU,DSP_SPOS_DC,
		/* 9 */ 0,
		/* A */ 0,HFG_FIRST_EXECUTE_MODE,
		/* B */ DSP_SPOS_UU,DSP_SPOS_UU,
		/* C */ DSP_SPOS_DC_DC,
		/* D */ DSP_SPOS_DC_DC,
		/* E */ DSP_SPOS_DC_DC,
		/* F */ DSP_SPOS_DC_DC
	पूर्ण;

	cs46xx_dsp_create_task_tree(chip, "sposCB", (u32 *)&sposcb, SPOSCB_ADDR, 0x10);

	null_algorithm  = cs46xx_dsp_lookup_symbol(chip, "NULLALGORITHM", SYMBOL_CODE);
	अगर (null_algorithm == शून्य) अणु
		dev_err(chip->card->dev,
			"dsp_spos: symbol NULLALGORITHM not found\n");
		वापस -EIO;
	पूर्ण

	fg_task_tree_header_code = cs46xx_dsp_lookup_symbol(chip, "FGTASKTREEHEADERCODE", SYMBOL_CODE);  
	अगर (fg_task_tree_header_code == शून्य) अणु
		dev_err(chip->card->dev,
			"dsp_spos: symbol FGTASKTREEHEADERCODE not found\n");
		वापस -EIO;
	पूर्ण

	task_tree_header_code = cs46xx_dsp_lookup_symbol(chip, "TASKTREEHEADERCODE", SYMBOL_CODE);  
	अगर (task_tree_header_code == शून्य) अणु
		dev_err(chip->card->dev,
			"dsp_spos: symbol TASKTREEHEADERCODE not found\n");
		वापस -EIO;
	पूर्ण
  
	task_tree_thपढ़ो = cs46xx_dsp_lookup_symbol(chip, "TASKTREETHREAD", SYMBOL_CODE);
	अगर (task_tree_thपढ़ो == शून्य) अणु
		dev_err(chip->card->dev,
			"dsp_spos: symbol TASKTREETHREAD not found\n");
		वापस -EIO;
	पूर्ण

	magic_snoop_task = cs46xx_dsp_lookup_symbol(chip, "MAGICSNOOPTASK", SYMBOL_CODE);
	अगर (magic_snoop_task == शून्य) अणु
		dev_err(chip->card->dev,
			"dsp_spos: symbol MAGICSNOOPTASK not found\n");
		वापस -EIO;
	पूर्ण
  
	अणु
		/* create the null SCB */
		अटल काष्ठा dsp_generic_scb null_scb = अणु
			अणु 0, 0, 0, 0 पूर्ण,
			अणु 0, 0, 0, 0, 0 पूर्ण,
			शून्य_SCB_ADDR, शून्य_SCB_ADDR,
			0, 0, 0, 0, 0,
			अणु
				0,0,
				0,0,
			पूर्ण
		पूर्ण;

		null_scb.entry_poपूर्णांक = null_algorithm->address;
		ins->the_null_scb = cs46xx_dsp_create_scb(chip, "nullSCB", (u32 *)&null_scb, शून्य_SCB_ADDR);
		ins->the_null_scb->task_entry = null_algorithm;
		ins->the_null_scb->sub_list_ptr = ins->the_null_scb;
		ins->the_null_scb->next_scb_ptr = ins->the_null_scb;
		ins->the_null_scb->parent_scb_ptr = शून्य;
		cs46xx_dsp_proc_रेजिस्टर_scb_desc (chip,ins->the_null_scb);
	पूर्ण

	अणु
		/* setup क्रमeground task tree */
		अटल काष्ठा dsp_task_tree_control_block fg_task_tree_hdr =  अणु
			अणु FG_TASK_HEADER_ADDR | (DSP_SPOS_DC << 0x10),
			  DSP_SPOS_DC_DC,
			  DSP_SPOS_DC_DC,
			  0x0000,DSP_SPOS_DC,
			  DSP_SPOS_DC, DSP_SPOS_DC,
			  DSP_SPOS_DC_DC,
			  DSP_SPOS_DC_DC,
			  DSP_SPOS_DC_DC,
			  DSP_SPOS_DC,DSP_SPOS_DC पूर्ण,
    
			अणु
				BG_TREE_SCB_ADDR,TIMINGMASTER_SCB_ADDR, 
				0,
				FG_TASK_HEADER_ADDR + TCBData,                  
			पूर्ण,

			अणु    
				4,0,
				1,0,
				2,SPOSCB_ADDR + HFGFlags,
				0,0,
				FG_TASK_HEADER_ADDR + TCBContextBlk,FG_STACK
			पूर्ण,

			अणु
				DSP_SPOS_DC,0,
				DSP_SPOS_DC,DSP_SPOS_DC,
				DSP_SPOS_DC,DSP_SPOS_DC,
				DSP_SPOS_DC,DSP_SPOS_DC,
				DSP_SPOS_DC,DSP_SPOS_DC,
				DSP_SPOS_DCDC,
				DSP_SPOS_UU,1,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC 
			पूर्ण,                                               
			अणु 
				FG_INTERVAL_TIMER_PERIOD,DSP_SPOS_UU,
				0,0
			पूर्ण
		पूर्ण;

		fg_task_tree_hdr.links.entry_poपूर्णांक = fg_task_tree_header_code->address;
		fg_task_tree_hdr.context_blk.stack0 = task_tree_thपढ़ो->address;
		cs46xx_dsp_create_task_tree(chip,"FGtaskTreeHdr",(u32 *)&fg_task_tree_hdr,FG_TASK_HEADER_ADDR,0x35);
	पूर्ण


	अणु
		/* setup क्रमeground task tree */
		अटल काष्ठा dsp_task_tree_control_block bg_task_tree_hdr =  अणु
			अणु DSP_SPOS_DC_DC,
			  DSP_SPOS_DC_DC,
			  DSP_SPOS_DC_DC,
			  DSP_SPOS_DC, DSP_SPOS_DC,
			  DSP_SPOS_DC, DSP_SPOS_DC,
			  DSP_SPOS_DC_DC,
			  DSP_SPOS_DC_DC,
			  DSP_SPOS_DC_DC,
			  DSP_SPOS_DC,DSP_SPOS_DC पूर्ण,
    
			अणु
				शून्य_SCB_ADDR,शून्य_SCB_ADDR,  /* Set up the background to करो nothing */
				0,
				BG_TREE_SCB_ADDR + TCBData,
			पूर्ण,

			अणु    
				9999,0,
				0,1,
				0,SPOSCB_ADDR + HFGFlags,
				0,0,
				BG_TREE_SCB_ADDR + TCBContextBlk,BG_STACK
			पूर्ण,

			अणु
				DSP_SPOS_DC,0,
				DSP_SPOS_DC,DSP_SPOS_DC,
				DSP_SPOS_DC,DSP_SPOS_DC,
				DSP_SPOS_DC,DSP_SPOS_DC,
				DSP_SPOS_DC,DSP_SPOS_DC,
				DSP_SPOS_DCDC,
				DSP_SPOS_UU,1,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC,
				DSP_SPOS_DCDC 
			पूर्ण,                                               
			अणु 
				BG_INTERVAL_TIMER_PERIOD,DSP_SPOS_UU,
				0,0
			पूर्ण
		पूर्ण;

		bg_task_tree_hdr.links.entry_poपूर्णांक = task_tree_header_code->address;
		bg_task_tree_hdr.context_blk.stack0 = task_tree_thपढ़ो->address;
		cs46xx_dsp_create_task_tree(chip,"BGtaskTreeHdr",(u32 *)&bg_task_tree_hdr,BG_TREE_SCB_ADDR,0x35);
	पूर्ण

	/* create timing master SCB */
	timing_master_scb = cs46xx_dsp_create_timing_master_scb(chip);

	/* create the CODEC output task */
	codec_out_scb = cs46xx_dsp_create_codec_out_scb(chip,"CodecOutSCB_I",0x0010,0x0000,
							MASTERMIX_SCB_ADDR,
							CODECOUT_SCB_ADDR,timing_master_scb,
							SCB_ON_PARENT_SUBLIST_SCB);

	अगर (!codec_out_scb) जाओ _fail_end;
	/* create the master mix SCB */
	master_mix_scb = cs46xx_dsp_create_mix_only_scb(chip,"MasterMixSCB",
							MIX_SAMPLE_BUF1,MASTERMIX_SCB_ADDR,
							codec_out_scb,
							SCB_ON_PARENT_SUBLIST_SCB);
	ins->master_mix_scb = master_mix_scb;

	अगर (!master_mix_scb) जाओ _fail_end;

	/* create codec in */
	codec_in_scb = cs46xx_dsp_create_codec_in_scb(chip,"CodecInSCB",0x0010,0x00A0,
						      CODEC_INPUT_BUF1,
						      CODECIN_SCB_ADDR,codec_out_scb,
						      SCB_ON_PARENT_NEXT_SCB);
	अगर (!codec_in_scb) जाओ _fail_end;
	ins->codec_in_scb = codec_in_scb;

	/* create ग_लिखो back scb */
	ग_लिखो_back_scb = cs46xx_dsp_create_mix_to_ostream_scb(chip,"WriteBackSCB",
							      WRITE_BACK_BUF1,WRITE_BACK_SPB,
							      WRITEBACK_SCB_ADDR,
							      timing_master_scb,
							      SCB_ON_PARENT_NEXT_SCB);
	अगर (!ग_लिखो_back_scb) जाओ _fail_end;

	अणु
		अटल काष्ठा dsp_mix2_ostream_spb mix2_ostream_spb = अणु
			0x00020000,
			0x0000ffff
		पूर्ण;
    
		अगर (!cs46xx_dsp_create_task_tree(chip, शून्य,
						 (u32 *)&mix2_ostream_spb,
						 WRITE_BACK_SPB, 2))
			जाओ _fail_end;
	पूर्ण

	/* input sample converter */
	vari_decimate_scb = cs46xx_dsp_create_vari_decimate_scb(chip,"VariDecimateSCB",
								VARI_DECIMATE_BUF0,
								VARI_DECIMATE_BUF1,
								VARIDECIMATE_SCB_ADDR,
								ग_लिखो_back_scb,
								SCB_ON_PARENT_SUBLIST_SCB);
	अगर (!vari_decimate_scb) जाओ _fail_end;

	/* create the record mixer SCB */
	record_mix_scb = cs46xx_dsp_create_mix_only_scb(chip,"RecordMixerSCB",
							MIX_SAMPLE_BUF2,
							RECORD_MIXER_SCB_ADDR,
							vari_decimate_scb,
							SCB_ON_PARENT_SUBLIST_SCB);
	ins->record_mixer_scb = record_mix_scb;

	अगर (!record_mix_scb) जाओ _fail_end;

	valid_slots = snd_cs46xx_peekBA0(chip, BA0_ACOSV);

	अगर (snd_BUG_ON(chip->nr_ac97_codecs != 1 && chip->nr_ac97_codecs != 2))
		जाओ _fail_end;

	अगर (chip->nr_ac97_codecs == 1) अणु
		/* output on slot 5 and 11 
		   on primary CODEC */
		fअगरo_addr = 0x20;
		fअगरo_span = 0x60;

		/* enable slot 5 and 11 */
		valid_slots |= ACOSV_SLV5 | ACOSV_SLV11;
	पूर्ण अन्यथा अणु
		/* output on slot 7 and 8 
		   on secondary CODEC */
		fअगरo_addr = 0x40;
		fअगरo_span = 0x10;

		/* enable slot 7 and 8 */
		valid_slots |= ACOSV_SLV7 | ACOSV_SLV8;
	पूर्ण
	/* create CODEC tasklet क्रम rear speakers output*/
	rear_codec_out_scb = cs46xx_dsp_create_codec_out_scb(chip,"CodecOutSCB_Rear",fअगरo_span,fअगरo_addr,
							     REAR_MIXER_SCB_ADDR,
							     REAR_CODECOUT_SCB_ADDR,codec_in_scb,
							     SCB_ON_PARENT_NEXT_SCB);
	अगर (!rear_codec_out_scb) जाओ _fail_end;
	
	
	/* create the rear PCM channel  mixer SCB */
	rear_mix_scb = cs46xx_dsp_create_mix_only_scb(chip,"RearMixerSCB",
						      MIX_SAMPLE_BUF3,
						      REAR_MIXER_SCB_ADDR,
						      rear_codec_out_scb,
						      SCB_ON_PARENT_SUBLIST_SCB);
	ins->rear_mix_scb = rear_mix_scb;
	अगर (!rear_mix_scb) जाओ _fail_end;
	
	अगर (chip->nr_ac97_codecs == 2) अणु
		/* create CODEC tasklet क्रम rear Center/LFE output 
		   slot 6 and 9 on secondary CODEC */
		clfe_codec_out_scb = cs46xx_dsp_create_codec_out_scb(chip,"CodecOutSCB_CLFE",0x0030,0x0030,
								     CLFE_MIXER_SCB_ADDR,
								     CLFE_CODEC_SCB_ADDR,
								     rear_codec_out_scb,
								     SCB_ON_PARENT_NEXT_SCB);
		अगर (!clfe_codec_out_scb) जाओ _fail_end;
		
		
		/* create the rear PCM channel  mixer SCB */
		ins->center_lfe_mix_scb = cs46xx_dsp_create_mix_only_scb(chip,"CLFEMixerSCB",
									 MIX_SAMPLE_BUF4,
									 CLFE_MIXER_SCB_ADDR,
									 clfe_codec_out_scb,
									 SCB_ON_PARENT_SUBLIST_SCB);
		अगर (!ins->center_lfe_mix_scb) जाओ _fail_end;

		/* enable slot 6 and 9 */
		valid_slots |= ACOSV_SLV6 | ACOSV_SLV9;
	पूर्ण अन्यथा अणु
		clfe_codec_out_scb = rear_codec_out_scb;
		ins->center_lfe_mix_scb = rear_mix_scb;
	पूर्ण

	/* enable slots depending on CODEC configuration */
	snd_cs46xx_pokeBA0(chip, BA0_ACOSV, valid_slots);

	/* the magic snooper */
	magic_snoop_scb = cs46xx_dsp_create_magic_snoop_scb (chip,"MagicSnoopSCB_I",OUTPUTSNOOP_SCB_ADDR,
							     OUTPUT_SNOOP_BUFFER,
							     codec_out_scb,
							     clfe_codec_out_scb,
							     SCB_ON_PARENT_NEXT_SCB);

    
	अगर (!magic_snoop_scb) जाओ _fail_end;
	ins->ref_snoop_scb = magic_snoop_scb;

	/* SP IO access */
	अगर (!cs46xx_dsp_create_spio_ग_लिखो_scb(chip,"SPIOWriteSCB",SPIOWRITE_SCB_ADDR,
					      magic_snoop_scb,
					      SCB_ON_PARENT_NEXT_SCB))
		जाओ _fail_end;

	/* SPDIF input sampel rate converter */
	src_task_scb = cs46xx_dsp_create_src_task_scb(chip,"SrcTaskSCB_SPDIFI",
						      ins->spdअगर_in_sample_rate,
						      SRC_OUTPUT_BUF1,
						      SRC_DELAY_BUF1,SRCTASK_SCB_ADDR,
						      master_mix_scb,
						      SCB_ON_PARENT_SUBLIST_SCB,1);

	अगर (!src_task_scb) जाओ _fail_end;
	cs46xx_src_unlink(chip,src_task_scb);

	/* NOTE: when we now how to detect the SPDIF input
	   sample rate we will use this SRC to adjust it */
	ins->spdअगर_in_src = src_task_scb;

	cs46xx_dsp_async_init(chip,timing_master_scb);
	वापस 0;

 _fail_end:
	dev_err(chip->card->dev, "dsp_spos: failed to setup SCB's in DSP\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cs46xx_dsp_async_init (काष्ठा snd_cs46xx *chip,
				  काष्ठा dsp_scb_descriptor * fg_entry)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	काष्ठा dsp_symbol_entry * s16_async_codec_input_task;
	काष्ठा dsp_symbol_entry * spdअगरo_task;
	काष्ठा dsp_symbol_entry * spdअगरi_task;
	काष्ठा dsp_scb_descriptor * spdअगरi_scb_desc, * spdअगरo_scb_desc, * async_codec_scb_desc;

	s16_async_codec_input_task = cs46xx_dsp_lookup_symbol(chip, "S16_ASYNCCODECINPUTTASK", SYMBOL_CODE);
	अगर (s16_async_codec_input_task == शून्य) अणु
		dev_err(chip->card->dev,
			"dsp_spos: symbol S16_ASYNCCODECINPUTTASK not found\n");
		वापस -EIO;
	पूर्ण
	spdअगरo_task = cs46xx_dsp_lookup_symbol(chip, "SPDIFOTASK", SYMBOL_CODE);
	अगर (spdअगरo_task == शून्य) अणु
		dev_err(chip->card->dev,
			"dsp_spos: symbol SPDIFOTASK not found\n");
		वापस -EIO;
	पूर्ण

	spdअगरi_task = cs46xx_dsp_lookup_symbol(chip, "SPDIFITASK", SYMBOL_CODE);
	अगर (spdअगरi_task == शून्य) अणु
		dev_err(chip->card->dev,
			"dsp_spos: symbol SPDIFITASK not found\n");
		वापस -EIO;
	पूर्ण

	अणु
		/* 0xBC0 */
		काष्ठा dsp_spdअगरoscb spdअगरo_scb = अणु
			/* 0 */ DSP_SPOS_UUUU,
			अणु
				/* 1 */ 0xb0, 
				/* 2 */ 0, 
				/* 3 */ 0, 
				/* 4 */ 0, 
			पूर्ण,
			/* NOTE: the SPDIF output task पढ़ो samples in mono
			   क्रमmat, the AsynchFGTxSCB task ग_लिखोs to buffer
			   in stereo क्रमmat
			*/
			/* 5 */ RSCONFIG_SAMPLE_16MONO + RSCONFIG_MODULO_256,
			/* 6 */ ( SPDIFO_IP_OUTPUT_BUFFER1 << 0x10 )  |  0xFFFC,
			/* 7 */ 0,0, 
			/* 8 */ 0, 
			/* 9 */ FG_TASK_HEADER_ADDR, शून्य_SCB_ADDR, 
			/* A */ spdअगरo_task->address,
			SPDIFO_SCB_INST + SPDIFOFIFOPoपूर्णांकer,
			अणु
				/* B */ 0x0040, /*DSP_SPOS_UUUU,*/
				/* C */ 0x20ff, /*DSP_SPOS_UUUU,*/
			पूर्ण,
			/* D */ 0x804c,0,							  /* SPDIFOFIFOPoपूर्णांकer:SPDIFOStatRegAddr; */
			/* E */ 0x0108,0x0001,					  /* SPDIFOStMoFormat:SPDIFOFIFOBaseAddr; */
			/* F */ DSP_SPOS_UUUU	  			          /* SPDIFOFree; */
		पूर्ण;

		/* 0xBB0 */
		काष्ठा dsp_spdअगरiscb spdअगरi_scb = अणु
			/* 0 */ DSP_SPOS_UULO,DSP_SPOS_UUHI,
			/* 1 */ 0,
			/* 2 */ 0,
			/* 3 */ 1,4000,        /* SPDIFICountLimit SPDIFICount */ 
			/* 4 */ DSP_SPOS_UUUU, /* SPDIFIStatusData */
			/* 5 */ 0,DSP_SPOS_UUHI, /* StatusData, Free4 */
			/* 6 */ DSP_SPOS_UUUU,  /* Free3 */
			/* 7 */ DSP_SPOS_UU,DSP_SPOS_DC,  /* Free2 BitCount*/
			/* 8 */ DSP_SPOS_UUUU,	/* TempStatus */
			/* 9 */ SPDIFO_SCB_INST, शून्य_SCB_ADDR,
			/* A */ spdअगरi_task->address,
			SPDIFI_SCB_INST + SPDIFIFIFOPoपूर्णांकer,
			/* NOTE: The SPDIF input task ग_लिखो the sample in mono
			   क्रमmat from the HW FIFO, the AsynchFGRxSCB task  पढ़ोs 
			   them in stereo 
			*/
			/* B */ RSCONFIG_SAMPLE_16MONO + RSCONFIG_MODULO_128,
			/* C */ (SPDIFI_IP_OUTPUT_BUFFER1 << 0x10) | 0xFFFC,
			/* D */ 0x8048,0,
			/* E */ 0x01f0,0x0001,
			/* F */ DSP_SPOS_UUUU /* SPDIN_STATUS monitor */
		पूर्ण;

		/* 0xBA0 */
		काष्ठा dsp_async_codec_input_scb async_codec_input_scb = अणु
			/* 0 */ DSP_SPOS_UUUU,
			/* 1 */ 0,
			/* 2 */ 0,
			/* 3 */ 1,4000,
			/* 4 */ 0x0118,0x0001,
			/* 5 */ RSCONFIG_SAMPLE_16MONO + RSCONFIG_MODULO_64,
			/* 6 */ (ASYNC_IP_OUTPUT_BUFFER1 << 0x10) | 0xFFFC,
			/* 7 */ DSP_SPOS_UU,0x3,
			/* 8 */ DSP_SPOS_UUUU,
			/* 9 */ SPDIFI_SCB_INST,शून्य_SCB_ADDR,
			/* A */ s16_async_codec_input_task->address,
			HFG_TREE_SCB + AsyncCIOFIFOPoपूर्णांकer,
              
			/* B */ RSCONFIG_SAMPLE_16STEREO + RSCONFIG_MODULO_64,
			/* C */ (ASYNC_IP_OUTPUT_BUFFER1 << 0x10),  /*(ASYNC_IP_OUTPUT_BUFFER1 << 0x10) | 0xFFFC,*/
      
#अगर_घोषित UseASER1Input
			/* लघु AsyncCIFIFOPoपूर्णांकer:AsyncCIStatRegAddr;	       
			   Init. 0000:8042: क्रम ASER1
			   0000:8044: क्रम ASER2 */
			/* D */ 0x8042,0,
      
			/* लघु AsyncCIStMoFormat:AsyncCIFIFOBaseAddr;
			   Init 1 stero:8050 ASER1
			   Init 0  mono:8070 ASER2
			   Init 1 Stereo : 0100 ASER1 (Set by script) */
			/* E */ 0x0100,0x0001,
      
#पूर्ण_अगर
      
#अगर_घोषित UseASER2Input
			/* लघु AsyncCIFIFOPoपूर्णांकer:AsyncCIStatRegAddr;
			   Init. 0000:8042: क्रम ASER1
			   0000:8044: क्रम ASER2 */
			/* D */ 0x8044,0,
      
			/* लघु AsyncCIStMoFormat:AsyncCIFIFOBaseAddr;
			   Init 1 stero:8050 ASER1
			   Init 0  mono:8070 ASER2
			   Init 1 Stereo : 0100 ASER1 (Set by script) */
			/* E */ 0x0110,0x0001,
      
#पूर्ण_अगर
      
			/* लघु AsyncCIOutputBufModulo:AsyncCIFree;
			   AsyncCIOutputBufModulo: The modulo size क्रम   
			   the output buffer of this task */
			/* F */ 0, /* DSP_SPOS_UUUU */
		पूर्ण;

		spdअगरo_scb_desc = cs46xx_dsp_create_scb(chip,"SPDIFOSCB",(u32 *)&spdअगरo_scb,SPDIFO_SCB_INST);

		अगर (snd_BUG_ON(!spdअगरo_scb_desc))
			वापस -EIO;
		spdअगरi_scb_desc = cs46xx_dsp_create_scb(chip,"SPDIFISCB",(u32 *)&spdअगरi_scb,SPDIFI_SCB_INST);
		अगर (snd_BUG_ON(!spdअगरi_scb_desc))
			वापस -EIO;
		async_codec_scb_desc = cs46xx_dsp_create_scb(chip,"AsynCodecInputSCB",(u32 *)&async_codec_input_scb, HFG_TREE_SCB);
		अगर (snd_BUG_ON(!async_codec_scb_desc))
			वापस -EIO;

		async_codec_scb_desc->parent_scb_ptr = शून्य;
		async_codec_scb_desc->next_scb_ptr = spdअगरi_scb_desc;
		async_codec_scb_desc->sub_list_ptr = ins->the_null_scb;
		async_codec_scb_desc->task_entry = s16_async_codec_input_task;

		spdअगरi_scb_desc->parent_scb_ptr = async_codec_scb_desc;
		spdअगरi_scb_desc->next_scb_ptr = spdअगरo_scb_desc;
		spdअगरi_scb_desc->sub_list_ptr = ins->the_null_scb;
		spdअगरi_scb_desc->task_entry = spdअगरi_task;

		spdअगरo_scb_desc->parent_scb_ptr = spdअगरi_scb_desc;
		spdअगरo_scb_desc->next_scb_ptr = fg_entry;
		spdअगरo_scb_desc->sub_list_ptr = ins->the_null_scb;
		spdअगरo_scb_desc->task_entry = spdअगरo_task;

		/* this one is faked, as the parnet of SPDIFO task
		   is the FG task tree */
		fg_entry->parent_scb_ptr = spdअगरo_scb_desc;

		/* क्रम proc fs */
		cs46xx_dsp_proc_रेजिस्टर_scb_desc (chip,spdअगरo_scb_desc);
		cs46xx_dsp_proc_रेजिस्टर_scb_desc (chip,spdअगरi_scb_desc);
		cs46xx_dsp_proc_रेजिस्टर_scb_desc (chip,async_codec_scb_desc);

		/* Async MASTER ENABLE, affects both SPDIF input and output */
		snd_cs46xx_pokeBA0(chip, BA0_ASER_MASTER, 0x1 );
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cs46xx_dsp_disable_spdअगर_hw (काष्ठा snd_cs46xx *chip)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	/* set SPDIF output FIFO slot */
	snd_cs46xx_pokeBA0(chip, BA0_ASER_FADDR, 0);

	/* SPDIF output MASTER ENABLE */
	cs46xx_poke_via_dsp (chip,SP_SPDOUT_CONTROL, 0);

	/* right and left validate bit */
	/*cs46xx_poke_via_dsp (chip,SP_SPDOUT_CSUV, ins->spdअगर_csuv_शेष);*/
	cs46xx_poke_via_dsp (chip,SP_SPDOUT_CSUV, 0x0);

	/* clear fअगरo poपूर्णांकer */
	cs46xx_poke_via_dsp (chip,SP_SPDIN_FIFOPTR, 0x0);

	/* monitor state */
	ins->spdअगर_status_out &= ~DSP_SPDIF_STATUS_HW_ENABLED;
पूर्ण

पूर्णांक cs46xx_dsp_enable_spdअगर_hw (काष्ठा snd_cs46xx *chip)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	/* अगर hw-ctrl alपढ़ोy enabled, turn off to reset logic ... */
	cs46xx_dsp_disable_spdअगर_hw (chip);
	udelay(50);

	/* set SPDIF output FIFO slot */
	snd_cs46xx_pokeBA0(chip, BA0_ASER_FADDR, ( 0x8000 | ((SP_SPDOUT_FIFO >> 4) << 4) ));

	/* SPDIF output MASTER ENABLE */
	cs46xx_poke_via_dsp (chip,SP_SPDOUT_CONTROL, 0x80000000);

	/* right and left validate bit */
	cs46xx_poke_via_dsp (chip,SP_SPDOUT_CSUV, ins->spdअगर_csuv_शेष);

	/* monitor state */
	ins->spdअगर_status_out |= DSP_SPDIF_STATUS_HW_ENABLED;

	वापस 0;
पूर्ण

पूर्णांक cs46xx_dsp_enable_spdअगर_in (काष्ठा snd_cs46xx *chip)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	/* turn on amplअगरier */
	chip->active_ctrl(chip, 1);
	chip->amplअगरier_ctrl(chip, 1);

	अगर (snd_BUG_ON(ins->asynch_rx_scb))
		वापस -EINVAL;
	अगर (snd_BUG_ON(!ins->spdअगर_in_src))
		वापस -EINVAL;

	mutex_lock(&chip->spos_mutex);

	अगर ( ! (ins->spdअगर_status_out & DSP_SPDIF_STATUS_INPUT_CTRL_ENABLED) ) अणु
		/* समय countकरोwn enable */
		cs46xx_poke_via_dsp (chip,SP_ASER_COUNTDOWN, 0x80000005);
		/* NOTE: 80000005 value is just magic. With all values
		   that I've tested this one seem to give the best result.
		   Got no explication why. (Benny) */

		/* SPDIF input MASTER ENABLE */
		cs46xx_poke_via_dsp (chip,SP_SPDIN_CONTROL, 0x800003ff);

		ins->spdअगर_status_out |= DSP_SPDIF_STATUS_INPUT_CTRL_ENABLED;
	पूर्ण

	/* create and start the asynchronous receiver SCB */
	ins->asynch_rx_scb = cs46xx_dsp_create_asynch_fg_rx_scb(chip,"AsynchFGRxSCB",
								ASYNCRX_SCB_ADDR,
								SPDIFI_SCB_INST,
								SPDIFI_IP_OUTPUT_BUFFER1,
								ins->spdअगर_in_src,
								SCB_ON_PARENT_SUBLIST_SCB);

	spin_lock_irq(&chip->reg_lock);

	/* reset SPDIF input sample buffer poपूर्णांकer */
	/*snd_cs46xx_poke (chip, (SPDIFI_SCB_INST + 0x0c) << 2,
	  (SPDIFI_IP_OUTPUT_BUFFER1 << 0x10) | 0xFFFC);*/

	/* reset FIFO ptr */
	/*cs46xx_poke_via_dsp (chip,SP_SPDIN_FIFOPTR, 0x0);*/
	cs46xx_src_link(chip,ins->spdअगर_in_src);

	/* unmute SRC volume */
	cs46xx_dsp_scb_set_volume (chip,ins->spdअगर_in_src,0x7fff,0x7fff);

	spin_unlock_irq(&chip->reg_lock);

	/* set SPDIF input sample rate and unmute
	   NOTE: only 48khz support क्रम SPDIF input this समय */
	/* cs46xx_dsp_set_src_sample_rate(chip,ins->spdअगर_in_src,48000); */

	/* monitor state */
	ins->spdअगर_status_in = 1;
	mutex_unlock(&chip->spos_mutex);

	वापस 0;
पूर्ण

पूर्णांक cs46xx_dsp_disable_spdअगर_in (काष्ठा snd_cs46xx *chip)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	अगर (snd_BUG_ON(!ins->asynch_rx_scb))
		वापस -EINVAL;
	अगर (snd_BUG_ON(!ins->spdअगर_in_src))
		वापस -EINVAL;

	mutex_lock(&chip->spos_mutex);

	/* Remove the asynchronous receiver SCB */
	cs46xx_dsp_हटाओ_scb (chip,ins->asynch_rx_scb);
	ins->asynch_rx_scb = शून्य;

	cs46xx_src_unlink(chip,ins->spdअगर_in_src);

	/* monitor state */
	ins->spdअगर_status_in = 0;
	mutex_unlock(&chip->spos_mutex);

	/* restore amplअगरier */
	chip->active_ctrl(chip, -1);
	chip->amplअगरier_ctrl(chip, -1);

	वापस 0;
पूर्ण

पूर्णांक cs46xx_dsp_enable_pcm_capture (काष्ठा snd_cs46xx *chip)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	अगर (snd_BUG_ON(ins->pcm_input))
		वापस -EINVAL;
	अगर (snd_BUG_ON(!ins->ref_snoop_scb))
		वापस -EINVAL;

	mutex_lock(&chip->spos_mutex);
	ins->pcm_input = cs46xx_add_record_source(chip,ins->ref_snoop_scb,PCMSERIALIN_PCM_SCB_ADDR,
                                                  "PCMSerialInput_Wave");
	mutex_unlock(&chip->spos_mutex);

	वापस 0;
पूर्ण

पूर्णांक cs46xx_dsp_disable_pcm_capture (काष्ठा snd_cs46xx *chip)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	अगर (snd_BUG_ON(!ins->pcm_input))
		वापस -EINVAL;

	mutex_lock(&chip->spos_mutex);
	cs46xx_dsp_हटाओ_scb (chip,ins->pcm_input);
	ins->pcm_input = शून्य;
	mutex_unlock(&chip->spos_mutex);

	वापस 0;
पूर्ण

पूर्णांक cs46xx_dsp_enable_adc_capture (काष्ठा snd_cs46xx *chip)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	अगर (snd_BUG_ON(ins->adc_input))
		वापस -EINVAL;
	अगर (snd_BUG_ON(!ins->codec_in_scb))
		वापस -EINVAL;

	mutex_lock(&chip->spos_mutex);
	ins->adc_input = cs46xx_add_record_source(chip,ins->codec_in_scb,PCMSERIALIN_SCB_ADDR,
						  "PCMSerialInput_ADC");
	mutex_unlock(&chip->spos_mutex);

	वापस 0;
पूर्ण

पूर्णांक cs46xx_dsp_disable_adc_capture (काष्ठा snd_cs46xx *chip)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	अगर (snd_BUG_ON(!ins->adc_input))
		वापस -EINVAL;

	mutex_lock(&chip->spos_mutex);
	cs46xx_dsp_हटाओ_scb (chip,ins->adc_input);
	ins->adc_input = शून्य;
	mutex_unlock(&chip->spos_mutex);

	वापस 0;
पूर्ण

पूर्णांक cs46xx_poke_via_dsp (काष्ठा snd_cs46xx *chip, u32 address, u32 data)
अणु
	u32 temp;
	पूर्णांक  i;

	/* santiy check the parameters.  (These numbers are not 100% correct.  They are
	   a rough guess from looking at the controller spec.) */
	अगर (address < 0x8000 || address >= 0x9000)
		वापस -EINVAL;
        
	/* initialize the SP_IO_WRITE SCB with the data. */
	temp = ( address << 16 ) | ( address & 0x0000FFFF);   /* offset 0 <-- address2 : address1 */

	snd_cs46xx_poke(chip,( SPIOWRITE_SCB_ADDR      << 2), temp);
	snd_cs46xx_poke(chip,((SPIOWRITE_SCB_ADDR + 1) << 2), data); /* offset 1 <-- data1 */
	snd_cs46xx_poke(chip,((SPIOWRITE_SCB_ADDR + 2) << 2), data); /* offset 1 <-- data2 */
    
	/* Poke this location to tell the task to start */
	snd_cs46xx_poke(chip,((SPIOWRITE_SCB_ADDR + 6) << 2), SPIOWRITE_SCB_ADDR << 0x10);

	/* Verअगरy that the task ran */
	क्रम (i=0; i<25; i++) अणु
		udelay(125);

		temp =  snd_cs46xx_peek(chip,((SPIOWRITE_SCB_ADDR + 6) << 2));
		अगर (temp == 0x00000000)
			अवरोध;
	पूर्ण

	अगर (i == 25) अणु
		dev_err(chip->card->dev,
			"dsp_spos: SPIOWriteTask not responding\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cs46xx_dsp_set_dac_volume (काष्ठा snd_cs46xx * chip, u16 left, u16 right)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	काष्ठा dsp_scb_descriptor * scb; 

	mutex_lock(&chip->spos_mutex);
	
	/* मुख्य output */
	scb = ins->master_mix_scb->sub_list_ptr;
	जबतक (scb != ins->the_null_scb) अणु
		cs46xx_dsp_scb_set_volume (chip,scb,left,right);
		scb = scb->next_scb_ptr;
	पूर्ण

	/* rear output */
	scb = ins->rear_mix_scb->sub_list_ptr;
	जबतक (scb != ins->the_null_scb) अणु
		cs46xx_dsp_scb_set_volume (chip,scb,left,right);
		scb = scb->next_scb_ptr;
	पूर्ण

	ins->dac_volume_left = left;
	ins->dac_volume_right = right;

	mutex_unlock(&chip->spos_mutex);

	वापस 0;
पूर्ण

पूर्णांक cs46xx_dsp_set_iec958_volume (काष्ठा snd_cs46xx * chip, u16 left, u16 right)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	mutex_lock(&chip->spos_mutex);

	अगर (ins->asynch_rx_scb != शून्य)
		cs46xx_dsp_scb_set_volume (chip,ins->asynch_rx_scb,
					   left,right);

	ins->spdअगर_input_volume_left = left;
	ins->spdअगर_input_volume_right = right;

	mutex_unlock(&chip->spos_mutex);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक cs46xx_dsp_resume(काष्ठा snd_cs46xx * chip)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	पूर्णांक i, err;

	/* clear parameter, sample and code areas */
	snd_cs46xx_clear_BA1(chip, DSP_PARAMETER_BYTE_OFFSET,
			     DSP_PARAMETER_BYTE_SIZE);
	snd_cs46xx_clear_BA1(chip, DSP_SAMPLE_BYTE_OFFSET,
			     DSP_SAMPLE_BYTE_SIZE);
	snd_cs46xx_clear_BA1(chip, DSP_CODE_BYTE_OFFSET, DSP_CODE_BYTE_SIZE);

	क्रम (i = 0; i < ins->nmodules; i++) अणु
		काष्ठा dsp_module_desc *module = &ins->modules[i];
		काष्ठा dsp_segment_desc *seg;
		u32 करोffset, dsize;

		seg = get_segment_desc(module, SEGTYPE_SP_PARAMETER);
		err = dsp_load_parameter(chip, seg);
		अगर (err < 0)
			वापस err;

		seg = get_segment_desc(module, SEGTYPE_SP_SAMPLE);
		err = dsp_load_sample(chip, seg);
		अगर (err < 0)
			वापस err;

		seg = get_segment_desc(module, SEGTYPE_SP_PROGRAM);
		अगर (!seg)
			जारी;

		करोffset = seg->offset * 4 + module->load_address * 4
			+ DSP_CODE_BYTE_OFFSET;
		dsize   = seg->size * 4;
		err = snd_cs46xx_करोwnload(chip,
					  ins->code.data + module->load_address,
					  करोffset, dsize);
		अगर (err < 0)
			वापस err;
	पूर्ण

	क्रम (i = 0; i < ins->ntask; i++) अणु
		काष्ठा dsp_task_descriptor *t = &ins->tasks[i];
		_dsp_create_task_tree(chip, t->data, t->address, t->size);
	पूर्ण

	क्रम (i = 0; i < ins->nscb; i++) अणु
		काष्ठा dsp_scb_descriptor *s = &ins->scbs[i];
		अगर (s->deleted)
			जारी;
		_dsp_create_scb(chip, s->data, s->address);
	पूर्ण
	क्रम (i = 0; i < ins->nscb; i++) अणु
		काष्ठा dsp_scb_descriptor *s = &ins->scbs[i];
		अगर (s->deleted)
			जारी;
		अगर (s->updated)
			cs46xx_dsp_spos_update_scb(chip, s);
		अगर (s->volume_set)
			cs46xx_dsp_scb_set_volume(chip, s,
						  s->volume[0], s->volume[1]);
	पूर्ण
	अगर (ins->spdअगर_status_out & DSP_SPDIF_STATUS_HW_ENABLED) अणु
		cs46xx_dsp_enable_spdअगर_hw(chip);
		snd_cs46xx_poke(chip, (ins->ref_snoop_scb->address + 2) << 2,
				(OUTPUT_SNOOP_BUFFER + 0x10) << 0x10);
		अगर (ins->spdअगर_status_out & DSP_SPDIF_STATUS_PLAYBACK_OPEN)
			cs46xx_poke_via_dsp(chip, SP_SPDOUT_CSUV,
					    ins->spdअगर_csuv_stream);
	पूर्ण
	अगर (chip->dsp_spos_instance->spdअगर_status_in) अणु
		cs46xx_poke_via_dsp(chip, SP_ASER_COUNTDOWN, 0x80000005);
		cs46xx_poke_via_dsp(chip, SP_SPDIN_CONTROL, 0x800003ff);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर
