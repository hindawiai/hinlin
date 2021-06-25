<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SPI_CAVIUM_H
#घोषणा __SPI_CAVIUM_H

#समावेश <linux/clk.h>

#घोषणा OCTEON_SPI_MAX_BYTES 9
#घोषणा OCTEON_SPI_MAX_CLOCK_HZ 16000000

काष्ठा octeon_spi_regs अणु
	पूर्णांक config;
	पूर्णांक status;
	पूर्णांक tx;
	पूर्णांक data;
पूर्ण;

काष्ठा octeon_spi अणु
	व्योम __iomem *रेजिस्टर_base;
	u64 last_cfg;
	u64 cs_enax;
	पूर्णांक sys_freq;
	काष्ठा octeon_spi_regs regs;
	काष्ठा clk *clk;
पूर्ण;

#घोषणा OCTEON_SPI_CFG(x)	(x->regs.config)
#घोषणा OCTEON_SPI_STS(x)	(x->regs.status)
#घोषणा OCTEON_SPI_TX(x)	(x->regs.tx)
#घोषणा OCTEON_SPI_DAT0(x)	(x->regs.data)

पूर्णांक octeon_spi_transfer_one_message(काष्ठा spi_master *master,
				    काष्ठा spi_message *msg);

/* MPI रेजिस्टर descriptions */

#घोषणा CVMX_MPI_CFG (CVMX_ADD_IO_SEG(0x0001070000001000ull))
#घोषणा CVMX_MPI_DATX(offset) (CVMX_ADD_IO_SEG(0x0001070000001080ull) + ((offset) & 15) * 8)
#घोषणा CVMX_MPI_STS (CVMX_ADD_IO_SEG(0x0001070000001008ull))
#घोषणा CVMX_MPI_TX (CVMX_ADD_IO_SEG(0x0001070000001010ull))

जोड़ cvmx_mpi_cfg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mpi_cfg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t clkभाग:13;
		uपूर्णांक64_t csena3:1;
		uपूर्णांक64_t csena2:1;
		uपूर्णांक64_t csena1:1;
		uपूर्णांक64_t csena0:1;
		uपूर्णांक64_t cslate:1;
		uपूर्णांक64_t tritx:1;
		uपूर्णांक64_t idleclks:2;
		uपूर्णांक64_t cshi:1;
		uपूर्णांक64_t csena:1;
		uपूर्णांक64_t पूर्णांक_ena:1;
		uपूर्णांक64_t lsbfirst:1;
		uपूर्णांक64_t wireor:1;
		uपूर्णांक64_t clk_cont:1;
		uपूर्णांक64_t idlelo:1;
		uपूर्णांक64_t enable:1;
#अन्यथा
		uपूर्णांक64_t enable:1;
		uपूर्णांक64_t idlelo:1;
		uपूर्णांक64_t clk_cont:1;
		uपूर्णांक64_t wireor:1;
		uपूर्णांक64_t lsbfirst:1;
		uपूर्णांक64_t पूर्णांक_ena:1;
		uपूर्णांक64_t csena:1;
		uपूर्णांक64_t cshi:1;
		uपूर्णांक64_t idleclks:2;
		uपूर्णांक64_t tritx:1;
		uपूर्णांक64_t cslate:1;
		uपूर्णांक64_t csena0:1;
		uपूर्णांक64_t csena1:1;
		uपूर्णांक64_t csena2:1;
		uपूर्णांक64_t csena3:1;
		uपूर्णांक64_t clkभाग:13;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mpi_cfg_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t clkभाग:13;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t cslate:1;
		uपूर्णांक64_t tritx:1;
		uपूर्णांक64_t idleclks:2;
		uपूर्णांक64_t cshi:1;
		uपूर्णांक64_t csena:1;
		uपूर्णांक64_t पूर्णांक_ena:1;
		uपूर्णांक64_t lsbfirst:1;
		uपूर्णांक64_t wireor:1;
		uपूर्णांक64_t clk_cont:1;
		uपूर्णांक64_t idlelo:1;
		uपूर्णांक64_t enable:1;
#अन्यथा
		uपूर्णांक64_t enable:1;
		uपूर्णांक64_t idlelo:1;
		uपूर्णांक64_t clk_cont:1;
		uपूर्णांक64_t wireor:1;
		uपूर्णांक64_t lsbfirst:1;
		uपूर्णांक64_t पूर्णांक_ena:1;
		uपूर्णांक64_t csena:1;
		uपूर्णांक64_t cshi:1;
		uपूर्णांक64_t idleclks:2;
		uपूर्णांक64_t tritx:1;
		uपूर्णांक64_t cslate:1;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t clkभाग:13;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_mpi_cfg_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t clkभाग:13;
		uपूर्णांक64_t reserved_11_15:5;
		uपूर्णांक64_t tritx:1;
		uपूर्णांक64_t idleclks:2;
		uपूर्णांक64_t cshi:1;
		uपूर्णांक64_t csena:1;
		uपूर्णांक64_t पूर्णांक_ena:1;
		uपूर्णांक64_t lsbfirst:1;
		uपूर्णांक64_t wireor:1;
		uपूर्णांक64_t clk_cont:1;
		uपूर्णांक64_t idlelo:1;
		uपूर्णांक64_t enable:1;
#अन्यथा
		uपूर्णांक64_t enable:1;
		uपूर्णांक64_t idlelo:1;
		uपूर्णांक64_t clk_cont:1;
		uपूर्णांक64_t wireor:1;
		uपूर्णांक64_t lsbfirst:1;
		uपूर्णांक64_t पूर्णांक_ena:1;
		uपूर्णांक64_t csena:1;
		uपूर्णांक64_t cshi:1;
		uपूर्णांक64_t idleclks:2;
		uपूर्णांक64_t tritx:1;
		uपूर्णांक64_t reserved_11_15:5;
		uपूर्णांक64_t clkभाग:13;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn31xx;
	काष्ठा cvmx_mpi_cfg_cn30xx cn50xx;
	काष्ठा cvmx_mpi_cfg_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t clkभाग:13;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t csena1:1;
		uपूर्णांक64_t csena0:1;
		uपूर्णांक64_t cslate:1;
		uपूर्णांक64_t tritx:1;
		uपूर्णांक64_t idleclks:2;
		uपूर्णांक64_t cshi:1;
		uपूर्णांक64_t reserved_6_6:1;
		uपूर्णांक64_t पूर्णांक_ena:1;
		uपूर्णांक64_t lsbfirst:1;
		uपूर्णांक64_t wireor:1;
		uपूर्णांक64_t clk_cont:1;
		uपूर्णांक64_t idlelo:1;
		uपूर्णांक64_t enable:1;
#अन्यथा
		uपूर्णांक64_t enable:1;
		uपूर्णांक64_t idlelo:1;
		uपूर्णांक64_t clk_cont:1;
		uपूर्णांक64_t wireor:1;
		uपूर्णांक64_t lsbfirst:1;
		uपूर्णांक64_t पूर्णांक_ena:1;
		uपूर्णांक64_t reserved_6_6:1;
		uपूर्णांक64_t cshi:1;
		uपूर्णांक64_t idleclks:2;
		uपूर्णांक64_t tritx:1;
		uपूर्णांक64_t cslate:1;
		uपूर्णांक64_t csena0:1;
		uपूर्णांक64_t csena1:1;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t clkभाग:13;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_mpi_cfg_cn66xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t clkभाग:13;
		uपूर्णांक64_t csena3:1;
		uपूर्णांक64_t csena2:1;
		uपूर्णांक64_t reserved_12_13:2;
		uपूर्णांक64_t cslate:1;
		uपूर्णांक64_t tritx:1;
		uपूर्णांक64_t idleclks:2;
		uपूर्णांक64_t cshi:1;
		uपूर्णांक64_t reserved_6_6:1;
		uपूर्णांक64_t पूर्णांक_ena:1;
		uपूर्णांक64_t lsbfirst:1;
		uपूर्णांक64_t wireor:1;
		uपूर्णांक64_t clk_cont:1;
		uपूर्णांक64_t idlelo:1;
		uपूर्णांक64_t enable:1;
#अन्यथा
		uपूर्णांक64_t enable:1;
		uपूर्णांक64_t idlelo:1;
		uपूर्णांक64_t clk_cont:1;
		uपूर्णांक64_t wireor:1;
		uपूर्णांक64_t lsbfirst:1;
		uपूर्णांक64_t पूर्णांक_ena:1;
		uपूर्णांक64_t reserved_6_6:1;
		uपूर्णांक64_t cshi:1;
		uपूर्णांक64_t idleclks:2;
		uपूर्णांक64_t tritx:1;
		uपूर्णांक64_t cslate:1;
		uपूर्णांक64_t reserved_12_13:2;
		uपूर्णांक64_t csena2:1;
		uपूर्णांक64_t csena3:1;
		uपूर्णांक64_t clkभाग:13;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn66xx;
	काष्ठा cvmx_mpi_cfg_cn61xx cnf71xx;
पूर्ण;

जोड़ cvmx_mpi_datx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mpi_datx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t data:8;
#अन्यथा
		uपूर्णांक64_t data:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mpi_datx_s cn30xx;
	काष्ठा cvmx_mpi_datx_s cn31xx;
	काष्ठा cvmx_mpi_datx_s cn50xx;
	काष्ठा cvmx_mpi_datx_s cn61xx;
	काष्ठा cvmx_mpi_datx_s cn66xx;
	काष्ठा cvmx_mpi_datx_s cnf71xx;
पूर्ण;

जोड़ cvmx_mpi_sts अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mpi_sts_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t rxnum:5;
		uपूर्णांक64_t reserved_1_7:7;
		uपूर्णांक64_t busy:1;
#अन्यथा
		uपूर्णांक64_t busy:1;
		uपूर्णांक64_t reserved_1_7:7;
		uपूर्णांक64_t rxnum:5;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mpi_sts_s cn30xx;
	काष्ठा cvmx_mpi_sts_s cn31xx;
	काष्ठा cvmx_mpi_sts_s cn50xx;
	काष्ठा cvmx_mpi_sts_s cn61xx;
	काष्ठा cvmx_mpi_sts_s cn66xx;
	काष्ठा cvmx_mpi_sts_s cnf71xx;
पूर्ण;

जोड़ cvmx_mpi_tx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mpi_tx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_22_63:42;
		uपूर्णांक64_t csid:2;
		uपूर्णांक64_t reserved_17_19:3;
		uपूर्णांक64_t leavecs:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t txnum:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t totnum:5;
#अन्यथा
		uपूर्णांक64_t totnum:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t txnum:5;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t leavecs:1;
		uपूर्णांक64_t reserved_17_19:3;
		uपूर्णांक64_t csid:2;
		uपूर्णांक64_t reserved_22_63:42;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mpi_tx_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_17_63:47;
		uपूर्णांक64_t leavecs:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t txnum:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t totnum:5;
#अन्यथा
		uपूर्णांक64_t totnum:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t txnum:5;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t leavecs:1;
		uपूर्णांक64_t reserved_17_63:47;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_mpi_tx_cn30xx cn31xx;
	काष्ठा cvmx_mpi_tx_cn30xx cn50xx;
	काष्ठा cvmx_mpi_tx_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_21_63:43;
		uपूर्णांक64_t csid:1;
		uपूर्णांक64_t reserved_17_19:3;
		uपूर्णांक64_t leavecs:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t txnum:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t totnum:5;
#अन्यथा
		uपूर्णांक64_t totnum:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t txnum:5;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t leavecs:1;
		uपूर्णांक64_t reserved_17_19:3;
		uपूर्णांक64_t csid:1;
		uपूर्णांक64_t reserved_21_63:43;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_mpi_tx_s cn66xx;
	काष्ठा cvmx_mpi_tx_cn61xx cnf71xx;
पूर्ण;

#पूर्ण_अगर /* __SPI_CAVIUM_H */
