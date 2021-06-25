<शैली गुरु>
/*
 * Copyright 2015 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#समावेश <core/pci.h>
#समावेश "priv.h"

काष्ठा nvkm_device_pci_device अणु
	u16 device;
	स्थिर अक्षर *name;
	स्थिर काष्ठा nvkm_device_pci_venकरोr *venकरोr;
पूर्ण;

काष्ठा nvkm_device_pci_venकरोr अणु
	u16 venकरोr;
	u16 device;
	स्थिर अक्षर *name;
	स्थिर काष्ठा nvkm_device_quirk quirk;
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0189[] = अणु
	/* Apple iMac G4 NV18 */
	अणु 0x10de, 0x0010, शून्य, अणु .tv_gpio = 4 पूर्ण पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_01f0[] = अणु
	/* MSI nForce2 IGP */
	अणु 0x1462, 0x5710, शून्य, अणु .tv_pin_mask = 0xc पूर्ण पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0322[] = अणु
	/* Zotac FX5200 */
	अणु 0x19da, 0x1035, शून्य, अणु .tv_pin_mask = 0xc पूर्ण पूर्ण,
	अणु 0x19da, 0x2035, शून्य, अणु .tv_pin_mask = 0xc पूर्ण पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_05e7[] = अणु
	अणु 0x10de, 0x0595, "Tesla T10 Processor" पूर्ण,
	अणु 0x10de, 0x068f, "Tesla T10 Processor" पूर्ण,
	अणु 0x10de, 0x0697, "Tesla M1060" पूर्ण,
	अणु 0x10de, 0x0714, "Tesla M1060" पूर्ण,
	अणु 0x10de, 0x0743, "Tesla M1060" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0609[] = अणु
	अणु 0x106b, 0x00a7, "GeForce 8800 GS" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_062e[] = अणु
	अणु 0x106b, 0x0605, "GeForce GT 130" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0649[] = अणु
	अणु 0x1043, 0x202d, "GeForce GT 220M" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0652[] = अणु
	अणु 0x152d, 0x0850, "GeForce GT 240M LE" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0654[] = अणु
	अणु 0x1043, 0x14a2, "GeForce GT 320M" पूर्ण,
	अणु 0x1043, 0x14d2, "GeForce GT 320M" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0655[] = अणु
	अणु 0x106b, 0x0633, "GeForce GT 120" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0656[] = अणु
	अणु 0x106b, 0x0693, "GeForce GT 120" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_06d1[] = अणु
	अणु 0x10de, 0x0771, "Tesla C2050" पूर्ण,
	अणु 0x10de, 0x0772, "Tesla C2070" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_06d2[] = अणु
	अणु 0x10de, 0x088f, "Tesla X2070" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_06de[] = अणु
	अणु 0x10de, 0x0773, "Tesla S2050" पूर्ण,
	अणु 0x10de, 0x082f, "Tesla M2050" पूर्ण,
	अणु 0x10de, 0x0840, "Tesla X2070" पूर्ण,
	अणु 0x10de, 0x0842, "Tesla M2050" पूर्ण,
	अणु 0x10de, 0x0846, "Tesla M2050" पूर्ण,
	अणु 0x10de, 0x0866, "Tesla M2050" पूर्ण,
	अणु 0x10de, 0x0907, "Tesla M2050" पूर्ण,
	अणु 0x10de, 0x091e, "Tesla M2050" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_06e8[] = अणु
	अणु 0x103c, 0x360b, "GeForce 9200M GE" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_06f9[] = अणु
	अणु 0x10de, 0x060d, "Quadro FX 370 Low Profile" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_06ff[] = अणु
	अणु 0x10de, 0x0711, "HICx8 + Graphics" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0866[] = अणु
	अणु 0x106b, 0x00b1, "GeForce 9400M" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0872[] = अणु
	अणु 0x1043, 0x1c42, "GeForce G205M" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0873[] = अणु
	अणु 0x1043, 0x1c52, "GeForce G205M" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0a6e[] = अणु
	अणु 0x17aa, 0x3607, "Second Generation ION" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0a70[] = अणु
	अणु 0x17aa, 0x3605, "Second Generation ION" पूर्ण,
	अणु 0x17aa, 0x3617, "Second Generation ION" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0a73[] = अणु
	अणु 0x17aa, 0x3607, "Second Generation ION" पूर्ण,
	अणु 0x17aa, 0x3610, "Second Generation ION" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0a74[] = अणु
	अणु 0x17aa, 0x903a, "GeForce G210" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0a75[] = अणु
	अणु 0x17aa, 0x3605, "Second Generation ION" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0a7a[] = अणु
	अणु 0x1462, 0xaa51, "GeForce 405" पूर्ण,
	अणु 0x1462, 0xaa58, "GeForce 405" पूर्ण,
	अणु 0x1462, 0xac71, "GeForce 405" पूर्ण,
	अणु 0x1462, 0xac82, "GeForce 405" पूर्ण,
	अणु 0x1642, 0x3980, "GeForce 405" पूर्ण,
	अणु 0x17aa, 0x3950, "GeForce 405M" पूर्ण,
	अणु 0x17aa, 0x397d, "GeForce 405M" पूर्ण,
	अणु 0x1b0a, 0x90b4, "GeForce 405" पूर्ण,
	अणु 0x1bfd, 0x0003, "GeForce 405" पूर्ण,
	अणु 0x1bfd, 0x8006, "GeForce 405" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0dd8[] = अणु
	अणु 0x10de, 0x0914, "Quadro 2000D" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0de9[] = अणु
	अणु 0x1025, 0x0692, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x0725, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x0728, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x072b, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x072e, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x0753, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x0754, "GeForce GT 620M" पूर्ण,
	अणु 0x17aa, 0x3977, "GeForce GT 640M LE" पूर्ण,
	अणु 0x1b0a, 0x2210, "GeForce GT 635M" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0dea[] = अणु
	अणु 0x17aa, 0x365a, "GeForce 615" पूर्ण,
	अणु 0x17aa, 0x365b, "GeForce 615" पूर्ण,
	अणु 0x17aa, 0x365e, "GeForce 615" पूर्ण,
	अणु 0x17aa, 0x3660, "GeForce 615" पूर्ण,
	अणु 0x17aa, 0x366c, "GeForce 615" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0df4[] = अणु
	अणु 0x152d, 0x0952, "GeForce GT 630M" पूर्ण,
	अणु 0x152d, 0x0953, "GeForce GT 630M" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0fd2[] = अणु
	अणु 0x1028, 0x0595, "GeForce GT 640M LE" पूर्ण,
	अणु 0x1028, 0x05b2, "GeForce GT 640M LE" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_0fe3[] = अणु
	अणु 0x103c, 0x2b16, "GeForce GT 745A" पूर्ण,
	अणु 0x17aa, 0x3675, "GeForce GT 745A" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_104b[] = अणु
	अणु 0x1043, 0x844c, "GeForce GT 625" पूर्ण,
	अणु 0x1043, 0x846b, "GeForce GT 625" पूर्ण,
	अणु 0x1462, 0xb590, "GeForce GT 625" पूर्ण,
	अणु 0x174b, 0x0625, "GeForce GT 625" पूर्ण,
	अणु 0x174b, 0xa625, "GeForce GT 625" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_1058[] = अणु
	अणु 0x103c, 0x2af1, "GeForce 610" पूर्ण,
	अणु 0x17aa, 0x3682, "GeForce 800A" पूर्ण,
	अणु 0x17aa, 0x3692, "GeForce 705A" पूर्ण,
	अणु 0x17aa, 0x3695, "GeForce 800A" पूर्ण,
	अणु 0x17aa, 0x36a8, "GeForce 800A" पूर्ण,
	अणु 0x17aa, 0x36ac, "GeForce 800A" पूर्ण,
	अणु 0x17aa, 0x36ad, "GeForce 800A" पूर्ण,
	अणु 0x705a, 0x3682, "GeForce 800A" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_105b[] = अणु
	अणु 0x103c, 0x2afb, "GeForce 705A" पूर्ण,
	अणु 0x17aa, 0x36a1, "GeForce 800A" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_1091[] = अणु
	अणु 0x10de, 0x088e, "Tesla X2090" पूर्ण,
	अणु 0x10de, 0x0891, "Tesla X2090" पूर्ण,
	अणु 0x10de, 0x0974, "Tesla X2090" पूर्ण,
	अणु 0x10de, 0x098d, "Tesla X2090" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_1096[] = अणु
	अणु 0x10de, 0x0911, "Tesla C2050" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_1140[] = अणु
	अणु 0x1019, 0x999f, "GeForce GT 720M" पूर्ण,
	अणु 0x1025, 0x0600, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x0606, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x064a, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x064c, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x067a, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x0680, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x0686, "GeForce 710M" पूर्ण,
	अणु 0x1025, 0x0689, "GeForce 710M" पूर्ण,
	अणु 0x1025, 0x068b, "GeForce 710M" पूर्ण,
	अणु 0x1025, 0x068d, "GeForce 710M" पूर्ण,
	अणु 0x1025, 0x068e, "GeForce 710M" पूर्ण,
	अणु 0x1025, 0x0691, "GeForce 710M" पूर्ण,
	अणु 0x1025, 0x0692, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x0694, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x0702, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x0719, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x0725, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x0728, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x072b, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x072e, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x0732, "GeForce GT 620M" पूर्ण,
	अणु 0x1025, 0x0763, "GeForce GT 720M" पूर्ण,
	अणु 0x1025, 0x0773, "GeForce 710M" पूर्ण,
	अणु 0x1025, 0x0774, "GeForce 710M" पूर्ण,
	अणु 0x1025, 0x0776, "GeForce GT 720M" पूर्ण,
	अणु 0x1025, 0x077a, "GeForce 710M" पूर्ण,
	अणु 0x1025, 0x077b, "GeForce 710M" पूर्ण,
	अणु 0x1025, 0x077c, "GeForce 710M" पूर्ण,
	अणु 0x1025, 0x077d, "GeForce 710M" पूर्ण,
	अणु 0x1025, 0x077e, "GeForce 710M" पूर्ण,
	अणु 0x1025, 0x077f, "GeForce 710M" पूर्ण,
	अणु 0x1025, 0x0781, "GeForce GT 720M" पूर्ण,
	अणु 0x1025, 0x0798, "GeForce GT 720M" पूर्ण,
	अणु 0x1025, 0x0799, "GeForce GT 720M" पूर्ण,
	अणु 0x1025, 0x079b, "GeForce GT 720M" पूर्ण,
	अणु 0x1025, 0x079c, "GeForce GT 720M" पूर्ण,
	अणु 0x1025, 0x0807, "GeForce GT 720M" पूर्ण,
	अणु 0x1025, 0x0821, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x0823, "GeForce GT 720M" पूर्ण,
	अणु 0x1025, 0x0830, "GeForce GT 720M" पूर्ण,
	अणु 0x1025, 0x0833, "GeForce GT 720M" पूर्ण,
	अणु 0x1025, 0x0837, "GeForce GT 720M" पूर्ण,
	अणु 0x1025, 0x083e, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x0841, "GeForce 710M" पूर्ण,
	अणु 0x1025, 0x0853, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x0854, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x0855, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x0856, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x0857, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x0858, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x0863, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x0868, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x0869, "GeForce 810M" पूर्ण,
	अणु 0x1025, 0x0873, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x0878, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x087b, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x087f, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x0881, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x0885, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x088a, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x089b, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x0921, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x092e, "GeForce 810M" पूर्ण,
	अणु 0x1025, 0x092f, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x0932, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x093a, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x093c, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x093f, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x0941, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x0945, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x0954, "GeForce 820M" पूर्ण,
	अणु 0x1025, 0x0965, "GeForce 820M" पूर्ण,
	अणु 0x1028, 0x054d, "GeForce GT 630M" पूर्ण,
	अणु 0x1028, 0x054e, "GeForce GT 630M" पूर्ण,
	अणु 0x1028, 0x0554, "GeForce GT 620M" पूर्ण,
	अणु 0x1028, 0x0557, "GeForce GT 620M" पूर्ण,
	अणु 0x1028, 0x0562, "GeForce GT625M" पूर्ण,
	अणु 0x1028, 0x0565, "GeForce GT 630M" पूर्ण,
	अणु 0x1028, 0x0568, "GeForce GT 630M" पूर्ण,
	अणु 0x1028, 0x0590, "GeForce GT 630M" पूर्ण,
	अणु 0x1028, 0x0592, "GeForce GT625M" पूर्ण,
	अणु 0x1028, 0x0594, "GeForce GT625M" पूर्ण,
	अणु 0x1028, 0x0595, "GeForce GT625M" पूर्ण,
	अणु 0x1028, 0x05a2, "GeForce GT625M" पूर्ण,
	अणु 0x1028, 0x05b1, "GeForce GT625M" पूर्ण,
	अणु 0x1028, 0x05b3, "GeForce GT625M" पूर्ण,
	अणु 0x1028, 0x05da, "GeForce GT 630M" पूर्ण,
	अणु 0x1028, 0x05de, "GeForce GT 720M" पूर्ण,
	अणु 0x1028, 0x05e0, "GeForce GT 720M" पूर्ण,
	अणु 0x1028, 0x05e8, "GeForce GT 630M" पूर्ण,
	अणु 0x1028, 0x05f4, "GeForce GT 720M" पूर्ण,
	अणु 0x1028, 0x060f, "GeForce GT 720M" पूर्ण,
	अणु 0x1028, 0x062f, "GeForce GT 720M" पूर्ण,
	अणु 0x1028, 0x064e, "GeForce 820M" पूर्ण,
	अणु 0x1028, 0x0652, "GeForce 820M" पूर्ण,
	अणु 0x1028, 0x0653, "GeForce 820M" पूर्ण,
	अणु 0x1028, 0x0655, "GeForce 820M" पूर्ण,
	अणु 0x1028, 0x065e, "GeForce 820M" पूर्ण,
	अणु 0x1028, 0x0662, "GeForce 820M" पूर्ण,
	अणु 0x1028, 0x068d, "GeForce 820M" पूर्ण,
	अणु 0x1028, 0x06ad, "GeForce 820M" पूर्ण,
	अणु 0x1028, 0x06ae, "GeForce 820M" पूर्ण,
	अणु 0x1028, 0x06af, "GeForce 820M" पूर्ण,
	अणु 0x1028, 0x06b0, "GeForce 820M" पूर्ण,
	अणु 0x1028, 0x06c0, "GeForce 820M" पूर्ण,
	अणु 0x1028, 0x06c1, "GeForce 820M" पूर्ण,
	अणु 0x103c, 0x18ef, "GeForce GT 630M" पूर्ण,
	अणु 0x103c, 0x18f9, "GeForce GT 630M" पूर्ण,
	अणु 0x103c, 0x18fb, "GeForce GT 630M" पूर्ण,
	अणु 0x103c, 0x18fd, "GeForce GT 630M" पूर्ण,
	अणु 0x103c, 0x18ff, "GeForce GT 630M" पूर्ण,
	अणु 0x103c, 0x218a, "GeForce 820M" पूर्ण,
	अणु 0x103c, 0x21bb, "GeForce 820M" पूर्ण,
	अणु 0x103c, 0x21bc, "GeForce 820M" पूर्ण,
	अणु 0x103c, 0x220e, "GeForce 820M" पूर्ण,
	अणु 0x103c, 0x2210, "GeForce 820M" पूर्ण,
	अणु 0x103c, 0x2212, "GeForce 820M" पूर्ण,
	अणु 0x103c, 0x2214, "GeForce 820M" पूर्ण,
	अणु 0x103c, 0x2218, "GeForce 820M" पूर्ण,
	अणु 0x103c, 0x225b, "GeForce 820M" पूर्ण,
	अणु 0x103c, 0x225d, "GeForce 820M" पूर्ण,
	अणु 0x103c, 0x226d, "GeForce 820M" पूर्ण,
	अणु 0x103c, 0x226f, "GeForce 820M" पूर्ण,
	अणु 0x103c, 0x22d2, "GeForce 820M" पूर्ण,
	अणु 0x103c, 0x22d9, "GeForce 820M" पूर्ण,
	अणु 0x103c, 0x2335, "GeForce 820M" पूर्ण,
	अणु 0x103c, 0x2337, "GeForce 820M" पूर्ण,
	अणु 0x103c, 0x2aef, "GeForce GT 720A" पूर्ण,
	अणु 0x103c, 0x2af9, "GeForce 710A" पूर्ण,
	अणु 0x1043, 0x10dd, "NVS 5200M" पूर्ण,
	अणु 0x1043, 0x10ed, "NVS 5200M" पूर्ण,
	अणु 0x1043, 0x11fd, "GeForce GT 720M" पूर्ण,
	अणु 0x1043, 0x124d, "GeForce GT 720M" पूर्ण,
	अणु 0x1043, 0x126d, "GeForce GT 720M" पूर्ण,
	अणु 0x1043, 0x131d, "GeForce GT 720M" पूर्ण,
	अणु 0x1043, 0x13fd, "GeForce GT 720M" पूर्ण,
	अणु 0x1043, 0x14c7, "GeForce GT 720M" पूर्ण,
	अणु 0x1043, 0x1507, "GeForce GT 620M" पूर्ण,
	अणु 0x1043, 0x15ad, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x15ed, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x160d, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x163d, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x165d, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x166d, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x16cd, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x16dd, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x170d, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x176d, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x178d, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x179d, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x2132, "GeForce GT 620M" पूर्ण,
	अणु 0x1043, 0x2136, "NVS 5200M" पूर्ण,
	अणु 0x1043, 0x21ba, "GeForce GT 720M" पूर्ण,
	अणु 0x1043, 0x21fa, "GeForce GT 720M" पूर्ण,
	अणु 0x1043, 0x220a, "GeForce GT 720M" पूर्ण,
	अणु 0x1043, 0x221a, "GeForce GT 720M" पूर्ण,
	अणु 0x1043, 0x223a, "GeForce GT 710M" पूर्ण,
	अणु 0x1043, 0x224a, "GeForce GT 710M" पूर्ण,
	अणु 0x1043, 0x227a, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x228a, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x22fa, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x232a, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x233a, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x235a, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x236a, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x238a, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x8595, "GeForce GT 720M" पूर्ण,
	अणु 0x1043, 0x85ea, "GeForce GT 720M" पूर्ण,
	अणु 0x1043, 0x85eb, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x85ec, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x85ee, "GeForce GT 720M" पूर्ण,
	अणु 0x1043, 0x85f3, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x860e, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x861a, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x861b, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x8628, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x8643, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x864c, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x8652, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x8660, "GeForce 820M" पूर्ण,
	अणु 0x1043, 0x8661, "GeForce 820M" पूर्ण,
	अणु 0x105b, 0x0dac, "GeForce GT 720M" पूर्ण,
	अणु 0x105b, 0x0dad, "GeForce GT 720M" पूर्ण,
	अणु 0x105b, 0x0ef3, "GeForce GT 720M" पूर्ण,
	अणु 0x10cf, 0x17f5, "GeForce GT 720M" पूर्ण,
	अणु 0x1179, 0xfa01, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa02, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa03, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa05, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa11, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa13, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa18, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa19, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa21, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa23, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa2a, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa32, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa33, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa36, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa38, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa42, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa43, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa45, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa47, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa49, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa58, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa59, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa88, "GeForce 710M" पूर्ण,
	अणु 0x1179, 0xfa89, "GeForce 710M" पूर्ण,
	अणु 0x144d, 0xb092, "GeForce GT 620M" पूर्ण,
	अणु 0x144d, 0xc0d5, "GeForce GT 630M" पूर्ण,
	अणु 0x144d, 0xc0d7, "GeForce GT 620M" पूर्ण,
	अणु 0x144d, 0xc0e2, "NVS 5200M" पूर्ण,
	अणु 0x144d, 0xc0e3, "NVS 5200M" पूर्ण,
	अणु 0x144d, 0xc0e4, "NVS 5200M" पूर्ण,
	अणु 0x144d, 0xc10d, "GeForce 820M" पूर्ण,
	अणु 0x144d, 0xc652, "GeForce GT 620M" पूर्ण,
	अणु 0x144d, 0xc709, "GeForce 710M" पूर्ण,
	अणु 0x144d, 0xc711, "GeForce 710M" पूर्ण,
	अणु 0x144d, 0xc736, "GeForce 710M" पूर्ण,
	अणु 0x144d, 0xc737, "GeForce 710M" पूर्ण,
	अणु 0x144d, 0xc745, "GeForce 820M" पूर्ण,
	अणु 0x144d, 0xc750, "GeForce 820M" पूर्ण,
	अणु 0x1462, 0x10b8, "GeForce GT 710M" पूर्ण,
	अणु 0x1462, 0x10e9, "GeForce GT 720M" पूर्ण,
	अणु 0x1462, 0x1116, "GeForce 820M" पूर्ण,
	अणु 0x1462, 0xaa33, "GeForce 720M" पूर्ण,
	अणु 0x1462, 0xaaa2, "GeForce GT 720M" पूर्ण,
	अणु 0x1462, 0xaaa3, "GeForce 820M" पूर्ण,
	अणु 0x1462, 0xacb2, "GeForce GT 720M" पूर्ण,
	अणु 0x1462, 0xacc1, "GeForce GT 720M" पूर्ण,
	अणु 0x1462, 0xae61, "GeForce 720M" पूर्ण,
	अणु 0x1462, 0xae65, "GeForce GT 720M" पूर्ण,
	अणु 0x1462, 0xae6a, "GeForce 820M" पूर्ण,
	अणु 0x1462, 0xae71, "GeForce GT 720M" पूर्ण,
	अणु 0x14c0, 0x0083, "GeForce 820M" पूर्ण,
	अणु 0x152d, 0x0926, "GeForce 620M" पूर्ण,
	अणु 0x152d, 0x0982, "GeForce GT 630M" पूर्ण,
	अणु 0x152d, 0x0983, "GeForce GT 630M" पूर्ण,
	अणु 0x152d, 0x1005, "GeForce GT820M" पूर्ण,
	अणु 0x152d, 0x1012, "GeForce 710M" पूर्ण,
	अणु 0x152d, 0x1019, "GeForce 820M" पूर्ण,
	अणु 0x152d, 0x1030, "GeForce GT 630M" पूर्ण,
	अणु 0x152d, 0x1055, "GeForce 710M" पूर्ण,
	अणु 0x152d, 0x1067, "GeForce GT 720M" पूर्ण,
	अणु 0x152d, 0x1092, "GeForce 820M" पूर्ण,
	अणु 0x17aa, 0x2200, "NVS 5200M" पूर्ण,
	अणु 0x17aa, 0x2213, "GeForce GT 720M" पूर्ण,
	अणु 0x17aa, 0x2220, "GeForce GT 720M" पूर्ण,
	अणु 0x17aa, 0x309c, "GeForce GT 720A" पूर्ण,
	अणु 0x17aa, 0x30b4, "GeForce 820A" पूर्ण,
	अणु 0x17aa, 0x30b7, "GeForce 720A" पूर्ण,
	अणु 0x17aa, 0x30e4, "GeForce 820A" पूर्ण,
	अणु 0x17aa, 0x361b, "GeForce 820A" पूर्ण,
	अणु 0x17aa, 0x361c, "GeForce 820A" पूर्ण,
	अणु 0x17aa, 0x361d, "GeForce 820A" पूर्ण,
	अणु 0x17aa, 0x3656, "GeForce GT620M" पूर्ण,
	अणु 0x17aa, 0x365a, "GeForce 705M" पूर्ण,
	अणु 0x17aa, 0x365e, "GeForce 800M" पूर्ण,
	अणु 0x17aa, 0x3661, "GeForce 820A" पूर्ण,
	अणु 0x17aa, 0x366c, "GeForce 800M" पूर्ण,
	अणु 0x17aa, 0x3685, "GeForce 800M" पूर्ण,
	अणु 0x17aa, 0x3686, "GeForce 800M" पूर्ण,
	अणु 0x17aa, 0x3687, "GeForce 705A" पूर्ण,
	अणु 0x17aa, 0x3696, "GeForce 820A" पूर्ण,
	अणु 0x17aa, 0x369b, "GeForce 820A" पूर्ण,
	अणु 0x17aa, 0x369c, "GeForce 820A" पूर्ण,
	अणु 0x17aa, 0x369d, "GeForce 820A" पूर्ण,
	अणु 0x17aa, 0x369e, "GeForce 820A" पूर्ण,
	अणु 0x17aa, 0x36a6, "GeForce 820A" पूर्ण,
	अणु 0x17aa, 0x36a7, "GeForce 820A" पूर्ण,
	अणु 0x17aa, 0x36a9, "GeForce 820A" पूर्ण,
	अणु 0x17aa, 0x36af, "GeForce 820A" पूर्ण,
	अणु 0x17aa, 0x36b0, "GeForce 820A" पूर्ण,
	अणु 0x17aa, 0x36b6, "GeForce 820A" पूर्ण,
	अणु 0x17aa, 0x3800, "GeForce GT 720M" पूर्ण,
	अणु 0x17aa, 0x3801, "GeForce GT 720M" पूर्ण,
	अणु 0x17aa, 0x3802, "GeForce GT 720M" पूर्ण,
	अणु 0x17aa, 0x3803, "GeForce GT 720M" पूर्ण,
	अणु 0x17aa, 0x3804, "GeForce GT 720M" पूर्ण,
	अणु 0x17aa, 0x3806, "GeForce GT 720M" पूर्ण,
	अणु 0x17aa, 0x3808, "GeForce GT 720M" पूर्ण,
	अणु 0x17aa, 0x380d, "GeForce 820M" पूर्ण,
	अणु 0x17aa, 0x380e, "GeForce 820M" पूर्ण,
	अणु 0x17aa, 0x380f, "GeForce 820M" पूर्ण,
	अणु 0x17aa, 0x3811, "GeForce 820M" पूर्ण,
	अणु 0x17aa, 0x3812, "GeForce 820M" पूर्ण,
	अणु 0x17aa, 0x3813, "GeForce 820M" पूर्ण,
	अणु 0x17aa, 0x3816, "GeForce 820M" पूर्ण,
	अणु 0x17aa, 0x3817, "GeForce 820M" पूर्ण,
	अणु 0x17aa, 0x3818, "GeForce 820M" पूर्ण,
	अणु 0x17aa, 0x381a, "GeForce 820M" पूर्ण,
	अणु 0x17aa, 0x381c, "GeForce 820M" पूर्ण,
	अणु 0x17aa, 0x381d, "GeForce 820M" पूर्ण,
	अणु 0x17aa, 0x3901, "GeForce 610M" पूर्ण,
	अणु 0x17aa, 0x3902, "GeForce 710M" पूर्ण,
	अणु 0x17aa, 0x3903, "GeForce 710M" पूर्ण,
	अणु 0x17aa, 0x3904, "GeForce GT 625M" पूर्ण,
	अणु 0x17aa, 0x3905, "GeForce GT 720M" पूर्ण,
	अणु 0x17aa, 0x3907, "GeForce 820M" पूर्ण,
	अणु 0x17aa, 0x3910, "GeForce GT 720M" पूर्ण,
	अणु 0x17aa, 0x3912, "GeForce GT 720M" पूर्ण,
	अणु 0x17aa, 0x3913, "GeForce 820M" पूर्ण,
	अणु 0x17aa, 0x3915, "GeForce 820M" पूर्ण,
	अणु 0x17aa, 0x3983, "GeForce 610M" पूर्ण,
	अणु 0x17aa, 0x5001, "GeForce 610M" पूर्ण,
	अणु 0x17aa, 0x5003, "GeForce GT 720M" पूर्ण,
	अणु 0x17aa, 0x5005, "GeForce 705M" पूर्ण,
	अणु 0x17aa, 0x500d, "GeForce GT 620M" पूर्ण,
	अणु 0x17aa, 0x5014, "GeForce 710M" पूर्ण,
	अणु 0x17aa, 0x5017, "GeForce 710M" पूर्ण,
	अणु 0x17aa, 0x5019, "GeForce 710M" पूर्ण,
	अणु 0x17aa, 0x501a, "GeForce 710M" पूर्ण,
	अणु 0x17aa, 0x501f, "GeForce GT 720M" पूर्ण,
	अणु 0x17aa, 0x5025, "GeForce 710M" पूर्ण,
	अणु 0x17aa, 0x5027, "GeForce 710M" पूर्ण,
	अणु 0x17aa, 0x502a, "GeForce 710M" पूर्ण,
	अणु 0x17aa, 0x502b, "GeForce GT 720M" पूर्ण,
	अणु 0x17aa, 0x502d, "GeForce 710M" पूर्ण,
	अणु 0x17aa, 0x502e, "GeForce GT 720M" पूर्ण,
	अणु 0x17aa, 0x502f, "GeForce GT 720M" पूर्ण,
	अणु 0x17aa, 0x5030, "GeForce 705M" पूर्ण,
	अणु 0x17aa, 0x5031, "GeForce 705M" पूर्ण,
	अणु 0x17aa, 0x5032, "GeForce 820M" पूर्ण,
	अणु 0x17aa, 0x5033, "GeForce 820M" पूर्ण,
	अणु 0x17aa, 0x503e, "GeForce 710M" पूर्ण,
	अणु 0x17aa, 0x503f, "GeForce 820M" पूर्ण,
	अणु 0x17aa, 0x5040, "GeForce 820M" पूर्ण,
	अणु 0x1854, 0x0177, "GeForce 710M" पूर्ण,
	अणु 0x1854, 0x0180, "GeForce 710M" पूर्ण,
	अणु 0x1854, 0x0190, "GeForce GT 720M" पूर्ण,
	अणु 0x1854, 0x0192, "GeForce GT 720M" पूर्ण,
	अणु 0x1854, 0x0224, "GeForce 820M" पूर्ण,
	अणु 0x1b0a, 0x20dd, "GeForce GT 620M" पूर्ण,
	अणु 0x1b0a, 0x20df, "GeForce GT 620M" पूर्ण,
	अणु 0x1b0a, 0x210e, "GeForce 820M" पूर्ण,
	अणु 0x1b0a, 0x2202, "GeForce GT 720M" पूर्ण,
	अणु 0x1b0a, 0x90d7, "GeForce 820M" पूर्ण,
	अणु 0x1b0a, 0x90dd, "GeForce 820M" पूर्ण,
	अणु 0x1b50, 0x5530, "GeForce 820M" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_1185[] = अणु
	अणु 0x10de, 0x106f, "GeForce GTX 760" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_1189[] = अणु
	अणु 0x10de, 0x1074, "GeForce GTX 760 Ti OEM" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_1199[] = अणु
	अणु 0x1458, 0xd001, "GeForce GTX 760" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_11e3[] = अणु
	अणु 0x17aa, 0x3683, "GeForce GTX 760A" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_1247[] = अणु
	अणु 0x1043, 0x212a, "GeForce GT 635M" पूर्ण,
	अणु 0x1043, 0x212b, "GeForce GT 635M" पूर्ण,
	अणु 0x1043, 0x212c, "GeForce GT 635M" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_124d[] = अणु
	अणु 0x1462, 0x10cc, "GeForce GT 635M" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_1290[] = अणु
	अणु 0x103c, 0x2afa, "GeForce 730A" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_1292[] = अणु
	अणु 0x17aa, 0x3675, "GeForce GT 740A" पूर्ण,
	अणु 0x17aa, 0x367c, "GeForce GT 740A" पूर्ण,
	अणु 0x17aa, 0x3684, "GeForce GT 740A" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_1295[] = अणु
	अणु 0x103c, 0x2b0d, "GeForce 710A" पूर्ण,
	अणु 0x103c, 0x2b0f, "GeForce 710A" पूर्ण,
	अणु 0x103c, 0x2b20, "GeForce 810A" पूर्ण,
	अणु 0x103c, 0x2b21, "GeForce 810A" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_1299[] = अणु
	अणु 0x17aa, 0x369b, "GeForce 920A" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_1340[] = अणु
	अणु 0x103c, 0x2b2b, "GeForce 830A" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_1341[] = अणु
	अणु 0x17aa, 0x3697, "GeForce 840A" पूर्ण,
	अणु 0x17aa, 0x3699, "GeForce 840A" पूर्ण,
	अणु 0x17aa, 0x369c, "GeForce 840A" पूर्ण,
	अणु 0x17aa, 0x36af, "GeForce 840A" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_1346[] = अणु
	अणु 0x17aa, 0x30ba, "GeForce 930A" पूर्ण,
	अणु 0x17aa, 0x362c, "GeForce 930A" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_1347[] = अणु
	अणु 0x17aa, 0x36b9, "GeForce 940A" पूर्ण,
	अणु 0x17aa, 0x36ba, "GeForce 940A" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_137a[] = अणु
	अणु 0x17aa, 0x2225, "Quadro K620M" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_137d[] = अणु
	अणु 0x17aa, 0x3699, "GeForce 940A" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_1391[] = अणु
	अणु 0x17aa, 0x3697, "GeForce GTX 850A" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_1392[] = अणु
	अणु 0x1028, 0x066a, "GeForce GPU" पूर्ण,
	अणु 0x1043, 0x861e, "GeForce GTX 750 Ti" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_139a[] = अणु
	अणु 0x17aa, 0x36b9, "GeForce GTX 950A" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_venकरोr
nvkm_device_pci_10de_139b[] = अणु
	अणु 0x1028, 0x06a3, "GeForce GTX 860M" पूर्ण,
	अणु 0x19da, 0xc248, "GeForce GTX 750 Ti" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_device_pci_device
nvkm_device_pci_10de[] = अणु
	अणु 0x0020, "RIVA TNT" पूर्ण,
	अणु 0x0028, "RIVA TNT2/TNT2 Pro" पूर्ण,
	अणु 0x0029, "RIVA TNT2 Ultra" पूर्ण,
	अणु 0x002c, "Vanta/Vanta LT" पूर्ण,
	अणु 0x002d, "RIVA TNT2 Model 64/Model 64 Pro" पूर्ण,
	अणु 0x0040, "GeForce 6800 Ultra" पूर्ण,
	अणु 0x0041, "GeForce 6800" पूर्ण,
	अणु 0x0042, "GeForce 6800 LE" पूर्ण,
	अणु 0x0043, "GeForce 6800 XE" पूर्ण,
	अणु 0x0044, "GeForce 6800 XT" पूर्ण,
	अणु 0x0045, "GeForce 6800 GT" पूर्ण,
	अणु 0x0046, "GeForce 6800 GT" पूर्ण,
	अणु 0x0047, "GeForce 6800 GS" पूर्ण,
	अणु 0x0048, "GeForce 6800 XT" पूर्ण,
	अणु 0x004e, "Quadro FX 4000" पूर्ण,
	अणु 0x0090, "GeForce 7800 GTX" पूर्ण,
	अणु 0x0091, "GeForce 7800 GTX" पूर्ण,
	अणु 0x0092, "GeForce 7800 GT" पूर्ण,
	अणु 0x0093, "GeForce 7800 GS" पूर्ण,
	अणु 0x0095, "GeForce 7800 SLI" पूर्ण,
	अणु 0x0098, "GeForce Go 7800" पूर्ण,
	अणु 0x0099, "GeForce Go 7800 GTX" पूर्ण,
	अणु 0x009d, "Quadro FX 4500" पूर्ण,
	अणु 0x00a0, "Aladdin TNT2" पूर्ण,
	अणु 0x00c0, "GeForce 6800 GS" पूर्ण,
	अणु 0x00c1, "GeForce 6800" पूर्ण,
	अणु 0x00c2, "GeForce 6800 LE" पूर्ण,
	अणु 0x00c3, "GeForce 6800 XT" पूर्ण,
	अणु 0x00c8, "GeForce Go 6800" पूर्ण,
	अणु 0x00c9, "GeForce Go 6800 Ultra" पूर्ण,
	अणु 0x00cc, "Quadro FX Go1400" पूर्ण,
	अणु 0x00cd, "Quadro FX 3450/4000 SDI" पूर्ण,
	अणु 0x00ce, "Quadro FX 1400" पूर्ण,
	अणु 0x00f1, "GeForce 6600 GT" पूर्ण,
	अणु 0x00f2, "GeForce 6600" पूर्ण,
	अणु 0x00f3, "GeForce 6200" पूर्ण,
	अणु 0x00f4, "GeForce 6600 LE" पूर्ण,
	अणु 0x00f5, "GeForce 7800 GS" पूर्ण,
	अणु 0x00f6, "GeForce 6800 GS" पूर्ण,
	अणु 0x00f8, "Quadro FX 3400/Quadro FX 4000" पूर्ण,
	अणु 0x00f9, "GeForce 6800 Ultra" पूर्ण,
	अणु 0x00fa, "GeForce PCX 5750" पूर्ण,
	अणु 0x00fb, "GeForce PCX 5900" पूर्ण,
	अणु 0x00fc, "Quadro FX 330/GeForce PCX 5300" पूर्ण,
	अणु 0x00fd, "Quadro FX 330/Quadro NVS 280 PCI-E" पूर्ण,
	अणु 0x00fe, "Quadro FX 1300" पूर्ण,
	अणु 0x0100, "GeForce 256" पूर्ण,
	अणु 0x0101, "GeForce DDR" पूर्ण,
	अणु 0x0103, "Quadro" पूर्ण,
	अणु 0x0110, "GeForce2 MX/MX 400" पूर्ण,
	अणु 0x0111, "GeForce2 MX 100/200" पूर्ण,
	अणु 0x0112, "GeForce2 Go" पूर्ण,
	अणु 0x0113, "Quadro2 MXR/EX/Go" पूर्ण,
	अणु 0x0140, "GeForce 6600 GT" पूर्ण,
	अणु 0x0141, "GeForce 6600" पूर्ण,
	अणु 0x0142, "GeForce 6600 LE" पूर्ण,
	अणु 0x0143, "GeForce 6600 VE" पूर्ण,
	अणु 0x0144, "GeForce Go 6600" पूर्ण,
	अणु 0x0145, "GeForce 6610 XL" पूर्ण,
	अणु 0x0146, "GeForce Go 6600 TE/6200 TE" पूर्ण,
	अणु 0x0147, "GeForce 6700 XL" पूर्ण,
	अणु 0x0148, "GeForce Go 6600" पूर्ण,
	अणु 0x0149, "GeForce Go 6600 GT" पूर्ण,
	अणु 0x014a, "Quadro NVS 440" पूर्ण,
	अणु 0x014c, "Quadro FX 540M" पूर्ण,
	अणु 0x014d, "Quadro FX 550" पूर्ण,
	अणु 0x014e, "Quadro FX 540" पूर्ण,
	अणु 0x014f, "GeForce 6200" पूर्ण,
	अणु 0x0150, "GeForce2 GTS/GeForce2 Pro" पूर्ण,
	अणु 0x0151, "GeForce2 Ti" पूर्ण,
	अणु 0x0152, "GeForce2 Ultra" पूर्ण,
	अणु 0x0153, "Quadro2 Pro" पूर्ण,
	अणु 0x0160, "GeForce 6500" पूर्ण,
	अणु 0x0161, "GeForce 6200 TurboCache(TM)" पूर्ण,
	अणु 0x0162, "GeForce 6200SE TurboCache(TM)" पूर्ण,
	अणु 0x0163, "GeForce 6200 LE" पूर्ण,
	अणु 0x0164, "GeForce Go 6200" पूर्ण,
	अणु 0x0165, "Quadro NVS 285" पूर्ण,
	अणु 0x0166, "GeForce Go 6400" पूर्ण,
	अणु 0x0167, "GeForce Go 6200" पूर्ण,
	अणु 0x0168, "GeForce Go 6400" पूर्ण,
	अणु 0x0169, "GeForce 6250" पूर्ण,
	अणु 0x016a, "GeForce 7100 GS" पूर्ण,
	अणु 0x0170, "GeForce4 MX 460" पूर्ण,
	अणु 0x0171, "GeForce4 MX 440" पूर्ण,
	अणु 0x0172, "GeForce4 MX 420" पूर्ण,
	अणु 0x0173, "GeForce4 MX 440-SE" पूर्ण,
	अणु 0x0174, "GeForce4 440 Go" पूर्ण,
	अणु 0x0175, "GeForce4 420 Go" पूर्ण,
	अणु 0x0176, "GeForce4 420 Go 32M" पूर्ण,
	अणु 0x0177, "GeForce4 460 Go" पूर्ण,
	अणु 0x0178, "Quadro4 550 XGL" पूर्ण,
	अणु 0x0179, "GeForce4 440 Go 64M" पूर्ण,
	अणु 0x017a, "Quadro NVS 400" पूर्ण,
	अणु 0x017c, "Quadro4 500 GoGL" पूर्ण,
	अणु 0x017d, "GeForce4 410 Go 16M" पूर्ण,
	अणु 0x0181, "GeForce4 MX 440 with AGP8X" पूर्ण,
	अणु 0x0182, "GeForce4 MX 440SE with AGP8X" पूर्ण,
	अणु 0x0183, "GeForce4 MX 420 with AGP8X" पूर्ण,
	अणु 0x0185, "GeForce4 MX 4000" पूर्ण,
	अणु 0x0188, "Quadro4 580 XGL" पूर्ण,
	अणु 0x0189, "GeForce4 MX with AGP8X (Mac)", nvkm_device_pci_10de_0189 पूर्ण,
	अणु 0x018a, "Quadro NVS 280 SD" पूर्ण,
	अणु 0x018b, "Quadro4 380 XGL" पूर्ण,
	अणु 0x018c, "Quadro NVS 50 PCI" पूर्ण,
	अणु 0x0191, "GeForce 8800 GTX" पूर्ण,
	अणु 0x0193, "GeForce 8800 GTS" पूर्ण,
	अणु 0x0194, "GeForce 8800 Ultra" पूर्ण,
	अणु 0x0197, "Tesla C870" पूर्ण,
	अणु 0x019d, "Quadro FX 5600" पूर्ण,
	अणु 0x019e, "Quadro FX 4600" पूर्ण,
	अणु 0x01a0, "GeForce2 Integrated GPU" पूर्ण,
	अणु 0x01d0, "GeForce 7350 LE" पूर्ण,
	अणु 0x01d1, "GeForce 7300 LE" पूर्ण,
	अणु 0x01d2, "GeForce 7550 LE" पूर्ण,
	अणु 0x01d3, "GeForce 7300 SE/7200 GS" पूर्ण,
	अणु 0x01d6, "GeForce Go 7200" पूर्ण,
	अणु 0x01d7, "GeForce Go 7300" पूर्ण,
	अणु 0x01d8, "GeForce Go 7400" पूर्ण,
	अणु 0x01da, "Quadro NVS 110M" पूर्ण,
	अणु 0x01db, "Quadro NVS 120M" पूर्ण,
	अणु 0x01dc, "Quadro FX 350M" पूर्ण,
	अणु 0x01dd, "GeForce 7500 LE" पूर्ण,
	अणु 0x01de, "Quadro FX 350" पूर्ण,
	अणु 0x01df, "GeForce 7300 GS" पूर्ण,
	अणु 0x01f0, "GeForce4 MX Integrated GPU", nvkm_device_pci_10de_01f0 पूर्ण,
	अणु 0x0200, "GeForce3" पूर्ण,
	अणु 0x0201, "GeForce3 Ti 200" पूर्ण,
	अणु 0x0202, "GeForce3 Ti 500" पूर्ण,
	अणु 0x0203, "Quadro DCC" पूर्ण,
	अणु 0x0211, "GeForce 6800" पूर्ण,
	अणु 0x0212, "GeForce 6800 LE" पूर्ण,
	अणु 0x0215, "GeForce 6800 GT" पूर्ण,
	अणु 0x0218, "GeForce 6800 XT" पूर्ण,
	अणु 0x0221, "GeForce 6200" पूर्ण,
	अणु 0x0222, "GeForce 6200 A-LE" पूर्ण,
	अणु 0x0240, "GeForce 6150" पूर्ण,
	अणु 0x0241, "GeForce 6150 LE" पूर्ण,
	अणु 0x0242, "GeForce 6100" पूर्ण,
	अणु 0x0244, "GeForce Go 6150" पूर्ण,
	अणु 0x0245, "Quadro NVS 210S / GeForce 6150LE" पूर्ण,
	अणु 0x0247, "GeForce Go 6100" पूर्ण,
	अणु 0x0250, "GeForce4 Ti 4600" पूर्ण,
	अणु 0x0251, "GeForce4 Ti 4400" पूर्ण,
	अणु 0x0253, "GeForce4 Ti 4200" पूर्ण,
	अणु 0x0258, "Quadro4 900 XGL" पूर्ण,
	अणु 0x0259, "Quadro4 750 XGL" पूर्ण,
	अणु 0x025b, "Quadro4 700 XGL" पूर्ण,
	अणु 0x0280, "GeForce4 Ti 4800" पूर्ण,
	अणु 0x0281, "GeForce4 Ti 4200 with AGP8X" पूर्ण,
	अणु 0x0282, "GeForce4 Ti 4800 SE" पूर्ण,
	अणु 0x0286, "GeForce4 4200 Go" पूर्ण,
	अणु 0x0288, "Quadro4 980 XGL" पूर्ण,
	अणु 0x0289, "Quadro4 780 XGL" पूर्ण,
	अणु 0x028c, "Quadro4 700 GoGL" पूर्ण,
	अणु 0x0290, "GeForce 7900 GTX" पूर्ण,
	अणु 0x0291, "GeForce 7900 GT/GTO" पूर्ण,
	अणु 0x0292, "GeForce 7900 GS" पूर्ण,
	अणु 0x0293, "GeForce 7950 GX2" पूर्ण,
	अणु 0x0294, "GeForce 7950 GX2" पूर्ण,
	अणु 0x0295, "GeForce 7950 GT" पूर्ण,
	अणु 0x0297, "GeForce Go 7950 GTX" पूर्ण,
	अणु 0x0298, "GeForce Go 7900 GS" पूर्ण,
	अणु 0x0299, "Quadro NVS 510M" पूर्ण,
	अणु 0x029a, "Quadro FX 2500M" पूर्ण,
	अणु 0x029b, "Quadro FX 1500M" पूर्ण,
	अणु 0x029c, "Quadro FX 5500" पूर्ण,
	अणु 0x029d, "Quadro FX 3500" पूर्ण,
	अणु 0x029e, "Quadro FX 1500" पूर्ण,
	अणु 0x029f, "Quadro FX 4500 X2" पूर्ण,
	अणु 0x02e0, "GeForce 7600 GT" पूर्ण,
	अणु 0x02e1, "GeForce 7600 GS" पूर्ण,
	अणु 0x02e2, "GeForce 7300 GT" पूर्ण,
	अणु 0x02e3, "GeForce 7900 GS" पूर्ण,
	अणु 0x02e4, "GeForce 7950 GT" पूर्ण,
	अणु 0x0301, "GeForce FX 5800 Ultra" पूर्ण,
	अणु 0x0302, "GeForce FX 5800" पूर्ण,
	अणु 0x0308, "Quadro FX 2000" पूर्ण,
	अणु 0x0309, "Quadro FX 1000" पूर्ण,
	अणु 0x0311, "GeForce FX 5600 Ultra" पूर्ण,
	अणु 0x0312, "GeForce FX 5600" पूर्ण,
	अणु 0x0314, "GeForce FX 5600XT" पूर्ण,
	अणु 0x031a, "GeForce FX Go5600" पूर्ण,
	अणु 0x031b, "GeForce FX Go5650" पूर्ण,
	अणु 0x031c, "Quadro FX Go700" पूर्ण,
	अणु 0x0320, "GeForce FX 5200" पूर्ण,
	अणु 0x0321, "GeForce FX 5200 Ultra" पूर्ण,
	अणु 0x0322, "GeForce FX 5200", nvkm_device_pci_10de_0322 पूर्ण,
	अणु 0x0323, "GeForce FX 5200LE" पूर्ण,
	अणु 0x0324, "GeForce FX Go5200" पूर्ण,
	अणु 0x0325, "GeForce FX Go5250" पूर्ण,
	अणु 0x0326, "GeForce FX 5500" पूर्ण,
	अणु 0x0327, "GeForce FX 5100" पूर्ण,
	अणु 0x0328, "GeForce FX Go5200 32M/64M" पूर्ण,
	अणु 0x032a, "Quadro NVS 55/280 PCI" पूर्ण,
	अणु 0x032b, "Quadro FX 500/FX 600" पूर्ण,
	अणु 0x032c, "GeForce FX Go53xx" पूर्ण,
	अणु 0x032d, "GeForce FX Go5100" पूर्ण,
	अणु 0x0330, "GeForce FX 5900 Ultra" पूर्ण,
	अणु 0x0331, "GeForce FX 5900" पूर्ण,
	अणु 0x0332, "GeForce FX 5900XT" पूर्ण,
	अणु 0x0333, "GeForce FX 5950 Ultra" पूर्ण,
	अणु 0x0334, "GeForce FX 5900ZT" पूर्ण,
	अणु 0x0338, "Quadro FX 3000" पूर्ण,
	अणु 0x033f, "Quadro FX 700" पूर्ण,
	अणु 0x0341, "GeForce FX 5700 Ultra" पूर्ण,
	अणु 0x0342, "GeForce FX 5700" पूर्ण,
	अणु 0x0343, "GeForce FX 5700LE" पूर्ण,
	अणु 0x0344, "GeForce FX 5700VE" पूर्ण,
	अणु 0x0347, "GeForce FX Go5700" पूर्ण,
	अणु 0x0348, "GeForce FX Go5700" पूर्ण,
	अणु 0x034c, "Quadro FX Go1000" पूर्ण,
	अणु 0x034e, "Quadro FX 1100" पूर्ण,
	अणु 0x038b, "GeForce 7650 GS" पूर्ण,
	अणु 0x0390, "GeForce 7650 GS" पूर्ण,
	अणु 0x0391, "GeForce 7600 GT" पूर्ण,
	अणु 0x0392, "GeForce 7600 GS" पूर्ण,
	अणु 0x0393, "GeForce 7300 GT" पूर्ण,
	अणु 0x0394, "GeForce 7600 LE" पूर्ण,
	अणु 0x0395, "GeForce 7300 GT" पूर्ण,
	अणु 0x0397, "GeForce Go 7700" पूर्ण,
	अणु 0x0398, "GeForce Go 7600" पूर्ण,
	अणु 0x0399, "GeForce Go 7600 GT" पूर्ण,
	अणु 0x039c, "Quadro FX 560M" पूर्ण,
	अणु 0x039e, "Quadro FX 560" पूर्ण,
	अणु 0x03d0, "GeForce 6150SE nForce 430" पूर्ण,
	अणु 0x03d1, "GeForce 6100 nForce 405" पूर्ण,
	अणु 0x03d2, "GeForce 6100 nForce 400" पूर्ण,
	अणु 0x03d5, "GeForce 6100 nForce 420" पूर्ण,
	अणु 0x03d6, "GeForce 7025 / nForce 630a" पूर्ण,
	अणु 0x0400, "GeForce 8600 GTS" पूर्ण,
	अणु 0x0401, "GeForce 8600 GT" पूर्ण,
	अणु 0x0402, "GeForce 8600 GT" पूर्ण,
	अणु 0x0403, "GeForce 8600 GS" पूर्ण,
	अणु 0x0404, "GeForce 8400 GS" पूर्ण,
	अणु 0x0405, "GeForce 9500M GS" पूर्ण,
	अणु 0x0406, "GeForce 8300 GS" पूर्ण,
	अणु 0x0407, "GeForce 8600M GT" पूर्ण,
	अणु 0x0408, "GeForce 9650M GS" पूर्ण,
	अणु 0x0409, "GeForce 8700M GT" पूर्ण,
	अणु 0x040a, "Quadro FX 370" पूर्ण,
	अणु 0x040b, "Quadro NVS 320M" पूर्ण,
	अणु 0x040c, "Quadro FX 570M" पूर्ण,
	अणु 0x040d, "Quadro FX 1600M" पूर्ण,
	अणु 0x040e, "Quadro FX 570" पूर्ण,
	अणु 0x040f, "Quadro FX 1700" पूर्ण,
	अणु 0x0410, "GeForce GT 330" पूर्ण,
	अणु 0x0420, "GeForce 8400 SE" पूर्ण,
	अणु 0x0421, "GeForce 8500 GT" पूर्ण,
	अणु 0x0422, "GeForce 8400 GS" पूर्ण,
	अणु 0x0423, "GeForce 8300 GS" पूर्ण,
	अणु 0x0424, "GeForce 8400 GS" पूर्ण,
	अणु 0x0425, "GeForce 8600M GS" पूर्ण,
	अणु 0x0426, "GeForce 8400M GT" पूर्ण,
	अणु 0x0427, "GeForce 8400M GS" पूर्ण,
	अणु 0x0428, "GeForce 8400M G" पूर्ण,
	अणु 0x0429, "Quadro NVS 140M" पूर्ण,
	अणु 0x042a, "Quadro NVS 130M" पूर्ण,
	अणु 0x042b, "Quadro NVS 135M" पूर्ण,
	अणु 0x042c, "GeForce 9400 GT" पूर्ण,
	अणु 0x042d, "Quadro FX 360M" पूर्ण,
	अणु 0x042e, "GeForce 9300M G" पूर्ण,
	अणु 0x042f, "Quadro NVS 290" पूर्ण,
	अणु 0x0531, "GeForce 7150M / nForce 630M" पूर्ण,
	अणु 0x0533, "GeForce 7000M / nForce 610M" पूर्ण,
	अणु 0x053a, "GeForce 7050 PV / nForce 630a" पूर्ण,
	अणु 0x053b, "GeForce 7050 PV / nForce 630a" पूर्ण,
	अणु 0x053e, "GeForce 7025 / nForce 630a" पूर्ण,
	अणु 0x05e0, "GeForce GTX 295" पूर्ण,
	अणु 0x05e1, "GeForce GTX 280" पूर्ण,
	अणु 0x05e2, "GeForce GTX 260" पूर्ण,
	अणु 0x05e3, "GeForce GTX 285" पूर्ण,
	अणु 0x05e6, "GeForce GTX 275" पूर्ण,
	अणु 0x05e7, "Tesla C1060", nvkm_device_pci_10de_05e7 पूर्ण,
	अणु 0x05ea, "GeForce GTX 260" पूर्ण,
	अणु 0x05eb, "GeForce GTX 295" पूर्ण,
	अणु 0x05ed, "Quadroplex 2200 D2" पूर्ण,
	अणु 0x05f8, "Quadroplex 2200 S4" पूर्ण,
	अणु 0x05f9, "Quadro CX" पूर्ण,
	अणु 0x05fd, "Quadro FX 5800" पूर्ण,
	अणु 0x05fe, "Quadro FX 4800" पूर्ण,
	अणु 0x05ff, "Quadro FX 3800" पूर्ण,
	अणु 0x0600, "GeForce 8800 GTS 512" पूर्ण,
	अणु 0x0601, "GeForce 9800 GT" पूर्ण,
	अणु 0x0602, "GeForce 8800 GT" पूर्ण,
	अणु 0x0603, "GeForce GT 230" पूर्ण,
	अणु 0x0604, "GeForce 9800 GX2" पूर्ण,
	अणु 0x0605, "GeForce 9800 GT" पूर्ण,
	अणु 0x0606, "GeForce 8800 GS" पूर्ण,
	अणु 0x0607, "GeForce GTS 240" पूर्ण,
	अणु 0x0608, "GeForce 9800M GTX" पूर्ण,
	अणु 0x0609, "GeForce 8800M GTS", nvkm_device_pci_10de_0609 पूर्ण,
	अणु 0x060a, "GeForce GTX 280M" पूर्ण,
	अणु 0x060b, "GeForce 9800M GT" पूर्ण,
	अणु 0x060c, "GeForce 8800M GTX" पूर्ण,
	अणु 0x060d, "GeForce 8800 GS" पूर्ण,
	अणु 0x060f, "GeForce GTX 285M" पूर्ण,
	अणु 0x0610, "GeForce 9600 GSO" पूर्ण,
	अणु 0x0611, "GeForce 8800 GT" पूर्ण,
	अणु 0x0612, "GeForce 9800 GTX/9800 GTX+" पूर्ण,
	अणु 0x0613, "GeForce 9800 GTX+" पूर्ण,
	अणु 0x0614, "GeForce 9800 GT" पूर्ण,
	अणु 0x0615, "GeForce GTS 250" पूर्ण,
	अणु 0x0617, "GeForce 9800M GTX" पूर्ण,
	अणु 0x0618, "GeForce GTX 260M" पूर्ण,
	अणु 0x0619, "Quadro FX 4700 X2" पूर्ण,
	अणु 0x061a, "Quadro FX 3700" पूर्ण,
	अणु 0x061b, "Quadro VX 200" पूर्ण,
	अणु 0x061c, "Quadro FX 3600M" पूर्ण,
	अणु 0x061d, "Quadro FX 2800M" पूर्ण,
	अणु 0x061e, "Quadro FX 3700M" पूर्ण,
	अणु 0x061f, "Quadro FX 3800M" पूर्ण,
	अणु 0x0621, "GeForce GT 230" पूर्ण,
	अणु 0x0622, "GeForce 9600 GT" पूर्ण,
	अणु 0x0623, "GeForce 9600 GS" पूर्ण,
	अणु 0x0625, "GeForce 9600 GSO 512" पूर्ण,
	अणु 0x0626, "GeForce GT 130" पूर्ण,
	अणु 0x0627, "GeForce GT 140" पूर्ण,
	अणु 0x0628, "GeForce 9800M GTS" पूर्ण,
	अणु 0x062a, "GeForce 9700M GTS" पूर्ण,
	अणु 0x062b, "GeForce 9800M GS" पूर्ण,
	अणु 0x062c, "GeForce 9800M GTS" पूर्ण,
	अणु 0x062d, "GeForce 9600 GT" पूर्ण,
	अणु 0x062e, "GeForce 9600 GT", nvkm_device_pci_10de_062e पूर्ण,
	अणु 0x0630, "GeForce 9700 S" पूर्ण,
	अणु 0x0631, "GeForce GTS 160M" पूर्ण,
	अणु 0x0632, "GeForce GTS 150M" पूर्ण,
	अणु 0x0635, "GeForce 9600 GSO" पूर्ण,
	अणु 0x0637, "GeForce 9600 GT" पूर्ण,
	अणु 0x0638, "Quadro FX 1800" पूर्ण,
	अणु 0x063a, "Quadro FX 2700M" पूर्ण,
	अणु 0x0640, "GeForce 9500 GT" पूर्ण,
	अणु 0x0641, "GeForce 9400 GT" पूर्ण,
	अणु 0x0643, "GeForce 9500 GT" पूर्ण,
	अणु 0x0644, "GeForce 9500 GS" पूर्ण,
	अणु 0x0645, "GeForce 9500 GS" पूर्ण,
	अणु 0x0646, "GeForce GT 120" पूर्ण,
	अणु 0x0647, "GeForce 9600M GT" पूर्ण,
	अणु 0x0648, "GeForce 9600M GS" पूर्ण,
	अणु 0x0649, "GeForce 9600M GT", nvkm_device_pci_10de_0649 पूर्ण,
	अणु 0x064a, "GeForce 9700M GT" पूर्ण,
	अणु 0x064b, "GeForce 9500M G" पूर्ण,
	अणु 0x064c, "GeForce 9650M GT" पूर्ण,
	अणु 0x0651, "GeForce G 110M" पूर्ण,
	अणु 0x0652, "GeForce GT 130M", nvkm_device_pci_10de_0652 पूर्ण,
	अणु 0x0653, "GeForce GT 120M" पूर्ण,
	अणु 0x0654, "GeForce GT 220M", nvkm_device_pci_10de_0654 पूर्ण,
	अणु 0x0655, शून्य, nvkm_device_pci_10de_0655 पूर्ण,
	अणु 0x0656, शून्य, nvkm_device_pci_10de_0656 पूर्ण,
	अणु 0x0658, "Quadro FX 380" पूर्ण,
	अणु 0x0659, "Quadro FX 580" पूर्ण,
	अणु 0x065a, "Quadro FX 1700M" पूर्ण,
	अणु 0x065b, "GeForce 9400 GT" पूर्ण,
	अणु 0x065c, "Quadro FX 770M" पूर्ण,
	अणु 0x06c0, "GeForce GTX 480" पूर्ण,
	अणु 0x06c4, "GeForce GTX 465" पूर्ण,
	अणु 0x06ca, "GeForce GTX 480M" पूर्ण,
	अणु 0x06cd, "GeForce GTX 470" पूर्ण,
	अणु 0x06d1, "Tesla C2050 / C2070", nvkm_device_pci_10de_06d1 पूर्ण,
	अणु 0x06d2, "Tesla M2070", nvkm_device_pci_10de_06d2 पूर्ण,
	अणु 0x06d8, "Quadro 6000" पूर्ण,
	अणु 0x06d9, "Quadro 5000" पूर्ण,
	अणु 0x06da, "Quadro 5000M" पूर्ण,
	अणु 0x06dc, "Quadro 6000" पूर्ण,
	अणु 0x06dd, "Quadro 4000" पूर्ण,
	अणु 0x06de, "Tesla T20 Processor", nvkm_device_pci_10de_06de पूर्ण,
	अणु 0x06df, "Tesla M2070-Q" पूर्ण,
	अणु 0x06e0, "GeForce 9300 GE" पूर्ण,
	अणु 0x06e1, "GeForce 9300 GS" पूर्ण,
	अणु 0x06e2, "GeForce 8400" पूर्ण,
	अणु 0x06e3, "GeForce 8400 SE" पूर्ण,
	अणु 0x06e4, "GeForce 8400 GS" पूर्ण,
	अणु 0x06e5, "GeForce 9300M GS" पूर्ण,
	अणु 0x06e6, "GeForce G100" पूर्ण,
	अणु 0x06e7, "GeForce 9300 SE" पूर्ण,
	अणु 0x06e8, "GeForce 9200M GS", nvkm_device_pci_10de_06e8 पूर्ण,
	अणु 0x06e9, "GeForce 9300M GS" पूर्ण,
	अणु 0x06ea, "Quadro NVS 150M" पूर्ण,
	अणु 0x06eb, "Quadro NVS 160M" पूर्ण,
	अणु 0x06ec, "GeForce G 105M" पूर्ण,
	अणु 0x06ef, "GeForce G 103M" पूर्ण,
	अणु 0x06f1, "GeForce G105M" पूर्ण,
	अणु 0x06f8, "Quadro NVS 420" पूर्ण,
	अणु 0x06f9, "Quadro FX 370 LP", nvkm_device_pci_10de_06f9 पूर्ण,
	अणु 0x06fa, "Quadro NVS 450" पूर्ण,
	अणु 0x06fb, "Quadro FX 370M" पूर्ण,
	अणु 0x06fd, "Quadro NVS 295" पूर्ण,
	अणु 0x06ff, "HICx16 + Graphics", nvkm_device_pci_10de_06ff पूर्ण,
	अणु 0x07e0, "GeForce 7150 / nForce 630i" पूर्ण,
	अणु 0x07e1, "GeForce 7100 / nForce 630i" पूर्ण,
	अणु 0x07e2, "GeForce 7050 / nForce 630i" पूर्ण,
	अणु 0x07e3, "GeForce 7050 / nForce 610i" पूर्ण,
	अणु 0x07e5, "GeForce 7050 / nForce 620i" पूर्ण,
	अणु 0x0840, "GeForce 8200M" पूर्ण,
	अणु 0x0844, "GeForce 9100M G" पूर्ण,
	अणु 0x0845, "GeForce 8200M G" पूर्ण,
	अणु 0x0846, "GeForce 9200" पूर्ण,
	अणु 0x0847, "GeForce 9100" पूर्ण,
	अणु 0x0848, "GeForce 8300" पूर्ण,
	अणु 0x0849, "GeForce 8200" पूर्ण,
	अणु 0x084a, "nForce 730a" पूर्ण,
	अणु 0x084b, "GeForce 9200" पूर्ण,
	अणु 0x084c, "nForce 980a/780a SLI" पूर्ण,
	अणु 0x084d, "nForce 750a SLI" पूर्ण,
	अणु 0x084f, "GeForce 8100 / nForce 720a" पूर्ण,
	अणु 0x0860, "GeForce 9400" पूर्ण,
	अणु 0x0861, "GeForce 9400" पूर्ण,
	अणु 0x0862, "GeForce 9400M G" पूर्ण,
	अणु 0x0863, "GeForce 9400M" पूर्ण,
	अणु 0x0864, "GeForce 9300" पूर्ण,
	अणु 0x0865, "ION" पूर्ण,
	अणु 0x0866, "GeForce 9400M G", nvkm_device_pci_10de_0866 पूर्ण,
	अणु 0x0867, "GeForce 9400" पूर्ण,
	अणु 0x0868, "nForce 760i SLI" पूर्ण,
	अणु 0x0869, "GeForce 9400" पूर्ण,
	अणु 0x086a, "GeForce 9400" पूर्ण,
	अणु 0x086c, "GeForce 9300 / nForce 730i" पूर्ण,
	अणु 0x086d, "GeForce 9200" पूर्ण,
	अणु 0x086e, "GeForce 9100M G" पूर्ण,
	अणु 0x086f, "GeForce 8200M G" पूर्ण,
	अणु 0x0870, "GeForce 9400M" पूर्ण,
	अणु 0x0871, "GeForce 9200" पूर्ण,
	अणु 0x0872, "GeForce G102M", nvkm_device_pci_10de_0872 पूर्ण,
	अणु 0x0873, "GeForce G102M", nvkm_device_pci_10de_0873 पूर्ण,
	अणु 0x0874, "ION" पूर्ण,
	अणु 0x0876, "ION" पूर्ण,
	अणु 0x087a, "GeForce 9400" पूर्ण,
	अणु 0x087d, "ION" पूर्ण,
	अणु 0x087e, "ION LE" पूर्ण,
	अणु 0x087f, "ION LE" पूर्ण,
	अणु 0x08a0, "GeForce 320M" पूर्ण,
	अणु 0x08a2, "GeForce 320M" पूर्ण,
	अणु 0x08a3, "GeForce 320M" पूर्ण,
	अणु 0x08a4, "GeForce 320M" पूर्ण,
	अणु 0x08a5, "GeForce 320M" पूर्ण,
	अणु 0x0a20, "GeForce GT 220" पूर्ण,
	अणु 0x0a22, "GeForce 315" पूर्ण,
	अणु 0x0a23, "GeForce 210" पूर्ण,
	अणु 0x0a26, "GeForce 405" पूर्ण,
	अणु 0x0a27, "GeForce 405" पूर्ण,
	अणु 0x0a28, "GeForce GT 230M" पूर्ण,
	अणु 0x0a29, "GeForce GT 330M" पूर्ण,
	अणु 0x0a2a, "GeForce GT 230M" पूर्ण,
	अणु 0x0a2b, "GeForce GT 330M" पूर्ण,
	अणु 0x0a2c, "NVS 5100M" पूर्ण,
	अणु 0x0a2d, "GeForce GT 320M" पूर्ण,
	अणु 0x0a32, "GeForce GT 415" पूर्ण,
	अणु 0x0a34, "GeForce GT 240M" पूर्ण,
	अणु 0x0a35, "GeForce GT 325M" पूर्ण,
	अणु 0x0a38, "Quadro 400" पूर्ण,
	अणु 0x0a3c, "Quadro FX 880M" पूर्ण,
	अणु 0x0a60, "GeForce G210" पूर्ण,
	अणु 0x0a62, "GeForce 205" पूर्ण,
	अणु 0x0a63, "GeForce 310" पूर्ण,
	अणु 0x0a64, "Second Generation ION" पूर्ण,
	अणु 0x0a65, "GeForce 210" पूर्ण,
	अणु 0x0a66, "GeForce 310" पूर्ण,
	अणु 0x0a67, "GeForce 315" पूर्ण,
	अणु 0x0a68, "GeForce G105M" पूर्ण,
	अणु 0x0a69, "GeForce G105M" पूर्ण,
	अणु 0x0a6a, "NVS 2100M" पूर्ण,
	अणु 0x0a6c, "NVS 3100M" पूर्ण,
	अणु 0x0a6e, "GeForce 305M", nvkm_device_pci_10de_0a6e पूर्ण,
	अणु 0x0a6f, "Second Generation ION" पूर्ण,
	अणु 0x0a70, "GeForce 310M", nvkm_device_pci_10de_0a70 पूर्ण,
	अणु 0x0a71, "GeForce 305M" पूर्ण,
	अणु 0x0a72, "GeForce 310M" पूर्ण,
	अणु 0x0a73, "GeForce 305M", nvkm_device_pci_10de_0a73 पूर्ण,
	अणु 0x0a74, "GeForce G210M", nvkm_device_pci_10de_0a74 पूर्ण,
	अणु 0x0a75, "GeForce 310M", nvkm_device_pci_10de_0a75 पूर्ण,
	अणु 0x0a76, "Second Generation ION" पूर्ण,
	अणु 0x0a78, "Quadro FX 380 LP" पूर्ण,
	अणु 0x0a7a, "GeForce 315M", nvkm_device_pci_10de_0a7a पूर्ण,
	अणु 0x0a7c, "Quadro FX 380M" पूर्ण,
	अणु 0x0ca0, "GeForce GT 330" पूर्ण,
	अणु 0x0ca2, "GeForce GT 320" पूर्ण,
	अणु 0x0ca3, "GeForce GT 240" पूर्ण,
	अणु 0x0ca4, "GeForce GT 340" पूर्ण,
	अणु 0x0ca5, "GeForce GT 220" पूर्ण,
	अणु 0x0ca7, "GeForce GT 330" पूर्ण,
	अणु 0x0ca8, "GeForce GTS 260M" पूर्ण,
	अणु 0x0ca9, "GeForce GTS 250M" पूर्ण,
	अणु 0x0cac, "GeForce GT 220" पूर्ण,
	अणु 0x0caf, "GeForce GT 335M" पूर्ण,
	अणु 0x0cb0, "GeForce GTS 350M" पूर्ण,
	अणु 0x0cb1, "GeForce GTS 360M" पूर्ण,
	अणु 0x0cbc, "Quadro FX 1800M" पूर्ण,
	अणु 0x0dc0, "GeForce GT 440" पूर्ण,
	अणु 0x0dc4, "GeForce GTS 450" पूर्ण,
	अणु 0x0dc5, "GeForce GTS 450" पूर्ण,
	अणु 0x0dc6, "GeForce GTS 450" पूर्ण,
	अणु 0x0dcd, "GeForce GT 555M" पूर्ण,
	अणु 0x0dce, "GeForce GT 555M" पूर्ण,
	अणु 0x0dd1, "GeForce GTX 460M" पूर्ण,
	अणु 0x0dd2, "GeForce GT 445M" पूर्ण,
	अणु 0x0dd3, "GeForce GT 435M" पूर्ण,
	अणु 0x0dd6, "GeForce GT 550M" पूर्ण,
	अणु 0x0dd8, "Quadro 2000", nvkm_device_pci_10de_0dd8 पूर्ण,
	अणु 0x0dda, "Quadro 2000M" पूर्ण,
	अणु 0x0de0, "GeForce GT 440" पूर्ण,
	अणु 0x0de1, "GeForce GT 430" पूर्ण,
	अणु 0x0de2, "GeForce GT 420" पूर्ण,
	अणु 0x0de3, "GeForce GT 635M" पूर्ण,
	अणु 0x0de4, "GeForce GT 520" पूर्ण,
	अणु 0x0de5, "GeForce GT 530" पूर्ण,
	अणु 0x0de7, "GeForce GT 610" पूर्ण,
	अणु 0x0de8, "GeForce GT 620M" पूर्ण,
	अणु 0x0de9, "GeForce GT 630M", nvkm_device_pci_10de_0de9 पूर्ण,
	अणु 0x0dea, "GeForce 610M", nvkm_device_pci_10de_0dea पूर्ण,
	अणु 0x0deb, "GeForce GT 555M" पूर्ण,
	अणु 0x0dec, "GeForce GT 525M" पूर्ण,
	अणु 0x0ded, "GeForce GT 520M" पूर्ण,
	अणु 0x0dee, "GeForce GT 415M" पूर्ण,
	अणु 0x0def, "NVS 5400M" पूर्ण,
	अणु 0x0df0, "GeForce GT 425M" पूर्ण,
	अणु 0x0df1, "GeForce GT 420M" पूर्ण,
	अणु 0x0df2, "GeForce GT 435M" पूर्ण,
	अणु 0x0df3, "GeForce GT 420M" पूर्ण,
	अणु 0x0df4, "GeForce GT 540M", nvkm_device_pci_10de_0df4 पूर्ण,
	अणु 0x0df5, "GeForce GT 525M" पूर्ण,
	अणु 0x0df6, "GeForce GT 550M" पूर्ण,
	अणु 0x0df7, "GeForce GT 520M" पूर्ण,
	अणु 0x0df8, "Quadro 600" पूर्ण,
	अणु 0x0df9, "Quadro 500M" पूर्ण,
	अणु 0x0dfa, "Quadro 1000M" पूर्ण,
	अणु 0x0dfc, "NVS 5200M" पूर्ण,
	अणु 0x0e22, "GeForce GTX 460" पूर्ण,
	अणु 0x0e23, "GeForce GTX 460 SE" पूर्ण,
	अणु 0x0e24, "GeForce GTX 460" पूर्ण,
	अणु 0x0e30, "GeForce GTX 470M" पूर्ण,
	अणु 0x0e31, "GeForce GTX 485M" पूर्ण,
	अणु 0x0e3a, "Quadro 3000M" पूर्ण,
	अणु 0x0e3b, "Quadro 4000M" पूर्ण,
	अणु 0x0f00, "GeForce GT 630" पूर्ण,
	अणु 0x0f01, "GeForce GT 620" पूर्ण,
	अणु 0x0f02, "GeForce GT 730" पूर्ण,
	अणु 0x0fc0, "GeForce GT 640" पूर्ण,
	अणु 0x0fc1, "GeForce GT 640" पूर्ण,
	अणु 0x0fc2, "GeForce GT 630" पूर्ण,
	अणु 0x0fc6, "GeForce GTX 650" पूर्ण,
	अणु 0x0fc8, "GeForce GT 740" पूर्ण,
	अणु 0x0fc9, "GeForce GT 730" पूर्ण,
	अणु 0x0fcd, "GeForce GT 755M" पूर्ण,
	अणु 0x0fce, "GeForce GT 640M LE" पूर्ण,
	अणु 0x0fd1, "GeForce GT 650M" पूर्ण,
	अणु 0x0fd2, "GeForce GT 640M", nvkm_device_pci_10de_0fd2 पूर्ण,
	अणु 0x0fd3, "GeForce GT 640M LE" पूर्ण,
	अणु 0x0fd4, "GeForce GTX 660M" पूर्ण,
	अणु 0x0fd5, "GeForce GT 650M" पूर्ण,
	अणु 0x0fd8, "GeForce GT 640M" पूर्ण,
	अणु 0x0fd9, "GeForce GT 645M" पूर्ण,
	अणु 0x0fdf, "GeForce GT 740M" पूर्ण,
	अणु 0x0fe0, "GeForce GTX 660M" पूर्ण,
	अणु 0x0fe1, "GeForce GT 730M" पूर्ण,
	अणु 0x0fe2, "GeForce GT 745M" पूर्ण,
	अणु 0x0fe3, "GeForce GT 745M", nvkm_device_pci_10de_0fe3 पूर्ण,
	अणु 0x0fe4, "GeForce GT 750M" पूर्ण,
	अणु 0x0fe9, "GeForce GT 750M" पूर्ण,
	अणु 0x0fea, "GeForce GT 755M" पूर्ण,
	अणु 0x0fec, "GeForce 710A" पूर्ण,
	अणु 0x0fef, "GRID K340" पूर्ण,
	अणु 0x0ff2, "GRID K1" पूर्ण,
	अणु 0x0ff3, "Quadro K420" पूर्ण,
	अणु 0x0ff6, "Quadro K1100M" पूर्ण,
	अणु 0x0ff8, "Quadro K500M" पूर्ण,
	अणु 0x0ff9, "Quadro K2000D" पूर्ण,
	अणु 0x0ffa, "Quadro K600" पूर्ण,
	अणु 0x0ffb, "Quadro K2000M" पूर्ण,
	अणु 0x0ffc, "Quadro K1000M" पूर्ण,
	अणु 0x0ffd, "NVS 510" पूर्ण,
	अणु 0x0ffe, "Quadro K2000" पूर्ण,
	अणु 0x0fff, "Quadro 410" पूर्ण,
	अणु 0x1001, "GeForce GTX TITAN Z" पूर्ण,
	अणु 0x1004, "GeForce GTX 780" पूर्ण,
	अणु 0x1005, "GeForce GTX TITAN" पूर्ण,
	अणु 0x1007, "GeForce GTX 780" पूर्ण,
	अणु 0x1008, "GeForce GTX 780 Ti" पूर्ण,
	अणु 0x100a, "GeForce GTX 780 Ti" पूर्ण,
	अणु 0x100c, "GeForce GTX TITAN Black" पूर्ण,
	अणु 0x1021, "Tesla K20Xm" पूर्ण,
	अणु 0x1022, "Tesla K20c" पूर्ण,
	अणु 0x1023, "Tesla K40m" पूर्ण,
	अणु 0x1024, "Tesla K40c" पूर्ण,
	अणु 0x1026, "Tesla K20s" पूर्ण,
	अणु 0x1027, "Tesla K40st" पूर्ण,
	अणु 0x1028, "Tesla K20m" पूर्ण,
	अणु 0x1029, "Tesla K40s" पूर्ण,
	अणु 0x102a, "Tesla K40t" पूर्ण,
	अणु 0x102d, "Tesla K80" पूर्ण,
	अणु 0x103a, "Quadro K6000" पूर्ण,
	अणु 0x103c, "Quadro K5200" पूर्ण,
	अणु 0x1040, "GeForce GT 520" पूर्ण,
	अणु 0x1042, "GeForce 510" पूर्ण,
	अणु 0x1048, "GeForce 605" पूर्ण,
	अणु 0x1049, "GeForce GT 620" पूर्ण,
	अणु 0x104a, "GeForce GT 610" पूर्ण,
	अणु 0x104b, "GeForce GT 625 (OEM)", nvkm_device_pci_10de_104b पूर्ण,
	अणु 0x104c, "GeForce GT 705" पूर्ण,
	अणु 0x1050, "GeForce GT 520M" पूर्ण,
	अणु 0x1051, "GeForce GT 520MX" पूर्ण,
	अणु 0x1052, "GeForce GT 520M" पूर्ण,
	अणु 0x1054, "GeForce 410M" पूर्ण,
	अणु 0x1055, "GeForce 410M" पूर्ण,
	अणु 0x1056, "NVS 4200M" पूर्ण,
	अणु 0x1057, "NVS 4200M" पूर्ण,
	अणु 0x1058, "GeForce 610M", nvkm_device_pci_10de_1058 पूर्ण,
	अणु 0x1059, "GeForce 610M" पूर्ण,
	अणु 0x105a, "GeForce 610M" पूर्ण,
	अणु 0x105b, "GeForce 705M", nvkm_device_pci_10de_105b पूर्ण,
	अणु 0x107c, "NVS 315" पूर्ण,
	अणु 0x107d, "NVS 310" पूर्ण,
	अणु 0x1080, "GeForce GTX 580" पूर्ण,
	अणु 0x1081, "GeForce GTX 570" पूर्ण,
	अणु 0x1082, "GeForce GTX 560 Ti" पूर्ण,
	अणु 0x1084, "GeForce GTX 560" पूर्ण,
	अणु 0x1086, "GeForce GTX 570" पूर्ण,
	अणु 0x1087, "GeForce GTX 560 Ti" पूर्ण,
	अणु 0x1088, "GeForce GTX 590" पूर्ण,
	अणु 0x1089, "GeForce GTX 580" पूर्ण,
	अणु 0x108b, "GeForce GTX 580" पूर्ण,
	अणु 0x1091, "Tesla M2090", nvkm_device_pci_10de_1091 पूर्ण,
	अणु 0x1094, "Tesla M2075" पूर्ण,
	अणु 0x1096, "Tesla C2075", nvkm_device_pci_10de_1096 पूर्ण,
	अणु 0x109a, "Quadro 5010M" पूर्ण,
	अणु 0x109b, "Quadro 7000" पूर्ण,
	अणु 0x10c0, "GeForce 9300 GS" पूर्ण,
	अणु 0x10c3, "GeForce 8400GS" पूर्ण,
	अणु 0x10c5, "GeForce 405" पूर्ण,
	अणु 0x10d8, "NVS 300" पूर्ण,
	अणु 0x1140, शून्य, nvkm_device_pci_10de_1140 पूर्ण,
	अणु 0x1180, "GeForce GTX 680" पूर्ण,
	अणु 0x1183, "GeForce GTX 660 Ti" पूर्ण,
	अणु 0x1184, "GeForce GTX 770" पूर्ण,
	अणु 0x1185, "GeForce GTX 660", nvkm_device_pci_10de_1185 पूर्ण,
	अणु 0x1187, "GeForce GTX 760" पूर्ण,
	अणु 0x1188, "GeForce GTX 690" पूर्ण,
	अणु 0x1189, "GeForce GTX 670", nvkm_device_pci_10de_1189 पूर्ण,
	अणु 0x118a, "GRID K520" पूर्ण,
	अणु 0x118e, "GeForce GTX 760 (192-bit)" पूर्ण,
	अणु 0x118f, "Tesla K10" पूर्ण,
	अणु 0x1193, "GeForce GTX 760 Ti OEM" पूर्ण,
	अणु 0x1194, "Tesla K8" पूर्ण,
	अणु 0x1195, "GeForce GTX 660" पूर्ण,
	अणु 0x1198, "GeForce GTX 880M" पूर्ण,
	अणु 0x1199, "GeForce GTX 870M", nvkm_device_pci_10de_1199 पूर्ण,
	अणु 0x119a, "GeForce GTX 860M" पूर्ण,
	अणु 0x119d, "GeForce GTX 775M" पूर्ण,
	अणु 0x119e, "GeForce GTX 780M" पूर्ण,
	अणु 0x119f, "GeForce GTX 780M" पूर्ण,
	अणु 0x11a0, "GeForce GTX 680M" पूर्ण,
	अणु 0x11a1, "GeForce GTX 670MX" पूर्ण,
	अणु 0x11a2, "GeForce GTX 675MX" पूर्ण,
	अणु 0x11a3, "GeForce GTX 680MX" पूर्ण,
	अणु 0x11a7, "GeForce GTX 675MX" पूर्ण,
	अणु 0x11b4, "Quadro K4200" पूर्ण,
	अणु 0x11b6, "Quadro K3100M" पूर्ण,
	अणु 0x11b7, "Quadro K4100M" पूर्ण,
	अणु 0x11b8, "Quadro K5100M" पूर्ण,
	अणु 0x11ba, "Quadro K5000" पूर्ण,
	अणु 0x11bc, "Quadro K5000M" पूर्ण,
	अणु 0x11bd, "Quadro K4000M" पूर्ण,
	अणु 0x11be, "Quadro K3000M" पूर्ण,
	अणु 0x11bf, "GRID K2" पूर्ण,
	अणु 0x11c0, "GeForce GTX 660" पूर्ण,
	अणु 0x11c2, "GeForce GTX 650 Ti BOOST" पूर्ण,
	अणु 0x11c3, "GeForce GTX 650 Ti" पूर्ण,
	अणु 0x11c4, "GeForce GTX 645" पूर्ण,
	अणु 0x11c5, "GeForce GT 740" पूर्ण,
	अणु 0x11c6, "GeForce GTX 650 Ti" पूर्ण,
	अणु 0x11c8, "GeForce GTX 650" पूर्ण,
	अणु 0x11cb, "GeForce GT 740" पूर्ण,
	अणु 0x11e0, "GeForce GTX 770M" पूर्ण,
	अणु 0x11e1, "GeForce GTX 765M" पूर्ण,
	अणु 0x11e2, "GeForce GTX 765M" पूर्ण,
	अणु 0x11e3, "GeForce GTX 760M", nvkm_device_pci_10de_11e3 पूर्ण,
	अणु 0x11fa, "Quadro K4000" पूर्ण,
	अणु 0x11fc, "Quadro K2100M" पूर्ण,
	अणु 0x1200, "GeForce GTX 560 Ti" पूर्ण,
	अणु 0x1201, "GeForce GTX 560" पूर्ण,
	अणु 0x1203, "GeForce GTX 460 SE v2" पूर्ण,
	अणु 0x1205, "GeForce GTX 460 v2" पूर्ण,
	अणु 0x1206, "GeForce GTX 555" पूर्ण,
	अणु 0x1207, "GeForce GT 645" पूर्ण,
	अणु 0x1208, "GeForce GTX 560 SE" पूर्ण,
	अणु 0x1210, "GeForce GTX 570M" पूर्ण,
	अणु 0x1211, "GeForce GTX 580M" पूर्ण,
	अणु 0x1212, "GeForce GTX 675M" पूर्ण,
	अणु 0x1213, "GeForce GTX 670M" पूर्ण,
	अणु 0x1241, "GeForce GT 545" पूर्ण,
	अणु 0x1243, "GeForce GT 545" पूर्ण,
	अणु 0x1244, "GeForce GTX 550 Ti" पूर्ण,
	अणु 0x1245, "GeForce GTS 450" पूर्ण,
	अणु 0x1246, "GeForce GT 550M" पूर्ण,
	अणु 0x1247, "GeForce GT 555M", nvkm_device_pci_10de_1247 पूर्ण,
	अणु 0x1248, "GeForce GT 555M" पूर्ण,
	अणु 0x1249, "GeForce GTS 450" पूर्ण,
	अणु 0x124b, "GeForce GT 640" पूर्ण,
	अणु 0x124d, "GeForce GT 555M", nvkm_device_pci_10de_124d पूर्ण,
	अणु 0x1251, "GeForce GTX 560M" पूर्ण,
	अणु 0x1280, "GeForce GT 635" पूर्ण,
	अणु 0x1281, "GeForce GT 710" पूर्ण,
	अणु 0x1282, "GeForce GT 640" पूर्ण,
	अणु 0x1284, "GeForce GT 630" पूर्ण,
	अणु 0x1286, "GeForce GT 720" पूर्ण,
	अणु 0x1287, "GeForce GT 730" पूर्ण,
	अणु 0x1288, "GeForce GT 720" पूर्ण,
	अणु 0x1289, "GeForce GT 710" पूर्ण,
	अणु 0x1290, "GeForce GT 730M", nvkm_device_pci_10de_1290 पूर्ण,
	अणु 0x1291, "GeForce GT 735M" पूर्ण,
	अणु 0x1292, "GeForce GT 740M", nvkm_device_pci_10de_1292 पूर्ण,
	अणु 0x1293, "GeForce GT 730M" पूर्ण,
	अणु 0x1295, "GeForce 710M", nvkm_device_pci_10de_1295 पूर्ण,
	अणु 0x1296, "GeForce 825M" पूर्ण,
	अणु 0x1298, "GeForce GT 720M" पूर्ण,
	अणु 0x1299, "GeForce 920M", nvkm_device_pci_10de_1299 पूर्ण,
	अणु 0x129a, "GeForce 910M" पूर्ण,
	अणु 0x12b9, "Quadro K610M" पूर्ण,
	अणु 0x12ba, "Quadro K510M" पूर्ण,
	अणु 0x1340, "GeForce 830M", nvkm_device_pci_10de_1340 पूर्ण,
	अणु 0x1341, "GeForce 840M", nvkm_device_pci_10de_1341 पूर्ण,
	अणु 0x1344, "GeForce 845M" पूर्ण,
	अणु 0x1346, "GeForce 930M", nvkm_device_pci_10de_1346 पूर्ण,
	अणु 0x1347, "GeForce 940M", nvkm_device_pci_10de_1347 पूर्ण,
	अणु 0x137a, शून्य, nvkm_device_pci_10de_137a पूर्ण,
	अणु 0x137d, शून्य, nvkm_device_pci_10de_137d पूर्ण,
	अणु 0x1380, "GeForce GTX 750 Ti" पूर्ण,
	अणु 0x1381, "GeForce GTX 750" पूर्ण,
	अणु 0x1382, "GeForce GTX 745" पूर्ण,
	अणु 0x1390, "GeForce 845M" पूर्ण,
	अणु 0x1391, "GeForce GTX 850M", nvkm_device_pci_10de_1391 पूर्ण,
	अणु 0x1392, "GeForce GTX 860M", nvkm_device_pci_10de_1392 पूर्ण,
	अणु 0x1393, "GeForce 840M" पूर्ण,
	अणु 0x1398, "GeForce 845M" पूर्ण,
	अणु 0x139a, "GeForce GTX 950M", nvkm_device_pci_10de_139a पूर्ण,
	अणु 0x139b, "GeForce GTX 960M", nvkm_device_pci_10de_139b पूर्ण,
	अणु 0x139c, "GeForce 940M" पूर्ण,
	अणु 0x13b3, "Quadro K2200M" पूर्ण,
	अणु 0x13ba, "Quadro K2200" पूर्ण,
	अणु 0x13bb, "Quadro K620" पूर्ण,
	अणु 0x13bc, "Quadro K1200" पूर्ण,
	अणु 0x13c0, "GeForce GTX 980" पूर्ण,
	अणु 0x13c2, "GeForce GTX 970" पूर्ण,
	अणु 0x13d7, "GeForce GTX 980M" पूर्ण,
	अणु 0x13d8, "GeForce GTX 970M" पूर्ण,
	अणु 0x13d9, "GeForce GTX 965M" पूर्ण,
	अणु 0x1401, "GeForce GTX 960" पूर्ण,
	अणु 0x1617, "GeForce GTX 980M" पूर्ण,
	अणु 0x1618, "GeForce GTX 970M" पूर्ण,
	अणु 0x1619, "GeForce GTX 965M" पूर्ण,
	अणु 0x17c2, "GeForce GTX TITAN X" पूर्ण,
	अणु 0x17c8, "GeForce GTX 980 Ti" पूर्ण,
	अणु 0x17f0, "Quadro M6000" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा nvkm_device_pci *
nvkm_device_pci(काष्ठा nvkm_device *device)
अणु
	वापस container_of(device, काष्ठा nvkm_device_pci, device);
पूर्ण

अटल resource_माप_प्रकार
nvkm_device_pci_resource_addr(काष्ठा nvkm_device *device, अचिन्हित bar)
अणु
	काष्ठा nvkm_device_pci *pdev = nvkm_device_pci(device);
	वापस pci_resource_start(pdev->pdev, bar);
पूर्ण

अटल resource_माप_प्रकार
nvkm_device_pci_resource_size(काष्ठा nvkm_device *device, अचिन्हित bar)
अणु
	काष्ठा nvkm_device_pci *pdev = nvkm_device_pci(device);
	वापस pci_resource_len(pdev->pdev, bar);
पूर्ण

अटल व्योम
nvkm_device_pci_fini(काष्ठा nvkm_device *device, bool suspend)
अणु
	काष्ठा nvkm_device_pci *pdev = nvkm_device_pci(device);
	अगर (suspend) अणु
		pci_disable_device(pdev->pdev);
		pdev->suspend = true;
	पूर्ण
पूर्ण

अटल पूर्णांक
nvkm_device_pci_preinit(काष्ठा nvkm_device *device)
अणु
	काष्ठा nvkm_device_pci *pdev = nvkm_device_pci(device);
	अगर (pdev->suspend) अणु
		पूर्णांक ret = pci_enable_device(pdev->pdev);
		अगर (ret)
			वापस ret;
		pci_set_master(pdev->pdev);
		pdev->suspend = false;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_device_pci_dtor(काष्ठा nvkm_device *device)
अणु
	काष्ठा nvkm_device_pci *pdev = nvkm_device_pci(device);
	pci_disable_device(pdev->pdev);
	वापस pdev;
पूर्ण

अटल स्थिर काष्ठा nvkm_device_func
nvkm_device_pci_func = अणु
	.pci = nvkm_device_pci,
	.dtor = nvkm_device_pci_dtor,
	.preinit = nvkm_device_pci_preinit,
	.fini = nvkm_device_pci_fini,
	.resource_addr = nvkm_device_pci_resource_addr,
	.resource_size = nvkm_device_pci_resource_size,
	.cpu_coherent = !IS_ENABLED(CONFIG_ARM),
पूर्ण;

पूर्णांक
nvkm_device_pci_new(काष्ठा pci_dev *pci_dev, स्थिर अक्षर *cfg, स्थिर अक्षर *dbg,
		    bool detect, bool mmio, u64 subdev_mask,
		    काष्ठा nvkm_device **pdevice)
अणु
	स्थिर काष्ठा nvkm_device_quirk *quirk = शून्य;
	स्थिर काष्ठा nvkm_device_pci_device *pcid;
	स्थिर काष्ठा nvkm_device_pci_venकरोr *pciv;
	स्थिर अक्षर *name = शून्य;
	काष्ठा nvkm_device_pci *pdev;
	पूर्णांक ret, bits;

	ret = pci_enable_device(pci_dev);
	अगर (ret)
		वापस ret;

	चयन (pci_dev->venकरोr) अणु
	हाल 0x10de: pcid = nvkm_device_pci_10de; अवरोध;
	शेष:
		pcid = शून्य;
		अवरोध;
	पूर्ण

	जबतक (pcid && pcid->device) अणु
		अगर (pciv = pcid->venकरोr, pcid->device == pci_dev->device) अणु
			जबतक (pciv && pciv->venकरोr) अणु
				अगर (pciv->venकरोr == pci_dev->subप्रणाली_venकरोr &&
				    pciv->device == pci_dev->subप्रणाली_device) अणु
					quirk = &pciv->quirk;
					name  =  pciv->name;
					अवरोध;
				पूर्ण
				pciv++;
			पूर्ण
			अगर (!name)
				name = pcid->name;
			अवरोध;
		पूर्ण
		pcid++;
	पूर्ण

	अगर (!(pdev = kzalloc(माप(*pdev), GFP_KERNEL))) अणु
		pci_disable_device(pci_dev);
		वापस -ENOMEM;
	पूर्ण
	*pdevice = &pdev->device;
	pdev->pdev = pci_dev;

	ret = nvkm_device_ctor(&nvkm_device_pci_func, quirk, &pci_dev->dev,
			       pci_is_pcie(pci_dev) ? NVKM_DEVICE_PCIE :
			       pci_find_capability(pci_dev, PCI_CAP_ID_AGP) ?
			       NVKM_DEVICE_AGP : NVKM_DEVICE_PCI,
			       (u64)pci_करोमुख्य_nr(pci_dev->bus) << 32 |
				    pci_dev->bus->number << 16 |
				    PCI_SLOT(pci_dev->devfn) << 8 |
				    PCI_FUNC(pci_dev->devfn), name,
			       cfg, dbg, detect, mmio, subdev_mask,
			       &pdev->device);

	अगर (ret)
		वापस ret;

	/* Set DMA mask based on capabilities reported by the MMU subdev. */
	अगर (pdev->device.mmu && !pdev->device.pci->agp.bridge)
		bits = pdev->device.mmu->dma_bits;
	अन्यथा
		bits = 32;

	ret = dma_set_mask_and_coherent(&pci_dev->dev, DMA_BIT_MASK(bits));
	अगर (ret && bits != 32) अणु
		dma_set_mask_and_coherent(&pci_dev->dev, DMA_BIT_MASK(32));
		pdev->device.mmu->dma_bits = 32;
	पूर्ण

	वापस 0;
पूर्ण
