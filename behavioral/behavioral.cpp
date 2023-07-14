#include "behavioral.h"

bool responsibility_chain::Dispenser::dispense(int amount, int banknote_value) {
  if (amount <= 0) {
    return false;
  }
  int available_currency_count = std::min(m_currency_amount, amount / banknote_value);
  int remainder = amount - available_currency_count * banknote_value;
  m_currency_amount -= available_currency_count;
  if (remainder > 0) {
    if (m_next_handler) {
      bool ok = m_next_handler->dispense(remainder);
      if (!ok) {
        m_currency_amount += available_currency_count;
      }
      return ok;
    }
    else {
      m_currency_amount += available_currency_count;
      return false;
    }
  }
  else {
    assert(remainder == 0);
    return true;
  }
}

bool responsibility_chain::Dispenser50::dispense(int amount) {
  return Dispenser::dispense(amount, 50);
}

bool responsibility_chain::Dispenser10::dispense(int amount) {
  return Dispenser::dispense(amount, 10);
}

int responsibility_chain::ATM::dispense(int amount) const {
  if (m_50_disp->dispense(amount)) {
    std::cout << "Here is your cash: " << amount << '\n';
    return amount;
  }
  else {
    std::cout << "Can't dispense sum " << amount << '\n';
    return 0;
  }
}
