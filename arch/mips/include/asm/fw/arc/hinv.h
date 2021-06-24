<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ARCS hardware/memory inventory/configuration and प्रणाली ID definitions.
 */
#अगर_अघोषित _ASM_ARC_HINV_H
#घोषणा _ASM_ARC_HINV_H

#समावेश <यंत्र/sgidefs.h>
#समावेश <यंत्र/fw/arc/types.h>

/* configuration query defines */
प्रकार क्रमागत configclass अणु
	SystemClass,
	ProcessorClass,
	CacheClass,
#अगर_अघोषित _NT_PROM
	MemoryClass,
	AdapterClass,
	ControllerClass,
	PeripheralClass
#अन्यथा	/* _NT_PROM */
	AdapterClass,
	ControllerClass,
	PeripheralClass,
	MemoryClass
#पूर्ण_अगर	/* _NT_PROM */
पूर्ण CONFIGCLASS;

प्रकार क्रमागत configtype अणु
	ARC,
	CPU,
	FPU,
	PrimaryICache,
	PrimaryDCache,
	SecondaryICache,
	SecondaryDCache,
	SecondaryCache,
#अगर_अघोषित _NT_PROM
	Memory,
#पूर्ण_अगर
	EISAAdapter,
	TCAdapter,
	SCSIAdapter,
	DTIAdapter,
	MultiFunctionAdapter,
	DiskController,
	TapeController,
	CDROMController,
	WORMController,
	SerialController,
	NetworkController,
	DisplayController,
	ParallelController,
	Poपूर्णांकerController,
	KeyboardController,
	AudioController,
	OtherController,
	DiskPeripheral,
	FloppyDiskPeripheral,
	TapePeripheral,
	ModemPeripheral,
	MonitorPeripheral,
	Prपूर्णांकerPeripheral,
	Poपूर्णांकerPeripheral,
	KeyboardPeripheral,
	TerminalPeripheral,
	LinePeripheral,
	NetworkPeripheral,
#अगर_घोषित	_NT_PROM
	Memory,
#पूर्ण_अगर
	OtherPeripheral,

	/* new stuff क्रम IP30 */
	/* added without moving anything */
	/* except ANONYMOUS. */

	XTalkAdapter,
	PCIAdapter,
	GIOAdapter,
	TPUAdapter,

	Anonymous
पूर्ण CONFIGTYPE;

प्रकार क्रमागत अणु
	Failed = 1,
	ReadOnly = 2,
	Removable = 4,
	ConsoleIn = 8,
	ConsoleOut = 16,
	Input = 32,
	Output = 64
पूर्ण IDENTIFIERFLAG;

#अगर_अघोषित शून्य			/* क्रम GetChild(शून्य); */
#घोषणा शून्य	0
#पूर्ण_अगर

जोड़ key_u अणु
	काष्ठा अणु
#अगर_घोषित	_MIPSEB
		अचिन्हित अक्षर  c_bsize;		/* block size in lines */
		अचिन्हित अक्षर  c_lsize;		/* line size in bytes/tag */
		अचिन्हित लघु c_size;		/* cache size in 4K pages */
#अन्यथा	/* _MIPSEL */
		अचिन्हित लघु c_size;		/* cache size in 4K pages */
		अचिन्हित अक्षर  c_lsize;		/* line size in bytes/tag */
		अचिन्हित अक्षर  c_bsize;		/* block size in lines */
#पूर्ण_अगर	/* _MIPSEL */
	पूर्ण cache;
	ULONG FullKey;
पूर्ण;

#अगर _MIPS_SIM == _MIPS_SIM_ABI64
#घोषणा SGI_ARCS_VERS	64			/* sgi 64-bit version */
#घोषणा SGI_ARCS_REV	0			/* rev .00 */
#अन्यथा
#घोषणा SGI_ARCS_VERS	1			/* first version */
#घोषणा SGI_ARCS_REV	10			/* rev .10, 3/04/92 */
#पूर्ण_अगर

प्रकार काष्ठा अणु
	CONFIGCLASS	Class;
	CONFIGTYPE	Type;
	IDENTIFIERFLAG	Flags;
	USHORT		Version;
	USHORT		Revision;
	ULONG		Key;
	ULONG		AffinityMask;
	ULONG		ConfigurationDataSize;
	ULONG		IdentअगरierLength;
	अक्षर		*Identअगरier;
पूर्ण COMPONENT;

/* पूर्णांकernal काष्ठाure that holds pathname parsing data */
काष्ठा cfgdata अणु
	अक्षर *name;			/* full name */
	पूर्णांक minlen;			/* minimum length to match */
	CONFIGTYPE type;		/* type of token */
पूर्ण;

/* System ID */
प्रकार काष्ठा अणु
	CHAR VenकरोrId[8];
	CHAR ProductId[8];
पूर्ण SYSTEMID;

/* memory query functions */
प्रकार क्रमागत memorytype अणु
	ExceptionBlock,
	SPBPage,			/* ARCS == SystemParameterBlock */
#अगर_अघोषित _NT_PROM
	FreeContiguous,
	FreeMemory,
	BadMemory,
	LoadedProgram,
	FirmwareTemporary,
	FirmwarePermanent
#अन्यथा	/* _NT_PROM */
	FreeMemory,
	BadMemory,
	LoadedProgram,
	FirmwareTemporary,
	FirmwarePermanent,
	FreeContiguous
#पूर्ण_अगर	/* _NT_PROM */
पूर्ण MEMORYTYPE;

प्रकार काष्ठा अणु
	MEMORYTYPE	Type;
	LONG		BasePage;
	LONG		PageCount;
पूर्ण MEMORYDESCRIPTOR;

#पूर्ण_अगर /* _ASM_ARC_HINV_H */
