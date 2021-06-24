<शैली गुरु>
/*
 * Workbit NinjaSCSI-32Bi/UDE PCI/CardBus SCSI Host Bus Adapter driver
 * Debug routine
 *
 * This software may be used and distributed according to the terms of
 * the GNU General Public License.
 */

/*
 * Show the command data of a command
 */
अटल स्थिर अक्षर unknown[] = "UNKNOWN";

अटल स्थिर अक्षर * group_0_commands[] = अणु
/* 00-03 */ "Test Unit Ready", "Rezero Unit", unknown, "Request Sense",
/* 04-07 */ "Format Unit", "Read Block Limits", unknown, "Reassign Blocks",
/* 08-0d */ "Read (6)", unknown, "Write (6)", "Seek (6)", unknown, unknown,
/* 0e-12 */ unknown, "Read Reverse", "Write Filemarks", "Space", "Inquiry",  
/* 13-16 */ unknown, "Recover Buffered Data", "Mode Select", "Reserve",
/* 17-1b */ "Release", "Copy", "Erase", "Mode Sense", "Start/Stop Unit",
/* 1c-1d */ "Receive Diagnostic", "Send Diagnostic", 
/* 1e-1f */ "Prevent/Allow Medium Removal", unknown,
पूर्ण;


अटल स्थिर अक्षर *group_1_commands[] = अणु
/* 20-22 */  unknown, unknown, unknown,
/* 23-28 */ unknown, unknown, "Read Capacity", unknown, unknown, "Read (10)",
/* 29-2d */ unknown, "Write (10)", "Seek (10)", unknown, unknown,
/* 2e-31 */ "Write Verify","Verify", "Search High", "Search Equal",
/* 32-34 */ "Search Low", "Set Limits", "Prefetch or Read Position", 
/* 35-37 */ "Synchronize Cache","Lock/Unlock Cache", "Read Defect Data",
/* 38-3c */ "Medium Scan", "Compare","Copy Verify", "Write Buffer", "Read Buffer",
/* 3d-3f */ "Update Block", "Read Long",  "Write Long",
पूर्ण;


अटल स्थिर अक्षर *group_2_commands[] = अणु
/* 40-41 */ "Change Definition", "Write Same", 
/* 42-48 */ "Read Sub-Ch(cd)", "Read TOC", "Read Header(cd)", "Play Audio(cd)", unknown, "Play Audio MSF(cd)", "Play Audio Track/Index(cd)", 
/* 49-4f */ "Play Track Relative(10)(cd)", unknown, "Pause/Resume(cd)", "Log Select", "Log Sense", unknown, unknown,
/* 50-55 */ unknown, unknown, unknown, unknown, unknown, "Mode Select (10)",
/* 56-5b */ unknown, unknown, unknown, unknown, "Mode Sense (10)", unknown,
/* 5c-5f */ unknown, unknown, unknown,
पूर्ण;

#घोषणा group(opcode) (((opcode) >> 5) & 7)

#घोषणा RESERVED_GROUP  0
#घोषणा VENDOR_GROUP    1
#घोषणा NOTEXT_GROUP    2

अटल स्थिर अक्षर **commands[] = अणु
    group_0_commands, group_1_commands, group_2_commands, 
    (स्थिर अक्षर **) RESERVED_GROUP, (स्थिर अक्षर **) RESERVED_GROUP, 
    (स्थिर अक्षर **) NOTEXT_GROUP, (स्थिर अक्षर **) VENDOR_GROUP, 
    (स्थिर अक्षर **) VENDOR_GROUP
पूर्ण;

अटल स्थिर अक्षर reserved[] = "RESERVED";
अटल स्थिर अक्षर venकरोr[] = "VENDOR SPECIFIC";

अटल व्योम prपूर्णांक_opcodek(अचिन्हित अक्षर opcode)
अणु
	स्थिर अक्षर **table = commands[ group(opcode) ];

	चयन ((अचिन्हित दीर्घ) table) अणु
	हाल RESERVED_GROUP:
		prपूर्णांकk("%s[%02x] ", reserved, opcode); 
		अवरोध;
	हाल NOTEXT_GROUP:
		prपूर्णांकk("%s(notext)[%02x] ", unknown, opcode); 
		अवरोध;
	हाल VENDOR_GROUP:
		prपूर्णांकk("%s[%02x] ", venकरोr, opcode); 
		अवरोध;
	शेष:
		अगर (table[opcode & 0x1f] != unknown)
			prपूर्णांकk("%s[%02x] ", table[opcode & 0x1f], opcode);
		अन्यथा
			prपूर्णांकk("%s[%02x] ", unknown, opcode);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_commandk (अचिन्हित अक्षर *command)
अणु
	पूर्णांक i,s;
//	prपूर्णांकk(KERN_DEBUG);
	prपूर्णांक_opcodek(command[0]);
	/*prपूर्णांकk(KERN_DEBUG "%s ", __func__);*/
	अगर ((command[0] >> 5) == 6 ||
	    (command[0] >> 5) == 7 ) अणु
		s = 12; /* vender specअगरic */
	पूर्ण अन्यथा अणु
		s = COMMAND_SIZE(command[0]);
	पूर्ण

	क्रम ( i = 1; i < s; ++i) अणु
		prपूर्णांकk("%02x ", command[i]);
	पूर्ण

	चयन (s) अणु
	हाल 6:
		prपूर्णांकk("LBA=%d len=%d",
		       (((अचिन्हित पूर्णांक)command[1] & 0x0f) << 16) |
		       ( (अचिन्हित पूर्णांक)command[2]         <<  8) |
		       ( (अचिन्हित पूर्णांक)command[3]              ),
		       (अचिन्हित पूर्णांक)command[4]
			);
		अवरोध;
	हाल 10:
		prपूर्णांकk("LBA=%d len=%d",
		       ((अचिन्हित पूर्णांक)command[2] << 24) |
		       ((अचिन्हित पूर्णांक)command[3] << 16) |
		       ((अचिन्हित पूर्णांक)command[4] <<  8) |
		       ((अचिन्हित पूर्णांक)command[5]      ),
		       ((अचिन्हित पूर्णांक)command[7] <<  8) |
		       ((अचिन्हित पूर्णांक)command[8]      )
		       );
		अवरोध;
	हाल 12:
		prपूर्णांकk("LBA=%d len=%d",
		       ((अचिन्हित पूर्णांक)command[2] << 24) |
		       ((अचिन्हित पूर्णांक)command[3] << 16) |
		       ((अचिन्हित पूर्णांक)command[4] <<  8) |
		       ((अचिन्हित पूर्णांक)command[5]      ),
		       ((अचिन्हित पूर्णांक)command[6] << 24) |
		       ((अचिन्हित पूर्णांक)command[7] << 16) |
		       ((अचिन्हित पूर्णांक)command[8] <<  8) |
		       ((अचिन्हित पूर्णांक)command[9]      )
		       );
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण

अटल व्योम show_command(काष्ठा scsi_cmnd *SCpnt)
अणु
	prपूर्णांक_commandk(SCpnt->cmnd);
पूर्ण

अटल व्योम show_busphase(अचिन्हित अक्षर stat)
अणु
	चयन(stat) अणु
	हाल BUSPHASE_COMMAND:
		prपूर्णांकk( "BUSPHASE_COMMAND\n");
		अवरोध;
	हाल BUSPHASE_MESSAGE_IN:
		prपूर्णांकk( "BUSPHASE_MESSAGE_IN\n");
		अवरोध;
	हाल BUSPHASE_MESSAGE_OUT:
		prपूर्णांकk( "BUSPHASE_MESSAGE_OUT\n");
		अवरोध;
	हाल BUSPHASE_DATA_IN:
		prपूर्णांकk( "BUSPHASE_DATA_IN\n");
		अवरोध;
	हाल BUSPHASE_DATA_OUT:
		prपूर्णांकk( "BUSPHASE_DATA_OUT\n");
		अवरोध;
	हाल BUSPHASE_STATUS:
		prपूर्णांकk( "BUSPHASE_STATUS\n");
		अवरोध;
	हाल BUSPHASE_SELECT:
		prपूर्णांकk( "BUSPHASE_SELECT\n");
		अवरोध;
	शेष:
		prपूर्णांकk( "BUSPHASE_other: 0x%x\n", stat);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम show_स्वतःphase(अचिन्हित लघु i)
अणु
	prपूर्णांकk("auto: 0x%x,", i);

	अगर(i & COMMAND_PHASE) अणु
		prपूर्णांकk(" cmd");
	पूर्ण
	अगर(i & DATA_IN_PHASE) अणु
		prपूर्णांकk(" din");
	पूर्ण
	अगर(i & DATA_OUT_PHASE) अणु
		prपूर्णांकk(" dout");
	पूर्ण
	अगर(i & MSGOUT_PHASE) अणु
		prपूर्णांकk(" mout");
	पूर्ण
	अगर(i & STATUS_PHASE) अणु
		prपूर्णांकk(" stat");
	पूर्ण
	अगर(i & ILLEGAL_PHASE) अणु
		prपूर्णांकk(" ill");
	पूर्ण
	अगर(i & BUS_FREE_OCCUER) अणु
		prपूर्णांकk(" bfree-o");
	पूर्ण
	अगर(i & MSG_IN_OCCUER) अणु
		prपूर्णांकk(" min-o");
	पूर्ण
	अगर(i & MSG_OUT_OCCUER) अणु
		prपूर्णांकk(" mout-o");
	पूर्ण
	अगर(i & SELECTION_TIMEOUT) अणु
		prपूर्णांकk(" sel");
	पूर्ण
	अगर(i & MSGIN_00_VALID) अणु
		prपूर्णांकk(" m0");
	पूर्ण
	अगर(i & MSGIN_02_VALID) अणु
		prपूर्णांकk(" m2");
	पूर्ण
	अगर(i & MSGIN_03_VALID) अणु
		prपूर्णांकk(" m3");
	पूर्ण
	अगर(i & MSGIN_04_VALID) अणु
		prपूर्णांकk(" m4");
	पूर्ण
	अगर(i & AUTOSCSI_BUSY) अणु
		prपूर्णांकk(" busy");
	पूर्ण

	prपूर्णांकk("\n");
पूर्ण

अटल व्योम nsp32_prपूर्णांक_रेजिस्टर(पूर्णांक base)
अणु
	अगर (!(NSP32_DEBUG_MASK & NSP32_SPECIAL_PRINT_REGISTER))
		वापस;

	prपूर्णांकk("Phase=0x%x, ", nsp32_पढ़ो1(base, SCSI_BUS_MONITOR));
	prपूर्णांकk("OldPhase=0x%x, ", nsp32_index_पढ़ो1(base, OLD_SCSI_PHASE));
	prपूर्णांकk("syncreg=0x%x, ", nsp32_पढ़ो1(base, SYNC_REG));
	prपूर्णांकk("ackwidth=0x%x, ", nsp32_पढ़ो1(base, ACK_WIDTH));
	prपूर्णांकk("sgtpaddr=0x%lx, ", nsp32_पढ़ो4(base, SGT_ADR));
	prपूर्णांकk("scsioutlatch=0x%x, ", nsp32_पढ़ो1(base, SCSI_OUT_LATCH_TARGET_ID));
	prपूर्णांकk("msgout=0x%lx, ", nsp32_पढ़ो4(base, SCSI_MSG_OUT));
	prपूर्णांकk("miscrd=0x%x, ", nsp32_index_पढ़ो2(base, MISC_WR));
	prपूर्णांकk("seltimeout=0x%x, ", nsp32_पढ़ो2(base, SEL_TIME_OUT));
	prपूर्णांकk("sreqrate=0x%x, ", nsp32_पढ़ो1(base, SREQ_SMPL_RATE));
	prपूर्णांकk("transStatus=0x%x, ", nsp32_पढ़ो2(base, TRANSFER_STATUS));
	prपूर्णांकk("reselectid=0x%x, ", nsp32_पढ़ो2(base, COMMAND_CONTROL));
	prपूर्णांकk("arbit=0x%x, ", nsp32_पढ़ो1(base, ARBIT_STATUS));
	prपूर्णांकk("BmStart=0x%lx, ", nsp32_पढ़ो4(base, BM_START_ADR));
	prपूर्णांकk("BmCount=0x%lx, ", nsp32_पढ़ो4(base, BM_CNT));
	prपूर्णांकk("SackCnt=0x%lx, ", nsp32_पढ़ो4(base, SACK_CNT));
	prपूर्णांकk("SReqCnt=0x%lx, ", nsp32_पढ़ो4(base, SREQ_CNT));
	prपूर्णांकk("SavedSackCnt=0x%lx, ", nsp32_पढ़ो4(base, SAVED_SACK_CNT));
	prपूर्णांकk("ScsiBusControl=0x%x, ", nsp32_पढ़ो1(base, SCSI_BUS_CONTROL));
	prपूर्णांकk("FifoRestCnt=0x%x, ", nsp32_पढ़ो2(base, FIFO_REST_CNT));
	prपूर्णांकk("CdbIn=0x%x, ", nsp32_पढ़ो1(base, SCSI_CSB_IN));
	prपूर्णांकk("\n");

	अगर (0) अणु
		prपूर्णांकk("execph=0x%x, ", nsp32_पढ़ो2(base, SCSI_EXECUTE_PHASE));
		prपूर्णांकk("IrqStatus=0x%x, ", nsp32_पढ़ो2(base, IRQ_STATUS));
		prपूर्णांकk("\n");
	पूर्ण
पूर्ण

/* end */
