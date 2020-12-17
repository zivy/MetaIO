/*============================================================================
  MetaIO
  Copyright 2000-2010 Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "metaGaussian.h"

#ifdef _MSC_VER
#  pragma warning(disable : 4702)
#endif

#if (METAIO_USE_NAMESPACE)
namespace METAIO_NAMESPACE
{
#endif

//
// MedImage Constructors
//
MetaGaussian::MetaGaussian()
  : MetaObject()
{
  if (META_DEBUG)
  {
    std::cout << "MetaGaussian()" << std::endl;
  }
  Clear();
}

//
MetaGaussian::MetaGaussian(const char * _headerName)
  : MetaObject()
{
  if (META_DEBUG)
  {
    std::cout << "MetaGaussian()" << std::endl;
  }
  Clear();
  Read(_headerName);
}

//
MetaGaussian::MetaGaussian(const MetaGaussian * _gaussian)
  : MetaObject()
{
  if (META_DEBUG)
  {
    std::cout << "MetaGaussian()" << std::endl;
  }
  Clear();
  CopyInfo(_gaussian);
}

MetaGaussian::MetaGaussian(unsigned int dim)
  : MetaObject(dim)
{
  if (META_DEBUG)
  {
    std::cout << "MetaGaussian()" << std::endl;
  }
  Clear();
}

//
MetaGaussian::~MetaGaussian()
{
  M_Destroy();
}

//
void
MetaGaussian::PrintInfo() const
{
  MetaObject::PrintInfo();
  std::cout << "\n"
            << "Maximum = " << m_Maximum << "\n"
            << "Radius = " << m_Radius << "Sigma = " << m_Sigma << std::endl;
}

void
MetaGaussian::CopyInfo(const MetaObject * _object)
{
  MetaObject::CopyInfo(_object);
}

/** Clear gaussian information */
void
MetaGaussian::Clear()
{
  if (META_DEBUG)
  {
    std::cout << "MetaGaussian: Clear" << std::endl;
  }

  MetaObject::Clear();

  strcpy(m_ObjectTypeName, "Gaussian");

  m_Maximum = 1;
  m_Radius = 1;
  m_Sigma = 1;
}

/** Destroy gaussian information */
void
MetaGaussian::M_Destroy()
{
  MetaObject::M_Destroy();
}

/** Set Read fields */
void
MetaGaussian::M_SetupReadFields()
{
  if (META_DEBUG)
  {
    std::cout << "MetaGaussian: M_SetupReadFields" << std::endl;
  }

  MetaObject::M_SetupReadFields();

  MET_FieldRecordType * mF;

  MET_GetFieldRecordNumber("NDims", &m_Fields);

  mF = new MET_FieldRecordType;
  MET_InitReadField(mF, "Maximum", MET_FLOAT, true);
  m_Fields.push_back(mF);

  mF = new MET_FieldRecordType;
  MET_InitReadField(mF, "Radius", MET_FLOAT, true);
  m_Fields.push_back(mF);

  mF = new MET_FieldRecordType;
  MET_InitReadField(mF, "Sigma", MET_FLOAT, true);
  m_Fields.push_back(mF);
}

void
MetaGaussian::M_SetupWriteFields()
{
  MetaObject::M_SetupWriteFields();

  MET_FieldRecordType * mF;

  mF = new MET_FieldRecordType;
  MET_InitWriteField(mF, "Maximum", MET_FLOAT, m_Maximum);
  m_Fields.push_back(mF);

  mF = new MET_FieldRecordType;
  MET_InitWriteField(mF, "Radius", MET_FLOAT, m_Radius);
  m_Fields.push_back(mF);

  mF = new MET_FieldRecordType;
  MET_InitWriteField(mF, "Sigma", MET_FLOAT, m_Sigma);
  m_Fields.push_back(mF);
}


bool
MetaGaussian::M_Read()
{
  if (META_DEBUG)
  {
    std::cout << "MetaGaussian: M_Read: Loading Header" << std::endl;
  }

  if (!MetaObject::M_Read())
  {
    std::cout << "MetaGaussian: M_Read: Error parsing file" << std::endl;
    return false;
  }

  if (META_DEBUG)
  {
    std::cout << "MetaGaussian: M_Read: Parsing Header" << std::endl;
  }

  MET_FieldRecordType * mF;

  mF = MET_GetFieldRecord("Maximum", &m_Fields);
  if (mF->defined)
  {
    m_Maximum = static_cast<float>(mF->value[0]);
  }

  mF = MET_GetFieldRecord("Radius", &m_Fields);
  if (mF->defined)
  {
    m_Radius = static_cast<float>(mF->value[0]);
  }

  mF = MET_GetFieldRecord("Sigma", &m_Fields);
  if (mF->defined)
  {
    m_Sigma = static_cast<float>(mF->value[0]);
  }

  return true;
}

#if (METAIO_USE_NAMESPACE)
};
#endif
