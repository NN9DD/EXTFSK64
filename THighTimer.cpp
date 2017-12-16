//Copyright+LGPL

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Copyright 2000-2017 Makoto Mori, Nobuyuki Oba
//-----------------------------------------------------------------------------------------------------------------------------------------------
// This file is part of EXTFSK64.

// EXTFSK64 is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

// EXTFSK64 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public License along with EXTFSK64.  If not, see
// <http://www.gnu.org/licenses/>.
//---------------------------------------------------------------------------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "THighTimer.h"
#include "Main.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

// ���ӁF�قȂ�X���b�h�����L���� VCL �̃��\�b�h/�֐�/�v���p�e�B��
//       �ʂ̃X���b�h�̒����爵���ꍇ�C�r�������̖�肪�������܂��B
//
//       ���C���X���b�h�̏��L����I�u�W�F�N�g�ɑ΂��Ă� Synchronize
//       ���\�b�h���g�������ł��܂��B���̃I�u�W�F�N�g���Q�Ƃ��邽��
//       �̃��\�b�h���X���b�h�N���X�ɒǉ����CSynchronize ���\�b�h��
//       �����Ƃ��ēn���܂��B
//
//       ���Ƃ��� UpdateCaption ���ȉ��̂悤�ɒ�`���A
//
//          void __fastcall Unit1::UpdateCaption()
//          {
//            Form1->Caption = "�X���b�h���珑�������܂���";
//          }
//
//       Execute ���\�b�h�̒��� Synchronize ���\�b�h�ɓn�����ƂŃ��C
//       ���X���b�h�����L���� Form1 �� Caption �v���p�e�B�����S�ɕ�
//       �X�ł��܂��B
//
//          Synchronize(UpdateCaption);
//
//---------------------------------------------------------------------------
extern TExtFSK *pMain;

__fastcall THighTimer::THighTimer(bool CreateSuspended)
  : TThread(CreateSuspended)
{
  FreeOnTerminate = true;
}
//---------------------------------------------------------------------------
void __fastcall THighTimer::Execute()
{
  _LARGE_INTEGER tFreq;
  _LARGE_INTEGER tCounter;
  _LARGE_INTEGER tCounterLast;
  QueryPerformanceFrequency( &tFreq );
  double tInterval;
  QueryPerformanceCounter( &tCounterLast );
  for(;;){
    QueryPerformanceCounter( &tCounter );
    tInterval = (double)tFreq.QuadPart * pMain->dblRate;
    if( (double)( tCounter.QuadPart - tCounterLast.QuadPart ) > tInterval ){
      pMain->TimeProc2();
      tCounterLast.QuadPart = tCounter.QuadPart;
    }
    if( Terminated )
      break;
    //Application->ProcessMessages();
  }
}
//---------------------------------------------------------------------------
