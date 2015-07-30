#include "genotype.hpp"

Genotype::Genotype() {
  mFitness = -1;
  setProbabilities(0,0);
}

Genotype::Genotype(std::vector<std::pair<double,double> > series) {
  mFitness = -1;
  setProbabilities(0,0);
  mInputData = series;
}

void Genotype::randomize_content(const int length) {
  mData.clear();

  mData.push_back('1');mData.push_back('1');mData.push_back('1');mData.push_back('1');

  for (int i=0; i<length-4; i++) {
    int r = rand() % 10;
    if (r < 4)
      mData.push_back('1');
    else
      mData.push_back('0');
  }
}

std::string Genotype::formula(bool only_valid=true) {
  std::string str;
  unsigned i=0;

  if (only_valid) {
    char lastOp = '+';
    bool num=true;

    while (i<mData.size()) {
      char c = cexpr(i);
      if (num && ((c >= '0' && c <= '9' && (c != '0' || lastOp != '/')) || c == 'x')) {
        num = false;
        str += c;
      }
      else if (!num && (c == '+' || c == '-' || c == '*' || c == '/' || c=='^')) {
        num = true;
        str += c;
        lastOp = c;
      }

      i += 4;
    }

    if (num) {
      str.pop_back();
    }
  }
  else {
    for (i=0; i<mData.size(); i+=4) {
      str += cexpr(i);
    }
  }

  return str;
}

double Genotype::fitness() {
  if (mFitness < 0) {
    double error=0.0;
    for (auto it = mInputData.begin(); it != mInputData.end(); ++it) {
        error += value_error(it->first, it->second);
    }

    if (error <= 0.00001)
      mFitness = (std::numeric_limits<double>::max())/2.0;
    else
      mFitness = 1.0/error;
  }

  return mFitness;
}

std::ostream& operator<<(std::ostream& os, Genotype& dt) {
  os << dt.formula();
  return os;
}

char& Genotype::operator[](int i) {
  char& element = mData[i];
  return element;
}

void Genotype::mutate() {
  mFitness = -1;

  std::uniform_real_distribution<double> unif(0.0, 1.0);
  std::default_random_engine re;

  for (unsigned i=0; i < mData.size(); i++) {
    if (unif(re) < mProbMutation) {
       mData[i] = '0' ? mData[i]=='1' : '1';
    }
  }
}

Genotype& Genotype::operator%(Genotype& rhs) {
  std::uniform_real_distribution<double> unif(0.0, 1.0);
  std::default_random_engine re;

  if (unif(re) < mProbFlip) {
    unsigned pos = rand() % mData.size();

    char temp;
    while (pos < mData.size()) {
      temp = mData[pos];
      mData[pos] = rhs[pos];
      rhs[pos] = temp;
      ++pos;
    }
  }

  this->mutate();
  rhs.mutate();

  return *this;
}

double Genotype::value_error(double& x, double& y) {
  double v=0.0;

  int prevOp=0;
  bool num=true;
  //std::cout << "\n\tformula=" << formula();

  for (unsigned pos=0; pos<mData.size(); pos+=4) {
    int i = expr(pos);

    if (num && (i < 10 || i == 15)) {
      num=false;
      double temp = x;
      if (i!=15) temp = (double)i;

      if (prevOp==0) v += temp;
      else if (prevOp==1) v -= temp;
      else if (prevOp==2) v *= temp;
      else if (prevOp==3 && temp > 0.0) v /= temp; // Avoid division by zero
      else if (prevOp==3) num=true;
      else if (prevOp==4) v = pow(v, temp);
    }
    else if (!num && i>=10 && i<=14) {
      num=true;
      prevOp = i-10;
    }
  }

  if (v > 999999.0 || v < -999999.0) {
    //std::cout << "\n\n\n\t\t\tHOLD YOUR HORSES\n\n\n";
    v = 999999.0;
  }

  v += penalty();

  return abs(y-v);
}

char Genotype::cexpr(int pos) {
  int value = this->expr(pos);

  switch (value) {
    case 0: return '0';
    case 1: return '1';
    case 2: return '2';
    case 3: return '3';
    case 4: return '4';
    case 5: return '5';
    case 6: return '6';
    case 7: return '7';
    case 8: return '8';
    case 9: return '9';
    case 10: return '+';
    case 11: return '-';
    case 12: return '*';
    case 13: return '/';
    case 14: return '^';
    case 15: return 'x';
    default: return '?';
  }
}

int Genotype::expr(int pos) {
  int value = 0;

  //if (pos % 4 == 0) {
    if (mData[pos]=='1') value += 8;
    if (mData[pos+1]=='1') value += 4;
    if (mData[pos+2]=='1') value += 2;
    if (mData[pos+3]=='1') value += 1;
  //}

  return value;
}

double Genotype::penalty() {
  bool has_x = false;

  std::string s = formula();

  if (s.find("x") != std::string::npos) {
    has_x = true;
  }

  double penalty = 0.0;
  if (!has_x) penalty += 5.0;
  return penalty;
}

void Genotype::setProbabilities(double probability_flip, double probability_mutation) {
  mProbFlip = probability_flip;
  mProbMutation = probability_mutation;
}
